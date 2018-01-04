#ifndef __KEYBOARD_H
#define __KEYBOARD_H

//interrupt subscription functions
int keyboard_subscribe_int(void );
int keyboard_unsubscribe_int();

//read from KBC
int readKBC(unsigned char *dataKBC);

//print functions
void printScancodeC(unsigned char *MSByte);

//lab3 (timer) functions
int timer_subscribe_int();
int timer_unsubscribe_int();
void timer_int_handler();

#endif /* __KEYBOARD */
