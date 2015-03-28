#define RESET_PORT PORTA
#define RESET_DDR DDRA
#define RESET_PIN 0

#define MAX_SPEED      255
#define QIK_ADDRESS    10

#define SYNC_COMMAND 0xAA

#define M0_FORWARD_COMMAND 0x88
#define M0_REVERSE_COMMAND 0x8A
#define M0_STOP_COMMAND 0x86

#define M1_FORWARD_COMMAND 0x8C
#define M1_REVERSE_COMMAND 0x8E
#define M1_STOP_COMMAND 0x87

#define SET_CONFIG_COMMAND 0x84

#define CONFIG_DEVICE_ID 0
#define CONFIG_PWM_PARAMETER 1
#define CONFIG_SHUT_DOWN_MOTORS_ON_ERROR 2
#define CONFIG_SERIAL_TIMEOUT 3
#define CONFIG_MOTOR_M0_ACCELERATION 4
#define CONFIG_MOTOR_M1_ACCELERATION 5
#define CONFIG_MOTOR_M0_BRAKE_DURATION 6
#define CONFIG_MOTOR_M1_BRAKE_DURATION 7
#define CONFIG_MOTOR_M0_CURRENT_LIMIT_DIV_2 8
#define CONFIG_MOTOR_M1_CURRENT_LIMIT_DIV_2 9
#define CONFIG_MOTOR_M0_CURRENT_LIMIT_RESPONSE 10
#define CONFIG_MOTOR_M1_CURRENT_LIMIT_RESPONSE 11

#define COMMAND_SHORT_MODE    1

void motors_init();

void motors_forward(unsigned char speed);

void motors_reverse(unsigned char speed);

void motors_stop(unsigned char brake);

void set_config(unsigned char param, unsigned char value); 
