#pragma warning (disable : 4996) 

#include "phone book.h"
#include "call log.h"
#include "text massage.h"

#include "list.h"
#include "eror.h"
#include "io.h"
#include "funcs.h"
#include "file.h"

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void operationProgram(PhoneBook* thePB, CallLog * TheCL, MessageLog * TheML);
int contactOperation(PhoneBook* thePB, CallLog * TheCL,  MessageLog * TheML, int *opCount);
int CallOperation(CallLog * theCL, PhoneBook* thePB, int *opCount);
int MessageOperation(MessageLog * theML, PhoneBook* thePB, int *opCount);

void closeProgram(PhoneBook* thePB, CallLog * theCL, MessageLog * theML);
int freeAll(PhoneBook* thePB, CallLog * theCL,  MessageLog * theML);
int   freePB(PhoneBook* thePB);
int   freeCL(CallLog * theCL);
int freeML( MessageLog * theML);

void main()
{
	int i=0;
	PhoneBook* thePB = initPB();
	CallLog * theCL  = initCallLog();
	MessageLog * theML = initMessageLog();

	if ( !readFiles(thePB, theCL, theML) )
		exit(1);

	operationProgram(thePB, theCL, theML);
	
	printEndOfProgram();
	system("pause");
}




//////////////////////////////////////////////////////////////////////////////////////
void closeProgram(PhoneBook* thePB, CallLog * theCL, MessageLog * theML)
{
	if ( !writeToFiles(thePB, PhoneBookFileName,
					     theCL, CallLogFileName,
							 theML, MessageLogFileName) )
									{
										fcloseall();
										exit(1);
									}

	freeAll( thePB, theCL, theML );
}
//////////////////////////////////////////////////////////////////////////////////////
//				OPERATION PROGRAM
//////////////////////////////////////////////////////////////////////////////////////
void operationProgram( PhoneBook* thePB, CallLog * theCL, MessageLog * theML )
{
	char operation;
	int opCount=0;

	do{
		MainMenu();
		operation = getOperation();
		switch(operation)
		{
		case '1':
			contactOperation(thePB, theCL, theML, &opCount);
			break;
		case '2':
			CallOperation(theCL, thePB, &opCount);
			break;
		case '3':
			MessageOperation(theML, thePB, &opCount);
			break;
		case '4':
			closeProgram(thePB, theCL, theML);
			return;
		default: 
			inPutEror();
		}

		if(++opCount == WRITE_TO_FILES)
		{
			writeToFiles(thePB, PhoneBookFileName, theCL, CallLogFileName, theML, MessageLogFileName);
			opCount = 0;
		}
	}while(1);
}
//////////////////////////////////////////////////////////////////////////////////////
//			CONTACT OPERATION
//////////////////////////////////////////////////////////////////////////////////////
int contactOperation(PhoneBook* thePB, CallLog * theCL,  MessageLog * theML, int *opCount)
{
	char operation;
	
	List list;
	Contact * Arr;

	do{
		ContactsMenu();
		operation = getOperation();
		switch(operation)
		{
		case '1':
			list = FindContact(NULL,thePB, FullNameComperator);
			printContactList( Advance(list) , NULL, 1);
			DeleteList(list);
			break;
		case '2':
			list = FindContact(NULL,thePB, partialNameComperator);
			printContactList( Advance(list) ,NULL,1);
			DeleteList(list);
			break;
		case '3':
			printPhoneBook(thePB);
			break;
		case '4':
			Arr = AddNewContact(thePB);
			if( Arr != NULL ){
			reOrganizeCallsContact(theCL, thePB);
			reOrganizeMessageContact(theML, thePB);
			}
			free(Arr);
			break;
		case '5':
			Arr = DeleteContact(thePB);
			reOrganizeCallsContact(theCL, thePB);
			reOrganizeMessageContact(theML, thePB);
			free(Arr);
			break;
		case '6':
			return *opCount; 
		default: 
			inPutEror();
		}
		system("pause");
		
		if( ++(*opCount) == WRITE_TO_FILES)
		{
			writeToFiles(thePB, PhoneBookFileName, theCL, CallLogFileName, theML, MessageLogFileName);
			*opCount = 0;
		}
	}while(1);
}

