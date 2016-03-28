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
