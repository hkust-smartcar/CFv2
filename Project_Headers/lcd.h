#ifndef __LCD_H_
#define __LCD_H_

#include "qspi.h"

void LcdInit(void);
void LcdClear(const uint16 color);
void LcdDrawSquare(const uint8 x, const uint8 y, const uint8 w, const uint8 h,
		const uint16_t color);
void LcdDrawString(const uint8 x, const uint8 y, const char *str,
		const uint16 color, const uint16 bg_color);
void LcdDrawChar(const uint8 x, const uint8 y, const char ch,
		const uint16 color, const uint16 bg_color);

#endif
