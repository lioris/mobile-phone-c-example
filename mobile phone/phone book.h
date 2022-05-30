/********************************MODULE PHONE BOOK******************************
In this module the Phone-Book structure and Contact structure  is defined
and the functions that deal with the structures are implemented.

The Phone-Book is an array of pointers to Contacts dynamic arrys.
Meaning, it's an static array of dynamic arrys.

Each contact arry is stored in array i, where the first letter of the contact 
name represent the index, for exp - thePB->contactArry[*name] , (name is a string).

also the Phone-Book stucture containe arry that contain the number of contacts in each
contact arry by index,

In addition it contain static contact of Unknown and Blocked contact.

the module is divided by parts
1. INITIALIZATIONS
2  opereting Function on contacts and PB
3. searching Function
4. compering Function
5. printing Function
**************************************************************************/

#ifndef __PHONE_BOOK
#define __PHONE_BOOK
#include "Phone Book Defines.h"

#include "list.h"

// Statement that this structs is exist and will be include in the .c file
// to prevent redefnition
/************************************************************************/
typedef struct Contact Contact;
typedef struct PhoneBook PhoneBook ;
/************************************************************************/

struct Contact
{
	char *Name;					  // dynamic string
	char *PhoneNumber;			  // dynamic string
	int  NumberIdentification;	  // 0-mobile , 1-home , 2-work
};

struct PhoneBook
{
	Contact *contactArray[PHONE_BOOK_SIZE];
	int numberOfContacts[PHONE_BOOK_SIZE];
	Contact* unknown;
	Contact* Blocked;
};

/**************************************************************/
//				 INITIALIZATIONS
/**************************************************************/
PhoneBook *initPB();
Contact * initUnKnown();
Contact * initBlocked();
/**************************************************************/


/**************************************************************/
//				 OPERATING CONTACTS AND PB
/**************************************************************/

/************************************************************************
Function name: setContact
Process: get a string and check for the matching contact.
		 contact from PB, UnKnown, Blocked, just number (with out name).
Arguments: string, thePB - pointers to alocatated memory.
outPut: none
Return: the matching contact.
************************************************************************/
Contact* setContact(char * string, PhoneBook* thePB);

/************************************************************************
Function name: freeContact
Process: free a contact (free the name and the number if needed).
Arguments: cont - pointers to alocatated memory.
outPut: none
Return: void
************************************************************************/
void freeContact(Contact* cont);

/************************************************************************
Function name: freeContact
Process: get a contact and free the name.
Arguments: toFree - pointers to alocatated memory.
outPut: none
Return: void
************************************************************************/
void freeNumber(Contact * toFree);

/************************************************************************
Function name: freeContact
Process: get a contact and free the number
Arguments: cont - pointers to alocatated memory.
outPut: none
Return: void
************************************************************************/
void freeName(Contact * toFree);

/************************************************************************
Function name: AddNewContact
Process: add a new contact to the phone book
Arguments: thePhoneBook - pointers to alocatated memory.
outPut: none
Return: the old contact arry memory for fixing the Call-log and Message-Log
************************************************************************/
Contact* AddNewContact(PhoneBook *thePhoneBook);

/************************************************************************
Function name: DeleteContact
Process: delete a contact from the Phone Book
Arguments: thePB - pointers to alocatated memory.
outPut: none
Return: the old contact arry memory for fixing the Call-log and Message-Log: 
************************************************************************/
Contact* DeleteContact(PhoneBook *thePB);

/************************************************************************
Function name: FindContact
Process: serch a contact by comperator
full name comperator 
partial name comperator 
Arguments: name - valid only in function, ThePB - pointers to alocatated memory.
			strComerator - function pointer
outPut: none
Return: list of found contacts.
************************************************************************/
List FindContact(char*name, PhoneBook *ThePB, int(*strComerator)(const char*,const char*) );

/************************************************************************
Function name: getNewContact
Process: get ditailes to creat a new contact, alocate memory and initaliza the new contact
Arguments: none
outPut: none
Return: the new contact
************************************************************************/
Contact* getNewContact();

/************************************************************************
Function name: insertContact
Process: insert the contact to his place in the arrys Phone-Book
Arguments: oldArr - the adrress of the arry in the Phone-Book
		   numberOfContacts - number of contacts int the old arry
		   newContact - the contact to insert
outPut: none
Return: new contact arry in different block memory with new contact inserted sorted
************************************************************************/
Contact* insertContact(Contact *oldArr,int numberOfContacts,  Contact *newContact);

/************************************************************************
Function name: getLexIndex
Process: calc the lexicography index 
Arguments: FirstLetter - valid only in function 
outPut: none
Return: the lexicography index 
************************************************************************/
int getLexIndex(int FirstLetter);

/************************************************************************
Function name: setNewArr
Process: creat a new contact arry, allocate memory block by the size given
Arguments: size - valid only in function 
outPut: none
Return: the new arry adrress
************************************************************************/
Contact* setNewArr(int size);

/************************************************************************
Function name: fixMemory
Process: get a old block memory contact and serch in the Phone-Book
		 if the contact exist.
				exist - fix the pointer to the contact
				not exist - put pointer to UnKnown adrress.
Arguments: thePB - pointers to alocatated memory, toFix - valid only in function 
outPut: none
Return: the contact in the Phone-Book if found other wise UnKnown adrress.
************************************************************************/
Contact* fixMemory(PhoneBook *thePB, Contact *toFix);

