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
