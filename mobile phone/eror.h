/********************************MODULE EROR*********************************
In this module you can find the functions that handle with erors in some 
opertions, print messages  to console, stop opertions, and exit program if 
needed.

the module basicly divided by main modules (PB, CL, TM)
and check initializations.
**************************************************************************/
#ifndef __EROR_H
#define __EROR_H


/////////////////////////////////////
// PB
/////////////////////////////////////

void ContactNotExistEror();
void ExsitingContactError();
/////////////////////////////////////
// CL
/////////////////////////////////////
void fullQueError(); 

/////////////////////////////////////
//  check INITIALIZATIONS
/////////////////////////////////////
void cheakInit( void * memory);
int cheackAllocation(void * memory);
void initEror(char * string);

#endif
