#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include "i8042.h"
#include "i8254.h"
#include "lmlib.h"
#include "vbe.h"
#include "video_gr.h"
#include "game.h"
#include "keyboard.h"
#include "timer.h"
#include "mouse.h"
#include "rtc.h"

void startGame(gameData *game){
	//dragon coords
	game->dragonX = 37;
	game->dragonY = 326;
	game->dragonCollision = 0;

	//dragon ball
	game->fireballCounter = 0;

	//bats
	game->batgroupCounter = 0;

	game->initializerBats.counter = 9;

	game->initializerBats.bats[0].x = 1023;
	game->initializerBats.bats[0].y = 35;
	game->initializerBats.bats[0].collision = 0;

	game->initializerBats.bats[1].x = 1023;
	game->initializerBats.bats[1].y = 115;
	game->initializerBats.bats[1].collision = 0;

	game->initializerBats.bats[2].x = 1023;
	game->initializerBats.bats[2].y = 195;
	game->initializerBats.bats[2].collision = 0;

	game->initializerBats.bats[3].x = 1023;
	game->initializerBats.bats[3].y = 275;
	game->initializerBats.bats[3].collision = 0;

	game->initializerBats.bats[4].x = 1023;
	game->initializerBats.bats[4].y = 355;
	game->initializerBats.bats[4].collision = 0;

	game->initializerBats.bats[5].x = 1023;
	game->initializerBats.bats[5].y = 435;
	game->initializerBats.bats[5].collision = 0;

	game->initializerBats.bats[6].x = 1023;
	game->initializerBats.bats[6].y = 515;
	game->initializerBats.bats[6].collision = 0;

	game->initializerBats.bats[7].x = 1023;
	game->initializerBats.bats[7].y = 595;
	game->initializerBats.bats[7].collision = 0;

	game->initializerBats.bats[8].x = 1023;
	game->initializerBats.bats[8].y = 675;
	game->initializerBats.bats[8].collision = 0;

	game->batSpeed = 3;

	game->batPeriod = 180;

	//score
	game->scoreAtual = 0;
}


