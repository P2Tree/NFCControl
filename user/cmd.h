/*************************************************************************
*
*! @file        cmd.h
*! @author      PWE
*! @version     V1.0
*! @date        2016-3-18
*! @brief       Basic commands in NFC module.
*
***************************************************************************/

#ifndef __CMD_H
#define __CMD_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define BEGIN1      0x55
#define BEGIN2      0xAA
#define END1        0x00
#define END2        0xFF

#define TR          0xFF

#define IO_LED      0x02    //LED DATA - 0X02
#define IO_LED_1   0x01     // only led 1 can control
#define IO_Buzzer   0x03
#define IO_SET		0x07
#define IO_ON   	0x01        //including every IO output
#define IO_OFF  	0x00
#define IO_HIGH		0x01
#define IO_LOW		0x00
#define IO_P1		0x01	// in NFC, it is PB3
#define IO_P2		0x02	// in NFC, it is PB4
#define IO_P3		0x03	// in NFC, it is PB5
#define IO_P4		0x04	// in NFC, it is PB6

#define BASICBITS   7       //basic bits is beginbits(2) + endbits(2) + len(1) + cod(1) + TR(1)
#define FUNCBITS    1       //if there is a function bits(after the TR), it also 1 bit
#define POSITIONBITS    1   //default reading position in setdefault
#define KEYBITS     6       //read keys, always are 6 bits
#define FLAGBITS    1       //return true(0x00) or false(0x01)
#define CONTENTBITS 16      //content in block

enum funcCod {
    ChangeMode      = 0x13, //!< change nfc module mode: change to Reader mode, or MUX mode or P2P mode
    ReaderMode      = 0x10,         //!< reader mode: can read and write card
    ChangeModeStatus_R  = 0x14,   //!< NFC return the status of ChangeMode
    MUXMode         = 0x16,            //!< MUX mode: can read NUMBER of IC card or NFC phone
    //P2PMode       = 0x12,             //!< P2P mode: P2P with another NFC module or NFC phone
    IOMode          = 0x15                //!< IO mode: operation on IO
    //BandrateMode    = 0x17        //!< Bandrate mode: change bandrate with NFC moduel, default is 9600
};

enum arg
{
    //! for ChangeMode:
    C_Reader,  //!< ChangeMode -> reader mode
    C_P2P,            //!< ChangeMode -> P2P mode
    C_MUX1,  //!< ChangeMode -> MUX1 mode
    C_MUX2,           //!< ChangeMode -> MUX2 mode

    //! for ReaderMode:

    //! for MUX1Mode:
    MUX_setDefault,     //!< MUXMode: set default card reading position

    //! for IO:
    IO_IOinit,      //!< IO initialization
    IO_LED_ON,         //!< LED control: LED1 ON
    IO_LED_OFF,       //!< LED control: LED1 OFF
    IO_Buzzer_ON,      //!< buzzer control: buzzer ON
    IO_Buzzer_OFF,      //!< buzzer control: buzzer OFF
    IO_PressButton,//!< press button control
    IO_IOget,       //!< get IO status
    IO_IOstatus_R,   //!< NFC return for IO status, return IO_IOget
    IO_IO1set_high,            //!< set IO1_PB3 status to high
	IO_IO1set_low	//!< set IO1_PB3 status to low

};

enum flag	//what do you want to read the cmd --control flag
{
    auto_ret,           //!< NFC auto return its card context with default positon and key
    setdefault_ret,      //!< when set default position and key, NFC module return right or wrong
	changeMode_ret		//!< when changeMode, NFC return
};

enum IOselect
{
	IO1,
	IO2,
	IO3,
	IO4
};

enum IOlevel
{
	high,
	low
};

//! create a command
uint16_t create_cmd(uint16_t * cmd, uint16_t funcCod, uint16_t arg);
//! command create
void cmd_init(void);

#ifdef __cplusplus
}
#endif

#endif
