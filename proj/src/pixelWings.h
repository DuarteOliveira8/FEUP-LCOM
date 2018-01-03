#ifndef __PIXELWINGS_H
#define __PIXELWINGS_H

#include "bitmap.h"

/** @defgroup pixelWings pixelWings
 * @{
 */

typedef struct {
	int timer;	/**< timer IRQ. */
	int keyboard;	/**< keyboard IRQ. */
	int mouse;	/**< mouse IRQ. */
} returnbits;

typedef struct {
	/** @name  bitmaps
	 *@{
	 *
	 */
	Bitmap *menu;
	Bitmap *cursor;
	Bitmap *fundo;
	Bitmap *fundo1;
	Bitmap *fundo2;
	Bitmap *fundo3;
	Bitmap *fundo4;
	Bitmap *fundo5;
	Bitmap *fundo6;
	Bitmap *fundo7;
	Bitmap *fundo8;
	Bitmap *fundo9;
	Bitmap *dragon1;
	Bitmap *dragon2;
	Bitmap *dragon3;
	Bitmap *dragon4;
	Bitmap *dragon11;
	Bitmap *dragon22;
	Bitmap *dragon33;
	Bitmap *dragon44;
	Bitmap *dragon1die;
	Bitmap *dragon11die;
	Bitmap *fire;
	Bitmap *firehit1;
	Bitmap *firehit2;
	Bitmap *ice;
	Bitmap *icehit1;
	Bitmap *icehit2;
	Bitmap *bat;
	Bitmap *batdie1;
	Bitmap *batdie2;
	Bitmap *zero;
	Bitmap *one;
	Bitmap *two;
	Bitmap *three;
	Bitmap *four;
	Bitmap *five;
	Bitmap *six;
	Bitmap *seven;
	Bitmap *eight;
	Bitmap *nine;
	Bitmap *score;
	Bitmap *gameover;
	Bitmap *pause;
	Bitmap *a;
	Bitmap *b;
	Bitmap *c;
	Bitmap *d;
	Bitmap *e;
	Bitmap *f;
	Bitmap *g;
	Bitmap *h;
	Bitmap *i;
	Bitmap *j;
	Bitmap *k;
	Bitmap *l;
	Bitmap *m;
	Bitmap *n;
	Bitmap *o;
	Bitmap *p;
	Bitmap *q;
	Bitmap *r;
	Bitmap *s;
	Bitmap *t;
	Bitmap *u;
	Bitmap *v;
	Bitmap *w;
	Bitmap *x;
	Bitmap *y;
	Bitmap *z;
	Bitmap *blank;
	Bitmap *leaderboard;
	Bitmap *options;
	Bitmap *saved;
	Bitmap *logodragon1;
	Bitmap *logodragon2;
	Bitmap *logodragon3;
	Bitmap *logodragon4;
	Bitmap *botoes2;
	Bitmap *botoes4;
	Bitmap *botoes6;
	Bitmap *botoes8;
	Bitmap *barra;
	Bitmap *colon;
	Bitmap *power04;
	Bitmap *power14;
	Bitmap *power24;
	Bitmap *power34;
	Bitmap *power44;
	Bitmap *hoverplay;
	Bitmap *hoverstats;
	Bitmap *hoveroptions;
	Bitmap *hoverexit;
	Bitmap *hoverexit2;
	Bitmap *hoverexit3;
	Bitmap *hoverexit4;
	Bitmap *hoverexit5;
	Bitmap *hoverok;
	Bitmap *hoverretry;
	Bitmap *hoverrestart;
	Bitmap *hovercontinue;
	/** @} end of bitmaps */
} bitmaps;

typedef struct {
	int x;	/**< x coordinate of the object. */
	int y;	/**< y coordinate of the object. */
	int counter;	/**< counter to create next object of type coordenada. */
	int collision;	/**< 0 - no collision / >=1 - collision. */
} coordenada;

typedef struct {
	coordenada bats[9];	/**< group of 9 bats of type coordenada. */
	int counter;	/**< counter for the size of the array bats. */
} batgroup;

typedef struct {
	char username[13];	/**< array for the characters of the username. */
	unsigned int usernameCounter;	/**< counter for the size of the array username. */
	int valor;	/**< value of the score. */
	char currentDate[10];	/**< date of the score. */
} score;

typedef struct {
	unsigned long day;	/**< last updated day. */
	unsigned long month;	/**< last updated month. */
	unsigned long year;	/**< last updated year. */
	unsigned long sec;	/**< last updated second. */
	unsigned long min;	/**< last updated minute. */
	unsigned long hour;	/**< last updated hour. */
} date;

