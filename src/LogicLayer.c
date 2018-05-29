/*
Author: 	M.F. Janssen
Date:		19-05-2018
Revision:	1


    LogicLayer.c:
          Inits all needed functions

    pin-info:
           --
 */
#include "LogicLayer.h"

uint8_t lineStructFiller(struct parsed *parsedData, char* tok);
uint8_t rectangleStructFiller(struct parsed *parsedData, char* tok);
uint8_t ellipseStructFiller(struct parsed *parsedData, char* tok);
uint8_t triangleStructFiller(struct parsed *parsedData, char* tok);
uint8_t getColor(const char* color);
uint8_t textStructFiller(struct parsed *parsedData, char* tok);
uint8_t clearscreenStructFiller(struct parsed *parsedData, char* tok);
uint8_t delayStructFiller(struct parsed *parsedData, char* tok);
uint8_t bitmapStructFiller(struct parsed *parsedData, char* tok);
const char *error_msg(int code);
extern char string[100];
char str2[100];
extern volatile int charcounter;
uint8_t error = 0;


const char *error_msg(int code)
{
    switch (code) {
        ERROR_CODES(ERROR_TEXT)
    }

    return "Unknown error";
}



void InterpretData(struct parsed *parsedData)
{
	char *tok;

	char tempString[100];
	strcpy(str2, string);

	memset(tempString, 0, sizeof tempString);
	while(1){
		DELAY_ms(50);//100
		if(error > 0)
		{
			UART_printf(256, error_msg(error));
			error = 0;
		}
		memset(tempString, 0, sizeof tempString);
		tok = strtok(string, ",");
		while(tok != NULL)
		{

			strcpy(tempString,tok);
			strcpy(parsedData->text,tok);
			if(strcmp("lijn", tempString)== 0)
				error = lineStructFiller(parsedData, tok);
			else if(strcmp( "clearscherm" ,tempString)== 0)
				error = clearscreenStructFiller(parsedData, tok);
			else if(strcmp( "driehoek", tempString)== 0)
				error = triangleStructFiller(parsedData, tok);
			else if(strcmp( "ellips", tempString)== 0)
				error = ellipseStructFiller(parsedData, tok);
			else if(strcmp( "bitmap", tempString)== 0)
				error = bitmapStructFiller(parsedData, tok);
			else if(strcmp( "tekst", tempString)== 0)
				error = textStructFiller(parsedData, tok);
			else if(strcmp( "wacht", tempString)== 0)
				error = delayStructFiller(parsedData, tok);
			else if(strcmp( "rechthoek", tempString)== 0)
				error = rectangleStructFiller(parsedData, tok);
			else
			{
				charcounter = 0;
				memset(string, 0, sizeof string);
				error = 6;
				tok = strtok(NULL, ",");
			}
			tok = strtok(NULL, ",");
			memset(tempString, 0, sizeof tempString);
		}
	}

}
//@TODO rename
uint8_t lineStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t error;
	uint8_t counter = 0;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->x[0] = strtol(tok, NULL, 10);
		break;
		case 1: parsedData->y[0] = strtol(tok, NULL, 10);
		break;
		case 2: parsedData->x[1] = strtol(tok, NULL, 10);
		break;
		case 3: parsedData->y[1] = strtol(tok, NULL, 10);
		break;
		case 4: parsedData->width = strtol(tok, NULL, 10);
		break;
		case 5: parsedData->color =  getColor(tok);
		break;
		case 6: error = 7;
		break;
		default:
			break;
		}

		counter++;
	}
	charcounter = 0;
	memset(string, 0, sizeof string);
	error = UB_VGA_drawLine(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1],parsedData->width, parsedData->color);
	tok = strtok(NULL, ",");
	return error;
}

uint8_t rectangleStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t error;
	uint8_t counter = 0;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->x[0] = strtol(tok, NULL, 10);
		break;
		case 1: parsedData->y[0] = strtol(tok, NULL, 10);
		break;
		case 2: parsedData->x[1] = strtol(tok, NULL, 10);
		break;
		case 3: parsedData->y[1] = strtol(tok, NULL, 10);
		break;
		case 4: parsedData->color =  getColor(tok);
		break;
		case 5: error = 7;
		break;
		default:
			break;
		}

		counter++;
	}
	charcounter = 0;
	memset(string, 0, sizeof string);
	error = UB_VGA_drawRectangle(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1],   parsedData->color);
	return error;
}


uint8_t ellipseStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t counter = 0;
	uint8_t error;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->x[0] = strtol(tok, NULL, 10);
		break;
		case 1: parsedData->y[0] = strtol(tok, NULL, 10);
		break;
		case 2: parsedData->x[1] = strtol(tok, NULL, 10);
		break;
		case 3: parsedData->y[1] = strtol(tok, NULL, 10);
		break;
		case 4: parsedData->color = getColor(tok);
		break;
		case 5: error = 7;
		break;
		default:
			break;
		}

		counter++;
	}
	charcounter = 0;
	memset(string, 0, sizeof string);
	error = UB_VGA_drawEllipse(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1],  parsedData->color);
	return error;
}