int openGame(gameData *game, projData *resources){
	//interrupts
	int ipc_status;
	message msg;
	char r;

	//keyboard
	unsigned char MSByte = 0;

	//mouse
	unsigned char packet[3];
	short y = 0;
	int counter_packets = 0;

	startGame(game);

	//power bar status counter;
	bar barstatus = NULLBAR;
	int lastscorebar = 0;
	int firecounter;

	//game state
	int gameState;


	while(1) {

		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & resources->returnbit.keyboard) {
					changeScancode(&MSByte);
					if(MSByte == ESC)
					{
						gameState = pauseMenu(game, resources);
						if (gameState != 0)
						{
							return gameState;
						}
					}
				}
				if (msg.NOTIFY_ARG & resources->returnbit.timer){

					if ((game->scoreAtual != 0) && (game->scoreAtual % 10 == 0)){
						if (game->scoreAtual != lastscorebar) {
							if(barstatus == NULLBAR)
								barstatus = ONEOUTOFFOUR;
							else if(barstatus == ONEOUTOFFOUR)
								barstatus = TWOOUTOFFOUR;
							else if(barstatus == TWOOUTOFFOUR)
								barstatus = THREEOUTOFFOUR;
							else if(barstatus == THREEOUTOFFOUR)
								barstatus = FOUROUTOFFOUR;

							lastscorebar = game->scoreAtual;
						}
					}

					//criar bolas de fogo (caso esteja parado)
					if (game->fireballCounter > 0)
					{
						game->fireBalls[game->fireballCounter - 1].counter += 1;
						if (game->fireBalls[game->fireballCounter - 1].counter >= 15)
						{
							//special attacks
							if ((packet[0] & BIT(0)) && (MSByte == SPACE) & (barstatus != NULLBAR)) //click esquerdo (fire ball)
							{
								if (barstatus == ONEOUTOFFOUR) { //two fireballs
									for (firecounter = 1; firecounter < 3; firecounter++) {
										coordenada fireBall;
										fireBall.collision = 0;
										fireBall.x = 212;
										if(firecounter == 1)
											fireBall.y = game->dragonY + 12;
										else if(firecounter == 2)
											fireBall.y = game->dragonY + 76;
										fireBall.counter = 0;
										game->fireballCounter++;
										game->fireBalls[game->fireballCounter - 1] = fireBall;
									}

									barstatus = NULLBAR;
								}
								else if (barstatus == TWOOUTOFFOUR) { //three fireballs
									for (firecounter = 1; firecounter < 4; firecounter++) {
										coordenada fireBall;
										fireBall.collision = 0;
										fireBall.x = 212;
										if(firecounter == 1)
											fireBall.y = game->dragonY + 58;
										else if(firecounter == 2)
											fireBall.y = game->dragonY + 120;
										else if(firecounter == 3)
											fireBall.y = game->dragonY - 12;
										fireBall.counter = 0;
										game->fireballCounter++;
										game->fireBalls[game->fireballCounter - 1] = fireBall;
									}

									barstatus = ONEOUTOFFOUR;
								}
								else if (barstatus == THREEOUTOFFOUR) { //four fireballs
									for (firecounter = 1; firecounter < 5; firecounter++) {
										coordenada fireBall;
										fireBall.collision = 0;
										fireBall.x = 212;
										if(firecounter == 1)
											fireBall.y = game->dragonY - 56;
										else if(firecounter == 2)
											fireBall.y = game->dragonY + 24;
										else if(firecounter == 3)
											fireBall.y = game->dragonY - 105;
										else if(firecounter == 3)
											fireBall.y = game->dragonY + 186;
										fireBall.counter = 0;
										game->fireballCounter++;
										game->fireBalls[game->fireballCounter - 1] = fireBall;
									}

									barstatus = TWOOUTOFFOUR;
								}
								else if (barstatus == FOUROUTOFFOUR) { //nine fireballs
									for (firecounter = 0; firecounter < 9; firecounter++) {
										coordenada fireBall;
										fireBall.collision = 0;
										fireBall.x = 212;
										fireBall.y = 56 + 80 * firecounter;
										fireBall.counter = 0;
										game->fireballCounter++;
										game->fireBalls[game->fireballCounter - 1] = fireBall;
									}

									barstatus = THREEOUTOFFOUR;
								}
							}
							else if (packet[0] & BIT(0)) //click esquerdo (fire ball)
							{
								coordenada fireBall;
								fireBall.collision = 0;
								fireBall.x = 212;
								fireBall.y = game->dragonY + 58;
								fireBall.counter = 0;
								game->fireballCounter++;
								game->fireBalls[game->fireballCounter - 1] = fireBall;
							}
						}
					}

					//desenhar frame
					if(drawFrame(game, resources, barstatus) == -1)
					{
						drawThirdBuffer();
						tickdelay(10);
						gameState = gameOver(game, resources);
						return gameState;
					}
					drawThirdBuffer();
				}
				if (msg.NOTIFY_ARG & resources->returnbit.mouse){
					//desenhar personagem
					mouseHandler(&packet[counter_packets]);

					counter_packets++;

					if(!(packet[0] & BIT(3)))
					{
						counter_packets = 0;
					}

					if (counter_packets == 3)
					{
						if (packet[0] & BIT(5))
						{
							y = -(256 - packet[2]);
						}
						else
						{
							y = packet[2];
						}

						if (game->fireballCounter > 0)
						{
							if (game->fireBalls[game->fireballCounter - 1].counter >= 15)
							{
								if (packet[0] & BIT(0)) //click esquerdo (fire ball)
								{
									coordenada fireBall;
									fireBall.collision = 0;
									fireBall.x = 212;
									fireBall.y = game->dragonY + 58;
									fireBall.counter = 0;
									game->fireballCounter++;
									game->fireBalls[game->fireballCounter - 1] = fireBall;
								}
							}
						}
						else
						{
							if (packet[0] & BIT(0)) //click esquerdo (fire ball)
							{
								coordenada fireBall;
								fireBall.collision = 0;
								fireBall.x = 212;
								fireBall.y = game->dragonY + 58;
								fireBall.counter = 0;
								game->fireballCounter++;
								game->fireBalls[game->fireballCounter - 1] = fireBall;
							}
						}

						moveCharacter(y, &game->dragonY);

						counter_packets = 0;
					}
				}
				break;
			default:
				break;
			}
		}
		else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	return 0;
}




