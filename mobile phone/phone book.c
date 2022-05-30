#pragma warning (disable : 4996) 
#include "phone book.h"
#include "io.h"
#include "list.h"
#include "eror.h"

#include<stdlib.h>
#include <string.h>
#include <stdio.h>
// initalize the Phone-Book
PhoneBook * initPB()
{	// allocate Memory block
	PhoneBook* thePB = (PhoneBook*)calloc(1, sizeof(PhoneBook) );
		cheakInit(thePB);
	// initalize the UnKnown and Blocked contacts
	thePB->unknown = initUnKnown();
	thePB->Blocked = initBlocked();
	return thePB;
}
// initalize the UnKnown contact
Contact * initUnKnown()
{	// allocate memory block
	Contact *UnKnown = (Contact*)calloc(1, sizeof(Contact));
		cheakInit(UnKnown);
	UnKnown->Name =  UN_KNOWN;
	UnKnown->PhoneNumber = NULL;
	UnKnown->NumberIdentification = NO_IDENTIFICATION;
	return UnKnown;
}
//initaliza the Blocked contact
Contact * initBlocked()
{   // allocate memory block
	Contact *Blocked = (Contact*)calloc(1, sizeof(Contact));
		cheakInit(Blocked);
	Blocked->Name = NULL;
	Blocked->PhoneNumber = BLOCKED;
	Blocked->NumberIdentification = NO_IDENTIFICATION;
	return Blocked;
}

void freeContact(Contact* cont)
{
	freeName( cont );
	freeNumber( cont );
	free(cont);
}

void freeNumber(Contact * toFree)
{
	if( toFree->PhoneNumber != NULL )
	{
		free( toFree->PhoneNumber );
		toFree->PhoneNumber = NULL;
	}
}

void freeName(Contact * toFree)
{
	if( toFree->Name != NULL )
	{
		free( toFree->Name );
		toFree->Name = NULL;
	}
}

Contact* getNewContact()
{	// allocate memory block for new contact
	Contact *newContact = (Contact*)calloc(1, sizeof(Contact));
	
	if ( !cheackAllocation( newContact ) ){
		return NULL;
		}
	EnterName();
	// get the contact details
	newContact->Name = getName(); 
	EnterNumber();
	newContact->PhoneNumber = getNumber();
	newContact->NumberIdentification = getIdentification();

	return newContact;
}

Contact* insertContact(Contact *oldArr,int numberOfContacts, Contact *newContact)
{
	Contact  *newArr = NULL;
	int i;
	// allocate one more place to new contact , 
	//the block memory allocated in diffrent place from the old block
	newArr = (Contact*)calloc( numberOfContacts+1, sizeof(Contact)) ;
	if( !cheackAllocation(newArr) )
		return NULL;
	// copy contacts to the new contact arry sorted and with the new contact
	for(i=0 ; i<numberOfContacts ; i++ )
	{
		if (comperContacts(&oldArr[i], newContact ) < 1)
			newArr[i] = oldArr[i] ;
		else
		{
			newArr[i] = *newContact;
			*newContact = oldArr[i];
		}
	}
	// the new contact represent the last contact ( becuas it use as temp cell in the buble sort)
	// the last contact is copying to his place in the new arry
	newArr[i] = *newContact;

	return newArr;
}

