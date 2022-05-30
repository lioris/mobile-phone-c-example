#pragma warning (disable : 4996) 

#include "call log.h"
#include "phone book.h"

#include "funcs.h"
#include "list.h"
#include "eror.h"
#include "io.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

// initalize the CALL LOG
CallLog *initCallLog()
{	// allocate Memory block
	CallLog *theCallLog = (CallLog*)calloc(1, sizeof(CallLog) );
		cheakInit(theCallLog);
	// initialize the call que and the number of calls
	theCallLog->callQue = MakeEmpty(theCallLog->callQue);
	theCallLog->numOfCalls = 0;
	return theCallLog;
}
// enque new call to the list
void NewCall(CallLog *theCallLog, Call *newCall)
{   // if the list is full , delte the last one
	if( isFull(theCallLog->numOfCalls) ){
		deQue(theCallLog); 
		theCallLog->numOfCalls--;
		}
	// insert the new call sorted by date and incremnt number of calls
	insertCall(newCall,  theCallLog->callQue);	
	theCallLog->numOfCalls++;
	addSucssfuly(); // message	
}

int isFull(int numOfCalls)
{
	if(numOfCalls == QUE_SIZE)
		return QUE_FULL;
	else
		return QUE_NOT_FULL;
}

int isEmpty(int numOfCalls)
{
	if( numOfCalls == 0 )
		return QUE_EMPTY;
	else
		return QUE_NOT_EMPTY;
}

//delete the last call
void deQue(CallLog * theCL)
{	
	Call *lastCall = NULL;
	Contact  *lastContact = NULL;
	
	if( IsEmpty(theCL->callQue) )
		return ;
	// delete last call node and return the last call
	lastCall = (Call*)deleteLast(theCL->callQue);
	
	freeCall(lastCall, theCL->callQue) ;
}

int freeCall(Call * toFree, List callQue)
{
	if ( toFree == NULL ){
		return 0;
		}
	// if need free contact, mening the contact is not in the PB or its UnKnown or Blocked
	if ( toFree->pContact->Name == NULL &&  !isBlockedNumber(toFree->pContact) ){
		freeContact(toFree->pContact);
		}
	// free the data memory ( duration and date)
	free(toFree->Info);
	// delete from list(call que)
	Delete(toFree, callQue ) ;
	// free call
	free(toFree);
	return 1;
}

Call *getNewCall(char *number, PhoneBook *thePB, CallLog * theCL )
{
	int duration ;
	Call *newCall = (Call*)calloc(1, sizeof(Call) );
	if ( !cheackAllocation( newCall) )
		return NULL;
	
	// if the number the divice gave is NULL it mean the number is blocked
	if(number == NULL) 
		newCall->Type =  IN_COMING_CALL ;
	else
		newCall->Type = getType(TYPE_CALL); // get the type of the call , we asume the divice know how to mange the function ,
	// missed call mean the duratin is 0    // here its hapen with rand function 
	if( newCall->Type == MISSED_CALL )
		duration = 0;
	else 
		duration = getCallDuration();  // other wise we get the duration, agian we asume the divice know to mange the function,
									   // here its implemnted with rand function
	//set date and time;
	newCall->Info = setDate(NULL);
	//set duration
	setInfo(newCall->Info, duration, DurationMask, DuratinMove );
	// serch in the phone book if the number exist under contact name
	newCall->pContact = setContact(number, thePB);

	showCall(newCall);
	return  newCall;
}

