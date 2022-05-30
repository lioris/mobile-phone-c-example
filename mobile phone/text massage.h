/***************************MODULE TEXT MESSAGES LOG******************************
In this module the TEXT MESSAGES LOG structure,  Converstion structure and
Text Message structure is defined and the functions that deal with the
structures are implemented.

The TEXT MESSAGES LOG is implemented by list that contain list for each converstion.

in my implemention i added the Converstion structure that in addition to the converstion 
list is contain the number of messages.

Message Log ->all converstions (in a list)
one converstion -> list and counter

Each Text Message contain a pointer to a contact, the type of the Message(in\out)
and the content of message.

contact can point to - 1. UnKnown (in the Phone Book)
					   2. Blocked (in the Phone Book)
					   3. contact in the phone book
					   4. a number with out a name ( not recognize but not block also)
**************************************************************************/
#ifndef __TEXT_MASSAGE
#define __TEXT_MASSAGE

#include "list.h"
#include "funcs.h"



#define IN_COMING_MESSAGE 0
#define OUT_GOING_MESSAGE 1

#define MAX_CHARACTERS 100
#define NOT_FOUND 0

// Statement that this structs is exist and will be include in the .c file
// to prevent redefnition
/************************************************************************/
typedef struct Contact Contact;
typedef struct PhoneBook PhoneBook ;

typedef struct TextMessage TextMessage;
typedef struct conversation conversation;
typedef struct MessageLog MessageLog;
/************************************************************************/

struct TextMessage 
{
	Contact *pContact;
	int Type;
	Pdata Info; // send recive time
	char *content;
};

struct conversation
{
	List messageList; // elmentType - textMessges
	int count; 
};

struct MessageLog
{
	List conversationsLists; // elmentype - converstion
};

/**************************************************************/
//				 INITIALIZATIONS
/**************************************************************/
MessageLog* initMessageLog();
conversation* initConversation();
/**************************************************************/
/************************************************************************
Function name: freeMessage
Process: free the message allocated memory, free the data allocated memory 
			  and if needed free the contact allocated memory
Arguments: toFree - valid only in function,  list - pointers to alocatated memory,
outPut: none 
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int freeMessage(TextMessage * toFree, List list);

/************************************************************************
Function name: getNewMessage
Process: get a new message details ( number, type(in-coming\out-going), date and content)
		 and initalize it to text message.
		 also look if the numer exist in phone book.
Arguments: number - valid only in function , thePB - pointers to alocatated memory,
outPut: none 
Return: the new message
************************************************************************/
TextMessage * getNewMessage(char *number, PhoneBook * thePB);

/************************************************************************
Function name: insertMessage
Process: insert the new message to the module 
		 if converstion with contact exist the message insert ther sorted by date.
		 if converstion not exist, creat new converstion and insert
Arguments: list, newTxT - pointers to alocatated memory,
outPut: none 
Return: void
************************************************************************/
void insertMessage( List list, TextMessage *newTxT);
void NewMessage(MessageLog * theML, TextMessage * TheMessage);
conversation* findConversationList(List conversationLists, Contact *pContact);
int isTheList(List list, Contact * pContact);

/************************************************************************
Function name: reOrganizeMessageContact
Process: coomper the contacts in the phone book with the contacts in the Message Log
		 if contact added recently to the PB- number is updated to contact with name 
		 if contact deleted recently from the PB- contact is switch to UnKnown 
Arguments: theML, thePB - pointers to alocatated memory
outPut: none
Return: void
************************************************************************/
void reOrganizeMessageContact(MessageLog *theML, PhoneBook* thePB);


///////////////////////////////////////////////////////////////////////
//					PRINTING FUNCTIONS					// CAN BE MOVED TO IO MOUDULE				
///////////////////////////////////////////////////////////////////////
/************************************************************************
Function name: ShowRecentMessages
Process: go throw all converstions and print the recent message to the console
Arguments: theML - pointers to alocatated memory,
outPut: none 
Return: void
************************************************************************/
void ShowRecentMessages(MessageLog * theML);

/************************************************************************
Function name: ShowConversation
Process: look for spesfic converstion with contact and if found show it to the console
Arguments: theML - pointers to alocatated memory,
outPut: none 
Return: void
************************************************************************/
void ShowConversation(MessageLog * theML);

/************************************************************************
Function name: showAll
Process: get a list with messages and show all of the messages to the console 
Arguments: list - pointers to alocatated memory,
outPut: none 
Return: void
************************************************************************/
void showAll(List list);

/************************************************************************
Function name: showMessage
Process: show one message details to the console
Arguments: message - pointers to alocatated memory,
outPut: none 
Return: void
************************************************************************/
void showMessage(TextMessage* message);

#endif


