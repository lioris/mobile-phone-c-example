#pragma warning (disable : 4996) 
#include "file.h"
#include "phone book.h"
#include "call log.h"
#include "text massage.h"

#include "io.h"
#include "eror.h"
#include "funcs.h"
#include"list.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saveString(FILE *fp, char *theString )
{	
	if(theString == NULL )
		fprintf(fp,"0 ");
	else
		fprintf(fp,"%d %s " ,strlen(theString), theString);
}

char* loadString(FILE *fp)
{
	int nameLen;
	char *theString;
	//name length
	fscanf(fp,"%d ", &nameLen);
	if(nameLen == 0 )
		theString = NULL;
	else
	{	//allocate memory for the name (+1 for '\0')
		theString = (char*)malloc(nameLen+1);	
			cheakInit(theString);
		//read the name	
		fgets(theString, nameLen+1, fp);		
	}

	return theString;
}

void saveInteger(FILE *fp, int integer){
	fprintf(fp,"%d ", integer);
	}

int loadInteger(FILE *fp)
{
	int integer;
	fscanf(fp,"%d ",&integer);
	return integer;
}

void saveData(FILE *fp, Pdata Info){
	fprintf(fp,"%d ", getInfoBlock(Info) );
	}

Pdata loadData(FILE *fp)
{
	int info;
	fscanf(fp,"%d ",&info);
	return  setDataBlock(info);
}

int readContactFromFile(PhoneBook * thePB, const char* filename)
{
	FILE *thePBfp = fopen(filename,"r");
	int i, j = 0;
	char theABC;
	
	if(thePBfp)	
	{				
		while(!feof(thePBfp))
		{
			// read the lex place 
			fscanf(thePBfp,"%c",&theABC);
			// calc the index
			i= getLexIndex(theABC);
			// read the number of contacts in the arry
			fscanf(thePBfp,"%d\n",&thePB->numberOfContacts[i]);
			// allocate memory for contact arry
			thePB->contactArray[i]= (Contact*)calloc(thePB->numberOfContacts[i], sizeof(Contact));
			// copy contacts
			// format-  14 Shy Avshalomov 6 123123 2
			for(j=0 ; j < thePB->numberOfContacts[i] ; j++) 
			{
				thePB->contactArray[i][j].Name = loadString(thePBfp);					// read name
				thePB->contactArray[i][j].PhoneNumber = loadString(thePBfp);			// read number
				thePB->contactArray[i][j].NumberIdentification = loadInteger(thePBfp);	// read id
				fscanf(thePBfp,"\n");
			}
		}
		fclose(thePBfp);
		return 1;
	}
	return 0;
}

int writeContactToFile(PhoneBook * thePB, const char* filename)
{
	FILE *thePBfp = fopen(filename,"w");
	int i, j = 0; // counters
	if(thePBfp)	
	{	
		for(i = 0 ; i < PHONE_BOOK_SIZE ; i++)		
		{	// check if ther is any contacts
			if(thePB->numberOfContacts[i] > 0)
			{	// save the head of the Lex name (by the first letter) and the number of contacts
				fprintf(thePBfp,"%c%d\n",*thePB->contactArray[i]->Name, thePB->numberOfContacts[i]);
				// saving the contacts 
				for(j = 0 ; j < thePB->numberOfContacts[i] ; j++) 
				{
					saveString(thePBfp, thePB->contactArray[i][j].Name);
					saveString(thePBfp, thePB->contactArray[i][j].PhoneNumber);
					saveInteger(thePBfp, thePB->contactArray[i][j].NumberIdentification);
					fprintf(thePBfp,"\n");
				}
			}	
		}
		fclose(thePBfp);
		return 1;
	}
	return 0;
}

int writeCallsToFile (CallLog * theCL, const char* filename)
{
	FILE *theCLfp = fopen(filename,"w");
	int i;
	int NumOfCalls = theCL->numOfCalls;
	List callQueList = Advance( theCL->callQue);
	Call *retrivCall = NULL;
	Contact *retrivContact = NULL;

	if(theCLfp)	
	{	// write the number of calls to head of the file
		fprintf(theCLfp,"%d\n",NumOfCalls);
		for(i = 0 ; i < NumOfCalls ; i++, callQueList = Advance( callQueList) )		
		{	// load call from list
			retrivCall = (Call*)Retrieve(callQueList);
			retrivContact = retrivCall->pContact;
			// save call details
			saveString(theCLfp, retrivContact->PhoneNumber );
			saveInteger(theCLfp, retrivCall->Type );
			saveData(theCLfp, retrivCall->Info);
			fprintf(theCLfp,"\n");
		}

		fclose(theCLfp);
		return 1;
	}
	return 0;
}

