/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>

#include "Robot.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_SENSORS 12
#define RECIVE_BUFFER_SIZE 2048
#define SEND_BUFFER_SIZE 2048
#define TRACKWIDTH 1
#define WHEELBASE 1
#define RADIUS (float)1.0
#define SAMPLING_TICKS 10
uint16_t ADC_Values[ADC_SENSORS];
#define LOGGING_FREQ 500
volatile uint8_t serialFinished=0;
char msg [100];
char g_reciveBuffer [RECIVE_BUFFER_SIZE];
char g_reciveBufferCopied [RECIVE_BUFFER_SIZE];
char g_sendBuffer[SEND_BUFFER_SIZE];
bool g_parseFlag(false);
FRESULT sdWriteRes; // FatFs Write to SD Card Result
char log_path[] = "/LOG.TXT"; //Path to file
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
FRESULT AppendToFile(char* path, size_t path_len, char* msg, size_t msg_len);
void SD_Log(RobotMsgOut& msg);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_UART7_Init();
  /* USER CODE BEGIN 2 */
  
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *) ADC_Values, ADC_SENSORS);
  ADCParams voltSensor(ADC_Values, 5,0.00685, 0), currentSensor(ADC_Values, 4, 1, 0),
            currentFL(ADC_Values, 1, 0.00806, -16.5), currentFR(ADC_Values, 0, 0.00806, -16.5),
            currentBL(ADC_Values, 3, 0.00806, -16.5), currentBR(ADC_Values, 2, 0.00806, -16.5);

  WheelParams wheelFL(RADIUS, htim2, htim1, Motor::channel::CHANNEL2, TIM_CHANNEL_2, PID::PIDParams(1, 0, 0, 50), currentFL, (uint8_t)25),
              wheelFR(RADIUS, htim5, htim1, Motor::channel::CHANNEL1, TIM_CHANNEL_1, PID::PIDParams(1, 0, 0, 50), currentFR, (uint8_t)25),
              wheelBL(RADIUS, htim4, htim1, Motor::channel::CHANNEL4, TIM_CHANNEL_4, PID::PIDParams(1, 0, 0, 50), currentFL, (uint8_t)25),
              wheelBR(RADIUS, htim3, htim1, Motor::channel::CHANNEL3, TIM_CHANNEL_3, PID::PIDParams(1, 0, 0, 50), currentFL, (uint8_t)25);

  RobotParams robotParams(wheelFL, wheelFR, wheelBL, wheelBR, voltSensor, currentSensor, 0, 0, WHEELBASE, TRACKWIDTH);
  //Motor fr(htim1, Motor::channel::CHANNEL1, TIM_CHANNEL_1);
  //AdcDevice batVolt(voltSensor);
  //AdcDevice curSensor(currentSensor);
  //Encoder enc1(htim5);

  //Start UART
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3,(uint8_t*)g_reciveBuffer, 256);




  Robot robot(robotParams);
  RobotMsgOut msg = robot.getInfo(0);  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint32_t pTicks = HAL_GetTick();
  uint32_t lTicks = HAL_GetTick();
  uint32_t logTicks = HAL_GetTick();
  while (1)
  { 
    uint32_t Ticks = HAL_GetTick();
    if(Ticks - lTicks > 5*SAMPLING_TICKS){
      HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
      lTicks += 5*SAMPLING_TICKS; 
    }
    if(g_parseFlag){
      int pos = 0;
      robot.parseAndDecide(g_reciveBufferCopied, pos, RECIVE_BUFFER_SIZE);
      g_parseFlag = false;
    }

     /*batVolt.update();
    curSensor.update();
    enc1.update();*/
    if(Ticks- pTicks >= SAMPLING_TICKS){
      robot.update();
      robot.run();
      int pos = 0;
      msg = robot.getInfo(Ticks);
      msg.convertToBytes(g_sendBuffer, SEND_BUFFER_SIZE, pos);
      HAL_UART_Transmit_DMA(&huart3,(uint8_t*)g_sendBuffer, 72);
      pTicks += SAMPLING_TICKS;
    }

    if(Ticks - logTicks >= LOGGING_FREQ){
    	SD_Log(msg);
    	logTicks+= LOGGING_FREQ;
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  g_parseFlag = true;
  for(int i = 0; i < Size; i++)
    g_reciveBufferCopied[i] = g_reciveBuffer[i];
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3,(uint8_t*)g_reciveBuffer, RECIVE_BUFFER_SIZE);
  HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}
FRESULT AppendToFile(char* path, size_t path_len, char* msg, size_t msg_len) {

  FATFS fs;
  FIL myFILE;
  UINT testByte;
  FRESULT stat;

  // Bounds check on strings
  if ( (path[path_len] != 0) || (msg[msg_len] != 0) ) {
    return FR_INVALID_NAME;
  }

  // Re-initialize SD
  if ( BSP_SD_Init() != MSD_OK ) {
    return FR_NOT_READY;
  }

  // Re-initialize FATFS
  if ( FATFS_UnLinkDriver(SDPath) != 0 ) {
    return FR_NOT_READY;
  }
  if ( FATFS_LinkDriver(&SD_Driver, SDPath) != 0 ) {
    return FR_NOT_READY;
  }

  // Mount filesystem
  stat = f_mount(&fs, SDPath, 0);
  if (stat != FR_OK) {
    f_mount(0, SDPath, 0);
    return stat;
  }

  // Open file for appending
  stat = f_open(&myFILE, path, FA_WRITE | FA_OPEN_APPEND);
  if (stat != FR_OK) {
    f_mount(0, SDPath, 0);
    return stat;
  }

  // Write message to end of file
  stat = f_write(&myFILE, msg, msg_len, &testByte);
  if (stat != FR_OK) {
    f_mount(0, SDPath, 0);
    return stat;
  }

  // Sync, close file, unmount
  stat = f_close(&myFILE);
  f_mount(0, SDPath, 0);
  return stat;

}

void SD_Log(RobotMsgOut& msg)
{
	char buff[sizeof(msg) + 2000];
	    	sprintf((char*) buff,"Time: %d\t""BatVolt: %.02f\t" "BatCurrent: %.04f\n\r"
	    			"FR: Ticks: %d\t" "Current:  %.04f A\t" "Vel: %.04f\t" "Output: %.04f\n\r"
	    			"FL: Ticks: %d\t" "Current:  %.04f A\t" "Vel: %.04f\t" "Output: %.04f\n\r"
	    			"BR: Ticks: %d\t" "Current:  %.04f A\t" "Vel: %.04f\t" "Output: %.04f\n\r"
	    			"BL: Ticks: %d\t" "Current:  %.04f A\t" "Vel: %.04f\t" "Output: %.04f\n\r\n\r",
	    	(int)msg._time, msg.batVolt,msg.current,
			(int)msg.wheelFR.ticks,msg.wheelFR.current,msg.wheelFR.vel,msg.wheelFR.output,
			(int)msg.wheelFL.ticks,msg.wheelFL.current,msg.wheelFL.vel,msg.wheelFL.output,
			(int)msg.wheelBR.ticks,msg.wheelBR.current,msg.wheelBR.vel,msg.wheelBR.output,
			(int)msg.wheelBL.ticks,msg.wheelBL.current,msg.wheelBL.vel,msg.wheelBL.output);
	    	sdWriteRes = AppendToFile(log_path, strlen(log_path),buff,strlen(buff));
	    	if(sdWriteRes == FR_OK )
	    	{
	    		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

	    	}
	    	else
	    		HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_RESET);
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
