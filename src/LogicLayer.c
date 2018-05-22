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

extern char string[100];
char str2[100];
/////////////////////////////


//char ** parse(char buffer){
//  uint8_t count=0;
//  char *ptr;
//  static char *return_buff[20];
//  ptr= strtok(buffer,",\n");
//  return_buff[count]=ptr;
//  while( ptr != NULL ) {
//    ptr = strtok(NULL, ",\n");
//    count++;
//    return_buff[count]=ptr;
//    }
//  return return_buff;
//
//}
//////////
void InterpretData(struct parsed *parsedData)
{
	uint8_t counter = 0;
	char tempString[100];
	strcpy(str2, string);
	//UART_printf(sizeof(str2), str2);
	memset(tempString, 0, sizeof tempString);
	char *tok = strtok(string, ",");
	while(tok != NULL)
	{
		strcpy(tempString,tok);
		strcpy(parsedData->tekst,tok);
		if(strcmp(tempString,"lijn")== 0)
			lineStructFiller(parsedData, tok);
		else if(strcmp( "clearscherm" ,tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "driehoek", tempString)== 0)
			UART_printf(sizeof(string), string);
		else if(strcmp( "ellips", tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "bitmap", tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "tekst", tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "wacht", tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else if(strcmp( "rechthoek", tempString)== 0)
			UART_printf(sizeof(tempString), tempString);
		else
			UART_printf(256, "error\n");
		memset(tempString, 0, sizeof tempString);
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
		case 5: parsedData->color = strtol(tok, NULL, 10);
		break;
		default:
		break;
		}

		counter++;
	}
UB_VGA_drawLine(parsedData->x[0], parsedData->y[0], parsedData->x[1], parsedData->y[1],  VGA_COL_BLUE,parsedData->width);
return 1;
}
