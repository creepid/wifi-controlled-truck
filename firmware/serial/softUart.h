#ifndef SOFT_UART_H
#define SOFT_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>

//______________________Настройки_____________________________________
#ifndef F_CPU
   #define F_CPU       16000000L      //тактовая частота мк
#endif
#define PRESCALER      64L            //прескалер таймера. 
#define BAUD_RATE      9600L          //скорость обмена 

#define IN_BUF_SIZE    32             //вместимость приемного буфера

//пин приемника
#define RX_PINX       PIND
#define RX_PORTX      PORTD
#define RX_DDRX       DDRD
#define RX_PIN        6  

//пин передатчика
#define TX_PORTX      PORTD
#define TX_DDRX       DDRD
#define TX_PIN        7

//_____________________Пользовательские функции______________________________
void SUART_Init(void);
void SUART_PutChar(char ch);
char SUART_GetChar(void);
void SUART_FlushInBuf(void);
char SUART_Kbhit(void);
void SUART_TurnRxOn(void);
void SUART_TurnRxOff(void);
//___________________________________________________________________________

#endif //SOFT_UART_H

