#include "softUart.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

static volatile unsigned char	inbuf[IN_BUF_SIZE];
static volatile unsigned char	qin = 0;
static volatile unsigned char	qout = 0;

static char 	        flag_rx_waiting_for_stop_bit;
static char 	        flag_rx_off;
static char 	        rx_mask;
static volatile char 	flag_rx_ready;
static volatile char 	flag_tx_ready;
static char 	        timer_rx_ctr;
static volatile char 	timer_tx_ctr;
static char 	        bits_left_in_rx;
static volatile char 	bits_left_in_tx;
static char 	        rx_num_of_bits;
static char 	        tx_num_of_bits;
static char	            internal_rx_buffer;
static volatile short	internal_tx_buffer;
static char	            user_tx_buffer;

//______________________________________________________
#define get_rx_pin_status() RX_PINX & (1<<RX_PIN)
#define set_tx_pin_high()   TX_PORTX |= (1<<TX_PIN)
#define set_tx_pin_low()    TX_PORTX &= ~(1<<TX_PIN)

#define TIMER_CONST (0xff - (F_CPU/(BAUD_RATE*3*PRESCALER)))

#if PRESCALER==1L 
  #define CSXX (0<<CS02)|(0<<CS01)|(1<<CS00)
#elif PRESCALER==8L 
  #define CSXX (0<<CS02)|(1<<CS01)|(0<<CS00)
#elif PRESCALER==64L 
  #define CSXX (0<<CS02)|(1<<CS01)|(1<<CS00)
#elif PRESCALER==256L 
  #define CSXX (1<<CS02)|(0<<CS01)|(0<<CS00)
#elif PRESCALER==1024L 
  #define CSXX (1<<CS02)|(1<<CS01)|(1<<CS00)
#else 
  #error "prescaller not correct"
#endif

void idle(void)
{
  
}
//______________________________________________________


ISR(TIMER0_OVF_vect)
{
   char	mask, start_bit, flag_in;
   TCNT0 = TIMER_CONST;
   char tmp;
// Transmitter Section
	if ( flag_tx_ready )
		{
		if ( --timer_tx_ctr<=0 )
			{
			mask = internal_tx_buffer&1;
			internal_tx_buffer >>= 1;
			if ( mask )
				{
				set_tx_pin_high();
				}
			else
				{
				set_tx_pin_low();
				}
			timer_tx_ctr = 3;
			if ( --bits_left_in_tx<=0 )
				{
				flag_tx_ready = FALSE;
                                set_tx_pin_high();
				}
			}
		}
// Receiver Section
	if ( flag_rx_off==FALSE )
		{
		if ( flag_rx_waiting_for_stop_bit )
			{
			if ( --timer_rx_ctr<=0 )
				{
				flag_rx_waiting_for_stop_bit = FALSE;
				flag_rx_ready = FALSE;
				internal_rx_buffer &= 0xFF;
				if ( internal_rx_buffer!=0xC2 )
					{
					inbuf[qin] = internal_rx_buffer;
					if ( ++qin>=IN_BUF_SIZE )
						{
						qin = 0;
						}
					}
				}
			}
		else		// rx_test_busy
			{
			if ( flag_rx_ready==FALSE )
				{
				start_bit = get_rx_pin_status();
// Test for Start Bit
				if ( start_bit==0 )
				        {
					flag_rx_ready = TRUE;
					internal_rx_buffer = 0;
					timer_rx_ctr = 4;
					bits_left_in_rx = rx_num_of_bits;
					rx_mask = 1;
					}
				}
			else	// rx_busy
				{
				if ( --timer_rx_ctr<=0 )
					{				// rcv
					timer_rx_ctr = 3;
					flag_in = get_rx_pin_status();
					if ( flag_in )
						{
						internal_rx_buffer |= rx_mask;
						}
					rx_mask <<= 1;
					if ( --bits_left_in_rx<=0 )
						{
						flag_rx_waiting_for_stop_bit = TRUE;
						}
					}
				}
			}
		}
	
}

void SUART_Init(void)
{
	flag_tx_ready = FALSE;
	flag_rx_ready = FALSE;
	flag_rx_waiting_for_stop_bit = FALSE;
	flag_rx_off = FALSE;
	rx_num_of_bits = 10;
	tx_num_of_bits = 10;
        
        RX_DDRX &= ~(1<<RX_PIN);//вход 
        RX_PORTX |= (1<<RX_PIN);//вкл pull-up резистор
  
        TX_DDRX |= (1<<TX_PIN);//выход
        TX_PORTX |= (1<<TX_PIN);//установить единицу 
        
        //настройка таймера Т0
        TCCR0 = CSXX;  
        TCNT0 = TIMER_CONST;
        TIMSK |= (1<<TOIE0);
}

char SUART_GetChar(void)
{
        unsigned char tmp;  
	char ch;

	do{
            tmp = qin;  
	    while (qout==tmp){
	       idle();
               tmp = qin;
            }
	    ch = inbuf[qout] & 0xFF;
	    if ( ++qout>=IN_BUF_SIZE ){
		qout = 0;
	    }
	}while ( ch==0x0A || ch==0xC2 );
	return(ch);
}

void SUART_PutChar(char ch)
{
	while ( flag_tx_ready );
	user_tx_buffer = ch;

// invoke_UART_transmit
	timer_tx_ctr = 3;	
	bits_left_in_tx = tx_num_of_bits;
	internal_tx_buffer = (user_tx_buffer<<1) | 0x200;
	flag_tx_ready = TRUE;
}

void SUART_FlushInBuf(void)
{
   qin = 0;
   qout = 0;
}

char SUART_Kbhit(void)
{
   unsigned char tmp = qout;
   return( qin!=tmp );
}

void SUART_TurnRxOn(void)
{
   flag_rx_off = FALSE;
}

void SUART_TurnRxOff(void)
{
   flag_rx_off = TRUE;
}
