#ifndef __MOUSE_H
#define __MOUSE_H

/** @defgroup mouse mouse
* @{
*/

/**
 *	@brief subscribes to the mouse and enables mouse interrupts.
 *	@return return 0 on success and 1 otherwise.
 */
int mouse_subscribe_int();

/**
 *	@brief disables mouse interrupts.
 *	@return return 0 on success and 1 otherwise.
 */
int mouse_irq_disable();

/**
 *	@brief enables mouse interrupts.
 *	@return return 0 on success and 1 otherwise.
 */
int mouse_irq_enable();

/**
 *	@brief unsubscribes to the mouse and disables mouse interrupts.
 *	@return return 0 on success and 1 otherwise.
 */
int mouse_unsubscribe_int();


/**
 *	@brief reads the mouse packet from the out buffer.
 *	@param bytepointer pointer to one of the three packets of the mouse.
 */
void mouseHandler(unsigned char *bytepointer);

/**@}*/

#endif /* __MOUSE */
