#ifndef __TIMER_H
#define __TIMER_H

/** @defgroup timer timer
 * @{
 */

/**
 *	@brief subscribes to the timer and enables timer interrupts.
 *	@return return return o bit of index oldhook on success and 1 otherwise.
 */
int timer_subscribe_int();

/**
 *	@brief unsubscribes to the timer and disables timer interrupts.
 *	@return return 0 on success and 1 otherwise.
 */
int timer_unsubscribe_int();

/**@}*/

#endif /* __TIMER_H */
