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
