/********************************MODULE IO*********************************
In this module you can find the functions that prints the menus
and the data to the consol.
**************************************************************************/
#include "io.h"
#include "funcs.h"
#include "eror.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

enum Month {January, February, March, April, May, June, July, August, September, October, November, December};

char *months[12] = { {"January"} , {"February"}, {"March"}, {"April"}, {"May"}, {"June"}, {"July"},
	{"August"}, {"September"}, {"October"}, {"November"}, {"December"}};

//------------------------------//
//			Out-Put
//------------------------------//
void MainMenu()
{
	system("cls");
	puts("\n\n\n");
	puts("\t\t\t         Main menu           ");
	puts("\t\t\t-----------------------------");	
	puts("\t\t\t*  1. Contacts              *");
	puts("\t\t\t*  2. Call log              *");
	puts("\t\t\t*  3. Message log           *");
	puts("\t\t\t*  4. Close (exit program)  *");
	puts("\t\t\t-----------------------------");
}
void ContactsMenu()
{
	system("cls");
	puts("\n\n\n");
	puts("\t\t\t           Contacts menu             ");
	puts("\t\t\t-------------------------------------");	
	puts("\t\t\t*  1. Find contact by name          *");
	puts("\t\t\t*  2. Find contact by partial name  *");
	puts("\t\t\t*  3. Show all contacts             *");
	puts("\t\t\t*  4. Add new contact               *");
	puts("\t\t\t*  5. Delete contact                *");
	puts("\t\t\t*  6. Return to main menu           *");
	puts("\t\t\t-------------------------------------");
}
void CallLogMenu()
{
	system("cls");
	puts("\n\n\n");
	puts("\t\t\t         Calls menu          ");
	puts("\t\t\t-----------------------------");
	puts("\t\t\t*  1. Show all calls        *");
	puts("\t\t\t*  2. Add new call          *");
	puts("\t\t\t*  3. Delete call           *");
	puts("\t\t\t*  4. Return to main menu   *");
	puts("\t\t\t-----------------------------");

}
void MessageLogMenu()
{
	system("cls");
	puts("\n\n\n");
	puts("\t\t\t        Messages menu        ");
	puts("\t\t\t-----------------------------");
	puts("\t\t\t* 1. Show recent messages   *"); 
	puts("\t\t\t* 2. Add new message        *");
	puts("\t\t\t* 3. Show conversation      *");
	puts("\t\t\t* 4. Return to main menu    *");
	puts("\t\t\t-----------------------------");

}


void NewLine()
{
	printf("\n");
}

void deletedSucssfuly(){
	printf("\n\t\t\t**DELETED SUCSSFULY**\n");
	}

void addSucssfuly(){
	printf("\n\t\t\t**ADD SUCSSFULY**\n");
	}

void printString( char* string, int TabSize )
{
	printf("%-*s",TabSize, string);
}

void printIdentification(int NumberIdentification, int TabSize )
{
	char Identification[][7] = { {"home"},{"mobile"},{"work"}};
	if( NumberIdentification >= 0  )
		printf("%-*s",TabSize, Identification[NumberIdentification]);
	else
		printString(" ", TabSize);
}

void printType(int callType)
{
	char type[][2]   = { {IN_COMING_SYMBOL,0} ,{OUT_GOING_SYMBOL,0}, {MISSED_CALL_SYMBOL,0} };
	printString(type[callType], 2);
}

void initErr(char * string)
{	
	printf("the %s is  Not Been Initialized\n", string);
}

void Empty()
{
	printf("the arry\\list is EMPTY\n");
}

void ContactExist(){
printf("\n**-the contact with this number is already exsist, could not be save-**\n"); 
}

void NotFound(){
		printf("\n**NOT FOUND**\n");
}

void printPBlistTitle()
{
	printf("the Phone Book List:\n\n");
}
	
void printLexIndex(char LexIndex)
{
	printf("\n%c:\n\n",LexIndex); // מדפיס את האות שנמצאים בה
}

void printIndex(int index){
	printf("%d) ", index);
	}

void printEnumrated(int index)
{
	printf("%d ",index);
}

void printDateAndTime(Pdata Info)
{
	unsigned int month,day, houer, min;

	month = getInfo(Info, MonthMask, MonthMove);
	day   = getInfo(Info, DayMask, DayMove );
	houer = getInfo(Info, HourMask, HourMove );
	min   = getInfo(Info, MinuteMask, MinuteMove );

	printf(" %-.7s %2dth, %02d:%02d ", months[month], day, houer, min);
}

void printDuration(Pdata CallInfo)
{
	int duration = getInfo(CallInfo, DurationMask, DuratinMove);
	printf("%02d:%02d", duration/60, duration%60);
}

void inPutEror(){
	puts("\n**INPUT EROR**\n");
}

void printSerchTitle()
{
	printf("\tSerching Contacts\n");
}

void chooseContact()
{
	printf("chose contact index: ");
}

void converstionTitle()
{
	system("cls");
	printf("the converstion \n\n");
}

void serchConverstion()
{
	printf("serch converstion with contact\n");
}

void EnterString()
{
	printf("enter a string ==> ");
}

