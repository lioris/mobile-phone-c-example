/********************************MODULE IO*********************************
In this module you can find the functions that prints the menus
and the data to the consol.
**************************************************************************/
#ifndef __IO_H
#define __IO_H
#pragma warning (disable : 4996) 

#include "io Defines.h" // contain al the constants of the i\o module
#include "funcs.h"
//------------------------------//
//			Menus
//------------------------------//
void MainMenu();
void ContactsMenu();
void CallLogMenu();
void MessageLogMenu();
//**********************************************************//


//------------------------------//
//			Out-Put
//------------------------------//
void inPutEror();
void initErr(char * string);	
void printString( char* string, int TabSize );
void printEndOfProgram();
void NewLine();
void NotFound();
void Empty();
void EnterString();
void EnterName();
void EnterNumber();
void deletedSucssfuly();
void addSucssfuly();
int cheackLegalName(char *Name);

// phone book
void printSerchTitle();
void ContactExist();
void printIdentification(int NumberIdentification, int TabSize );
void printPBlistTitle();
void printLexIndex(char LexIndex);
void printEnumrated(int index);

// call log
void printDuration(Pdata CallInfo);

// massage
void converstionTitle();
void serchConverstion();
void RecentMessagesTitle();
void MesageTabTitle();

// massage and call
void printType(int callType);
void printDateAndTime(Pdata Info);
void chooseContact();
void printIndex(int index);
//**********************************************************//

//------------------------------//
//			In-Put
//------------------------------//
int getOperation();
char *getString(int max);
char*getName(); 
char*getNumber();
int getOffSet();

// phone book
int getIdentification();

// call and message
int getCallDuration();
struct tm * getDate();
int getType(int type);

//**********************************************************//


#endif


