#ifndef	_EVENT_H
#define	_EVENT_H

struct NEWLOGSTA{
       //unsigned char Sta;//event status bit0: alarm  bit1:recorded times of the alarm        bit2:recorded time of this alarm
	unsigned char Sta;//�¼�״̬  bit0:�б���  bit1:�˴α����Ѽ�¼����  bit2:�˴α����Ѽ�¼ʱ��
       //unsigned short Time;//event time
	unsigned short Time;//�¼�ʱ��
  };


extern void Events(void);
void EventsRead(int8u *ucBuf,unsigned int E_ENTRY,unsigned char Num);
void EventsTimes(unsigned int uiAdr);
void EventsReadTimes(unsigned int uiAdr,unsigned char *ucCnt);

#endif