uint8_t triangleStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t counter = 0;
	uint8_t error;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->x[0] = strtol(tok, NULL, 10);
		break;
		case 1: parsedData->y[0] = strtol(tok, NULL, 10);
		break;
		case 2: parsedData->x[1] = strtol(tok, NULL, 10);
		break;
		case 3: parsedData->y[1] = strtol(tok, NULL, 10);
		break;
		case 4: parsedData->x[2] = strtol(tok, NULL, 10);
		break;
		case 5: parsedData->y[2] = strtol(tok, NULL, 10);
		break;
		case 6: parsedData->color =  getColor(tok);
		break;
		case 7: error = 7;
		break;
		default:
			break;
		}

		counter++;
	}
	charcounter = 0;
	memset(string, 0, sizeof string);
	error = UB_VGA_drawTriangle(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1], parsedData->x[2], parsedData->y[2],  parsedData->color);
	return error;
}

uint8_t bitmapStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t error;
	uint8_t counter = 0;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->bitmapNr = strtol(tok, NULL, 10);//voeg nummer toe aan bitmap
		break;
		case 1: parsedData->x[0] = strtol(tok, NULL, 10);
		break;
		case 2: parsedData->y[0] = strtol(tok, NULL, 10);
		break;
		case 3: error = 7;
		break;
		default:
			break;
		}

		counter++;
	}
	charcounter = 0;
	memset(string, 0, sizeof string);
	error = Draw_Bitmap(parsedData->bitmapNr,parsedData->x[0], parsedData->y[0]);
	return error;
}

uint8_t textStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t error;
	uint8_t counter = 0;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->x[0] = strtol(tok, NULL, 10);
		break;
		case 1: parsedData->y[0] = strtol(tok, NULL, 10);
		break;
		case 2: strcpy(parsedData->text,tok);
		break;
		case 3: parsedData->color =  getColor(tok);
		break;
		case 4: error = 7;
		break;
		default:
			break;
		}
//tekst
		counter++;
	}
	charcounter = 0;
	memset(string, 0, sizeof string);
	error = Draw_Text(parsedData->x[0] , parsedData->y[0],parsedData->text , parsedData->color);
	return error;
}


uint8_t delayStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t error;
	uint8_t counter = 0;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->timeMS = strtol(tok, NULL, 10);
		break;
		case 1: error = 7;
		break;
		default:
			break;
		}
		counter++;
	}
//	charcounter = 0;
//	memset(string, 0, sizeof string);
	error = DELAY_ms(parsedData->timeMS);
	return error;
}

uint8_t clearscreenStructFiller(struct parsed *parsedData, char* tok)
{
	uint8_t error;
	uint8_t counter = 0;
	while(tok != NULL)
	{
		tok = strtok(NULL, ",");

		switch(counter)
		{
		case 0: parsedData->color =  getColor(tok);
		break;
		case 1: error = 7;
		break;
		default:
			break;
		}
		counter++;
	}
	charcounter = 0;
	memset(string, 0, sizeof string);
	error = UB_VGA_FillScreen(parsedData->color);
	return error;
}

uint8_t getColor(const char* color)
{
	if(strcmp("rood", color)== 0)
		return VGA_COL_RED;
	else if(strcmp("blauw", color)== 0)
		return VGA_COL_BLUE;
	else if(strcmp("groen", color)== 0)
		return VGA_COL_GREEN;
	else if(strcmp("zwart", color)== 0)
		return VGA_COL_BLACK;
	else if(strcmp("wit", color)== 0)
		return VGA_COL_WHITE;
	else if(strcmp("cyaan", color)== 0)
		return VGA_COL_CYAN;
	else if(strcmp("magenta", color)== 0)
		return VGA_COL_MAGENTA;
	else if(strcmp("geel", color)== 0)
		return VGA_COL_YELLOW;
	else if(strcmp("lichtblauw", color)== 0)
		return VGA_COL_LBLUE;
	else if(strcmp("lichtgroen", color)== 0)
		return VGA_COL_LGREEN;
	else if(strcmp("lichtrood", color)== 0)
		return VGA_COL_LRED;
	else if(strcmp("lichtcyaan", color)== 0)
		return VGA_COL_LCYAN;
	else if(strcmp("lichtmagenta", color)== 0)
		return VGA_COL_LMAGENTA;
	else if(strcmp("bruin", color)== 0)
		return VGA_COL_BROWN;
	else if(strcmp("grijs", color)== 0)
		return VGA_COL_GREY;
	else if(strcmp("roze", color)== 0)
		return VGA_COL_PINK;
	else if(strcmp("paars", color)== 0)
		return VGA_COL_PURPLE;
	else return 0;

}
