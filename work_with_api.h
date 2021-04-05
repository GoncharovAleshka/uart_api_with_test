#ifndef __WORK_WITH_API_H__
#define __WORK_WITH_API_H__

#include "uart_api.h"

#define RECEIVE_BAUDRATE    9600
#define TRANSMIT_BAUDRATE   115200
#define TRASMIT_BLOCK_SIZE	128

UART_Descriptor* InitReceiveUART(const void* UART);
UART_Descriptor* InitTransmitUART(const void* UART);

void DataReceived(uint16_t data);
void DataTransmitted(uint16_t data);

int TestFunc();

#endif