List FindContact(char*name, PhoneBook *ThePB, int(*strComerator)(const char*,const char*) )
{
	Contact *contArr;
	int index=0, j, numOfCont;
	List contactList = MakeEmpty(NULL);
	system("cls");
	printSerchTitle();

	// if the name is not send to the function it ask for a name to serch
	if(name == NULL)
	{
		EnterString();
		name = getString(MAX_NAME); 
	}

	if(ThePB == NULL){
		initEror("Phone Book");
		return contactList; 
		}

	for(index=0 ; index < PHONE_BOOK_SIZE ; index++ )
	{	// load the arry lexicography  and the number of contacts
		contArr = ThePB->contactArray[ index ];
		numOfCont = ThePB->numberOfContacts[ index ];
		// serch in the arry
		for(j=0 ; j<numOfCont ; j++ )
		{
			if( !strComerator(contArr[j].Name, name) )
				InsertLats(&contArr[j],contactList); // if found, insert to the list
		}
	}
	// if nothing has been found
	if( Advance(contactList) == NULL)
	{
		ContactNotExistEror();
		return contactList;
	}
	return contactList; // retun the list of found contacts
}
//to use in the Phone-Book Moudle
int partialNameComperator(const char *sourceName, const char *toSerchPart)
{
	if( sourceName == NULL || toSerchPart == NULL )
		return NULL_EROR;

	if( strcmp(sourceName, toSerchPart) == 0) return 0;
	if(strstr(sourceName, toSerchPart) != NULL) return 0;
	return -1;
}
//to use in the Phone-Book Moudle
int FullNameComperator(const char *sourceName, const char *toSerchPart)
{
	if( sourceName == NULL || toSerchPart == NULL )
		return NULL_EROR;

	return strcmp(sourceName, toSerchPart) ;
}
// for use out side of the Phone-Book Module or as comperator
int comperByName(const void* contactA, const void* contactB)
{
	char *nameA = ((Contact*)contactA)->Name; 
	char *nameB = ((Contact*)contactB)->Name;
	
	if( nameA == NULL || nameB == NULL)
		return NULL_EROR;

	return strcmp( nameA , nameB );	
}
// for use out side of the Phone-Book Module or as comperator
int comperByNumber(const void* contactA, const void* contactB)
{
	char *numberA = ((Contact*)contactA)->PhoneNumber; 
	char *numberB = ((Contact*)contactB)->PhoneNumber;
	
	if( numberA == NULL || numberB == NULL)
		return NULL_EROR;

	return strcmp( numberA , numberB );	
}

Contact* searchByNumber(char *number, PhoneBook *thePB)
{
	int index = 0, ArrIndex, count ;

	if(number == NULL ){
		initEror("name");
		return NULL;
		}
	// serch the number in the Phone-Book
	for(index=0; index < PHONE_BOOK_SIZE ; index++)
	{	// load the number of contacts in the arry lexicography index
		count = thePB->numberOfContacts[index];
		for(ArrIndex=0 ; ArrIndex < count ; ArrIndex++)
		{
			if(strcmp(number, thePB->contactArray[index][ArrIndex].PhoneNumber) == 0)
				return &(thePB->contactArray[index][ArrIndex]); // if contact found , return it
		}
	}
	return NULL; // contact not Found
}

Contact* contactArrSerch(Contact *contArr, int numOfCont, Contact *theContact)
{
	int index;

	if(contArr == NULL || numOfCont==0){
		return EMPTY_ARRY;
		}
	// if one of the parmetrs is NULL the contact is not in the PB
	if( theContact->Name == NULL || theContact->PhoneNumber == NULL ){
		return NULL;
		}

	for(index=0 ; index < numOfCont ; index++)
		if( comperByName(&contArr[index], theContact) == 0 )
			if( comperByNumber(&contArr[index], theContact) == 0)
				return &contArr[index]; // if found return the contact

	return NULL; // contact not found
}

int comperContacts(const Contact *CA,const Contact *CB)
{
	int res = comperByName(CA,CB);
	if( res != 0 )
		return res;

	if(CA->NumberIdentification < CB->NumberIdentification )
		return -1;
	else if (CA->NumberIdentification > CB->NumberIdentification)
		return 1;
	else
		return 0;
}

int comperIdentity(Contact* CA, Contact* CB) // בודק האם שני אנשי קשר זהיים
{
	if ( (comperByName(CA, CB ) == 0) || (CA->Name == NULL && CB->Name == NULL) )
	{
		if ( (comperByNumber(CA, CB) == 0)  || (CA->PhoneNumber == NULL && CB->PhoneNumber == NULL) )
			return 1;
		else 
			return 0;
	}
	
	return 0;
}

