#include "eror.h"
#include "io.h"

#include <stdio.h>
#include<stdlib.h>


void initEror(char * string)
{
	initErr(string);	
}

void ExsitingContactError()
{
	ContactExist();
}

void ContactNotExistEror()
{
	NotFound();	
}

void fullQueError()
{
	printf("\n**-- THE QUE IS FULL, THE LAST CALL WAS DEQUE  --**\n");
}

void cheakInit( void * memory)
{
	if ( memory == NULL )  { perror("Out of Space!"); exit(1);}
}

int cheackAllocation(void * memory)
{
	if ( memory == NULL )  { perror("Out of Space!"); return 0;}

	return 1;
}
