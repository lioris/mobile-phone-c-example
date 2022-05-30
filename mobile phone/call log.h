/********************************MODULE CALL LOG******************************
In this module the CALL LOG structure and Call structure  is defined
and the functions that deal with the structures are implemented.

The Call-Log is implemented by list as Que ( MAX size is 200 calls)
the size of the que can be changed in the Call Log Defines.

In addition the Call-Log contain the number of calls in the que.

Each Call contain a pointer to a contact, the type of the call(in\out\missed call)
and the duration of the call.

contact can point to - 1. UnKnown (in the Phone Book)
					   2. Blocked (in the Phone Book)
					   3. contact in the phone book
					   4. a number with out a name ( not recognize but not block also)
**************************************************************************/

#ifndef __CALL_LOG
#define __CALL_LOG

#include "Call Log Defines.h"

#include "list.h"
#include "funcs.h"

// Statement that this structs is exist and will be include in the .c file
// to prevent redefnition
/************************************************************************/
typedef struct Contact Contact;
typedef struct PhoneBook PhoneBook ;

typedef struct Call Call;
typedef struct CallLog CallLog;
/************************************************************************/

struct Call
{
	Contact *pContact;	
	int Type;
	Pdata Info; 
};

struct CallLog
{
	List callQue;
	int numOfCalls ;
};

/**************************************************************/
//				 INITIALIZATIONS
/**************************************************************/
CallLog *initCallLog();
/**************************************************************/

/************************************************************************
Function name: freeCall
Process: free allocated memory for call, if needed the contact free too
Arguments: toFree - valid only in function , callQue - pointers to alocatated memory,
outPut: none
Return:Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int freeCall(Call * toFree, List callQue);

/************************************************************************
Function name: ShowAllCalls
Process: print all calls in the Que
Arguments: theCL - pointers to alocatated memory,
outPut: none
Return: void
************************************************************************/
void ShowAllCalls(CallLog * theCL);

/************************************************************************
Function name: NewCall
Process: insert a new call to the Calls Que
Arguments: theCL - pointers to alocatated memory,
outPut: none
Return: void
************************************************************************/
void NewCall(CallLog *theCallLog, Call* newCall); // enque

/************************************************************************
Function name: deQue
Process: delete the last call from the Calls Que
Arguments: theCL - pointers to alocatated memory,
outPut: none
Return: void
************************************************************************/
void deQue(CallLog * theCL);						 // deque

/************************************************************************
Function name: DeleteCall
Process: user chose to delete a call from the Calls Que,
		 if ther is more then one, user get a list and choose wich call to delete
Arguments: theCL - pointers to alocatated memory,
outPut: none
Return: void
************************************************************************/
void DeleteCall(CallLog * theCL); 

/************************************************************************
Function name: CallListToDelete
Process: make an arry with pointers to calls to delete.
Arguments: callQue - pointers to alocatated memory, nameToDEL - valid only in function
outPut: none
Return: arry of poiters to calls
************************************************************************/
Call ** CallListToDelete(List callQue, char * nameToDEL);

/************************************************************************
Function name: isFull
Process: check if the calls que is full
Arguments: numOfCalls - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int isFull (int numOfCalls);	
/************************************************************************
Function name: isEmpty
Process: check if the calls que is empty
Arguments: numOfCalls - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int isEmpty(int numOfCalls);

/************************************************************************
Function name: getNewCall
Process: get the number(in coming\ out going) search on the phone book 
		 if the number exist, init the contact and the call data.
		 asume the the divice know how to give some of the parmters ( in\out, date, duration),
		 we giving the parmetrs in the fucntions or taking from an ather library(time.h)
Arguments: numOfCalls - valid only in function
outPut: none
Return: the new call initalized with all the details
************************************************************************/
Call *getNewCall(char *number, PhoneBook *thePB, CallLog * theCL );

/************************************************************************
Function name: insertCall
Process: get a new call and isert it sorted by date to the list.
Arguments: newCall - valid only in function, callQue - pointers to alocatated memory
outPut: none
Return: void
************************************************************************/
void insertCall(Call *newCall, List callQue);

/************************************************************************
Function name: showCall
Process: print call details to the console
Arguments: theCall - pointers to alocatated memory
outPut: none
Return: void
************************************************************************/
void showCall(Call* theCall);

/************************************************************************
Function name: reOrganizeCallsContact
Process: coomper the contacts in the phone book with the contacts in the call que
		 if contact add recently to the PB- number is updated to contact with name in the call que
		 if contact deleted recently from the PB- contact in call que switch to UnKnown 
Arguments: theCall, thePB - pointers to alocatated memory
outPut: none
Return: void
************************************************************************/
void reOrganizeCallsContact(CallLog *theCL, PhoneBook *thePB);

#endif

