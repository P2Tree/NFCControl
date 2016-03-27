#ifndef __NFC_H_
#define __NFC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE	1
#define FALSE 	0

extern uint16_t cmd_ledon[];
extern uint16_t cmd_ledoff[];
extern uint16_t cmdlen_ledon;
extern uint16_t cmdlen_ledoff;
extern uint16_t cmd_buzzeron[];
extern uint16_t cmd_buzzeroff[];
extern uint16_t cmdlen_buzzeron;
extern uint16_t cmdlen_buzzeroff;
extern uint16_t cmd_setdefault[];
extern uint16_t cmdlen_setdefault;
extern uint16_t cmd_changetoMUXmode[];
extern uint16_t cmdlen_changetoMUXmode;
extern uint16_t cmd_IO1setHigh[];
extern uint16_t cmdlen_IO1setHigh;
extern uint16_t cmd_IO1setLow[];
extern uint16_t cmdlen_IO1setLow;

//! context args was used to check NFC card context.
extern const uint16_t context[];
extern const uint16_t key[];
extern const uint16_t block;

//! USART of STM32 initialization.
void uart_init(void);
//! send command to NFC module.
void send_cmd(uint16_t *, uint16_t);
//! receive command from NFC module.
uint8_t rece_cmd(uint16_t *, uint8_t);
//! action LED for right operate, flash every 100ms
void rightLight(void);
//! action LED for wrong operate, flash every 30ms
void wrongLight(void);
//! read and analysis received cmd
uint8_t read_cmd(uint16_t *cmd, uint8_t flag);
//! set default read block and key
void setDefault(void);
//! change NFC module mode to MUX1
void changetoMUXmode(void);
#ifdef __cplusplus
}
#endif

#endif
