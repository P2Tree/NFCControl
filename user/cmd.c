/*************************************************************************
*
*! @file        cmd.c
*! @author      PWE
*! @version     V1.0
*! @date        2016-3-18
*! @brief       Basic commands in NFC module.
*
***************************************************************************/
#include "cmd.h"
#include <string.h>
#include <stdint.h>


/**************************************************************************
*
*! @func: create_cmd
*! @args:   cmd: created command in this arg
*!           funcCod: select COD
*!           arg: select next func in COD
*! @return: uint16_t cmdl: the length of cmd
*! @decription: create a command for send
*!              BEGIN1 BEGIN2 LEN COD TR DATA(several bits) END1 END2
*!              LEN = LEN(1bit) + COD(1bit) + TR(1bit) + DATA(several bits)
*
****************************************************************************/
uint16_t create_cmd(uint16_t *cmd, uint16_t funcCod, uint16_t arg)
{

    uint16_t *point = cmd;
    uint16_t cmdl = 0;
    uint16_t *len_point;
    *cmd++ = BEGIN1;
    *cmd++ = BEGIN2;
    len_point = cmd;
    cmd++;                       //empty for LEN
    switch(funcCod) {           // add COD
    case ChangeMode : *cmd++ = ChangeMode;    break;
    case ReaderMode : *cmd++ = 0x10;    break;
    case IOMode : *cmd++ = IOMode;    break;

    default: break;
    }
    *cmd++ = TR;                //add check bit
	switch(arg) {              //add DATA
	case C_Reader :
		*cmd++ = C_Reader;
         cmdl += 1;
		break;
    case C_MUX1 :
        *cmd++ = C_MUX1;
        cmdl += 1;
        break;

    // FOR IO:
    case IO_LED_ON :
        *cmd++ = IO_LED;
        *cmd++ = IO_LED_1;
        *cmd++ = IO_ON;
        cmdl += 3;
        break;
    case IO_LED_OFF :
        *cmd++ = IO_LED;
        *cmd++ = IO_LED_1;
        *cmd++ = IO_OFF;
        cmdl += 3;
		break;
    case IO_Buzzer_ON :
        *cmd++ = IO_Buzzer;
        *cmd++ = IO_ON;
        cmdl += 2;
        break;
    case IO_Buzzer_OFF :
        *cmd++ = IO_Buzzer;
        *cmd++ = IO_OFF;
        cmdl += 2;
        break;

	default: break;
	}
    *cmd++ = END1;
    *cmd++ = END2;
    *len_point = cmdl+3;    //LEN = LEN(1bit) + COD(1bit) + TR(1bit) + DATA(?bits)
	cmdl += 7;		       //begin 2 byte and end 2 byte and LEN(1bit) and TR(1bit) and COD(1bit)
	cmd = point;
	return cmdl;
}
