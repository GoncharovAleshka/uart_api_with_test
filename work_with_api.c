#include "work_with_api.h"

UART_Descriptor ReceiveUSART;
UART_Descriptor TransmitUSART;

const void* USART1;
const void* USART2;

uint16_t dataBuffer[TRASMIT_BLOCK_SIZE * 2];

uint16_t recCntr = 0;
uint8_t blockReady = 0;

uint16_t transData[TRASMIT_BLOCK_SIZE];
uint16_t transCntr = 0;
volatile uint8_t transDone = 0;
volatile uint8_t testInProgress = 0;

UART_Descriptor* InitReceiveUSART(const void* UART)
{
    ReceiveUSART.Settings.BaudRate = RECEIVE_BAUDRATE;
    ReceiveUSART.Settings.Mode = UART_Mode_RX;
    ReceiveUSART.ReceiveCallBack = DataReceived;
    UART_Init(UART, &ReceiveUSART);

    if (ReceiveUSART.Status != UART_Status_NotInitialized)
        UART_Start(&ReceiveUSART);

    return &ReceiveUSART;
}

UART_Descriptor* InitTransmitUSART(const void* UART)
{
    UART_Init(UART, &TransmitUSART);
    UART_SetBaudRate(&TransmitUSART, TRANSMIT_BAUDRATE);
    UART_SetMode(&TransmitUSART, UART_Mode_TX);
    UART_SetTransmitCallBack(&TransmitUSART, DataTransmitted);

    if (TransmitUSART.Status != UART_Status_NotInitialized)
        UART_Start(&TransmitUSART);

    return &TransmitUSART;
}

void DataReceived(uint16_t data)
{
    printf("DataReceived %u\n", data);
    dataBuffer[recCntr++] = data;

    if (recCntr == TRASMIT_BLOCK_SIZE)
        blockReady = 1;
    else if (recCntr == TRASMIT_BLOCK_SIZE * 2)
    {
        blockReady = 2;
        recCntr = 0;
    }

    if (blockReady != 0)
    {
        UART_SendArray(&TransmitUSART, &dataBuffer[(blockReady - 1) * TRASMIT_BLOCK_SIZE], TRASMIT_BLOCK_SIZE);
        blockReady = 0;
    }
}

void DataTransmitted(uint16_t data)
{
    printf("DataTransmitted %u\n", data);
    if (testInProgress)
    {
        transData[transCntr++] = data;
        if (transCntr >= TRASMIT_BLOCK_SIZE)
        {
            transCntr = 0;
            transDone = 1;
        }
    }
}

int TestFunc()
{
    InitReceiveUSART(USART1);
    InitTransmitUSART(USART2);

    if (ReceiveUSART.Status != UART_Status_NotInitialized)
        UART_Stop(&ReceiveUSART);
    else
    {
        printf("Init Failded USART1!\n");
        return 1;
    }

    if (TransmitUSART.Status != UART_Status_NotInitialized)
        UART_Start(&TransmitUSART);
    else
    {
        printf("Init Failded USART2!\n");
        return 2;
    }

    printf("Test in progress!\n");
    testInProgress = 1;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < TRASMIT_BLOCK_SIZE; j++)
            DataReceived((j + 1) * (i + 1));

        while(!transDone);
        transDone = 0;
    }
    testInProgress = 0;

    return 0;
}