void moveCharacter(short y, unsigned short *yi) {
	if(y > 0)
	{
		if (*yi - y < 0)
		{
			*yi = 0;
		}
		else
		{
			*yi -= y;
		}
	}
	else if(y < 0)
	{
		if (*yi - y >= 651)
		{
			*yi = 650;
		}
		else
		{
			*yi -= y;
		}
	}
}



int drawFrame(gameData *game, projData *resources, bar powerbarstatus){
	static int counterdragon = 1, counter = 0, counterFreq = 0;

	//fundo animacao
	drawSecondBuffer(resources->bitmap.fundo, 0 - ((counter*2) % 1024), 0);
	drawSecondBuffer(resources->bitmap.fundo, 1024 - ((counter*2) % 1024), 0);

	//BATS
	if (batHandler(game, resources, &counter, &counterFreq) == -1)
		return -1;

	//move fireball
	fireballHandler(game, resources);

	//bat speed
	if (counter % 1200 == 0)
	{
		game->batSpeed *= 1.5;
		if (game->batPeriod > 50)
			game->batPeriod /= 1.2;
	}

	//dragon gif
	if(counterdragon == 1){
		if(game->currentDragon == 0){
			drawSecondBuffer(resources->bitmap.dragon1, game->dragonX, game->dragonY);
		}
		else if(game->currentDragon == 1)
			drawSecondBuffer(resources->bitmap.dragon11, game->dragonX, game->dragonY);
	}
	else if(counterdragon == 2){
		if(game->currentDragon == 0)
			drawSecondBuffer(resources->bitmap.dragon2, game->dragonX, game->dragonY);
		else if(game->currentDragon == 1)
			drawSecondBuffer(resources->bitmap.dragon22, game->dragonX, game->dragonY);
	}
	else if(counterdragon == 3){
		if(game->currentDragon == 0)
			drawSecondBuffer(resources->bitmap.dragon3, game->dragonX, game->dragonY);
		else if(game->currentDragon == 1)
			drawSecondBuffer(resources->bitmap.dragon33, game->dragonX, game->dragonY);
	}
	else if(counterdragon == 4){
		if(game->currentDragon == 0)
			drawSecondBuffer(resources->bitmap.dragon4, game->dragonX, game->dragonY);
		else if(game->currentDragon == 1)
			drawSecondBuffer(resources->bitmap.dragon44, game->dragonX, game->dragonY);
	}

	counter++;

	if (counter % 7 == 0)
	{
		if(counterdragon == 4)
		{
			counterdragon = 1;
		}
		else
		{
			counterdragon++;
		}
	}

	if(powerbarstatus == NULLBAR)
		drawSecondBuffer(resources->bitmap.power04, 815, 738);
	else if(powerbarstatus == ONEOUTOFFOUR)
		drawSecondBuffer(resources->bitmap.power14, 815, 738);
	else if(powerbarstatus == TWOOUTOFFOUR)
		drawSecondBuffer(resources->bitmap.power24, 815, 738);
	else if(powerbarstatus == THREEOUTOFFOUR)
		drawSecondBuffer(resources->bitmap.power34, 815, 738);
	else if(powerbarstatus == FOUROUTOFFOUR)
		drawSecondBuffer(resources->bitmap.power44, 815, 738);

	//SCORE
	scoreHandler(game, resources);

	//DRAW ON SCREEN
	drawMainBuffer();

	return 0;
}



