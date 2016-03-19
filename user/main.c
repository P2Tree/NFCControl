#include <stm32f0xx.h>
#include <stm32f0xx_conf.h>
#include <stdio.h>
#include "cmd.h"
#include "delay.h"

uint16_t cmd_ledon[10];
uint16_t cmd_ledoff[10];
uint16_t cmdlen_ledon;
uint16_t cmdlen_ledoff;
uint16_t cmd_buzzeron[9];
uint16_t cmd_buzzeroff[9];
uint16_t cmdlen_buzzeron;
uint16_t cmdlen_buzzeroff;

void uart_init(void);
void send_cmd(uint16_t *, uint16_t);
uint8_t rece_cmd(uint16_t *, uint8_t);
void rightLight(void);
void wrongLight(void);
void cmd_init(void);

int main()
{
	uint16_t receData[24];
	uint16_t SBUFF[2];

    uart_init();
    cmd_init();

    while(1)
    {

        rece_cmd(receData, 24);
        //rece_cmd(SBUFF, 2);
        if(receData[6] == 0x01)
            rightLight();
        //else if(SBUFF[0] == 0x0020)
        //    wrongLight();
        //if(rece_cmd(receData, 10))
        //   send_cmd(receData, 10);
    }
}

void cmd_init(void)
{
    cmdlen_ledon = create_cmd(cmd_ledon, IOMode, IO_LED_ON);
    cmdlen_ledoff = create_cmd(cmd_ledoff, IOMode, IO_LED_OFF);
    cmdlen_buzzeron = create_cmd(cmd_buzzeron, IOMode, IO_Buzzer_ON);
    cmdlen_buzzeroff = create_cmd(cmd_buzzeroff, IOMode, IO_Buzzer_OFF);
}

void rightLight(void)
{
    send_cmd(cmd_ledon, cmdlen_ledon);
    delay_ms(100);
    send_cmd(cmd_ledoff, cmdlen_ledoff);
    delay_ms(100);
}
void wrongLight(void)
{
    send_cmd(cmd_ledon, cmdlen_ledon);
    delay_ms(50);
    send_cmd(cmd_ledoff, cmdlen_ledoff);
    delay_ms(50);
    send_cmd(cmd_ledon, cmdlen_ledon);
    delay_ms(50);
    send_cmd(cmd_ledoff, cmdlen_ledoff);
    delay_ms(50);
}
uint8_t rece_cmd(uint16_t *receData, uint8_t len)
{
    uint8_t ax = 0;
    for(ax = 0; ax<len; ax++)
    {
        while(!USART_GetFlagStatus(USART1, USART_FLAG_RXNE));
        USART_ClearFlag(USART1, USART_FLAG_RXNE);
        receData[ax] = USART_ReceiveData(USART1);
    }
    return 1;
}

void send_cmd(uint16_t *cmd, uint16_t cmdlen)
{
    int ax=0;
    for(ax=0; ax< cmdlen; ax++)
    {
        USART_SendData(USART1, cmd[ax]);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

void uart_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);

    //RCC_USARTCLKConfig(RCC_USART1CLK_PCLK);
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);
}
