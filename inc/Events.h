#ifndef	_EVENT_H
#define	_EVENT_H

struct NEWLOGSTA{
       //unsigned char Sta;//event status bit0: alarm  bit1:recorded times of the alarm        bit2:recorded time of this alarm
	unsigned char Sta;//事件状态  bit0:有报警  bit1:此次报警已记录次数  bit2:此次报警已记录时间
       //unsigned short Time;//event time
	unsigned short Time;//事件时间
  };


extern void Events(void);
void EventsRead(int8u *ucBuf,unsigned int E_ENTRY,unsigned char Num);
void EventsTimes(unsigned int uiAdr);
void EventsReadTimes(unsigned int uiAdr,unsigned char *ucCnt);

#endif