int readCallsFromFile(CallLog * theCL, PhoneBook *thePB, const char* filename)
{
	FILE *theCLfp = fopen(filename,"r");
	int i;
	Call *readCall = NULL;
	char *string = NULL;
	if(theCLfp)	
	{	// read the number of calls
		fscanf(theCLfp,"%d\n",&theCL->numOfCalls);
		for(i = 0 ; i < theCL->numOfCalls ; i++ )		
		{	// allocate memory for read call
			readCall = (Call*)calloc(1, sizeof(Call) );
			// load string from file
			string = loadString(theCLfp);
			// init call and contact call 
			readCall->pContact = setContact(string, thePB);
			readCall->Type = loadInteger(theCLfp);
			readCall->Info = loadData(theCLfp);
			fscanf(theCLfp,"\n");
			// insert to the call list
			insertCall(readCall, theCL->callQue);
		}

		fclose(theCLfp);
		return 1;
	}
	return 0;
}

int writeTextsToFile (MessageLog * theML, const char* filename)
{
	FILE *fp = fopen(filename,"w");
	List lists = Advance(theML->conversationsLists);
	conversation * oneConver;
	List theList;
	TextMessage* text;
	
	if(fp)	
	{	
		while(lists) // all converstions
		{	// load converstion -> load converstion list -> load single text message
			oneConver = (conversation*)Retrieve( lists );
			theList = Advance(oneConver->messageList);
			text = (TextMessage*)Retrieve(theList);
			// save the number of messages in the converstion and the phone number
			saveInteger(fp,oneConver->count);
			saveString(fp, text->pContact->PhoneNumber );
			fprintf(fp,"\n");
			// save the text Messages details to file
			while(theList)
			{
				text = (TextMessage*)Retrieve(theList);
				saveInteger(fp,text->Type);
				saveData(fp,text->Info);
				saveString(fp,text->content);
				fprintf(fp,"\n");
				theList = Advance(theList);
			}
			// next converstion
			lists = Advance(lists);
		}
					
	fclose(fp);
	return 1;
	}
	return 0;
}

int readTextsFromFile(MessageLog * theML,PhoneBook *thePB, const char* filename)
{
	FILE *fp = fopen(filename,"r");
	int index, count=-1;
	char *string;
	conversation * oneConver;
	TextMessage* text;
	Contact * tempC = NULL;

	if(fp)	
	{	
		while(!feof(fp))
		{	// if not read enything the file is empty
			if ( (count = loadInteger(fp)) > 0 )
			{	// init converstion module and insert it to Message Log lists
				oneConver = initConversation();
				Insert(oneConver, theML->conversationsLists, theML->conversationsLists);
				oneConver->count = count;
				// load number(string)
				string = loadString(fp);
				tempC = setContact(string, thePB); // check if contact exist
				fscanf(fp,"\n");
				// load all messages below the phone number
				for(index=0 ; index < oneConver->count ; index++)
				{
					text = (TextMessage*)calloc(1,sizeof(TextMessage));
					text->pContact = tempC;
					text->Type = loadInteger(fp);
					text->Info = loadData(fp);
					text->content = loadString(fp);
					fscanf(fp,"\n");
					insertMessage(oneConver->messageList, text);
				}
			}
		}
					
	fclose(fp);
	return 1;
	}
	return 0;
}

int writeToFiles(PhoneBook * thePB, const char* filename1,
				     CallLog * theCL, const char* filename2,
				         MessageLog * theML, const char* filename3)
			{
				if( thePB != NULL && filename1 != NULL )
					if( !writeContactToFile(thePB,filename1) )
						return 0;

				if( theCL != NULL && filename2 != NULL )
					if( !writeCallsToFile(theCL, filename2) )
						return 0;

				if( theML != NULL && filename3 != NULL )
					if( !writeTextsToFile(theML, filename3) ) 
						return 0;

				return 1;
			}

int readFiles(PhoneBook* thePB, CallLog * theCL, MessageLog * theML)
{
	if ( !readContactFromFile(thePB, PhoneBookFileName) ||
			!readCallsFromFile(theCL, thePB, CallLogFileName) ||
				!readTextsFromFile(theML, thePB, MessageLogFileName) )
						return 0;
	return 1;
}