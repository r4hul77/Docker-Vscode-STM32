#ifndef _MICROROS_CLIENT_FREERTOS_SERIAL_TRANSPORT_H_
#define _MICROROS_CLIENT_FREERTOS_SERIAL_TRANSPORT_H_

#ifdef __cplusplus
extern "C"
{
#endif

bool dma_transport_open(struct uxrCustomTransport * transport);
bool dma_transport_close(struct uxrCustomTransport * transport);
size_t dma_transport_write(struct uxrCustomTransport* transport, const uint8_t * buf, size_t len, uint8_t * err);
size_t dma_transport_read(struct uxrCustomTransport* transport, uint8_t* buf, size_t len, int timeout, uint8_t* err);

#ifdef __cplusplus
}
#endif

#endif //_MICROROS_CLIENT_FREERTOS_SERIAL_TRANSPORT_H_