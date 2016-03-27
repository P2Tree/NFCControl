/*****************************************************************
*
*! @FILE	main.c
*! @author	PWE
*! @version	V1.0.0
*! @date	2016-3-19
*! @brief	main file for NFCControl
*
*******************************************************************/
#include <stm32f0xx.h>
#include <stm32f0xx_conf.h>
#include <stdio.h>
#include "cmd.h"
#include "delay.h"
#include "nfc.h"

void IOset(uint16_t, uint16_t);
void IOinit(void);
//void LightOFF(void);

int main()
{
	const uint8_t recebits = BASICBITS + FUNCBITS + CONTENTBITS;
	uint16_t receData[recebits];
	uint8_t lockFlag = 0;	// 0 is locked, 1 is unlock
	uint8_t isRightCard = 0;	// 0 is wrong card or no card, 1 is right card
	
    uart_init();
    cmd_init();
	send_cmd(cmd_ledoff, cmdlen_ledoff);
	changetoMUXmode();
	delay_ms(2);
	setDefault();
	IOinit();
	
    while(1)
    {
        rece_cmd(receData, recebits);
		isRightCard = read_cmd(receData, auto_ret);
		// locker is run and unlock mode
		if( isRightCard && !lockFlag)
		{
			IOset(IO1, high);	//unlock
			rightLight();
			lockFlag = 1;		// flag : unlock
			isRightCard = 0;	// no card
		}
		else if( isRightCard && lockFlag)
		{
			IOset(IO1, low);	//locked
			rightLight();
			lockFlag = 0;		// flag : locked
			isRightCard = 0;	// no card
		}
		else
		{
			IOset(IO1, low);	//locked
			wrongLight();		
			lockFlag = 0;		// flag : locked
			isRightCard = 0;	// wrong card
		}
    }
}

void IOset(uint16_t IOselect, uint16_t IOlevel)
{

	if(IOselect == IO1 && IOlevel == high)
	{
		GPIOA->BSRR |= GPIO_BSRR_BS_4;
		GPIOA->BSRR |= GPIO_BSRR_BS_5;	//output high
		//send_cmd(cmd_IO1setHigh, cmdlen_IO1setHigh);	// NOT RUN
	}
	else if(IOselect == IO1 && IOlevel == low)
	{
		GPIOA->BRR |= GPIO_BSRR_BS_4;
		GPIOA->BRR |= GPIO_BSRR_BS_5;		//output low
		//send_cmd(cmd_IO1setLow, cmdlen_IO1setLow);	// NOT RUN
	}
	
}

void IOinit(void)
{
	//IOPAEN=1, enable clk of GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	//set IO mode,general IO
	GPIOA->MODER |= GPIO_MODER_MODER4_0 + GPIO_MODER_MODER5_0;
	GPIOA->MODER &= ~(GPIO_MODER_MODER4_1 + GPIO_MODER_MODER5_1);
	//set output mode
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_4 + GPIO_OTYPER_OT_5);
	//set speed,10MHz
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0 + GPIO_OSPEEDER_OSPEEDR5_0;
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR4_1 + GPIO_OSPEEDER_OSPEEDR5_1);
	//set pullupdown,no up no down
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR4_0 + GPIO_PUPDR_PUPDR5_0);
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR4_1 + GPIO_PUPDR_PUPDR5_1);
	
	GPIOA->BRR |= GPIO_BSRR_BS_4;
	GPIOA->BRR |= GPIO_BSRR_BS_5;		//output low
}