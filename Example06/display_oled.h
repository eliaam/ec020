/*
 * display_oled.h
 *
 *  Created on: 21/11/2016
 *      Author: aluno
 */

#ifndef DISPLAY_OLED_H_
#define DISPLAY_OLED_H_

void DisplayOled_write(long a);
void DisplayOled_new(void);
void intToString(int value, uint8_t* pBuf, uint32_t len, uint32_t base);

#endif /* DISPLAY_OLED_H_ */
