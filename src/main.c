/**
 ***************************************************************
 *@file 	main.c
 *@author 	Menno Janssen and Benno Driessen
 *@date		29 may 2018
 *@brief	Main program body can also be seen as the front layer.
 ***************************************************************
 */

#include "main.h"
extern char string[100];
int main(void)
{
	IO_init();
	parser parsedData;
  while(1)
  {

	 InterpretData(&parsedData);
  }
}

