/************************************************************************************************************/
/*                                                                                                          */
/*                                           Interface.h                                                    */
/*                                                                                                          */
/*                                                                                       2023. 1. 9.        */
/************************************************************************************************************/
#ifndef __INTERFACE_H
#define __INTERFACE_H

typedef unsigned char uc;
typedef unsigned int ui;
typedef double db;
typedef volatile uc vuc;
typedef volatile int vi;
typedef volatile db vdb;

extern vuc tc, psd[], vcam_en, vcam_n, vcam_cnt, vcam_buff[], vcam_data[10][5], vcam[10][5];
extern int stand, tsize, aup, adn, acc, cset[], cnt[], xs, xb, ys, yb;
extern vdb totc, enx, eny, ena, enx2, eny2, lzig, lhd, wzig, whd, vb[], vg[], vm[], vf[3][51];


#define rr			return
#define LED			0x07
#define LED1		0x01
#define LED2		0x02
#define LED3		0x04
#define BZ			0x08
#define SWIN		(~PINB&SW)
#define SW			0xF0
#define SW1			0x10
#define SW2			0x20
#define SW3			0x40
#define SWB			0x80
#define IR			0x1C
#define IR2			0x50 //외부 DI에 접속(D포트 상위 비트)

#define led_on(x)			PORTB |=(x)
#define led_off(x)			PORTB &=~(x)
#define bz_on			PORTB |=BZ
#define bz_off			PORTB &=~BZ
#define bz(x1, x2)		bz_on; _delay_ms(x1); bz_off; _delay_ms(x2)

#define lcd(y,x,...) do{char buf[21];sprintf(buf,__VA_ARGS__);lcd_display_str(y,x,buf);}while(0)

uc ir_in(void);
uc sw_in(void);



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Interface.h"
#include "Motor.h"
#include "Move.h"
#include "Sensor.h"





//2020.01.01 추가********************************************************************************************
unsigned char read_gyro(unsigned char addr);
void write_gyro(unsigned char addr, unsigned char data);
//***********************************************************************************************************


#define SLA             0x07

extern volatile unsigned char rx1_flg, rx1_buff;
extern volatile unsigned char psd_value[];


void MCU_init(void);
void Interface_init(void);
char getchar1(void);
void putchar1(char data);

void lcd_write_data(unsigned char data);
void lcd_display_str(unsigned char Y_line, unsigned char X_line,char *string);
void write_lcd_data(unsigned char Y_line, unsigned char X_line, long data);
void lcd_clear_screen(void);
void display_char(unsigned char line, unsigned char col, unsigned char data);

#endif		// __INTERFACE_H
