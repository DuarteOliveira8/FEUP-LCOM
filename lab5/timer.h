#ifndef __TIMER_H
#define __TIMER_H

/**
 * @brief Tests Timer 0 interrupt handling
 *
 * Subscribes Timer 0 interrupts and prints a message once
 *  per second for the specified time interval
 *
 * @param time Length of time interval while interrupts are subscribed
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_test_int(unsigned long time);


#endif /* __TIMER_H */
