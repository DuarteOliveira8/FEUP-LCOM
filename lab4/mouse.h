#ifndef __KEYBOARD_H
#define __KEYBOARD_H

//lab2 (timer) functions
int timer_subscribe_int();
int timer_unsubscribe_int();
void timer_int_handler();

//lab4 (mouse) functions
int mouse_subscribe_int();
int mouse_unsubscribe_int();
void mouseHandler(unsigned char *bytepointer);
int readMouse(unsigned char *packet, int mouseIRQ);
int readMouse_poll(unsigned char *packet);

#endif /* __KEYBOARD */
