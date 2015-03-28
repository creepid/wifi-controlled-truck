#define MOTORS_PORT PORTB
#define MOTORS_DDR DDRB

#define MOTORS_LEFT_PIN 0
#define MOTORS_RIGHT_PIN 1
#define MOTORS_FORWARD_PIN 3
#define MOTORS_BACKWARD_PIN 2

void motorsRight();

void motorsLeft();

void motorsRelease();

void motorsForward();

void motorsBackward();

void motorsStop();



