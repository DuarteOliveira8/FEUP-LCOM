#ifndef __GAME_H
#define __GAME_H

/** @defgroup game game
* @{
*/

#include "pixelWings.h"


/**
 *	@brief initializes variables to start the game.
 *	@param game pointer to an object of type gameData.
 */
void startGame(gameData *game);

/**
 *	@brief handles all the interrupts from the timer, keyboard and mouse for the gameplay.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@return gameState returned by functions pauseMenu or gameOver. Returns 1 to retry or 2 to exit to mainMenu.
 */
int openGame(gameData *game, projData *resources);

/**
 *	@brief moves the position of the dragon vertically.
 *	@param y number of pixels to move.
 *	@param yi pointer to the current y coordinate of the dragon.
 */
void moveCharacter(short y, unsigned short *yi);

/**
 *	@brief prepares the frame on second buffer and copies to main buffer at the end. Also checks the collisions.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@param powerbarstatus object of type bar.
 *	@return -1 if there's a collision with the dragon (game over) or 0 if no collision with the dragon.
 */
int drawFrame(gameData *game, projData *resources, bar powerbarstatus);

/**
 *	@brief handles the movement of the fireballs and draws each on the second buffer.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 */
void fireballHandler(gameData *game, projData *resources);

/**
 * 	@brief handles the movement for the bats and collisions with the fireballs and the dragon.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@param counter pointer to the counter of timer ticks to create bats groups.
 *	@param counterFreq pointer to the counter of the timer ticks to change the frequency.
 *	@return -1 if there's a collision with the dragon (game over) or 0 if no collision with the dragon.
 */
int batHandler(gameData *game, projData *resources, int *counter, int *counterFreq);

/**
 *	@brief handles the current score of the player and draws the number on the second buffer.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 */
void scoreHandler(gameData *game, projData *resources);

/**@}*/

#endif /* __GAME_H */