//////////////////////////////////////////////////////////////////////////////////////
//			CALL OPERATION
//////////////////////////////////////////////////////////////////////////////////////
int CallOperation(CallLog * theCL, PhoneBook* thePB, int *opCount)
{
	char operation;
	Call *newCall = NULL;
	char *number;

	do{
		CallLogMenu();
		operation = getOperation();
		system("cls");
		switch(operation)
		{
		case '1':
			ShowAllCalls(theCL);
			break;
		case '2':
			EnterNumber();
			number = getNumber();
			if ( ( newCall = getNewCall(number, thePB, theCL) ) )
				NewCall( theCL, newCall );
			break;
		case '3':
			DeleteCall(theCL);
			break;
		case '4':
			return *opCount; 
		default: 
			inPutEror();
		}
		system("pause");

		if(++(*opCount) == WRITE_TO_FILES)
		{
			writeToFiles(thePB, PhoneBookFileName, theCL, CallLogFileName, NULL, NULL);
			*opCount = 0;
		}
	}while(1);

}

//////////////////////////////////////////////////////////////////////////////////////
//			MESSAGE OPERATION
//////////////////////////////////////////////////////////////////////////////////////
int MessageOperation(MessageLog * theML, PhoneBook* thePB, int *opCount)
{
	char operation;
	TextMessage * newMessage = NULL;
	char * number = NULL;

	do{
		MessageLogMenu();
		operation = getOperation();
		switch(operation)
		{
		case '1':
			ShowRecentMessages(theML);
			break;
		case '2':
			system("cls");
			EnterNumber();
			number = getNumber();
			newMessage = getNewMessage(number, thePB);
			NewMessage(theML, newMessage);
			break;
		case '3':
			ShowConversation(theML);
			break;
		case '4':
			return *opCount; 
		default: 
			inPutEror();
		}
		system("pause");

		if(++(*opCount) == WRITE_TO_FILES)
		{
			writeToFiles(thePB, PhoneBookFileName, NULL, NULL, theML, MessageLogFileName);
			*opCount = 0;
		}
	}while(1);
}

/////////////////////////////////////////////////////////////////////////


int freeAll(PhoneBook* thePB, CallLog * theCL,  MessageLog * theML)
{
	
	if ( !freeCL(theCL) ||
		  !freeML(theML) ||
		   !freePB(thePB) )
			return 0;
	return 1;
}

int     freePB(PhoneBook* thePB)
{
	int i,j;
	Contact *Arr = NULL;
	int NumOfCont = 0;

	if( thePB == NULL )
		initEror("The Phone Book");

	for(i=0 ; i < PHONE_BOOK_SIZE ; i++)
	{
		Arr		  = thePB->contactArray[i];
		NumOfCont = thePB->numberOfContacts[i];

		for(j=0 ; j<NumOfCont ; j++)
		{
			freeName(&Arr[j]);
			freeNumber(&Arr[j]);
		}
		if( Arr != NULL )
			free(Arr);
	}
	free(thePB->Blocked);
	free(thePB->unknown);
	return 1;
}

int freeCL(CallLog * theCL)
{
	Position callQue = theCL->callQue;
	Call * retCall = NULL;

	if( IsEmpty(callQue) ){// cheaks the next one
		Empty();
		if ( callQue != NULL ) // cheak the head
			free(callQue);
		return 1;
	}
	
	callQue = Advance(callQue);
	while(callQue)
	{
		retCall = (Call*)Retrieve(callQue);
		callQue = Advance(callQue);
		freeCall(retCall,theCL->callQue);
	} 
	free(theCL->callQue);
	return 1;
}

int freeML( MessageLog * theML)
{
	List allConverstions = theML->conversationsLists;
	conversation * headConverstion = NULL;
	List converstionList;
	TextMessage * tempM = NULL;

	if ( IsEmpty(allConverstions) )
	{
		Empty();
		if(allConverstions != NULL)
			free(allConverstions);
		return 1;
	}

	allConverstions = Advance( allConverstions );
	while(allConverstions)
	{
		headConverstion = (conversation*)Retrieve(allConverstions);
		converstionList = Advance( headConverstion->messageList );
		
		while(converstionList)
		{
			tempM = (TextMessage*)Retrieve(converstionList);
			converstionList = Advance( converstionList );
			freeMessage(tempM, headConverstion->messageList);
		}

		allConverstions = Advance( allConverstions );
		Delete(headConverstion, theML->conversationsLists );
	}
	if(allConverstions != NULL)
		free(allConverstions);
	return 1;
}