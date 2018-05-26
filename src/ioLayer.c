/*
Author: 	M.F. Janssen
Date:		19-05-2018
Revision:	1


    ioLayer.c:
          Inits all needed functions

    pin-info:
           --
*/

#include "ioLayer.h"
extern volatile int charcounter;
extern char string[100];

void IO_init(void)
{

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	DELAY_init();	// Init delay lib

	UART_init();	// To enable UART
	UART_INT_init(); // To use UART on interrupt base
}
