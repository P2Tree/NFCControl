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
#include "nfc.h"
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
    uint8_t ax=0;
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
    case MUXMode : *cmd++ = MUXMode;    break;
    case IOMode : *cmd++ = IOMode;    break;
    default: break;
    }
    *cmd++ = TR;                //add check bit
	switch(arg) {              //add DATA(begin with "FF", end to "00 FF")
    // FOR ChangeMode:
	case C_Reader :
		*cmd++ = 0x01;
         cmdl += 1;
		break;
    case C_MUX1 :
        *cmd++ = 0x03;
        cmdl += 1;
        break;

    // FOR MUXMode:
    case MUX_setDefault :
        *cmd++ = 0x01;
        *cmd++ = block;
        for(ax=0;ax<KEYBITS;ax++)
        {
            *cmd++ = key[ax];
        }
        cmdl += (KEYBITS+POSITIONBITS+FUNCBITS);
        break;

    // FOR IOMode:
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
	case IO_IO1set_high :
		*cmd++ = IO_SET;
		*cmd++ = IO_P1;
		*cmd++ = IO_HIGH;
		cmdl += 3;
		break;
	case IO_IO1set_low :
		*cmd++ = IO_SET;
		*cmd++ = IO_P1;
		*cmd++ = IO_LOW;
		cmdl += 3;
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

/**********************************************************************
*
*! @brief   command create
*! @note    you can add any command to create by add line in this function
*! @note    and ATTATION, you will also change create_cmd function.
*! @param   void
*! @retval  void
*
***********************************************************************/
void cmd_init(void)
{
    cmdlen_ledon = create_cmd(cmd_ledon, IOMode, IO_LED_ON);
    cmdlen_ledoff = create_cmd(cmd_ledoff, IOMode, IO_LED_OFF);
    cmdlen_buzzeron = create_cmd(cmd_buzzeron, IOMode, IO_Buzzer_ON);
    cmdlen_buzzeroff = create_cmd(cmd_buzzeroff, IOMode, IO_Buzzer_OFF);
    //default key and position is key[] and position
    cmdlen_setdefault = create_cmd(cmd_setdefault, MUXMode, MUX_setDefault);
	//once to up the SMC532, change to MUX mode will be called for readMUX function
	cmdlen_changetoMUXmode = create_cmd(cmd_changetoMUXmode, ChangeMode, C_MUX1);
	cmdlen_IO1setHigh = create_cmd(cmd_IO1setHigh, IOMode, IO_IO1set_high);
	cmdlen_IO1setLow = create_cmd(cmd_IO1setLow, IOMode, IO_IO1set_low);
}
