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

int main()
{
	const uint8_t recebits = BASICBITS + FUNCBITS + CONTENTBITS;
	uint16_t receData[recebits];
    uart_init();
    cmd_init();

	setDefault();

    while(1)
    {
        rece_cmd(receData, recebits);
		if(read_cmd(receData, auto_ret))
			rightLight();
		else
			wrongLight();
    }
}
