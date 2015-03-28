//#include "uart.h"
#include "softUart.h"
#include "../template.h"
#include "QikMotors.h"

void motors_init(){	
	//uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	SUART_Init();
	ClrBit(RESET_PORT, RESET_PIN);
	SetBit(RESET_DDR, RESET_PIN);
	_delay_ms(1);
	ClrBit(RESET_DDR, RESET_PIN);
	_delay_ms(10);
	SUART_PutChar(SYNC_COMMAND);
}

void motors_forward(unsigned char speed){
	if (speed<=MAX_SPEED){

		if(!COMMAND_SHORT_MODE){
			SUART_PutChar(SYNC_COMMAND);
			SUART_PutChar(QIK_ADDRESS);
			SUART_PutChar(M0_FORWARD_COMMAND^0x80);
		}else{ 
			SUART_PutChar(M0_FORWARD_COMMAND);
		}
			SUART_PutChar(speed);


		if(!COMMAND_SHORT_MODE){
			SUART_PutChar(SYNC_COMMAND);
			SUART_PutChar(QIK_ADDRESS);
			SUART_PutChar(M1_FORWARD_COMMAND^0x80);
		}else{
			SUART_PutChar(M1_FORWARD_COMMAND);
		}
			SUART_PutChar(speed);
	}
}

void motors_reverse(unsigned char speed){
	if (speed<=MAX_SPEED){

		if(!COMMAND_SHORT_MODE){
			SUART_PutChar(SYNC_COMMAND);
			SUART_PutChar(QIK_ADDRESS);
			SUART_PutChar(M0_REVERSE_COMMAND^0x80);
		}else{
			SUART_PutChar(M0_REVERSE_COMMAND);
		}
			SUART_PutChar(speed);

		if(!COMMAND_SHORT_MODE){
			SUART_PutChar(SYNC_COMMAND);
			SUART_PutChar(QIK_ADDRESS);
			SUART_PutChar(M1_REVERSE_COMMAND^0x80);
		}else{
			SUART_PutChar(M1_REVERSE_COMMAND);
		}
			SUART_PutChar(speed);
		}
}

void motors_stop(unsigned char brake){
	//unsigned char brake = 50;
		if(!COMMAND_SHORT_MODE){
			SUART_PutChar(SYNC_COMMAND);
			SUART_PutChar(QIK_ADDRESS);
			SUART_PutChar(M0_STOP_COMMAND^0x80);
		}else{
			SUART_PutChar(M0_STOP_COMMAND);
		}
			SUART_PutChar(brake);

		if(!COMMAND_SHORT_MODE){
			SUART_PutChar(SYNC_COMMAND);
			SUART_PutChar(QIK_ADDRESS);
			SUART_PutChar(M1_STOP_COMMAND^0x80);
		}else{
			SUART_PutChar(M1_STOP_COMMAND);
		}
			SUART_PutChar(brake);
}

void set_config(unsigned char param, unsigned char value){
	if (param<=11 && value<=127){
			if(!COMMAND_SHORT_MODE){
			SUART_PutChar(SYNC_COMMAND);
			SUART_PutChar(QIK_ADDRESS);
			SUART_PutChar(SET_CONFIG_COMMAND^0x80);
		}else{
			SUART_PutChar(SET_CONFIG_COMMAND);
		}
			SUART_PutChar(param);
			SUART_PutChar(value);
			SUART_PutChar(0x55);
			SUART_PutChar(0x2A);
	}
} 