////////////////////////////////////////////////////////////////////
//					SERCHING FUNCTIONS	
////////////////////////////////////////////////////////////////////
/************************************************************************
Function name: serachFirst
Process: serch for the first show of the contact ( if there is more then one)
Arguments: thePB - pointers to alocatated memory, tempC - valid only in function 
outPut: none
Return: the index in the arry of contacts
************************************************************************/
int serachFirst(PhoneBook *thePB, Contact tempC);

/************************************************************************
Function name: contactArrSerch
Process: serch for a contact in a given arry.
Arguments: contArr - pointers to alocatated memory, numOfCont, theContact - valid only in function 
outPut: none
Return: the contact if found other wise NULL
************************************************************************/
Contact* contactArrSerch(Contact *contArr, int numOfCont, Contact *theContact);

/************************************************************************
Function name: searchByNumber
Process: serch for a contact by phone number in the phone-book
Arguments: thePB - pointers to alocatated memory, number - valid only in function 
outPut: none
Return: the contact if found other wise NULL
************************************************************************/
Contact* searchByNumber(char *number, PhoneBook *thePB);

///////////////////////////////////////////////////////////////////////
//						COMPER FUNCTIONS				
///////////////////////////////////////////////////////////////////////
/************************************************************************
Function name: comperIdentity
Process: check if to contacts is equle ditailes
Arguments: CA, CB - pointers to alocatated memory.
outPut: none
Return: indication for true(1)\false(0).
************************************************************************/
int comperIdentity(Contact* CA, Contact* CB);	// בודק הם שני אנשי קשר זהיים

/************************************************************************
Function name: comperContacts
Process: comper betwen contacts by lexicography place
Arguments: CA, CB - pointers to alocatated memory.
outPut: none
Return: indication for cA>CB (1), for cA<CB (-1),for cA==CB (0).
************************************************************************/
int comperContacts(const Contact *CA, const Contact *CB);		// בודק איזה איש קשר גדול יותר מבחינת מיקום במערך

/************************************************************************
Function name: comperByName
Process: comper contacts by lexicography name.
Arguments: contactA, contactB - pointers to alocatated memory.
outPut: none
Return: indication for A>B (1), for A<B (-1),for A==B (0).
		NULL_EROR return if one of the contacts is NULL.
************************************************************************/
int comperByName(const void* contactA, const void* contactB);

/************************************************************************
Function name: comperByNumber
Process: comper betwen contacts by lexicography number
Arguments: contactA, contactB - pointers to alocatated memory.
outPut: none
Return: indication for A>B (1), for A<B (-1),for A==B (0).
		NULL_EROR return if one of the contacts is NULL.
************************************************************************/
int comperByNumber(const void* contactA, const void* contactB);

/************************************************************************
Function name: partialNameComperator
Process: check if toSerchPart string is apart of the sourceName
Arguments: sourceName, toSerchPart - pointers to alocatated memory.
outPut: none
Return: indication for true(0)\false(-1)
		NULL_EROR return if one of the contacts is NULL.
************************************************************************/
int partialNameComperator(const char *sourceName, const char *toSerchPart);

/************************************************************************
Function name: FullNameComperator
Process: check if toSerchPart string is equle of the sourceName
Arguments: sourceName, toSerchPart - pointers to alocatated memory.
outPut: none
Return: indication for true(0)\false(-1)
		NULL_EROR return if one of the contacts is NULL.
************************************************************************/
int FullNameComperator(const char *sourceName, const char *toSerchPart);

/************************************************************************
Function name: isBlockedNumber
Process: check if contact is from blocked number
Arguments: cont - pointers to alocatated memory.
outPut: none
Return: indication for true(1)\false(0)
************************************************************************/
int isBlockedNumber(Contact * cont);

/************************************************************************
Function name: isUnKnownName
Process: check if contact is an UnKnown contact
Arguments: cont - pointers to alocatated memory.
outPut: none
Return: indication for true(1)\false(0)
************************************************************************/
int isUnKnownName(Contact * cont);


///////////////////////////////////////////////////////////////////////
//					PRINTING FUNCTIONS					// CAN BE MOVED TO IO MOUDULE				
///////////////////////////////////////////////////////////////////////
/************************************************************************
Function name: printPhoneBook
Process: print the contacts to the console lexicography.
Arguments: thePhoneBook - pointers to alocatated memory.
outPut: none
Return: void
************************************************************************/
void printPhoneBook(const PhoneBook * thePhoneBook);

/************************************************************************
Function name: printContactList
Process: get a list of contacts and print it to the console
Arguments: ContactList, prevContact - pointers to alocatated memory, 
		   index - valid only in function .
outPut: none
Return: void
************************************************************************/
void printContactList(List ContactList, Contact *prevContact, int index);

/************************************************************************
Function name: pirntContactDetails
Process: print one contact details
Arguments: contact - pointers to alocatated memory.
outPut: none
Return: void
************************************************************************/
void pirntContactDetails(const Contact contact);

/************************************************************************
Function name: listToDelete
Process: get a arry of contacts to delete and print it to the console
Arguments: Arr - pointers to alocatated memory, numOfcontacts - valid only in function .
outPut: none
Return: the offset (the number of printed contacts).
************************************************************************/
int listToDelete(Contact *Arr, int numOfcontacts  );




#endif


