#ifndef __KEYBOARD_H
#define __KEYBOARD_H


/**
 *	@brief subscribes to the keyboard and enables keyboard interrupts.
 *	@return return 0 on success and 1 otherwise.
 */
int keyboard_subscribe_int();

/**
 *	@brief unsubscribes to the keyboard and disables keyboard interrupts.
 *	@return return 0 on success and 1 otherwise.
 */
int keyboard_unsubscribe_int();

/**
 *	@brief reads the scan code from the output buffer.
 *	@return return 0 on success and 1 otherwise.
 */
void kbc_handler();

/**
 *	@brief changes MSByte to the scna code received by the keyboard.
 *	@param MSByte, pointer to MSByte to store the scan code received by the keyboard.
 */
void changeScancode(unsigned char *MSByte);

/**@}*/

#endif /* __KEYBOARD */
