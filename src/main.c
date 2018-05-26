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
extern char string[100];
char *ding = "hoi/n";
int main(void)
{

	IO_init();

	UB_VGA_FillScreen(VGA_COL_GREEN);
	UB_VGA_SetPixel(10,10,10);
//	UB_VGA_drawLine(10,10 ,50, 50, VGA_COL_RED, 3);
//	UB_VGA_drawLine(50,50 ,100, 50, VGA_COL_RED, 3);
//	UB_VGA_drawLine(100,50 ,100, 150, VGA_COL_RED, 3);
	parser parsedData;
	UB_VGA_drawLine(1,1 ,100, 100,3, VGA_COL_RED);

	UB_VGA_drawTriangle(10,10,130, 120,240, 200, VGA_COL_WHITE);
	UB_VGA_drawTriangle(100,100,30, 20,250, 250, VGA_COL_MAGENTA);
	UB_VGA_drawTriangle(130,130,17, 12,333, 233, VGA_COL_YELLOW);
//	UB_VGA_drawLine(100,1 ,100, 1, 3, VGA_COL_RED);

  while(1)
  {
	  //memset(string, 0, sizeof(string));
	  //UART_printf(sizeof(string), string);
	  DELAY_ms(100);
	 InterpretData(&parsedData);
	 //memset(string, 0, sizeof(string));
	// UART_printf(sizeof(ding), ding);
  }
}

