/*
** Author: Gaël GILET-COURAUD
** STM8S103F3 code for handling data coming from the odometry sensors.
** It makes use of the several ports and external interrupt possibilities
** to be able to track more than one sensor and reports the data through
** its UART. Note that because the baud rate works through a frequency
** divider and the code must work with software serial on the Arduino side,
** the selected baud rate is 9600 and not 15200.
*/

#include <stdint.h>

#define CLK_DIVR (*(volatile uint8_t *)0x50c6)

#define TIM1_CR1 (*(volatile uint8_t *)0x5250)
#define TIM1_CNTRH (*(volatile uint8_t *)0x525e)
#define TIM1_CNTRL (*(volatile uint8_t *)0x525f)
#define TIM1_PSCRH (*(volatile uint8_t *)0x5260)
#define TIM1_PSCRL (*(volatile uint8_t *)0x5261)

// control registers for port B
#define PB_ODR (*(volatile uint8_t *)0x5005)
#define PB_DDR (*(volatile uint8_t *)0x5007)
#define PB_CR1 (*(volatile uint8_t *)0x5008)

// control registers for port D
// PD_IDR is not used but kept for the record since
#define PD_IDR (*(volatile uint8_t *)0x5010)
#define PD_DDR (*(volatile uint8_t *)0x5011)
#define PD_CR1 (*(volatile uint8_t *)0x5012)
#define PD_CR2 (*(volatile uint8_t *)0x5013)

// Control registers for external interrupts.
// Used to ask for rising edge detection only.
#define EXTI_CR1 (*(volatile uint8_t *)0x50A0)
#define EXTI_CR2 (*(volatile uint8_t *)0x50A1)

#define UART1_SR (*(volatile uint8_t *)0x5230)
#define UART1_DR (*(volatile uint8_t *)0x5231)
#define UART1_BRR1 (*(volatile uint8_t *)0x5232)
#define UART1_BRR2 (*(volatile uint8_t *)0x5233)
#define UART1_CR1 (*(volatile uint8_t *)0x5234)
#define UART1_CR2 (*(volatile uint8_t *)0x5235)
#define UART1_CR3 (*(volatile uint8_t *)0x5236)
#define UART1_CR4 (*(volatile uint8_t *)0x5237)
#define UART1_CR5 (*(volatile uint8_t *)0x5238)
#define UART1_GTR (*(volatile uint8_t *)0x5239)
#define UART1_PSCR (*(volatile uint8_t *)0x523A)

void uart_init(void)
{
	UART1_CR1 = 0;
	UART1_CR2 = 0;
	UART1_CR4 = 0;
	UART1_CR3 = 0;
	UART1_CR5 = 0;
	UART1_GTR = 0;
	UART1_PSCR = 0;
	
	// We set the divider to 0x0682 (16MHz / 0x0682 ~= 9600Hz)
	UART1_BRR2 = 0x02;
	UART1_BRR1 = 0x68;
	// We have SCK==1 => LOW with a phase.
	UART1_CR3= 0x07;
	// We activate the receiver and emitter.
	UART1_CR2 = 0x0C;
	// Enable the clock.
	UART1_CR3 |= 8;
}

// TODO: Migrate to an array to have a more generic handling of multiple
// ports with sensors connected.
volatile unsigned last_clock_d = 0;
volatile uint32_t nb_d = 0;

unsigned int clock(void)
{
	unsigned char h = TIM1_CNTRH;
	unsigned char l = TIM1_CNTRL;
	return((unsigned int)(h) << 8 | l);
}

void portd_handler() __interrupt(6)
{
	unsigned x = clock();
	// The first part is not a mistake but here to take the overflow into
	// account.
	if (last_clock_d < x && x - last_clock_d < 100)
		return;
	last_clock_d = x;
	nb_d++;
	// Flip the debug LED. Used to ensure that the code works properly.
	PB_ODR ^= 0x20;
}

void uart_putc(unsigned char c)
{
	UART1_DR = c;
	// Wait until the buffer is empty.
	while (!(UART1_SR & 0x80))
		continue;
}

void uart_print_int(uint32_t i)
{
	if (i < 10)
		uart_putc(i + '0');
	else
	{
		uart_print_int(i / 10);
		uart_putc(i % 10 + '0');
	}
}

void uart_print_data(void)
{
	uart_print_int(nb_d);
	uart_putc('\n');
}

void main(void)
{
	uint32_t r;
	// 16MHz / 0x3e80 ~= 1kHz
	TIM1_PSCRH = 0x3e;
	TIM1_PSCRL = 0x80;
	CLK_DIVR = 0x00;
	// Enable the timer
	TIM1_CR1 = 0x01;

	// Set PB5 (LED) as output.
	PB_DDR = 0x20;
	PB_CR1 = 0x20;
	// Set PD4 as input.
	PD_DDR = 0x00;
	PD_CR1 = 0x10;
	PD_CR2 = 0x10;
	// Set the interrupts as rising edge only.
	A = 0xAA;
	B = 0x0;
	// Enable interrupts.
	__asm__("rim");

	uart_init();
	while(1)
	{
		// To be changed to an interruption-timed wait.
		for (r = 0; r < 100000; r++)
			continue;
		uart_print_data();
	}
}