typedef struct {
	returnbits returnbit;	/**< object of type returnbits. Contains all the IRQs. */

	bitmaps bitmap;	/**< object of type bitmaps. Contains all the bitmaps. */

	date currentDate;	/**< object of type date. Contains the last updated date. */
} projData;

typedef struct {
	unsigned short dragonX;	/**< current x coordinate of the dragon. */
	unsigned short dragonY;	/**< current y coordinate of the dragon. */
	int dragonCollision; /**< 0 - no collision / >=1 - collision. */

	coordenada fireBalls[40];	/**< array of fireballs of type coordenada. */
	int fireballCounter;	/**< counter to the size of the array fireBalls. */

	int scoreAtual;	/**< current score of the player. */
	score scores[11];	/**< array of the best 10 scores. The 11th score is from the last gameplay (not displayed or saved). */
	int scoreCounter;	/**< counter to the size of the array scores. */

	unsigned int currentDragon;	/**< 0 - fire dragon / 1 - ice dragon. */

	batgroup batgroups[20];	/**< array of bat groups of type batgroup. */
	int batgroupCounter;	/**< counter to the size of the array batgroups. */
	batgroup initializerBats;	/**< variable of type batgroup initialized at the start of the game to make creation of bat groups easier. */
	int batSpeed;	/**< speed of the bat groups. */
	int batPeriod;	/**< period in between bat groups spawning. */
} gameData;

/**< Represents the buttons on the menus. */
typedef enum {
	PLAYBUTTON, OPTIONSBUTTON, STATSBUTTON, EXITBUTTON, RESTARTBUTTON, NOTHING
} button;
typedef enum {
	HOVERPLAY, HOVEROPTIONS, HOVERSTATS, HOVEREXIT, HOVEREXIT2, HOVEREXIT3, HOVEREXIT4, HOVEREXIT5, HOVEROK, HOVERRETRY, HOVERCONTINUE, HOVERRESTART, HOVERNOTHING
} hoverbutton;

/**< Represents the power bar states in game. */
typedef enum {
	ONEOUTOFFOUR, TWOOUTOFFOUR, THREEOUTOFFOUR, FOUROUTOFFOUR, NULLBAR
} bar;


/**
 * 	@brief loads all the bitmaps, allocs memory for the date variables, loads the scores from the file, prepare the screen to mode 0x117, shows the intro animation and subscribes to the mouse, keyboard and timer.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@return return 0 on success and -1 otherwise.
 */
int initPixelWings(gameData *game, projData *resources);

/**
 *	@brief deletes all the bitmaps, saves the scores to the file, exits to the original screen mode and unsubscribes to the mouse, keyboard and timer.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@return return 0 on success and -1 otherwise.
 */
int leavePixelWings(gameData *game, projData *resources);


/**
 *	@brief handles the interrupts form the mouse, keyboard and timer on the main menu.
 *	Calls the function upon clicking button the PLAY button,
 *	calls function leaderboardDisplay upon clicking LEADERBOARD button,
 *	calls function options upon clicking the OPTIONS button and
 *	calls function leavePixelWings and exits the program upon clicking the EXIT button.
 *	@return return 0 on success and -1 otherwise.
 */
int mainMenu();


/**
 *	@brief handles the interrupts form the mouse, keyboard and timer on the pause menu.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@return returns 0 upon clicking the CONTINUE button,
 *	returns 1 upon clicking the RETRY button and
 *	returns 2 upon clicking the EXIT button.
 */
int pauseMenu(gameData *game, projData *resources);


/**
 *	@brief handles the interrupts form the mouse, keyboard and timer on the pause menu.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 *	@return returns 1 upon clicking the RESTART button and
 *	returns 2 upon clicking the EXIT button.
 */
int gameOver(gameData *game, projData *resources);


/**
 *	@brief handles the interrupts form the mouse, keyboard and timer on the options menu.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 */
void options(gameData *game, projData *resources);


/**
 *	@brief handles the interrupts form the mouse, keyboard and timer on the leaderboard menu.
 *	@param game pointer to an object of type gameData.
 *	@param resources pointer to an object of type projData.
 */
void leaderboardDisplay(gameData *game, projData *resources);


/**
 *	@brief loads the scores from the file scores.txt to the game structure.
 *	@param game pointer to an object of type gameData.
 */
void loadScores(gameData *game);

/**
 *	@brief saves the scores from game structure to the the file scores.txt.
 *	@param game pointer to an object of type gameData.
 */
void saveScores(gameData *game);

/**@}*/

#endif /* __PIXELWINGS_H */
