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
extern char string[100];
char str2[100];

void InterpretData(struct parsed *parsedData)
{
	char tempString[100];
	strcpy(str2, string);
	//UART_printf(sizeof(str2), str2);
	memset(tempString, 0, sizeof tempString);
	char *tok = strtok(string, ",");
	while(tok != NULL)
	{
		strcpy(tempString,tok);
		strcpy(parsedData->text,tok);
		if(strcmp(tempString,"lijn")== 0)
			lineStructFiller(parsedData, tok);
		else if(strcmp( "clearscherm" ,tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "driehoek", tempString)== 0)
			triangleStructFiller(parsedData, tok);
		else if(strcmp( "ellips", tempString)== 0)
			ellipseStructFiller(parsedData, tok);
		else if(strcmp( "bitmap", tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "tekst", tempString)== 0)
			textStructFiller(parsedData, tok);
		else if(strcmp( "wacht", tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "rechthoek", tempString)== 0)
			rectangleStructFiller(parsedData, tok);
		else
			UART_printf(256, "error\n");
		//memset(tempString, 0, sizeof tempString);
		memset(string, 0, sizeof string);
		tok = strtok(NULL, ",");
	}

}
//@TODO rename
uint8_t lineStructFiller(struct parsed *parsedData, char* tok)
{
	//char *tok = strtok(string, " ,.-");
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
		default:
			break;
		}

		counter++;
	}
	UB_VGA_drawLine(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1],parsedData->width, parsedData->color);
	return 1;
}

uint8_t rectangleStructFiller(struct parsed *parsedData, char* tok)
{
	//char *tok = strtok(string, " ,.-");
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
		default:
			break;
		}

		counter++;
	}
	UB_VGA_drawRectangle(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1],  VGA_COL_BLUE);
	return 1;
}


uint8_t ellipseStructFiller(struct parsed *parsedData, char* tok)
{
	//char *tok = strtok(string, " ,.-");
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
		case 4: parsedData->color = getColor(tok);
		break;
		default:
			break;
		}

		counter++;
	}
	UB_VGA_drawEllipse(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1],  parsedData->color);
	return 1;
}


uint8_t triangleStructFiller(struct parsed *parsedData, char* tok)
{
	//char *tok = strtok(string, " ,.-");
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
		case 4: parsedData->x[2] = strtol(tok, NULL, 10);
		break;
		case 5: parsedData->x[4] = strtol(tok, NULL, 10);
		break;
		case 6: parsedData->color =  getColor(tok);
		break;
		default:
			break;
		}

		counter++;
	}
	UB_VGA_drawTriangle(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1], parsedData->x[2], parsedData->y[3],  parsedData->color);
	return 1;
}

uint8_t bitmapStructFiller(struct parsed *parsedData, char* tok)
{
	//char *tok = strtok(string, " ,.-");
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
		default:
			break;
		}

		counter++;
	}
	// bitmap UB_VGA_drawTriangle(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1], parsedData->x[2], parsedData->y[3],  parsedData->color);
	//Draw_Bitmap(uint8_t *image,parsedData->x[0], parsedData->y[0]);
	return 1;
}

uint8_t textStructFiller(struct parsed *parsedData, char* tok)
{
	//char *tok = strtok(string, " ,.-");
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
		default:
			break;
		}
//tekst
		counter++;
	}
	Draw_Text(parsedData->x[0] , parsedData->y[0],parsedData->text , parsedData->color);
	return 1;
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
	else return 0;

}
