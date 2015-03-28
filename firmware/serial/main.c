#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "motors.h"
#include "../template.h"

#define UART_BAUD_RATE 9600
#define comm_count 6

#define SPACE_BYTE 0x0A
#define START_BYTE 0xAA

#define RELEASE_COMM 0x30
#define RIGHT_COMM 0x31
#define LEFT_COMM 0x32
#define BACKWARD_COMM 0x34
#define STOP_COMM 0x33
#define FORWARD_COMM 0x35

static volatile unsigned int buff[1];
static unsigned char commands[comm_count]={RELEASE_COMM, RIGHT_COMM, LEFT_COMM, 
										   FORWARD_COMM, BACKWARD_COMM, STOP_COMM};

volatile static unsigned char firbFlag = FALSE;
volatile static unsigned char secbFlag = FALSE;

void start();
unsigned char checkCommand(unsigned char comm);
unsigned char getComm(unsigned int data);

int main( void )
{
  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );
  wdt_enable(WDTO_1S);
  sei();
  start();
	
  	for(;;){
			wdt_reset();
		
			while (buff[0] == UART_NO_DATA){
				wdt_reset();
				buff[0] = uart_getc();
			}

			if (checkCommand( getComm(buff[0]) )){
				firbFlag = TRUE;
				while (buff[1] == UART_NO_DATA){
					wdt_reset();
				buff[1] = uart_getc();
				if (getComm(buff[1]) == SPACE_BYTE){
						secbFlag = TRUE;
					}
				}
				buff[1] = UART_NO_DATA;
			}

			if (firbFlag && secbFlag){
				wdt_reset();
				switch(getComm(buff[0])){
					case RIGHT_COMM: motorsRight();break;
					case LEFT_COMM: motorsLeft();break;
					case RELEASE_COMM: motorsRelease();break;

					case FORWARD_COMM: motorsForward();break;
					case BACKWARD_COMM: motorsBackward();break;
					case STOP_COMM: motorsStop();break;

					default:break;
				}
			}

		firbFlag = FALSE;
		secbFlag = FALSE;
		buff[0] = UART_NO_DATA;	
    }
  return 0;
}

void start(){
  uart_putc(START_BYTE);
  uart_putc(START_BYTE);

  buff[0] = UART_NO_DATA;
  buff[1] = UART_NO_DATA;
}

unsigned char checkCommand(unsigned char comm){
	for(unsigned char i=0; i<comm_count; i++){
		if (comm == commands[i]){
			return TRUE;
		}
	}
	return FALSE;
}

unsigned char getComm(unsigned int data){
	return (data & 0x00FF);
}
