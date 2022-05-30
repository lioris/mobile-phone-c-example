#include "text massage.h"
#include "phone book.h"
#include "funcs.h"
#include "io.h"
#include "eror.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
// initalize the Message-Log
MessageLog* initMessageLog(  )
{	// allocate Memory block
	MessageLog * TheML = (MessageLog*)calloc( 1, sizeof(MessageLog) );
		cheakInit(TheML);
	// initialize the list
	TheML->conversationsLists = MakeEmpty(NULL);
	return TheML;
}

conversation* initConversation()
{	// allocate Memory block
	conversation * theConver = (conversation*)malloc( sizeof(conversation) ) ;
	cheakInit(theConver);
	// initialize the list and the number of TxT messages
	theConver->messageList = MakeEmpty(NULL);
	theConver->count = 0;

	return theConver;
}

TextMessage * getNewMessage(char *number, PhoneBook * thePB)
{
	TextMessage *newMessage = (TextMessage*)calloc(1, sizeof(TextMessage) );
	if ( !cheackAllocation( newMessage) )
		return NULL;
	
	// if the number the divice gave is NULL it mean the number is blocked
	if(number == NULL)
		newMessage->Type =  IN_COMING_MESSAGE ;
	else
		newMessage->Type = getType(TYPE_MESSAGE); // get the type of the call , we asume the divice know how to mange the function ,
												  // here its hapen with rand function 
	//set date and time;
	newMessage->Info = setDate(NULL);
	// set the message to the contact metch ( contact PB, UnKnown, Blocked, Regular).
	newMessage->pContact = setContact(number ,thePB);
	// get the TxT message content
	MesageTabTitle();
	newMessage->content = getString(MAX_CHARACTERS);

	showMessage(newMessage);
	return  newMessage;
}

void showMessage(TextMessage* message)
{
	if( message->pContact->Name != NULL )
		printString(message->pContact->Name, TAB_NAME_SIZE);
	else
		printString(message->pContact->PhoneNumber, TAB_NAME_SIZE);
	printIdentification(message->pContact->NumberIdentification, TAB_IDENTFICATION);
	printType(message->Type);
	printDateAndTime(message->Info);
	printString(message->content, TAB_MESSAGE_TAB);
	NewLine();
}

void NewMessage(MessageLog * theML, TextMessage * TheMessage)
{
	List converLists = theML->conversationsLists;
	conversation* theConver = NULL;
	// serch for converstion that metch to the contact
	if( (theConver = findConversationList(converLists, TheMessage->pContact)) == NULL)
	{	// not found - init new converstion and insert to the message log
		theConver = initConversation();
		Insert(theConver, converLists, converLists);
	}
	// insert sorted by date
	insertMessage(theConver->messageList, TheMessage); 
	theConver->count++;
	addSucssfuly();
}

void insertMessage( List list, TextMessage *newTxT)
{
	Position nodes = list;
	Position nextNode = NULL;
	TextMessage * retTxT = NULL;
	
	if ( IsEmpty(list) ){
		Insert(newTxT, list, list );
		return;
		}

	while(nodes)
	{
		if ( nextNode = Advance(nodes) )
		{	// load TxT message
			retTxT = (TextMessage*)Retrieve(nextNode);
			// comper by date
			if ( comperDate(newTxT->Info , retTxT->Info) == 1 )
			{	
				Insert(newTxT, list, nodes);
				return;
			}
		}
		else
		{	// end of list reched - insert last
			Insert(newTxT, list, nodes);
			return;
		}

		nodes = Advance(nodes);
	}
}

conversation* findConversationList(List conversationLists,  Contact * pContact )
{
	List lists = Advance( conversationLists );
	conversation *theConver = NULL;
	
	if ( IsEmpty(conversationLists) ){
		Empty();
		return NULL;
		}

	while( lists )
	{
		theConver = (conversation *)Retrieve(lists);
		
		if ( isTheList(theConver->messageList, pContact) )
			return theConver;

		lists = Advance(lists);
	}
	return NULL;
}