int isBlockedNumber(Contact * cont)
{
	if ( cont->Name == NULL)
		if ( cont->PhoneNumber != NULL )
			if(strcmp( cont->PhoneNumber, BLOCKED) == 0)
				return 1;
	return 0;
}

int isUnKnownName(Contact * cont)
{
	if ( cont->PhoneNumber == NULL)
		if ( cont->Name != NULL )
			if(strcmp( cont->Name, UN_KNOWN) == 0)
				return 1;
	return 0;
}

Contact* setContact(char * string, PhoneBook* thePB) // המספר מייצג את המספר טלפון
{		// string represent the Phone Number
	Contact * tempC;
			if( string == NULL) // NULL mean the number is not known 
			{
				free(string);
				return thePB->unknown;
			} // check if the number is Blocked
			else if( strcmp(string, BLOCKED) == 0)
			{
				free(string);
				return thePB->Blocked;
			}// serch fot the number in the phone-book
			else if ( tempC = searchByNumber(string, thePB) ) // the number found in the phone book 
			{
				free(string);
				return  tempC;
			}
			else
			{	// the number is a ruglar number and not in the phome book 
				// initalize a memory block for the number
				tempC = (Contact*)calloc( 1, sizeof(Contact) );
				tempC->Name = NULL;
				tempC->PhoneNumber = (char*)calloc( strlen(string)+1, sizeof(char)  );
				strcpy(tempC->PhoneNumber, string);
				tempC->NumberIdentification = NO_IDENTIFICATION;
				return tempC;
			}
}

void printPhoneBook(const PhoneBook * thePhoneBook)
{
	int phoneBookIndex, contactArrIndex, numberOfContacts;
	Contact *contactArr;
	system("cls");
	printPBlistTitle();
	// run on all the phone book
	for(phoneBookIndex=0 ; phoneBookIndex<PHONE_BOOK_SIZE ; phoneBookIndex++)
	{	// load the contact arry and the number of contacts in the arry
		numberOfContacts = thePhoneBook->numberOfContacts[phoneBookIndex];
		(contactArr)  = thePhoneBook->contactArray[phoneBookIndex];
		// if entery exisit
		if(thePhoneBook->contactArray[phoneBookIndex])
			//printf the Lexicographic index
		printLexIndex( thePhoneBook->contactArray[phoneBookIndex]->Name[0] ); // מדפיס את האות שנמצאים בה
		for(contactArrIndex=0; contactArrIndex<numberOfContacts; contactArrIndex++)
		{	// print the contact details
			pirntContactDetails(contactArr[contactArrIndex]);
		}
		
	}
}

// RECURSIVE FUNCTION
void printContactList(List ContactList, Contact *prevContact, int index) 
{
	Contact * tempC;

	if( ContactList == NULL)
		return;

	tempC = (Contact*)Retrieve(ContactList);
	if( prevContact == NULL) // if prev is NULL and the list is not Empty its a new Contact to print
	{
		NewLine();
		// print name
		printString(tempC->Name,TAB_NAME_SIZE); 
		NewLine();
		// print the identificition
		printIdentification(tempC->NumberIdentification, TAB_IDENTFICATION);
		printEnumrated(index=1); // if its a new contact enumrated index is 1
		// print phone number
		printString(tempC->PhoneNumber, TAB_NUMBER_SIZE);
		NewLine();
		// REC CALL TO THE SAME FUNCTION
		printContactList(Advance(ContactList), tempC, index+1);
	}	// check if there is more the one for the same contact
	else if( FullNameComperator(prevContact->Name, tempC->Name) == 0   )
	{	// print idntfication
		printIdentification(tempC->NumberIdentification, TAB_IDENTFICATION);
		// if the prev id the currunt id is the same print next index other wise index is 1
		if(tempC->NumberIdentification == prevContact->NumberIdentification ) 
			printEnumrated(index);
		else
			printEnumrated(index=1);
		// print the phone number
		printString(tempC->PhoneNumber, TAB_NUMBER_SIZE);
		NewLine();
		// REC CALL TO THE SAME FUNCTION
		printContactList(Advance(ContactList), tempC, index+1);
	}
	else// REC CALL TO THE SAME FUNCTION, if the current contact is drffrent from prev 
		printContactList(ContactList, NULL, 1);
}

