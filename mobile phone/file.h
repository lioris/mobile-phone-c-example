/********************************MODULE FILE****************************
In this module you can find the functions that read Contacts, calls list 
and mesaages lists data from the data files and writes data to the data files. 
Each of the functions get a file name, opens the file, works with the 
file and closes the file.

1. PhoneBook.txt  
 format - firstLetter(char)numberOfContacts(int) \n nameLen(int) name(string) numberLen(int) number(string) id(int)
 exp - "L1 \n 13 Lior Israelov 10 0546916671 1" 

2. call Log.txt
 format - first number of calls(int)
		  calls -"numberLen(int) number(string) type(int) data(unsigend int) 	
		  exp - "1"
			    "10 0578182134 2 610095 "

3. Message Log.txt
 format - count(int) numberLen(int) number(string) 
 list of messages - type(int) data(unsigend int) contentLen(int) content(string)
 exp -  "1 5 #3131 "
		"1 30505 4 mes4 "
**************************************************************************/

#ifndef __FILE
#define __FILE
#include <stdio.h>
#include "funcs.h"

#define PhoneBookFileName "PhoneBook.txt"
#define CallLogFileName "Call Log.txt"
#define MessageLogFileName "Message Log.txt"

// Statement that this structs is exist and will be include in the .c file
// to prevent redefnition
/************************************************************************/
typedef struct Contact Contact;
typedef struct PhoneBook PhoneBook ;

typedef struct Call Call;
typedef struct CallLog CallLog;

typedef struct TextMessage TextMessage;
typedef struct conversation conversation;
typedef struct MessageLog MessageLog;
/************************************************************************/

/************************************************************************
Function name: saveString
Process: save a string to file
Arguments: fp - valid only in function, theString - pointer to alocatated memory
outPut: none
Return: void
************************************************************************/
void saveString(FILE *fp, char* theString);

/************************************************************************
Function name: loadString
Process: load a string from file and allocate memory
Arguments: fp - valid only in function
outPut: none
Return: adrress to the beginning of the string
************************************************************************/
char* loadString(FILE *fp);

/************************************************************************
Function name: saveInteger
Process: save an integer to file
Arguments: fp, integer - valid only in function
outPut: none
Return: void
************************************************************************/
void saveInteger(FILE *fp, int integer);

/************************************************************************
Function name: loadInteger
Process: load an Integer from file
Arguments: fp - valid only in function
outPut: none
Return: the read integer
************************************************************************/
int loadInteger(FILE *fp);

/************************************************************************
Function name: saveData
Process: save the data block to file
Arguments: fp - valid only in function, CallInfo - pointer to alocatated memory
outPut: none
Return: void
************************************************************************/
void saveData(FILE *fp, Pdata CallInfo);

/************************************************************************
Function name: loadData
Process: load Data block from file and allocate memory
Arguments: fp - valid only in function
outPut: none
Return: the read data block
************************************************************************/
Pdata loadData(FILE *fp);


/************************************************************************
Function name: writeContactToFile
Process: save contacts in the Phone Book to File
Arguments: thePB - pointer to alocatated memory , filename - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int writeContactToFile(PhoneBook * thePB, const char* filename);

/************************************************************************
Function name: readContactFromFile
Process: load contacts from the File to thePB moudule
Arguments: thePB - pointer to alocatated memory , filename - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int readContactFromFile (PhoneBook * thePB, const char* filename);

/************************************************************************
Function name: writeCallsToFile
Process: save the call list to file, (the head of file contain the
		 number of calls).
Arguments: theCL - pointer to alocatated memory , filename - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int writeCallsToFile (CallLog * theCL, const char* filename);

/************************************************************************
Function name: readCallsFromFile
Process: load the call list from file, (the head of file contain the
		 number of calls).
Arguments: theCL - pointer to alocatated memory , filename - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int readCallsFromFile(CallLog * theCL, PhoneBook *thePB, const char* filename);

/************************************************************************
Function name: writeTextsToFile
Process: save the text messages lists to file.
Arguments: theML - pointer to alocatated memory , filename - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int writeTextsToFile (MessageLog * theML, const char* filename);

/************************************************************************
Function name: readTextsFromFile
Process: load the text messages lists from file.
Arguments: theML - pointer to alocatated memory , filename - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int readTextsFromFile(MessageLog * theML,PhoneBook *thePB, const char* filename);

/************************************************************************
Function name: readFiles
Process: read all 3 files together.
Arguments: thePB, theCL, theML - pointer to alocatated memory 
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int readFiles(PhoneBook* thePB, CallLog * theCL, MessageLog * theML);

/************************************************************************
Function name: writeToFiles
Process: write to all 3 files together.
Arguments: thePB, theCL, theML - pointer to alocatated memory, 
		   filename1/2/3 - valid only in function
outPut: none
Return: Indication for success\Failure ( integer(1,0) ).
************************************************************************/
int writeToFiles(PhoneBook * thePB, const char* filename1,
				    CallLog * theCL, const char* filename2,
				       MessageLog * theML, const char* filename3);


#endif