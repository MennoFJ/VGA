//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"


int main(void)
{

	//  uint32_t n;

	char *functionality = "ARM-board \r";		// Showed on UART3 at startup

	SystemInit(); // System speed to 168MHz


	UART_init();			// Initialise UART3 Without interrupt
	UART_printf(256,functionality);

//	UART_INT_init();		// Initialise UART3 With interrupt enabled (Also use UART_init())

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_GREEN);
	UB_VGA_SetPixel(10,10,10);
	UB_VGA_drawLine(10,10 ,50, 50, VGA_COL_RED, 3);
	UB_VGA_drawLine(50,50 ,100, 50, VGA_COL_RED, 3);
	UB_VGA_drawLine(100,50 ,100, 150, VGA_COL_RED, 3);


  while(1)
  {

  }
}

