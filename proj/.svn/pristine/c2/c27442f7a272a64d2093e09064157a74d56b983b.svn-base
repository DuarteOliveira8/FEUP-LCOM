#include <minix/sysutil.h>
#include <minix/drivers.h>
#include "rtc.h"
#include "i8042.h"


int rtcUpdating(){
	unsigned long rega = 0;
	sys_outb(RTC_ADDRESS, RTC_REGA);
	sys_inb(RTC_DATA, &rega);

	if((rega & RTC_REGA_UIP) != 0)
		return 1;
	else
		return 0;
}


int bcd(){
	unsigned long regb = 0;
	sys_outb(RTC_ADDRESS, RTC_REGB);
	sys_inb(RTC_DATA, &regb);

	if(!(regb & RTC_REGB_DM))
		return 1;
	else
		return 0;
}


unsigned long bcdToBinary(unsigned long *bcd){
	unsigned long binary;
	binary = (((*bcd) & 0xF0) >> 4)*10 + ((*bcd) & 0x0F);

	return binary;
}


void getDate(unsigned long *year, unsigned long *month, unsigned long *day){
	sys_outb(RTC_ADDRESS, RTC_YEAR);
	sys_inb(RTC_DATA, year);
	sys_outb(RTC_ADDRESS, RTC_MONTH);
	sys_inb(RTC_DATA, month);
	sys_outb(RTC_ADDRESS, RTC_DAY);
	sys_inb(RTC_DATA, day);

	if(bcd()){
		*year = bcdToBinary(year);
		*month = bcdToBinary(month);
		*day = bcdToBinary(day);
	}
}


void getHour(unsigned long *hour, unsigned long *minutes, unsigned long *seconds){
	sys_outb(RTC_ADDRESS, RTC_HOURS);
	sys_inb(RTC_DATA, hour);
	sys_outb(RTC_ADDRESS, RTC_MINUTES);
	sys_inb(RTC_DATA, minutes);
	sys_outb(RTC_ADDRESS, RTC_SECONDS);
	sys_inb(RTC_DATA, seconds);

	if(bcd()){
		*hour = bcdToBinary(hour);
		*minutes = bcdToBinary(minutes);
		*seconds = bcdToBinary(seconds);
	}
}

void updateRTC(projData *resources){
	do{
		if(!rtcUpdating()){
			getDate(&resources->currentDate.year, &resources->currentDate.month, &resources->currentDate.day);
			getHour(&resources->currentDate.hour, &resources->currentDate.min, &resources->currentDate.sec);
		}
	} while (rtcUpdating());
}
