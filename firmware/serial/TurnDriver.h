#define DRIVER_PORT PORTB
#define DRIVER_DDR DDRB
#define DRIVER_PIN PINB

#define EN12_PIN 4
/*right*/
#define IN1_PIN 3
/*left*/ 
#define IN2_PIN 2
#define EN34_PIN 7
#define IN3_PIN 6
#define IN4_PIN 5

#define FEEDBACK_PORT PORTA
#define FEEDBACK_DDR DDRA
#define FEEDBACK_PIN PINA

#define RIGHT_FEEDBACK_PIN 1
#define LEFT_FEEDBACK_PIN 2

void turn_driver_init();

void turn_right(unsigned int ang);

void turn_left(unsigned int ang);

void turn_release();
