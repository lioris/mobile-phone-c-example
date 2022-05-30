/********************************MODULE FUNCS*********************************
In this module you can find the genreic functions of the project 
and the function that work with bit opertion.

i added here the data structure and all functions that work with this struct.

data structure is a block of informatin that contain the date for both 
Call Log and Message Log and the duration for Call Log
**************************************************************************/
#ifndef __FUNCS_H			//מניעת הכללה כפולה
#define __FUNCS_H

#define MOVE_MONTH 5
#define MOVE_MINUTE 9
#define MOVE_HOUR 15
#define MOVE_DURATION 20

#define MOVE_LEFT 0 
#define MOVE_RIGHT 1

#define DAY_LOW 0
#define DAY_HIGH 4

#define MONTH_LOW 5
#define MONTH_HIGH 8

#define MINUTE_LOW 9
#define MINUTE_HIGH 14

#define HOUR_LOW 15
#define HOUR_HIGH 19

#define DURATION_LOW 20
#define DURATION_HIGH 31

#define MAX_DURATION 4096

struct data;
typedef struct data Data;
typedef struct data* Pdata;

// Working with bit opertion - set and get  

/************************************************************************
Function name: creatMask
Process: creat mask of bit from high to low
Arguments: high, low - valid only in function
outPut: none
Return: the mask
************************************************************************/
unsigned int creatMask(int high, int low);

/************************************************************************
Function name: setInfo
Process: get information and set it to the data block by bit operation
Arguments: Info - pointers to alocatated memory , TheInfo - valid only in function
		   masking - pointer to function - make mask by the function it get
		   bitMove - pointer to function - move the bits lsft or right by the function it get
outPut: none
Return: the mask
************************************************************************/
void setInfo( Pdata Info, unsigned int TheInfo, unsigned int(*masking)(), unsigned int(*bitMove)(unsigned int, int) );

/************************************************************************
Function name: getInfo
Process: get the informatin from the data block by bit operation
Arguments: Info - pointers to alocatated memory , TheInfo - valid only in function
		   masking - pointer to function - make mask by the function it get
		   bitMove - pointer to function - move the bits lsft or right by the function it get
outPut: none
Return: the information needed (duration/date)
************************************************************************/
unsigned int getInfo(Pdata Info, unsigned int(*masking)(), unsigned int(*bitMove)(unsigned int, int) );

/************************************************************************
Function name: setDate
Process: get the current date ( here from time.h) and set it to the block data
		 if the block data given is NULL, creat a new block data and set the date
		 if the block data exist - set the date 
Arguments: Info - pointers to alocatated memory.
outPut: none
Return: the block information (Pdata)
************************************************************************/
Pdata setDate(Pdata Info);

/************************************************************************
Function name: setDataBlock
Process: get the information as block ( unsigned int), creat a new 
		 data block and set the information as block.
Arguments: Block - valid only in function.
outPut: none
Return: the block information (Pdata)
************************************************************************/
Pdata setDataBlock(int Block);

/************************************************************************
Function name: getInfoBlock
Process: get the information as block ( unsigned int), creat a new 
		 data block and set the information as block.
Arguments: Block - valid only in function.
outPut: none
Return: the block information (Pdata)
************************************************************************/
int getInfoBlock(const Pdata theData);

/************************************************************************
Function name: DayMove, MonthMove, MinuteMove, HourMove, DuratinMove.
Process: all functions move the information right\left by move opertion 
		 the number of bit need to get thir place in the data block,
		 or for retrive the information from the block.
		 move can get - MOVE_LEFT\MOVE_RIGHT
Arguments: day, month, minute, hour, duration, move.
outPut: none
Return: the information after moving
************************************************************************/
unsigned int DayMove     (unsigned int day      , int move );
unsigned int MonthMove   (unsigned int month    , int move);
unsigned int MinuteMove  (unsigned int minute   , int move);
unsigned int HourMove    (unsigned int hour     , int move);
unsigned int DuratinMove (unsigned int duration , int move);

/************************************************************************
Function name: DayMask, MonthMask, MinuteMask, HourMask, DurationMask.
Process: all functions make mask of the bits metch in the block.
Arguments: none
outPut: none
Return: the mask
************************************************************************/
unsigned int DayMask();
unsigned int MonthMask();
unsigned int MinuteMask();
unsigned int HourMask();
unsigned int DurationMask();

/************************************************************************
Function name: comperDate
Process: get the date from the block data and comper the by date.
		 A>B - A is newer from B (1)
		 A<B - B is newer from A (-1)
		 A==B - A and B is equle ( month,day,hour and min)(0)
Arguments: infoA, infoB
outPut: none
Return: indication who is beeger ( equle to strcmp)
************************************************************************/
int comperDate(Pdata infoA , Pdata infoB);
#endif
