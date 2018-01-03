#ifndef __GRAPHICS_H
#define __GRAPHICS_H

/** @defgroup mouse mouse
* @{
*/

#include "pixelWings.h"

/**
 *	@brief creates animation with logo and main menu at the start of the program.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 */
void intro(gameData *game, projData *resources);


/**
 *	@brief updates the position of the cursor on the menus.
 *	@param x number of pixels to move horizontally.
 *	@param y number of pixels to move vertically.
 *	@param xi pointer to the current x coordinate of the cursor.
 *	@param yi pointer to the current y coordinate of the cursor.
 */
void moveCursor(short x, short y, unsigned short *xi, unsigned short *yi);

/**
 *	@brief updates the time (hours, minutes and seconds) and displays on the main menu.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 */
void displayTime(gameData *game, projData *resources);


/**
 *	@brief adds a letter to the username (maximum 12) that the player is wrtting on the game over menu depending on the scancode stored in MSByte.
 *	@param currentUsername pointer to the start of the username letter's array.
 *	@param cUsernameCounter pointer counter of the number of letters that contains the array.
 *	@param MSByte current scan code of the letter to add to the username.
 */
void addLetterUsername(char *currentUsername, int *cUsernameCounter, unsigned char MSByte);

/**
 *	@brief draws all the letters of the username on the game over menu.
 *	@param currentUsername pointer to the start of the username letter's array.
 *	@param cUsernameCounter pointer counter of the number of letters that contains the array.
 *	@param resources pointer to an object of type projData.
 */
void drawLetters(char *currentUsername, int cUsernameCounter, projData *resources);


/**
 *	@brief draws all the scores (username, points and date) on the leaderboard table.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 */
void printLeaderBoard(gameData *game, projData *resources);

/**
 *	@brief auxiliary function to print the username on the leaderboard.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@param x x coordinate to the start of the username.
 *	@param y y coordinate to the start of the username.
 *	@param pos position of the score on the array of scores.
 */
void printUsernameLeaderBoard(gameData *game, projData *resources, int x, int y, int pos);

/**@}*/

#endif /* __GRAPHICS_H */
