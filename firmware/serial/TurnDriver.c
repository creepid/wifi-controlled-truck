#include "../template.h"
#include "TurnDriver.h"

void turn_driver_init(){
	DRIVER_DDR|=(1<<EN12_PIN)|(1<<IN1_PIN)|(1<<IN2_PIN);
	FEEDBACK_PORT|=(1<<RIGHT_FEEDBACK_PIN)|(1<<LEFT_FEEDBACK_PIN);
	turn_release();
}

void turn_left(unsigned int ang){
	DRIVER_PORT|=(1<<EN12_PIN);
	while(!IsBitOff(FEEDBACK_PIN, RIGHT_FEEDBACK_PIN)){
			SetBit(DRIVER_PORT, IN1_PIN);
	}
	delay(ang);
	ClrBit(DRIVER_PORT, IN1_PIN);
	DRIVER_PORT&=~((1<<EN12_PIN)|(1<<IN1_PIN));
}


void turn_right(unsigned int ang){
	DRIVER_PORT|=(1<<EN12_PIN);
	while(!IsBitOff(FEEDBACK_PIN, LEFT_FEEDBACK_PIN)){
			SetBit(DRIVER_PORT, IN2_PIN);
	}
	delay(ang);
	ClrBit(DRIVER_PORT, IN2_PIN);
	DRIVER_PORT&=~((1<<EN12_PIN)|(1<<IN2_PIN));
}

void turn_release(){
	if (IsBitOff(FEEDBACK_PIN, RIGHT_FEEDBACK_PIN)){
		DRIVER_PORT|=(1<<EN12_PIN);
		ClrBit(DRIVER_PORT, IN1_PIN);
		while(IsBitOff(FEEDBACK_PIN, RIGHT_FEEDBACK_PIN)){
			SetBit(DRIVER_PORT, IN2_PIN);
		}
		ClrBit(DRIVER_PORT, IN2_PIN);
		DRIVER_PORT&=~((1<<EN12_PIN)|(1<<IN2_PIN));
	}else if (IsBitOff(FEEDBACK_PIN, LEFT_FEEDBACK_PIN)){
		DRIVER_PORT|=(1<<EN12_PIN);
		ClrBit(DRIVER_PORT, IN2_PIN);
		while(IsBitOff(FEEDBACK_PIN, LEFT_FEEDBACK_PIN)){
			SetBit(DRIVER_PORT, IN1_PIN);
		}
		delay(100);
		ClrBit(DRIVER_PORT, IN1_PIN);
		DRIVER_PORT&=~((1<<EN12_PIN)|(1<<IN1_PIN));
	}
}


