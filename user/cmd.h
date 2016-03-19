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
#define IO_ON   0x01
#define IO_OFF  0x00

#define IO_Buzzer   0x03




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
    C_Reader        = 0x01,  //!< ChangeMode -> reader mode
    C_P2P,            //!< ChangeMode -> P2P mode
    C_MUX1          = 0x03,  //!< ChangeMode -> MUX1 mode
    C_MUX2,           //!< ChangeMode -> MUX2 mode

    //! for ReaderMode:

    //! for MUX1Mode:

    //! for IO:
    IO_IOinit,      //!< IO initialization
    IO_LED_ON,         //!< LED control: LED1 ON
    IO_LED_OFF,       //!< LED control: LED1 OFF
    IO_Buzzer_ON,      //!< buzzer control: buzzer ON
    IO_Buzzer_OFF,      //!< buzzer control: buzzer OFF
    IO_PressButton,//!< press button control
    IO_IOget,       //!< get IO status
    IO_IOstatus_R,   //!< NFC return for IO status, return IO_IOget
    IO_IOset            //!< set IO status

};

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
uint16_t create_cmd(uint16_t * cmd, uint16_t funcCod, uint16_t arg);

#ifdef __cplusplus
}
#endif

#endif
