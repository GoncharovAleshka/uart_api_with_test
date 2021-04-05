#include "uart_api.h"

void UART_Init(const void* UARTx, UART_Descriptor* Dscr)
{
    Dscr->UARTx = UARTx;
    Dscr->Status = UART_Status_Stopped;
}

void UART_Start(UART_Descriptor* Dscr)
{
    Dscr->Status = UART_Status_Started;
}

void UART_Stop(UART_Descriptor* Dscr)
{
    Dscr->Status = UART_Status_Stopped;
}

void UART_SetBaudRate(UART_Descriptor* Dscr, uint32_t BaudRate)
{
    Dscr->Settings.BaudRate = BaudRate;
}

void UART_SetWordLength(UART_Descriptor* Dscr, UART_WordLength WordLength)
{
    Dscr->Settings.WordLength = WordLength;
}

void UART_SetStopBits(UART_Descriptor* Dscr, UART_StopBits StopBits)
{
    Dscr->Settings.StopBits = StopBits;
}

void UART_SetParity(UART_Descriptor* Dscr, UART_Parity Parity)
{
    Dscr->Settings.Parity = Parity;
}

void UART_SetMode(UART_Descriptor* Dscr, UART_Mode Mode)
{
    Dscr->Settings.Mode = Mode;
}

void UART_SetFlowControl(UART_Descriptor* Dscr, UART_FlowControl FlowControl)
{
    Dscr->Settings.FlowControl = FlowControl;
}

void UART_SetReceiveCallBack(UART_Descriptor* Dscr, void(*CallBack)(uint16_t data))
{
    Dscr->ReceiveCallBack = CallBack;
}

void UART_SetTransmitCallBack(UART_Descriptor* Dscr, void(*CallBack)(uint16_t data))
{
    Dscr->TransmitCallBack = CallBack;
}

void UART_SendArray(UART_Descriptor* Dscr, uint16_t* data, uint16_t size)
{
    Dscr->transArray = data;
    Dscr->transArraySize = size;
    for (int i = 0; i < size; i++)
        Dscr->TransmitCallBack(data[i]);
}