void RecentMessagesTitle()
{
	system("cls");
	printf("Recent Messages \n\n");
}

void MesageTabTitle()
{
	printf("Message Tab \n\n");
}

void printEndOfProgram()
{
	system("cls");
	printf("\n\n\n\t\tPROGRAM CLOSED, ALL DATA SAVED TO FILES\n");
}

void EnterNumber()
{
	printf("\nenter the contact number : ");
}

void EnterName()
{
	printf("\nenter the contact name <first and last name>: ");
}

//------------------------------//
//			In-Put
//------------------------------//

char * getString(int max)
{
	char * string = (char*)calloc(1, sizeof(char) );
	char temp;
	int index = 0 ;
	flushall();

	do
	{
		flushall();
		temp = getche() ;

		if( temp == ENTER_KEY ){
			string[index] = END_OF_STRING;
		}
		else if( temp == BACK_SPACE_KEY )
		{
			putch(' ');
			putch(BACK_SPACE_KEY);
			if( index > 0 )
				index--;
			string = (char*)realloc(string, sizeof(char)*(index+1) );
		}
		else
		{
			string = (char*)realloc(string, sizeof(char)*(index+1) );
			string[index++] = temp;
		}

	}while( string[index] != END_OF_STRING && index < max-1 );

	if( index == max-1 ){
		string[max] = END_OF_STRING;
	}
	printf("\n");
	return string;
}

char*getName()
{
	char *name = (char*)malloc(sizeof(char));
	int i =0;
	
	if ( !cheackAllocation(name) )
		return NULL;
	
	do
	{
		flushall();
		name[i]= getche(); // get char
		
		if(isalpha(name[i])!=NOT_LETTER || name[i]==ENTER_KEY || name[i]==SPACE_KEY || name[i] == BACK_SPACE_KEY)
		{
			// make the first letter of the first and kast name uppercase
			if((i==0) || (name[i-1]==SPACE_KEY) )
				name[i] = toupper(name[i]);
			// end of name
			if(name[i] == ENTER_KEY)
			{
				name[i] = END_OF_NAME;
				printf("\n");
			}
			else
			{// allcoating one more place or delting charcter
				if(name[i] == BACK_SPACE_KEY)
				{
					if( i==0 )
						putchar(' ');
					else
					{
						putchar(' ');
						putchar(BACK_SPACE_KEY);
						name = (char*)realloc(name,i);
						if ( !cheackAllocation(name) )
							return NULL;
						i--;
					}
				}
				else
				{
				name = (char*)realloc(name,++i+1);
				if ( !cheackAllocation(name) )
					return NULL;
				}
			}
		}
		else // ilegal chercter 
		{
			putchar(BACK_SPACE_KEY);
			putchar(' ');
			putchar(BACK_SPACE_KEY);
		}
	}while(name[i] != END_OF_NAME );
	printf("\n");
	return name;
}

char*getNumber()
{
	int i =0;
	char *number = (char*)malloc(sizeof(char));
	
	 if ( !cheackAllocation(number) ){
		return NULL;
		}
	
	do
	{
		flushall();
		number[i]= getche(); // get char
		
		if( isdigit(number[i]) != NOT_DIGIT || number[i]==SOLAMIT_KEY || number[i]==KOCHVIT_KEY || number[i]==ENTER_KEY)
		{
			// end of number
			if(number[i] == ENTER_KEY)
				number[i] = END_OF_NUMBER;
			else
			{
				number = (char*)realloc(number,++i+1);
					 if ( !cheackAllocation(number) ){
						 return NULL;
					 }
			}
		}
		else // ilegal chercter or back space
		{
			if( number[i] == BACK_SPACE_KEY )
			{
				if( i==0 )
						putchar(' ');
				else
				{
					putchar(' ');
					putchar(BACK_SPACE_KEY);
					number = (char*)realloc(number,i);
					if ( !cheackAllocation(number) )
						return NULL;
					i--;
				}

			}
			else
			{
				putchar(BACK_SPACE_KEY);
				putchar(' ');
				putchar(BACK_SPACE_KEY);
			}
		}
		
	}while(number[i] != END_OF_NUMBER );
	printf("\n");
	return number;
}

 int cheackLegalName(char *Name)
 {
	 if ( Name == NULL )
		 return 0;

	 if ( (*Name >= LOW_ASCII_LEX) && (*Name <= HIGH_ASCII_LEX) )
		 return 1;
	 return 0;
 }

int getIdentification()
{
	int id=-1;
	printf("\nenter the Identification of the number: ");
	while(id<0 || id>2)
	{
		flushall();
		scanf("%d",&id);
	}
	return id;
}

int getOffSet()
{
	int offSet;
	flushall();
	scanf("%d",&offSet);
	return offSet -1;
}

int getType(int type)
{
	int num = rand() % type;
	
	return num; 
}

int getCallDuration()
{
	int duration, random;
	srand( (unsigned int)time(NULL) );
	random = rand();
	
	duration =  random % MAX_DURATION ;

	return duration;
}

struct tm * getDate()
{
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return timeinfo;
}

int getOperation()
{
	flushall();
	return  getch();
}
