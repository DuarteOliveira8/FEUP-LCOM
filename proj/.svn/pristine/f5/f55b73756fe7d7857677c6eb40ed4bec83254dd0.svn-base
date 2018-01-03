#ifndef __RTC_H
#define __RTC_H

/** @defgroup rtc rtc
 * @{
 */

#include "pixelWings.h"

/**
 *	@brief verifies if the rtc is updating.
 *	@return returns 1 if the rtc is updating and 0 if not.
 */
int rtcUpdating();

/**
 *	@brief verifies if the values given by RTC are in binary-coded decimals (BCD).
 *	@return returns 1 if the values given by the RTC are in BCD and 0 otherwise.
 */
int bcd();

/**
 *	@brief converts the values given by the RTC form BCD to binary.
 *	@return returns the value in binary.
 */
unsigned long bcdToBinary(unsigned long *bcd);

/**
 *	@brief updates to the current year, current month and current day.
 *	@param year pointer to the last updated year from the struct resources.
 *	@param month pointer to the last updated month from the struct resources.
 *	@param day pointer to the last updated day from the struct resources.
 */
void getDate(unsigned long *year, unsigned long *month, unsigned long *day);

/**
 *	@brief updates to the current hour, current minutes and current seconds.
 *	@param hour pointer to the last updated hour from the struct resources.
 *	@param minutes pointer to the last updated minutes from the struct resources.
 *	@param seconds pointer to the last updated seconds from the struct resources.
 */
void getHour(unsigned long *hour, unsigned long *minutes, unsigned long *seconds);

/**
 * 	@brief updates the current date from the struct resources.
 *	@param resources pointer to an object of type projData struct.
 */
void updateRTC(projData *resources);

/**@}*/


#endif /* __RTC_H */