void pirntContactDetails(const Contact contact)
{
	printString(contact.Name, TAB_NAME_SIZE);
	printString(contact.PhoneNumber, TAB_NUMBER_SIZE);
	printIdentification(contact.NumberIdentification, TAB_IDENTFICATION );
	printf("\n");
}

int getLexIndex(int FirstLetter)
{
	if (FirstLetter>=LOW_ASCII_LEX && FirstLetter<=HIGH_ASCII_LEX )
		return FirstLetter - INDEX_FACTOR ;
	// not leggal charcter
	return -1;
}

Contact* DeleteContact(PhoneBook *thePB)
{
	Contact tempC, *oldArr = NULL, *newArr = NULL;
	int numOfcontacts, theABC , i, index;
	char * nameToDelete = NULL;

	system("cls");
	// get the name to delete
	EnterName();
	nameToDelete = getName();
	// get the Lexicographic index the contact arry and the number of contacts
	theABC = getLexIndex( *nameToDelete );
	oldArr  = thePB->contactArray[theABC];
	numOfcontacts = thePB->numberOfContacts[theABC];
	// check if the contact arry is empty
	if(numOfcontacts == 0){
		Empty();
		return EMPTY_ARRY; 
		}
	// make a temo contact to contain the name to delte , we want to work in contact level.
	tempC.Name = nameToDelete;
	index = serachFirst(thePB, tempC); //look for the first index the contact is apper

	if( index < 0 ){ // contact has not been found
		return CONTACT_NOT_EXIST;
		}
	// make a new arry to contain the arry after deleting the contact
	newArr = setNewArr(numOfcontacts);
	// make a arry of contacts to delete and check if there is more then one
	if ( listToDelete(&oldArr[index], numOfcontacts ) > 1 ) 
	{
		chooseContact(); // massege
		index += getOffSet();	// get the offset to the contact to delete in the arry
	}
	// print the contact details to delete
	pirntContactDetails(oldArr[index]);
	// copy the contacts to the new arry block memory sorted and with out the contact to delete
	for(i=0 ; i<index; i++)
		newArr[i] = oldArr[i];
	for( ; i<numOfcontacts-1 ; i++)
		newArr[i] = oldArr[i+1];
	// decrement the number of contacts
	if ( --(thePB->numberOfContacts[theABC])  > 0 )
		thePB->contactArray[theABC] = newArr;
	else // if decremnt to 0 it meen there is no nore contact, init to NULL the arry
		thePB->contactArray[theABC] = NULL;
	deletedSucssfuly(); // message
	freeName ( &oldArr[index] );	// free the name	// the contact block memory will be free after re organizing memory
	freeNumber ( &oldArr[index] );  // free the number	// the block memory is no more in the Phone Book use 
	return oldArr;
}

int listToDelete(Contact *Arr, int numOfcontacts  )
{
	int stopFlag =FLAG_ON, offSet =0;
	printString(Arr->Name, TAB_NAME_SIZE); //print the name to delete
	NewLine();
	// get the first apper contact in the arry and print numbers untill next defrent contact
	while( stopFlag && ( comperByName(Arr , Arr + offSet ) == 0 ) )
	{	// print numbers indexed to the console 
		printIndex(offSet+1);
		printString( Arr[offSet].PhoneNumber, TAB_NUMBER_SIZE);
		NewLine();
		if( offSet < numOfcontacts-1)
			offSet++;
		else
			stopFlag = FLAG_OFF;
	}

	return offSet;
}

