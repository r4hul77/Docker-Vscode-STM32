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

#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Robot.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_SENSORS 12
uint16_t ADC_Values[ADC_SENSORS];
volatile uint8_t serialFinished=0;
char msg [100];
char receive [6];
#define TRACKWIDTH 1
#define WHEELBASE 1
#define RADIUS (float)1.0
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
  ADCParams voltSensor(ADC_Values, 0, 1, 0), currentSensor(ADC_Values, 1, 1, 0),
            currentFL(ADC_Values, 2, 1, 0), currentFR(ADC_Values, 3, 1, 0),
            currentBL(ADC_Values, 4, 1, 0), currentBR(ADC_Values, 5, 1, 0);

  WheelParams wheelFL(RADIUS, htim2, htim1, Motor::channel::CHANNEL2, TIM_CHANNEL_2, PID::PIDParams(1, 0, 0, 50), currentFL, (uint8_t)25),
              wheelFR(RADIUS, htim5, htim1, Motor::channel::CHANNEL1, TIM_CHANNEL_1, PID::PIDParams(1, 0, 0, 50), currentFR, (uint8_t)25),
              wheelBL(RADIUS, htim4, htim1, Motor::channel::CHANNEL4, TIM_CHANNEL_4, PID::PIDParams(1, 0, 0, 50), currentFL, (uint8_t)25),
              wheelBR(RADIUS, htim3, htim1, Motor::channel::CHANNEL3, TIM_CHANNEL_3, PID::PIDParams(1, 0, 0, 50), currentFL, (uint8_t)25);

  //RobotParams robotParams(wheelFL, wheelFR, wheelBL, wheelBR, voltSensor, currentSensor, 0, 0, WHEELBASE, TRACKWIDTH);
  Motor fr(htim1, Motor::channel::CHANNEL1, TIM_CHANNEL_1);
  AdcDevice batVolt(voltSensor);
  AdcDevice curSensor(currentSensor);
  Encoder enc1(htim5);

  //Start UART
  sprintf(msg,"Start Transmission \r\n");
  HAL_UART_Receive_DMA(&huart3,(uint8_t*)receive, 6);
  HAL_UART_Transmit_DMA(&huart3,(uint8_t*)msg,strlen(msg));



  //Robot robot(robotParams);  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  float voltage = 0;
  float current = 0;
  uint16_t val = 0;
  float speed = 0.1;
  while (1)
  {
    speed += 0.005;
    if(speed >= 1)
      speed = 0.005;
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    fr.run(speed);
    /* USER CODE END WHILE */
    batVolt.update();
    curSensor.update();
    enc1.update();
    voltage = batVolt.sample();
    current = curSensor.sample();
    val = enc1.sample();

    if ((serialFinished == 1)) 
    {
      sprintf(msg, "Voltage = %f \n Current = %f \n Encoder Ticks : %d \n ", voltage, current, val);
      HAL_UART_Transmit_DMA(&huart3, (uint8_t* )msg, strlen(msg));
      serialFinished = 0;
    }

    
    /* USER CODE BEGIN 3 */
    HAL_Delay(500);
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

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  //HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_14);
  serialFinished = 1;
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_Receive_DMA(&huart3,(uint8_t*)receive,6);
  serialFinished =1;
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
