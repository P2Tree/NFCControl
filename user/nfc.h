#ifndef __NFC_H_
#define __NFC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE	1
#define FALSE 	0

extern uint16_t cmd_ledon[10];
extern uint16_t cmd_ledoff[10];
extern uint16_t cmdlen_ledon;
extern uint16_t cmdlen_ledoff;
extern uint16_t cmd_buzzeron[9];
extern uint16_t cmd_buzzeroff[9];
extern uint16_t cmdlen_buzzeron;
extern uint16_t cmdlen_buzzeroff;

//! USART of STM32 initialization.
void uart_init(void);
//! send command to NFC module.
void send_cmd(uint16_t *, uint16_t);
//! receive command from NFC module.
uint8_t rece_cmd(uint16_t *, uint8_t);
//! action LED for right operate
void rightLight(void);
//! action LED for wrong operate
void wrongLight(void);
//! command create
void cmd_init(void);

#ifdef __cplusplus
}
#endif

#endif
