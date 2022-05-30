#pragma warning (disable : 4996) 
#include "funcs.h"
#include "io.h"

#include<stdlib.h>
#include <time.h>


struct data
{
	unsigned int block; // duration(12),hour(5),minute(6),month(4),day(5)
};

unsigned int creatMask(int high, int low)
{
	return (1<<(high+1)) - (1<<low);
}


void setInfo(Pdata Info, unsigned int TheInfo, unsigned int(*masking)(), unsigned int(*bitMove)(unsigned int, int) )
{
	TheInfo = bitMove(TheInfo,MOVE_LEFT) ;
	Info->block &= ~masking(); 
	Info->block |=  TheInfo;
}

Pdata setDate(Pdata Info)
{
	struct tm *date = getDate();
	// if info is NULL init new data block
	if( Info == NULL )
		Info = (Pdata)calloc(1, sizeof(Data) );
	//set date and time;
	setInfo(Info, date->tm_mday , DayMask   , DayMove );
	setInfo(Info, date->tm_mon+1, MonthMask , MonthMove);
	setInfo(Info, date->tm_min  , MinuteMask, MinuteMove);
	setInfo(Info, date->tm_hour , HourMask  , HourMove);

	return Info;
}

unsigned int getInfo(Pdata Info, unsigned int(*masking)(), unsigned int(*bitMove)(unsigned int, int) )
{
	unsigned int data = Info->block & masking();
	return bitMove(data, MOVE_RIGHT);
}

unsigned int DayMask(){ 
	return creatMask(DAY_HIGH      , DAY_LOW); 
	}

unsigned int MonthMask(){ 
	return creatMask(MONTH_HIGH    , MONTH_LOW); 
	}

unsigned int MinuteMask(){ 
	return creatMask(MINUTE_HIGH   , MINUTE_LOW ); 
	}

unsigned int HourMask(){
	return creatMask(HOUR_HIGH     , HOUR_LOW); 
	}

unsigned int DurationMask()  
{ 
	unsigned int mask = creatMask(DURATION_HIGH , DURATION_LOW);
	mask-=1;
	return mask;
	}


unsigned int DayMove(unsigned int day, int move ){
	return  day;
	}

unsigned int MonthMove(unsigned int month, int move){
	if(move == MOVE_LEFT )  return month << MOVE_MONTH ;
	else return month >> MOVE_MONTH;
	}

unsigned int MinuteMove(unsigned int minute, int move ){
	if(move == MOVE_LEFT )  return minute << MOVE_MINUTE ;
	else return minute >> MOVE_MINUTE ;
	}

unsigned int HourMove(unsigned int hour, int move){
	if(move == MOVE_LEFT )  return hour << MOVE_HOUR;
	else return hour >> MOVE_HOUR;
	}

unsigned int DuratinMove(unsigned int duration, int move){
	if(move == MOVE_LEFT )  return duration << MOVE_DURATION ;
	else return duration >> MOVE_DURATION ;
	}


int getInfoBlock(const Pdata theData){
	return theData->block;
	}

Pdata setDataBlock(int Block)
{
	Pdata theData = (Pdata)calloc(1, sizeof(Data) );
	theData->block = Block ; 
	return theData;
}

int comperDate(Pdata infoA , Pdata infoB)
{
	unsigned int monthA,dayA, houerA, minA;
	unsigned int monthB,dayB, houerB, minB;

	monthA = getInfo(infoA, MonthMask, MonthMove);
	dayA   = getInfo(infoA, DayMask, DayMove );
	houerA = getInfo(infoA, HourMask, HourMove );
	minA   = getInfo(infoA, MinuteMask, MinuteMove );

	monthB = getInfo(infoB, MonthMask, MonthMove);
	dayB   = getInfo(infoB, DayMask, DayMove );
	houerB = getInfo(infoB, HourMask, HourMove );
	minB   = getInfo(infoB, MinuteMask, MinuteMove );
 
	// simply comper from month->day->hour->min
	// if one is bigger or lower the comperation stop;
	// if all equle the date equle
	if( monthA > monthB)
		return 1;
	else if ( monthA < monthB )
		return -1;
	else
	{
		if( dayA  > dayB )
			return 1;
		else if ( dayA < dayB )
			return -1;
		else
		{
			if( houerA  > houerB )
				return 1;
			else if ( houerA < houerB )
				return -1;
			else
			{
				if( minA  > minB )
					return 1;
				else if ( minA < minB )
					return -1;
				else
				return 0;
			}
		}
	}
}