int serachFirst(PhoneBook *thePB, Contact tempC)
{
	int theABC = getLexIndex(*tempC.Name), index, StopFlag=1;
	Contact *Arr  = thePB->contactArray[theABC], *res = NULL ;
	int numOfcontacts = thePB->numberOfContacts[theABC] ;

	if( numOfcontacts == 0 )
		return -1; 
	// serch for contact name, not nessry the first aperance in the arry
	res =  (Contact*)bsearch(&tempC, Arr, numOfcontacts, sizeof(Contact), comperByName );
	index = res - Arr ;  
	// find the first aperance if ther is more the one
	while( index > 0 && StopFlag )
	{
		if ( comperByName(Arr+index, Arr+index-1) == 0 )
			index--;
		else 
			StopFlag = 0;
	}
	// the index of the first contact by name
	return index;
}

 Contact* setNewArr(int size)
 {
	 Contact * newArr = NULL;
	 if ( size > 1 )
	 {
		 newArr = (Contact*)calloc(1, sizeof(Contact)*(size-1));
		 if ( cheackAllocation(newArr) )
			 return newArr;
	 }

	 return NULL;
 }

 Contact* AddNewContact(PhoneBook *thePhoneBook )
{
	int theABC, numberOfContacts;
	Contact **ArrAdress = NULL , *newArr = NULL , *oldArr = NULL ;
	Contact *newContact = NULL;

	system("cls");
	// get new contact details
	if ( (newContact = getNewContact()) == NULL ){
		return NULL;
	}
	if( !cheackLegalName(newContact->Name) ){
		freeContact(newContact);
		return NULL;
		}

	// calc the index in the phone book
	theABC = getLexIndex( *(newContact->Name) );
	ArrAdress = &thePhoneBook->contactArray[theABC];
	numberOfContacts = thePhoneBook->numberOfContacts[theABC];
	
	// cheack if the contact allready exsist
	if ( contactArrSerch(*ArrAdress, numberOfContacts, newContact) ) {
			ExsitingContactError();
			freeContact(newContact);
			return CONTACT_EXIST;
			 }
	// insert contact and get the new memory block back, incrment the number of contacts in the arry
	newArr = insertContact(*ArrAdress, numberOfContacts, newContact);
	++thePhoneBook->numberOfContacts[theABC]; 
	// switch the old arry with the new arry in the Phone Book
	oldArr = *ArrAdress;
	*ArrAdress = newArr;

	addSucssfuly(); // message
	return oldArr;
}

 Contact* fixMemory(PhoneBook *thePB, Contact *toFix)
 {
	 int index;
	 Contact *tempC = NULL;
	 // NULL && NULL - its an contact that has been deleted 
	 if( toFix->Name == NULL && toFix->PhoneNumber == NULL ) 
		 return thePB->unknown;
	 // contact that had been exist in the old arry ( old memory block)
	 else if( toFix->Name != NULL &&  comperByName(toFix, thePB->unknown) )
	 {	 // serch the contact in the phone book 
		 index =	getLexIndex( *(toFix->Name) );			
		 toFix = contactArrSerch( thePB->contactArray[index], thePB->numberOfContacts[index], toFix );
		 if(toFix != NULL )
			 return toFix; // contact found in a new memory block
		 else
			 return thePB->unknown; // contact was not found - replace it with UnKnown
	 }
	 // not a contact, just a number.
	 else if( toFix->PhoneNumber != NULL && toFix->Name == NULL && comperByNumber( toFix, thePB->Blocked) )
	 {	 // serch if the number been saved recntly to the phone book
		 tempC = searchByNumber(toFix->PhoneNumber, thePB);
		 if(tempC != NULL ) // number found in the phone book 
		 {
			 free(toFix);  // free the contact number
			 return tempC; // replace with contact pointer in the phone book
		 }
		 else
			 return toFix;	// not found, return the same number
	 }
	 else
		 return toFix; // not found, return the same number
 }


