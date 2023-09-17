#ifndef GNSSTASKS_H    /* Guard against multiple inclusion */
#define GNSSTASKS_H

#include "configuration.h"
#include "definitions.h"

extern TaskHandle_t xTaskGetUART1byte;
extern TaskHandle_t xTaskProcessUBXmessage;
extern TaskHandle_t xTaskSendUBXmessage;
extern QueueHandle_t xUBXqueue;
extern SemaphoreHandle_t xUBXMutex;

void vTaskGetUART1byte_Init(void);
void vTaskProcessUBXmessage_Init(void);
void vTaskSendUBXmessage_Init(void);

void vTaskGetUART1byte(void);
void vTaskProcessUBXmessage(void);
void vTaskSendUBXmessage(void);

uint8_t UBXframeFound(uint8_t UBXByte, uint8_t *FrameType);
uint8_t UBXframeProcess(uint8_t UBXByte, uint8_t FrameType);
void PackPDU(uint8_t FrameType);



#endif