void DeleteCall(CallLog * theCL)
{
	Call **callArr = NULL;
	char *nameToDEL = NULL;
	int index = 0 ;

	system("cls");
	if ( IsEmpty(theCL->callQue) ){
		Empty();
		return;
		}

	EnterName(); // get a name to delete
	if( (nameToDEL = getName()) == NULL)
	{
		inPutEror();
		return;
	}
	// make a arry of pointer to calls to delete
	if ( (callArr = CallListToDelete(theCL->callQue, nameToDEL)) == NULL )
	{ // not found metch calls
		NotFound();
		return;
	} // one call found, delete it instently
	else if(callArr[1] == NULL) 
	{
		freeCall(*callArr, theCL->callQue);
	}
	else // ask from the call list wich call to delete
	{
		chooseContact();
		index =  getOffSet();
		freeCall(callArr[index],  theCL->callQue );
	}
	// free the arry of pointers
	free(callArr);
	theCL->numOfCalls--;
	deletedSucssfuly();  
}

Call ** CallListToDelete(List callQue, char * nameToDEL)
{
	Call ** callArr = NULL;
	Call *retrvCall = NULL;
	int index=1;
	Contact tempC;
	tempC.Name = nameToDEL;
	tempC.PhoneNumber = nameToDEL;

	callQue = Advance(callQue);
	while( callQue ) // run on the call que
	{   // load a call 
		retrvCall = (Call*)Retrieve(callQue);
		// if the name to delete match to a number or to a numbe it insert to the arry
		if ( !comperByName(&tempC, retrvCall->pContact) || !comperByNumber(&tempC, retrvCall->pContact) )
		{
				callArr = (Call**)realloc(callArr, sizeof(Call*) * (index+1) );
					if ( !cheackAllocation(callArr) ){
						return NULL;
						}
				callArr[index-1] = retrvCall;
				printIndex(index++);
				showCall(retrvCall);
		}

		callQue = Advance(callQue) ;
	}
	// if insert at least one call end the arry with null 
	if ( index > 1)
		callArr[index-1] = NULL;
	return callArr; // return pointer to arry(if at least one inserted) or null 
}

void reOrganizeCallsContact(CallLog *theCL, PhoneBook *thePB)
{
	List callQue = theCL->callQue;
	Call *retrvCall = NULL;

	if (IsEmpty(callQue) ){
		return;
	}

	callQue = Advance(callQue);
	while(callQue) // run on call que
	{   // load a call 
		retrvCall = (Call*)Retrieve(callQue);
		// check if fix memory needed
		retrvCall->pContact = fixMemory(thePB, retrvCall->pContact);
		callQue = Advance(callQue) ;
	}
}

void showCall(Call* theCall)
{
	if( theCall->pContact->Name != NULL )
		printString(theCall->pContact->Name, TAB_NAME_SIZE);
	else
		printString(theCall->pContact->PhoneNumber, TAB_NAME_SIZE);
	printIdentification(theCall->pContact->NumberIdentification, TAB_IDENTFICATION);
	printType(theCall->Type);
	printDateAndTime(theCall->Info);
	printDuration(theCall->Info);
	NewLine();
}

void ShowAllCalls(CallLog * theCL)
{
	List callQue = Advance( theCL->callQue ); 
	Call *retrvCall = NULL;
	system("cls");
	if(callQue == NULL ){
		Empty();
		return;
		}
	
	while(callQue){
		retrvCall = (Call*)Retrieve(callQue);
		showCall(retrvCall);
		callQue = Advance( callQue );   
	}
}

void insertCall(Call *newCall, List callQue)
{
	Position nodes = callQue;
	Position nextNode = NULL;
	Call * retCall;
	// if the call que is empty insert to first and return
	if ( IsEmpty(callQue) ){
		Insert(newCall, callQue, callQue );
		return;
		}

	// look for place to insert sorted by date
	while(nodes)
	{
		if ( nextNode = Advance(nodes) )
		{   // load call
			retCall = (Call*)Retrieve(nextNode);
			// check by date
			if ( comperDate(newCall->Info , retCall->Info) == 1 )
			{	// place found , insert and return
				Insert(newCall, callQue, nodes);
				return;
			}
		}
		else
		{	// end of list reched, insert last
			Insert(newCall, callQue, nodes);
			return;
		}

		nodes = Advance(nodes);
	}
}