int isTheList(List list, Contact * pContact)
{
	List nodes;
	TextMessage *theTM;
	Contact * tempC;
	if( (nodes = Advance(list)) == NULL)
		return  0;

	while(nodes)
	{
		theTM = (TextMessage*)Retrieve(nodes);
		tempC = theTM->pContact;

		if( comperIdentity(pContact, tempC ) == 1 ) 
			return 1;
		nodes = Advance(nodes);
	}

	return 0;
}

void ShowRecentMessages(MessageLog * theML) 
{
	List lists = Advance(theML->conversationsLists);
	conversation* oneConversation = NULL;
	List messagesList;
	TextMessage * firstMessage = NULL;
	

	if( IsEmpty(theML->conversationsLists) ){
		Empty();
		return ;
		}

	RecentMessagesTitle(); 

	while (lists)
	{	
		oneConversation = (conversation*)Retrieve(lists);			// load conversation
		messagesList = (List)Advance(oneConversation->messageList); // load messages list
		firstMessage = (TextMessage*)Retrieve(messagesList);		// load the message
		showMessage(firstMessage);
		
		lists = Advance(lists);
	}
}

void ShowConversation(MessageLog * theML)
{
	List *listArr = NULL ;
	int index = 0;
	List allLists = Advance(theML->conversationsLists) ;
	conversation* oneList = NULL;
	List messageList;
	TextMessage * retText = NULL;
	char * name = NULL;

	if( IsEmpty(theML->conversationsLists) ){
		Empty();
		return ;
		}
	
	system("cls");
	serchConverstion();
	EnterString();
	if ( (name = getString(MAX_NAME)) == NULL ){
		initEror("name");
		return;
		}

	while( allLists ) // can modified to function
	{	
		oneList = (conversation*)Retrieve(allLists);		// load converstion
		messageList = (List)Advance(oneList->messageList);  // load messages list
		retText = (TextMessage*)Retrieve(messageList);		// load single message
		// if the name is apart of the contact name - insert to arr of pointers to lists
		if( partialNameComperator(retText->pContact->Name, name) == 0 )
		{
			listArr = (List*)realloc(listArr, sizeof(List) * (index+1) );
			if ( !cheackAllocation(listArr) )
				return;
			listArr[index++] = oneList->messageList;
			printIndex(index);
			showMessage(retText);
		}

		allLists = Advance(allLists);
	}
	
	if ( index == NOT_FOUND ) 
		return;
	else if(index == 1)  // one converstion found - show it
	{
		messageList = *listArr;
	}
	else // ask for wich converstion to show from a list of converstion that found
	{
		flushall();
		chooseContact();
		index =  getOffSet();
		messageList = listArr[index];	
	}
	// show converstion
	converstionTitle();
	showAll(messageList);
	free(listArr);
}

void showAll(List list) // show converstion (show a list of messages
{
	List tempList = Advance(list);
	TextMessage *textM;

	if( IsEmpty(list) ){
		Empty();
		return;
		}
	
	while(tempList)
	{
		textM = (TextMessage*)Retrieve(tempList);
		showMessage(textM);
		tempList = Advance(tempList);
	}
}


void reOrganizeMessageContact(MessageLog *theML, PhoneBook* thePB)
{
	List lists = Advance(theML->conversationsLists);
	conversation * oneConver = NULL;
	List theList;
	TextMessage* text = NULL;

	while(lists)
	{   // load converstion
		oneConver = (conversation*)Retrieve( lists );
		// load messages list
		theList = Advance(oneConver->messageList);

		while(theList)
		{
			// load TxT Message
			text = (TextMessage*)Retrieve(theList);
			// check if contact need to fix memory
			text->pContact = fixMemory(thePB, text->pContact);

			theList = Advance( theList ) ;
		}
		lists = Advance(lists);
	}
}

int freeMessage(TextMessage * toFree, List list)
{
	if ( toFree == NULL ){
		return 0;
		}
	// if need free contact
	if ( toFree->pContact->Name == NULL &&  !isBlockedNumber(toFree->pContact) ){
		freeContact(toFree->pContact);
		}
	free(toFree->Info);
	// dekte from list
	Delete(toFree, list ) ;
	// free call
	free(toFree);
	return 1;
}