void fireballHandler(gameData *game, projData *resources){
	int i, k, m;

	if (game->fireballCounter > 0)
	{
		for (i = 0; i < game->fireballCounter; i++)
		{
			if (game->fireBalls[i].collision > 0)
			{
				game->fireBalls[i].collision += 1;
				if (game->fireBalls[i].collision <= 7)
				{
					if(game->currentDragon == 0){
						drawSecondBuffer(resources->bitmap.firehit1, game->fireBalls[i].x, game->fireBalls[i].y);
					}

					if(game->currentDragon == 1){
						drawSecondBuffer(resources->bitmap.icehit1, game->fireBalls[i].x, game->fireBalls[i].y);
					}
				}
				else if (game->fireBalls[i].collision <= 14)
				{
					if(game->currentDragon == 0){
						drawSecondBuffer(resources->bitmap.firehit1, game->fireBalls[i].x, game->fireBalls[i].y);
					}

					if(game->currentDragon == 1){
						drawSecondBuffer(resources->bitmap.icehit2, game->fireBalls[i].x, game->fireBalls[i].y);
					}
				}
				else if (game->fireBalls[i].collision > 14)
				{
					for (m = i; m < game->fireballCounter - 1; m++)
					{
						game->fireBalls[m] = game->fireBalls[m + 1];
					}
					game->fireballCounter -= 1;
				}
				game->fireBalls[i].x -= game->batSpeed;

			}
			else
			{
				if(game->currentDragon == 0){
					drawSecondBuffer(resources->bitmap.fire, game->fireBalls[i].x, game->fireBalls[i].y);
				}

				if(game->currentDragon == 1){
					drawSecondBuffer(resources->bitmap.ice, game->fireBalls[i].x, game->fireBalls[i].y);
				}

				game->fireBalls[i].x += 5;
			}

			if (game->fireBalls[i].x >= 1024)
			{
				for (k = i; k < game->fireballCounter - 1; k++)
				{
					game->fireBalls[k] = game->fireBalls[k + 1];
				}
				game->fireballCounter -= 1;
			}
		}
	}
}



int batHandler(gameData *game, projData *resources, int *counter, int *counterFreq){
	int i, k, j, m;

	//bat creation
	if (*counterFreq >= game->batPeriod)
	{
		game->batgroups[game->batgroupCounter] = game->initializerBats;
		game->batgroupCounter++;
		*counterFreq = 0;
	}
	*counterFreq += 1;

	//move bats and collisions
	if (game->batgroupCounter > 0)
	{
		for (i = 0; i < game->batgroupCounter; i++)
		{
			for (k = 0; k < game->batgroups[i].counter; k++)
			{
				if (game->batgroups[i].bats[k].collision == 0)
				{
					for (j = 0; j < game->fireballCounter; j++)
					{
						if ((game->fireBalls[j].x + 44 >= game->batgroups[i].bats[k].x) && (game->fireBalls[j].x + 44 <= game->batgroups[i].bats[k].x + 72))
						{
							if (((game->fireBalls[j].y < game->batgroups[i].bats[k].y + 60) && (game->fireBalls[j].y > game->batgroups[i].bats[k].y)) ||
									((game->fireBalls[j].y + 26 < game->batgroups[i].bats[k].y + 60) && (game->fireBalls[j].y + 26 > game->batgroups[i].bats[k].y)))
							{
								//								for (m = j; m < game->fireballCounter - 1; m++)
								//								{
								//									game->fireBalls[m] = game->fireBalls[m + 1];
								//								}
								//								game->fireballCounter -= 1;
								game->fireBalls[j].collision += 1;

								game->batgroups[i].bats[k].collision += 1;

								game->scoreAtual += 1;
							}
						}
					}
				}

				if (game->batgroups[i].bats[k].collision == 0)
				{
					if (((game->batgroups[i].bats[k].x >= game->dragonX) && (game->batgroups[i].bats[k].x <= game->dragonX + 176)) ||
							((game->batgroups[i].bats[k].x + 72 >= game->dragonX) && (game->batgroups[i].bats[k].x + 72 <= game->dragonX + 176)))
					{
						if (((game->batgroups[i].bats[k].y >= game->dragonY + 22) && (game->batgroups[i].bats[k].y <= game->dragonY + 118)) ||
								((game->batgroups[i].bats[k].y + 60 >= game->dragonY + 22) && (game->batgroups[i].bats[k].y + 60 <= game->dragonY + 118)))
						{
							updateRTC(resources);
							drawSecondBuffer(resources->bitmap.fundo, 0 - ((*counter * 2) % 1024), 0);
							drawSecondBuffer(resources->bitmap.fundo, 1024 - ((*counter * 2) % 1024), 0);
							if(game->currentDragon == 0)
								drawSecondBuffer(resources->bitmap.dragon1die, game->dragonX, game->dragonY - 20);
							if(game->currentDragon == 1)
								drawSecondBuffer(resources->bitmap.dragon11die, game->dragonX, game->dragonY - 20);
							*counter = 0;
							return -1;
						}
					}
				}

				if (game->batgroups[i].bats[k].collision > 0)
				{
					game->batgroups[i].bats[k].collision += 1;
					if (game->batgroups[i].bats[k].collision <= 7)
					{
						drawSecondBuffer(resources->bitmap.batdie1, game->batgroups[i].bats[k].x, game->batgroups[i].bats[k].y);
					}
					else if (game->batgroups[i].bats[k].collision <= 14)
					{
						drawSecondBuffer(resources->bitmap.batdie2, game->batgroups[i].bats[k].x, game->batgroups[i].bats[k].y);
					}
					else if (game->batgroups[i].bats[k].collision > 14)
					{
						for (m = k; m < game->batgroups[i].counter - 1; m++)
						{
							game->batgroups[i].bats[m] = game->batgroups[i].bats[m + 1];
						}
						game->batgroups[i].counter -= 1;
					}
				}
				else
				{
					drawSecondBuffer(resources->bitmap.bat, game->batgroups[i].bats[k].x, game->batgroups[i].bats[k].y);
				}
				game->batgroups[i].bats[k].x -= game->batSpeed;
			}

			if (game->batgroups[i].counter == 0)
			{
				for (k = 0; k < game->batgroupCounter - 1; k++)
				{
					game->batgroups[k] = game->batgroups[k + 1];
				}
				game->batgroupCounter--;
			}
		}

		if (game->batgroups[0].bats[0].x + 72 <= 0)
		{
			for (k = 0; k < game->batgroupCounter - 1; k++)
			{
				game->batgroups[k] = game->batgroups[k + 1];
			}
			game->batgroupCounter--;
		}
	}

	return 0;
}



