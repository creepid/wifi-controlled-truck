#include "../template.h"
#include "motors.h"

void motorsTurnInit(){
	MOTORS_DDR|=(1<<MOTORS_LEFT_PIN)|(1<<MOTORS_RIGHT_PIN);
	MOTORS_PORT&=~((1<<MOTORS_LEFT_PIN)|(1<<MOTORS_RIGHT_PIN));
}

void motorsMoveInit(){
	MOTORS_DDR|=(1<<MOTORS_FORWARD_PIN)|(1<<MOTORS_BACKWARD_PIN);
	MOTORS_PORT&=~((1<<MOTORS_FORWARD_PIN)|(1<<MOTORS_BACKWARD_PIN));
}

void motorsMoveFinal(){
	MOTORS_PORT&=~((1<<MOTORS_FORWARD_PIN)|(1<<MOTORS_BACKWARD_PIN));
	MOTORS_DDR&=~((1<<MOTORS_FORWARD_PIN)|(1<<MOTORS_BACKWARD_PIN));
}

void motorsTurnFinal(){
	MOTORS_PORT&=~((1<<MOTORS_LEFT_PIN)|(1<<MOTORS_RIGHT_PIN));
	MOTORS_DDR&=~((1<<MOTORS_LEFT_PIN)|(1<<MOTORS_RIGHT_PIN));
}

void motorsLeft(){
	motorsTurnInit();
	ClrBit(MOTORS_PORT, MOTORS_RIGHT_PIN);
	SetBit(MOTORS_PORT, MOTORS_LEFT_PIN);
}

void motorsRight(){
	motorsTurnInit();
	ClrBit(MOTORS_PORT, MOTORS_LEFT_PIN);
	SetBit(MOTORS_PORT, MOTORS_RIGHT_PIN);
}

void motorsRelease(){
	motorsTurnInit();
	ClrBit(MOTORS_PORT, MOTORS_LEFT_PIN);
	ClrBit(MOTORS_PORT, MOTORS_RIGHT_PIN);
	motorsTurnFinal();
}

void motorsForward(){
	motorsMoveInit();
	ClrBit(MOTORS_PORT, MOTORS_BACKWARD_PIN);
	SetBit(MOTORS_PORT, MOTORS_FORWARD_PIN);
}

void motorsBackward(){
	motorsMoveInit();
	ClrBit(MOTORS_PORT, MOTORS_FORWARD_PIN);
	SetBit(MOTORS_PORT, MOTORS_BACKWARD_PIN);
}

void motorsStop(){
	motorsMoveInit();
	ClrBit(MOTORS_PORT, MOTORS_BACKWARD_PIN);
	ClrBit(MOTORS_PORT, MOTORS_FORWARD_PIN);
	motorsMoveFinal();
}
	
