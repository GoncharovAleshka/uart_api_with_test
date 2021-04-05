#ifndef __UART_API_H__
#define __UART_API_H__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

#define UART_BAUDRATE_Baud2400      2400
#define UART_BAUDRATE_Baud4800      4800
#define UART_BAUDRATE_Baud9600      9600
#define UART_BAUDRATE_Baud14400     14400
#define UART_BAUDRATE_Baud19200     19200
#define UART_BAUDRATE_Baud28800     28800
#define UART_BAUDRATE_Baud38400     38400
#define UART_BAUDRATE_Baud57600     57600
#define UART_BAUDRATE_Baud76800     76800
#define UART_BAUDRATE_Baud115200    115200

typedef enum
{
    UART_Parity_None,
    UART_Parity_Even,
    UART_Parity_Odd
}UART_Parity;

typedef enum
{
    UART_StopBits_1b,
    UART_StopBits_2b,
    UART_StopBits_1_5b
}UART_StopBits;

typedef enum
{
    UART_WORd_8b,
    UART_WORd_5b,
    UART_WORd_6b,
    UART_WORd_7b,
    UART_WORd_9b
}UART_WordLength;

typedef enum
{
    UART_Mode_RX_TX,
    UART_Mode_RX,
    UART_Mode_TX
}UART_Mode;

typedef enum
{
    UART_FlowControl_None,
    UART_FlowControl_RTS,
    UART_FlowControl_CTS,
    UART_FlowControl_RTS_CTS
}UART_FlowControl;

typedef enum
{
    UART_Status_NotInitialized,
    UART_Status_Stopped,
    UART_Status_Started
}UART_Status;

typedef struct
{
    uint32_t BaudRate;
    UART_WordLength WordLength;
    UART_StopBits StopBits;
    UART_Parity Parity;
    UART_Mode Mode;
    UART_FlowControl FlowControl;
} UART_Settings;

typedef struct
{
    const void* UARTx;
    UART_Status Status;
    void(*ReceiveCallBack)(uint16_t data);
    void(*TransmitCallBack)(uint16_t data);
    UART_Settings Settings;

    uint16_t* transArray;
    uint16_t transArraySize;
    volatile uint16_t transArrayCntr;
} UART_Descriptor;

void UART_Init(const void* UARTx, UART_Descriptor* Dscr);
void UART_Start(UART_Descriptor* Dscr);
void UART_Stop(UART_Descriptor* Dscr);
void UART_SetBaudRate(UART_Descriptor* Dscr, uint32_t BaudRate);
void UART_SetWordLength(UART_Descriptor* Dscr, UART_WordLength WordLength);
void UART_SetStopBits(UART_Descriptor* Dscr, UART_StopBits StopBits);
void UART_SetParity(UART_Descriptor* Dscr, UART_Parity Parity);
void UART_SetMode(UART_Descriptor* Dscr, UART_Mode Mode);
void UART_SetFlowControl(UART_Descriptor* Dscr, UART_FlowControl FlowControl);
void UART_SetReceiveCallBack(UART_Descriptor* Dscr, void(*CallBack)(uint16_t data));
void UART_SetTransmitCallBack(UART_Descriptor* Dscr, void(*CallBack)(uint16_t data));
void UART_SendArray(UART_Descriptor* Dscr, uint16_t* data, uint16_t size);

#endif
