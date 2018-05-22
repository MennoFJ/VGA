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



extern char string[100];


void InterpretData(struct parsed *parsedData)
{
	char *tok = strtok(string, " ,.-");
	int counter = 0;
	while(tok != NULL)
	{
//		switch(counter)
//		{
//			case 0: parser.shape = strtol(tok, NULL, 10);
//			break;
//			case 1: parser.X = strtol(tok, NULL, 10);
//			break;
//			case 2: parser.Y = strtol(tok, NULL, 10);
//			break;
//			case 3: strcpy(parser.K,tok);
//			break;
//		}
		counter++;
		tok = strtok(NULL, " ,.-");
	}


}