void scoreHandler(gameData *game, projData *resources){
	int zeros;
	int digits;
	int currentDigit;
	int numberX = 923;
	int i;

	if (game->scoreAtual != 0)
	{
		zeros  = 5 - (floor(log10(game->scoreAtual)) + 1);
		digits = 5 - zeros;
	}
	else
	{
		zeros = 5;
		digits = -1;
	}

	drawSecondBuffer(resources->bitmap.score, 815, 6);

	for (i = 0; i < zeros; i++)
	{
		drawSecondBuffer(resources->bitmap.zero, numberX, 6);
		numberX += 20;
	}

	for (i = digits - 1; i >= 0; i--)
	{
		currentDigit = floor((game->scoreAtual/(int)pow(10,i))%10);

		switch (currentDigit)
		{
		case 0:
			drawSecondBuffer(resources->bitmap.zero, numberX, 6);
			break;
		case 1:
			drawSecondBuffer(resources->bitmap.one, numberX, 6);
			break;
		case 2:
			drawSecondBuffer(resources->bitmap.two, numberX, 6);
			break;
		case 3:
			drawSecondBuffer(resources->bitmap.three, numberX, 6);
			break;
		case 4:
			drawSecondBuffer(resources->bitmap.four, numberX, 6);
			break;
		case 5:
			drawSecondBuffer(resources->bitmap.five, numberX, 6);
			break;
		case 6:
			drawSecondBuffer(resources->bitmap.six, numberX, 6);
			break;
		case 7:
			drawSecondBuffer(resources->bitmap.seven, numberX, 6);
			break;
		case 8:
			drawSecondBuffer(resources->bitmap.eight, numberX, 6);
			break;
		case 9:
			drawSecondBuffer(resources->bitmap.nine, numberX, 6);
			break;
		}

		numberX += 20;
	}
}
