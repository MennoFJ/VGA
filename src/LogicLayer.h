/*
Author: 	M.F. Janssen
Date:		19-05-2018
Revision:	1


    LogicLayer.c:
          Inits all needed functions

    pin-info:
           --
*/

#ifndef __LOGICLAYER_H
#define __LOGICLAYER_H


/****************Libraries******************************/
#include "main.h"


/****************Defines********************************/

/****************Function Prototypes********************/

//struct for command data. The data is gathered from the UARD and parsed by the parse function.
typedef struct parsed{
	char tekst[100];
	char* font;
	uint16_t x[3];
	uint16_t y[3];
	uint8_t color;
	uint16_t width;
	uint8_t bitmapNr;
	uint16_t timeMS;
}parser;

void InterpretData(struct parsed *parsedData);


#endif// __LOGICLAYER_H
