/*	
 *	Lab Section: 023
 *	Assignment: CS120B Final Project
 *	Exercise Description: This project is an implementation of the game Dance
 *						  Dance Revoluton.
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "nokia5110.c"
#include "usart.h"

//Macros holding values of musical notes
#define c_n 261.626
#define c_s 277.183
#define d_n 293.665
#define d_s 311.127
#define e_n 329.628
#define f_n 349.228
#define f_s 369.994
#define g_n 391.995
#define g_s 415.305
#define a_n 440.000
#define a_s 466.164
#define b_n 493.883
#define z_n 0

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

//32 secs
//double notes1[] = {g, c * 2, g, c, g, c * 2, g, g, c * 2, g, c * 2, e_n * 2, d * 2, c * 2, b, a, g_s, g, c * 2, g, c, g, c * 2, g, f * 2, d * 2, c * 2, a_s, a, g, f};
//
//double tempo1[] = {500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 370, 130, 120, 130, 120, 130, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 1000};
	
const unsigned char ARRAY_SIZE1 = 31;

//64 secs
//double notes2[] = {e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f,
				   //e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f,
				   //e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f,
				   //e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f, e_n, d_s, a_s, f};
//
//double tempo2[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
				   //1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
				   //1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,
				   //1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};

const unsigned char ARRAY_SIZE2 = 64;

//64 secs
//double notes3[] = {b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, e_n * 2,
				   //z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, d * 2,
				   //z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, a, z,
				   //b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, e_n * 2,
				   //z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, d * 2,
				   //z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, a, z,
				   //b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, e_n * 2,
				   //z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, d * 2,
				   //z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, a, z,
				   //b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, b, z, e_n * 2,
				   //z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, e_n * 2, z, d * 2,
				   //z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, d * 2, z, a, z};
				   //
//short tempo3[] = {60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
				  //60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60,
				  //60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 120, 120,
				  //60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
				  //60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60,
				  //60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 120, 120,
				  //60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
				  //60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60,
				  //60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 120, 120,
				  //60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
				  //60, 60, 120, 120, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 60, 60,
				  //60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 120, 120, 120, 120};

const unsigned char ARRAY_SIZE3 = 320;

unsigned short song1[][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
							 {0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,0,0}};
								
const unsigned char SONG_SIZE1 = 13;

//unsigned short song1[][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},
							 //{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,1,0},{0,1,0,0},
							 //{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,1,0,0},{0,0,1,0},{0,0,1,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},
							 //{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,1,0,0},
							 //{0,0,1,0},{0,0,1,0},{0,0,0,0}};
								 
unsigned short song2[][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
							 {0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,1,0},{0,1,0,0},
							 {0,0,0,1},{1,0,0,0},{0,1,0,0},{0,1,0,0},{0,0,1,0},{0,0,1,0},{0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},
							 {0,0,0,1},{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,1,0},{0,1,0,0},{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,1,0,0},
							 {0,0,1,0},{0,0,1,0},{0,0,0,0}};
								 
const unsigned char SONG_SIZE2 = 36;

unsigned short song3[][4] = {{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0},{0,0,0,1},{0,0,1,1},{1,0,0,0},{1,1,0,0}};
	
const unsigned char SONG_SIZE3 = 8;

unsigned char i, j, k, l, m_press, m_return, m_reset_done, game, song, reset;
unsigned char up, down, left, right, time;
unsigned short score;

//--------Find GCD function --------------------------------------------------
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
b = c;
	}
	return 0;
}
//--------End find GCD function ----------------------------------------------

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;


void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void set_PWM(double frequency) {
	static double current_frequency = -1; // Keeps track of the currently set frequency
	
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counter

		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }

		// prevents OCR0A from underflowing, using prescaler 64     // 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }

		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
	
		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);

	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

//Function that draws a cursor character
void drawCursor(int x, int y, int e){
	nokia_lcd_set_pixel(x + 4, y, e);
	nokia_lcd_set_pixel(x + 4, y + 1, e);
	nokia_lcd_set_pixel(x + 4, y + 2, e);
	nokia_lcd_set_pixel(x + 4, y + 3, e);
	nokia_lcd_set_pixel(x + 4, y + 4, e);
	nokia_lcd_set_pixel(x + 3, y + 1, e);
	nokia_lcd_set_pixel(x + 3, y + 2, e);
	nokia_lcd_set_pixel(x + 3, y + 3, e);
	nokia_lcd_set_pixel(x + 2, y + 2, e);
}

enum M_States{M_Init, M_Wait, M_Press, M_Start, M_Menu, M_Game, M_Score, M_Reset, M_HighScore} M_State;

int M_tick(int state) {
	switch(M_State){
		case M_Init:
		M_State = M_Wait;
		i = 0;
		song = 0;
		game = 0;
		m_press = 0;
		nokia_lcd_clear();
		nokia_lcd_write_string("Press any",1);
		nokia_lcd_set_cursor(0, 8);
		nokia_lcd_write_string("button to",1);
		nokia_lcd_set_cursor(0, 16);
		nokia_lcd_write_string("start the game",1);
		nokia_lcd_render();
		eeprom_write_byte(0,10);
		eeprom_write_byte(1,0);
		break;
		
		case M_Wait:
		if(~PINA & 0x1E){
			M_State = M_Press;
			m_press = 2;
			nokia_lcd_clear();
			nokia_lcd_write_string(" Dance Dance   Revolution!",1);
			nokia_lcd_render();
			song = 3;
		}
		else{
			M_State = M_Wait;
		}
		break;
		
		case M_Press:
		if(!(~PINA & 0x1F)){
			switch(m_press){
				case 0:
				M_State = M_Init;
				break;
				
				case 1:
				M_State = M_Wait;
				break;
				
				case 2:
				M_State = M_Start;
				break;
				
				case 3:
				M_State = M_Menu;
				break;
				
				case 4:
				M_State = M_Game;
				break;
				
				case 5:
				M_State = M_Score;
				break;
				
				case 6:
				M_State = M_Reset;
				break;
				
				case 7:
				M_State = M_HighScore;
				break;
					
				default:
				M_State = M_Init;
				break;
			}
		}
		else{
			M_State = M_Press;
		}
		break;
		
		case M_Start:
		if((~PINA & 0x02) && !(~PINA & 0x01)){
			M_State = M_Press;
			m_press = 3;
			nokia_lcd_clear();
			nokia_lcd_write_string("Jeopardy",1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_string("Closing Time",1);
			nokia_lcd_set_cursor(0, 16);
			nokia_lcd_write_string("Sandstorm",1);
			nokia_lcd_set_cursor(0, 24);
			nokia_lcd_write_string("HIGH SCORE",1);
			drawCursor(78, 1, 1);
			nokia_lcd_render();
			i = 1;
		}
		else if(~PINA & 0x01){
			M_State = M_Press;
			m_press = 6;
			m_return = 2;
			m_reset_done = 0;
			reset = 1; k = 8;
			nokia_lcd_clear();
			nokia_lcd_write_string("Reset Game?",1);
			nokia_lcd_set_cursor(0,8);
			nokia_lcd_write_string("Yes",1);
			drawCursor(78, 8, 1);
			nokia_lcd_set_cursor(0,16);
			nokia_lcd_write_string("No",1);
			nokia_lcd_render();
		}
		else if(i == 40){
			nokia_lcd_set_cursor(0, 24);
			nokia_lcd_write_string("Press right",1);
			nokia_lcd_set_cursor(0, 32);
			nokia_lcd_write_string("button to",1);
			nokia_lcd_set_cursor(0, 40);
			nokia_lcd_write_string("continue",1);
			nokia_lcd_render();
		}
		else{
			i++;
			M_State = M_Start;
		}
		break;
		
		case M_Menu:
		if((~PINA & 0x02) && !(~PINA & 0x01) && i <= 17){
			song = (i / 8) + 1;
			M_State = M_Press;
			m_press = 4;
			nokia_lcd_clear();
			nokia_lcd_write_string("SCORE: ",1);
			nokia_lcd_render();
			game = 1;
			if(song == 1){
				if ( USART_IsSendReady(0) ) {
					USART_Send(0x05);
				}
			}
			else if(song == 2){
				if ( USART_IsSendReady(0) ) {
					USART_Send(0x06);
				}
			}
			else if(song == 3){
				if ( USART_IsSendReady(0) ) {
					USART_Send(0x07);
				}
			}
		}
		else if((~PINA & 0x02) && !(~PINA & 0x01) && i > 17){
			M_State = M_Press;
			m_press = 7;
			short high_score = (short) eeprom_read_byte(0);
			high_score += (short) eeprom_read_byte(1) >> 8;
			nokia_lcd_clear();
			nokia_lcd_write_string("HIGH SCORE:",1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_char('0' + ((high_score % 10000000) / 1000000), 1);
			nokia_lcd_write_char('0' + ((high_score % 1000000) / 100000), 1);
			nokia_lcd_write_char('0' + ((high_score % 100000) / 10000), 1);
			nokia_lcd_write_char('0' + ((high_score % 10000) / 1000), 1);
			nokia_lcd_write_char('0' + ((high_score % 1000) / 100), 1);
			nokia_lcd_write_char('0' + ((high_score % 100) / 10), 1);
			nokia_lcd_write_char('0' + ((high_score % 10) / 1), 1);
			nokia_lcd_render();
		}
		else if((~PINA & 0x04) && !(~PINA & 0x01)){
			M_State = M_Menu;
			if(i > 1){
				drawCursor(78, i, 0);
				i -= 8;
				drawCursor(78, i, 1);
				nokia_lcd_render();
			}
		}
		else if((~PINA & 0x10) && !(~PINA & 0x01)){
			M_State = M_Menu;
			if(i < 25){
				drawCursor(78, i, 0);
				i += 8;
				drawCursor(78, i, 1);
				nokia_lcd_render();
			}
		}
		else if(~PINA & 0x01){
			M_State = M_Press;
			m_press = 6;
			m_return = 3;
			m_reset_done = 0;
			reset = 1; k = 8;
			nokia_lcd_clear();
			nokia_lcd_write_string("Reset Game?",1);
			nokia_lcd_set_cursor(0,8);
			nokia_lcd_write_string("Yes",1);
			drawCursor(78, 8, 1);
			nokia_lcd_set_cursor(0,16);
			nokia_lcd_write_string("No",1);
			nokia_lcd_render();
		}
		else{
			M_State = M_Menu;
		}
		
		break;
		
		case M_HighScore:
		if((~PINA & 0x17) && !(~PINA & 0x01)){
			M_State = M_Press;
			m_press = 3;
			nokia_lcd_clear();
			nokia_lcd_write_string("Jeopardy",1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_string("Closing Time",1);
			nokia_lcd_set_cursor(0, 16);
			nokia_lcd_write_string("Sandstorm",1);
			nokia_lcd_set_cursor(0, 24);
			nokia_lcd_write_string("HIGH SCORE",1);
			drawCursor(78, 1, 1);
			nokia_lcd_render();
			i = 1;
		}
		else if(~PINA & 0x01){
			M_State = M_Press;
			m_press = 6;
			m_return = 7;
			m_reset_done = 0;
			reset = 1; k = 8;
			nokia_lcd_clear();
			nokia_lcd_write_string("Reset Game?",1);
			nokia_lcd_set_cursor(0,8);
			nokia_lcd_write_string("Yes",1);
			drawCursor(78, 8, 1);
			nokia_lcd_set_cursor(0,16);
			nokia_lcd_write_string("No",1);
			nokia_lcd_render();
		}
		else{
			M_State = M_HighScore;
		}
		break;
		
		case M_Game:
		if(!game && !(~PINA & 0x01)){
			M_State = M_Press;
			m_press = 5;
			short high_score = (short) eeprom_read_byte(0);
			high_score += (short) eeprom_read_byte(1) >> 8;
			nokia_lcd_clear();
			nokia_lcd_write_string("FINAL SCORE:",1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_char('0' + ((score % 10000000) / 1000000), 1);
			nokia_lcd_write_char('0' + ((score % 1000000) / 100000), 1);
			nokia_lcd_write_char('0' + ((score % 100000) / 10000), 1);
			nokia_lcd_write_char('0' + ((score % 10000) / 1000), 1);
			nokia_lcd_write_char('0' + ((score % 1000) / 100), 1);
			nokia_lcd_write_char('0' + ((score % 100) / 10), 1);
			nokia_lcd_write_char('0' + ((score % 10) / 1), 1);
			nokia_lcd_set_cursor(0, 16);
			nokia_lcd_write_string("HIGH SCORE:",1);
			nokia_lcd_set_cursor(0, 24);
			nokia_lcd_write_char('0' + ((high_score % 10000000) / 1000000), 1);
			nokia_lcd_write_char('0' + ((high_score % 1000000) / 100000), 1);
			nokia_lcd_write_char('0' + ((high_score % 100000) / 10000), 1);
			nokia_lcd_write_char('0' + ((high_score % 10000) / 1000), 1);
			nokia_lcd_write_char('0' + ((high_score % 1000) / 100), 1);
			nokia_lcd_write_char('0' + ((high_score % 100) / 10), 1);
			nokia_lcd_write_char('0' + ((high_score % 10) / 1), 1);
			if(score > high_score){
				nokia_lcd_set_cursor(0, 40);
				nokia_lcd_write_string("NEW HIGH SCORE",1);
				if(eeprom_is_ready()){
					eeprom_write_byte(0, (char) score & 0xFF);
					eeprom_write_byte(1, (char) score >> 8);
				}
			}
			nokia_lcd_render();
		}
		else if(~PINA & 0x01){
			M_State = M_Press;
			m_press = 6;
			m_return = 4;
			m_reset_done = 0;
			reset = 1; k = 8;
			nokia_lcd_clear();
			nokia_lcd_write_string("Reset Game?",1);
			nokia_lcd_set_cursor(0,8);
			nokia_lcd_write_string("Yes",1);
			drawCursor(78, 8, 1);
			nokia_lcd_set_cursor(0,16);
			nokia_lcd_write_string("No",1);
			nokia_lcd_render();
		}
		else{
			M_State = M_Game;
			nokia_lcd_clear();
			nokia_lcd_write_string("SCORE: ",1);
			nokia_lcd_write_char('0' + ((score % 10000000) / 1000000), 1);
			nokia_lcd_write_char('0' + ((score % 1000000) / 100000), 1);
			nokia_lcd_write_char('0' + ((score % 100000) / 10000), 1);
			nokia_lcd_write_char('0' + ((score % 10000) / 1000), 1);
			nokia_lcd_write_char('0' + ((score % 1000) / 100), 1);
			nokia_lcd_write_char('0' + ((score % 100) / 10), 1);
			nokia_lcd_write_char('0' + ((score % 10) / 1), 1);
			nokia_lcd_render();
		}
		break;
		
		case M_Score:
		if((~PINA & 0x02) && !(~PINA & 0x01)){
			M_State = M_Press;
			m_press = 3;
			nokia_lcd_clear();
			nokia_lcd_write_string("Jeopardy",1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_string("Closing Time",1);
			nokia_lcd_set_cursor(0, 16);
			nokia_lcd_write_string("Sandstorm",1);
			nokia_lcd_set_cursor(0, 24);
			nokia_lcd_write_string("HIGH SCORE",1);
			drawCursor(78, 1, 1);
			nokia_lcd_render();
			i = 1;
		}
		else if(~PINA & 0x01){
			M_State = M_Press;
			m_press = 6;
			m_return = 5;
			m_reset_done = 0;
			reset = 1; k = 8;
			nokia_lcd_clear();
			nokia_lcd_write_string("Reset Game?",1);
			nokia_lcd_set_cursor(0,8);
			nokia_lcd_write_string("Yes",1);
			drawCursor(78, 8, 1);
			nokia_lcd_set_cursor(0,16);
			nokia_lcd_write_string("No",1);
			nokia_lcd_render();
		}
		else{
			M_State = M_Score;
		}
		break;
		
		case M_Reset:
		if((~PINA & 0x02) && k == 8){
			M_State = M_Press;
			m_reset_done = 1;
			m_press = 0;
			reset = 0;
			game = 0;
		}
		else if ((~PINA & 0x02) && k == 16){
			M_State = M_Press;
			m_reset_done = 2;
			m_press = m_return;
			reset = 0;
			switch(m_press){
				case 2:
				nokia_lcd_clear();
				nokia_lcd_write_string(" Dance Dance   Revolution!",1);
				nokia_lcd_render();
				break;
				
				case 3:
				nokia_lcd_clear();
				nokia_lcd_write_string("Jeopardy",1);
				nokia_lcd_set_cursor(0, 8);
				nokia_lcd_write_string("Closing Time",1);
				nokia_lcd_set_cursor(0, 16);
				nokia_lcd_write_string("Sandstorm",1);
				nokia_lcd_set_cursor(0, 24);
				nokia_lcd_write_string("HIGH SCORE",1);
				drawCursor(78, 1, 1);
				nokia_lcd_render();
				i = 1;
				break;
				
				case 4:
				nokia_lcd_clear();
				nokia_lcd_write_string("SCORE: ",1);
				nokia_lcd_render();
				break;
				
				case 5:
				;
				short high_score2 = (short) eeprom_read_byte(0);
				high_score2 += (short) eeprom_read_byte(1) >> 8;
				nokia_lcd_clear();
				nokia_lcd_write_string("FINAL SCORE:",1);
				nokia_lcd_set_cursor(0, 8);
				nokia_lcd_write_char('0' + ((score % 10000000) / 1000000), 1);
				nokia_lcd_write_char('0' + ((score % 1000000) / 100000), 1);
				nokia_lcd_write_char('0' + ((score % 100000) / 10000), 1);
				nokia_lcd_write_char('0' + ((score % 10000) / 1000), 1);
				nokia_lcd_write_char('0' + ((score % 1000) / 100), 1);
				nokia_lcd_write_char('0' + ((score % 100) / 10), 1);
				nokia_lcd_write_char('0' + ((score % 10) / 1), 1);
				nokia_lcd_set_cursor(0, 16);
				nokia_lcd_write_string("HIGH SCORE:",1);
				nokia_lcd_set_cursor(0, 24);
				nokia_lcd_write_char('0' + ((high_score2 % 10000000) / 1000000), 1);
				nokia_lcd_write_char('0' + ((high_score2 % 1000000) / 100000), 1);
				nokia_lcd_write_char('0' + ((high_score2 % 100000) / 10000), 1);
				nokia_lcd_write_char('0' + ((high_score2 % 10000) / 1000), 1);
				nokia_lcd_write_char('0' + ((high_score2 % 1000) / 100), 1);
				nokia_lcd_write_char('0' + ((high_score2 % 100) / 10), 1);
				nokia_lcd_write_char('0' + ((high_score2 % 10) / 1), 1);
				nokia_lcd_render();
				break;
				
				case 7:
				;
				short high_score = (short) eeprom_read_byte(0);
				high_score += (short) eeprom_read_byte(1) >> 8;
				nokia_lcd_clear();
				nokia_lcd_write_string("HIGH SCORE:",1);
				nokia_lcd_set_cursor(0, 8);
				nokia_lcd_write_char('0' + ((high_score % 10000000) / 1000000), 1);
				nokia_lcd_write_char('0' + ((high_score % 1000000) / 100000), 1);
				nokia_lcd_write_char('0' + ((high_score % 100000) / 10000), 1);
				nokia_lcd_write_char('0' + ((high_score % 10000) / 1000), 1);
				nokia_lcd_write_char('0' + ((high_score % 1000) / 100), 1);
				nokia_lcd_write_char('0' + ((high_score % 100) / 10), 1);
				nokia_lcd_write_char('0' + ((high_score % 10) / 1), 1);
				nokia_lcd_render();
				break;
				
				default:
				break;
			}
		}
		else if(~PINA & 0x04){
			if(k > 8){
				drawCursor(78, k, 0);
				k -= 8;
				drawCursor(78, k, 1);
				nokia_lcd_render();
			}
			
		}
		else if(~PINA & 0x10){
			if(k < 16){
				drawCursor(78, k, 0);
				k += 8;
				drawCursor(78, k, 1);
				nokia_lcd_render();
			}
		}
		else{
			M_State = M_Reset;
		}
		break;
		
		default:
		break;
	}//State transitions and actions
	return state;
}

enum D_States{D_Wait, D_Generate, D_Reset} D_State;
	
int D_tick(int state) {
	switch(D_State){
		case D_Wait:
		if(game){
			D_State = D_Generate;
			i = 0; j = 0;
			up = 0; down = 0;
			left = 0; right = 0;
		}
		else{
			D_State = D_Wait;
		}
		break;
		
		case D_Generate:
		if(!game && !reset){
			D_State = D_Wait;
		}
		else if(reset){
			D_State = D_Reset;
			if ( USART_IsSendReady(0) ) {
				USART_Send(0x02);
			}
		}
		else{
			D_State = D_Generate;
			if(j % 4 == 2){
				left = 0; down = 0; up = 0; right = 0;
			}
			else if(j % 4 == 0){
				left = song1[i][0]; down = song1[i][1]; up = song1[i][2]; right = song1[i][3];
				if(j % 4 == 0){
					i++;
				}
			}
			if(song == 1){
				if(i >= SONG_SIZE1){
					game = 0;
				}
			}
			j++;
		}
		break;
		
		case D_Reset:
		if(m_reset_done == 1){
			D_State = D_Wait;
			if ( USART_IsSendReady(0) ) {
				USART_Send(0x04);
			}
		}
		else if(m_reset_done == 2){
			D_State = D_Generate;
			if ( USART_IsSendReady(0) ) {
				USART_Send(0x03);
			}
		}
		else{
			D_State = D_Reset;
		}
		break;
		
		default:
		break;
	}//State transitions and actions
	return state;
}

enum G_States{G_Wait, G_Play, G_Press, G_Reset} G_State;
	
int G_tick(int state) {
	switch(G_State){
		case G_Wait:
		if(game && !reset){
			G_State = G_Play;
			score = 0;
		}
		else{
			G_State = G_Wait;
		}
		break;
		
		case G_Play:
		if(!game && !reset){
			G_State = G_Wait;
		}
		else if(reset){
			G_State = G_Reset;
		}
		else{
			G_State = G_Play;
			if(~PINA & 0x1E){
				G_State = G_Press;
				if((~PINA & 0x02) && right){
					score+=10;
					right = 0;
				}
				if((~PINA & 0x04) && up){
					score+=10;
					up = 0;
				}
				if((~PINA & 0x08) && left){
					score+=10;
					left = 0;
				}
				if((~PINA & 0x10) && down){
					score+=10;
					down = 0;
				}
			}
		}
		break;
		
		case G_Press:
		if(!(~PINA & 0x1E) && !reset){
			G_State = G_Play;
		}
		else if(reset){
			G_State = G_Reset;
		}
		else{
			G_State = G_Press;
		}
		break;
		
		case G_Reset:
		if(m_reset_done == 1){
			G_State = G_Wait;
		}
		else if(m_reset_done == 2){
			G_State = G_Play;
		}
		else{
			G_State = G_Reset;
		}
		break;
		
		default:
		G_State = G_Wait;
		break;
	}//State transitions and actions
	return state;
}

//enum SW_States{SW_Wait, SW_Play} SW_State;
//
//int SW_tick(int state) {
	//switch(SW_State){
		//case SW_Wait:
		//if(song == 1){
			//SW_State = SW_Play;
			//l = 0;
			//PWM_on();
			//set_PWM(notes1[l]);
		//}
		//else if(song == 2){
			//SW_State = SW_Play;
			//l = 0;
			//PWM_on();
			//set_PWM(notes2[l]);
		//}
		//else if(song == 3){
			//SW_State = SW_Play;
			//l = 0;
			//PWM_on();
			//set_PWM(notes3[l]);
		//}
		//else{
			//SW_State = SW_Wait;
		//}
		//break;
		//
		//case SW_Play:
		//if(song == 1){
			//if(l < ARRAY_SIZE1){
				//SW_State = SW_Play;
				//if(time < tempo1[l]){
					//time += 1;
				//}
				//else{
					//l++;
					//time = 0;
					//set_PWM(notes1[l]);
				//}
			//}
			//else{
				//SW_State = SW_Wait;
				//PWM_off();
			//}
		//}
		//else if(song == 2){
			//if(l < ARRAY_SIZE2){
				//SW_State = SW_Play;
				//if(time < tempo2[l]){
					//time += 1;
				//}
				//else{
					//l++;
					//time = 0;
					//set_PWM(notes2[l]);
				//}
			//}
			//else{
				//SW_State = SW_Wait;
				//PWM_off();
			//}
		//}
		//else if (song == 3){
			//if(l < ARRAY_SIZE3){
				//SW_State = SW_Play;
				//if(time < tempo3[l]){
					//time += 1;
				//}
				//else{
					//l++;
					//time = 0;
					//set_PWM(notes3[l]);
				//}
			//}
			//else{
				//SW_State = SW_Wait;
				//PWM_off();
			//}
		//}
		//break;
		//
		//default:
		//break;
	//}
	//return state;
//}

int main(void){
	//Initiate Ports
	PORTA = 0xFF; DDRA = 0x00;
	PORTB = 0x00; DDRB = 0xFF;
	PORTD = 0xFF; DDRD = 0x00;

	const short TASK_SIZE = 3;
	
	//Periods and functions for each task
	unsigned long int SMTickLengths[] = {100, 250, 50};
	int (*SMTickFunctions[])(int) = {&M_tick, &D_tick, &G_tick};
	
	//Calculating GCD
	unsigned long int GCD = 1000;
	for(int i = 0; i < TASK_SIZE; i++){
		GCD = findGCD(GCD, SMTickLengths[i]);
	}

	//Declare an array of tasks
	static task task1, task2, task3;
	task *tasks[] = { &task1, &task2, &task3};

	for(int i = 0; i < TASK_SIZE; i++){
		unsigned long int SMTickPeriod = SMTickLengths[i] / GCD;
		tasks[i]->state = -1;
		tasks[i]->period = SMTickPeriod;
		tasks[i]->elapsedTime = SMTickPeriod;
		tasks[i]->TickFct = SMTickFunctions[i];
	}
	
	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();
	
	initUSART(0);
	
	nokia_lcd_init();
	nokia_lcd_clear();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		// Scheduler code
		for ( i = 0; i < TASK_SIZE; i++ ) {
			// Task is ready to tick
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				// Setting next state for task
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				// Reset the elapsed time for next tick.
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	
	// Error: Program should not exit!
	return 0;
}