#ifndef __LCD_H_
#define __LCD_H_

#include "qspi.h"
typedef enum{
	FALSE = 0,
	TRUE = 1
}isCmd;

#define W 128
#define H 160
#define FONT_W 8
#define FONT_H 16

#define CMD_SW_RESET 0x01
#define CMD_SLEEP_OUT 0x11
#define CMD_DISPLAY_ON 0x29
#define CMD_COLUMN_ADDRESS_SET 0x2A
#define CMD_ROW_ADDRESS_SET 0x2B
#define CMD_MEMORY_WRITE 0x2C
#define CMD_MEM_DATA_ACCESS_CTRL 0x36
#define CMD_PIXEL_FORMAT 0x3A
#define CMD_FRAME_RATE_CTRL_NORMAL 0xB1
#define CMD_POWER_CTRL1 0xC0
#define CMD_POWER_CTRL2 0xC1
#define CMD_POWER_CTRL3 0xC2
#define CMD_POWER_CTRL4 0xC3
#define CMD_POWER_CTRL5 0xC4
#define CMD_VCOM_CTRL 0xC5
#define CMD_GAMMA_CORRECTION_POS_POLARITY 0xE0
#define CMD_GAMMA_CORRECTION_NEG_POLARITY 0xE1

void SetActiveRect(const uint8 x, const uint8 y, const uint8 w,
		const uint8 h);
void Send(isCmd is_cmd, uint8_t data);

void SEND_COMMAND(uint8_t dat);
void SEND_DATA(uint8_t dat);

void LcdInit(void);
void LcdClear(const uint16 color);
void LcdDrawSquare(const uint8 x, const uint8 y, const uint8 w, const uint8 h,
		const uint16_t color);
void LcdDrawString(const uint8 x, const uint8 y, const char *str,
		const uint16 color, const uint16 bg_color);
void LcdDrawChar(const uint8 x, const uint8 y, const char ch,
		const uint16 color, const uint16 bg_color);

#endif
