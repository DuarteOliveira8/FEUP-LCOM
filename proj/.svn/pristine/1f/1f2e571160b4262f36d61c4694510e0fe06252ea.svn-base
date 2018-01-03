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
#include "graphics.h"


void intro(gameData *game, projData *resources){
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo1, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo2, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo3, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo4, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo5, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo6, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo7, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo8, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo9, 0, 0);
	drawMainBuffer();
	tickdelay(5);

	drawSecondBuffer(resources->bitmap.fundo, 0, 0);
	drawMainBuffer();
	tickdelay(5);


	int i;
	int xlogodragon = -584;
	for(i = 0; i < 45; i++){
		drawSecondBuffer(resources->bitmap.fundo, 0, 0);

		if(i % 4 == 0)
			drawSecondBuffer(resources->bitmap.logodragon1, xlogodragon + i*20, 101);
		else if(i % 4 == 1)
			drawSecondBuffer(resources->bitmap.logodragon2, xlogodragon + i*20, 101);
		else if(i % 4 == 2)
			drawSecondBuffer(resources->bitmap.logodragon3, xlogodragon + i*20, 101);
		else if(i % 4 == 3)
			drawSecondBuffer(resources->bitmap.logodragon4, xlogodragon + i*20, 101);

		if (i == 41)
			drawSecondBuffer(resources->bitmap.botoes2, 95, 367);
		else if (i == 42)
			drawSecondBuffer(resources->bitmap.botoes4, 95, 367);
		else if (i == 43)
			drawSecondBuffer(resources->bitmap.botoes6, 95, 367);
		else if (i == 44)
			drawSecondBuffer(resources->bitmap.botoes8, 95, 367);

		drawMainBuffer();
		tickdelay(5);
	}

	xlogodragon = 743;

	for(i = 0; i < 14; i++){
		drawSecondBuffer(resources->bitmap.menu, 0, 0);

		if(i % 4 == 0)
			drawSecondBuffer(resources->bitmap.dragon2, xlogodragon + i*20, 139);
		else if(i % 4 == 1)
			drawSecondBuffer(resources->bitmap.dragon3, xlogodragon + i*20, 139);
		else if(i % 4 == 2)
			drawSecondBuffer(resources->bitmap.dragon4, xlogodragon + i*20, 139);
		else if(i % 4 == 3)
			drawSecondBuffer(resources->bitmap.dragon1, xlogodragon + i*20, 139);

		drawMainBuffer();
		tickdelay(5);

	}
}


void moveCursor(short x, short y, unsigned short *xi, unsigned short *yi) {
	if(x < 0)
	{
		if (*xi + x < 0)
		{
			*xi = 0;
		}
		else
		{
			*xi += x;
		}
	}
	else if(x > 0)
	{
		if (*xi + x >= 986)
		{
			*xi = 985;
		}
		else
		{
			*xi += x;
		}
	}

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
		if (*yi - y >= 732)
		{
			*yi = 731;
		}
		else
		{
			*yi -= y;
		}
	}
}

void displayTime(gameData *game, projData *resources){
	updateRTC(resources);

	int time[6];
	int x = 440;
	int y = 735;
	int i;

	time[0] = floor((resources->currentDate.hour/(int)pow(10,1))%10);
	time[1] = floor((resources->currentDate.hour/(int)pow(10,0))%10);
	time[2] = floor((resources->currentDate.min/(int)pow(10,1))%10);
	time[3] = floor((resources->currentDate.min/(int)pow(10,0))%10);
	time[4] = floor((resources->currentDate.sec/(int)pow(10,1))%10);
	time[5] = floor((resources->currentDate.sec/(int)pow(10,0))%10);

	for(i = 0; i < 6; i++){
		if(time[i] == 0)
			drawSecondBuffer(resources->bitmap.zero, x, y);
		else if(time[i] == 1)
			drawSecondBuffer(resources->bitmap.one, x, y);
		else if(time[i] == 2)
			drawSecondBuffer(resources->bitmap.two, x, y);
		else if(time[i] == 3)
			drawSecondBuffer(resources->bitmap.three, x, y);
		else if(time[i] == 4)
			drawSecondBuffer(resources->bitmap.four, x, y);
		else if(time[i] == 5)
			drawSecondBuffer(resources->bitmap.five, x, y);
		else if(time[i] == 6)
			drawSecondBuffer(resources->bitmap.six, x, y);
		else if(time[i] == 7)
			drawSecondBuffer(resources->bitmap.seven, x, y);
		else if(time[i] == 8)
			drawSecondBuffer(resources->bitmap.eight, x, y);
		else if(time[i] == 9)
			drawSecondBuffer(resources->bitmap.nine, x, y);

		if(i == 1 || i == 3)
			x+=32;
		else
			x+=20;
	}

	drawSecondBuffer(resources->bitmap.colon, 480, y);
	drawSecondBuffer(resources->bitmap.colon, 532, y);

}


void addLetterUsername(char *currentUsername, int *cUsernameCounter, unsigned char MSByte){
	if (*cUsernameCounter < 12) {
		if(MSByte == AA){
			currentUsername[*cUsernameCounter] = 'A';
			*cUsernameCounter += 1;
		}
		else if(MSByte == BB){
			currentUsername[*cUsernameCounter] = 'B';
			*cUsernameCounter += 1;
		}
		else if(MSByte == CC || MSByte == CCC){
			currentUsername[*cUsernameCounter] = 'C';
			*cUsernameCounter += 1;
		}
		else if(MSByte == DD){
			currentUsername[*cUsernameCounter] = 'D';
			*cUsernameCounter += 1;
		}
		else if(MSByte == EE){
			currentUsername[*cUsernameCounter] = 'E';
			*cUsernameCounter += 1;
		}
		else if(MSByte == FF){
			currentUsername[*cUsernameCounter] = 'F';
			*cUsernameCounter += 1;
		}
		else if(MSByte == GG){
			currentUsername[*cUsernameCounter] = 'G';
			*cUsernameCounter += 1;
		}
		else if(MSByte == HH){
			currentUsername[*cUsernameCounter] = 'H';
			*cUsernameCounter += 1;
		}
		else if(MSByte == II){
			currentUsername[*cUsernameCounter] = 'I';
			*cUsernameCounter += 1;
		}
		else if(MSByte == JJ){
			currentUsername[*cUsernameCounter] = 'J';
			*cUsernameCounter += 1;
		}
		else if(MSByte == KK){
			currentUsername[*cUsernameCounter] = 'K';
			*cUsernameCounter += 1;
		}
		else if(MSByte == LL){
			currentUsername[*cUsernameCounter] = 'L';
			*cUsernameCounter += 1;
		}
		else if(MSByte == MM){
			currentUsername[*cUsernameCounter] = 'M';
			*cUsernameCounter += 1;
		}
		else if(MSByte == NN){
			currentUsername[*cUsernameCounter] = 'N';
			*cUsernameCounter += 1;
		}
		else if(MSByte == OO){
			currentUsername[*cUsernameCounter] = 'O';
			*cUsernameCounter += 1;
		}
		else if(MSByte == PP){
			currentUsername[*cUsernameCounter] = 'P';
			*cUsernameCounter += 1;
		}
		else if(MSByte == QQ){
			currentUsername[*cUsernameCounter] = 'Q';
			*cUsernameCounter += 1;
		}
		else if(MSByte == RR){
			currentUsername[*cUsernameCounter] = 'R';
			*cUsernameCounter += 1;
		}
		else if(MSByte == SS){
			currentUsername[*cUsernameCounter] = 'S';
			*cUsernameCounter += 1;
		}
		else if(MSByte == TT){
			currentUsername[*cUsernameCounter] = 'T';
			*cUsernameCounter += 1;
		}
		else if(MSByte == UU){
			currentUsername[*cUsernameCounter] = 'U';
			*cUsernameCounter += 1;
		}
		else if(MSByte == VV){
			currentUsername[*cUsernameCounter] = 'V';
			*cUsernameCounter += 1;
		}
		else if(MSByte == WW){
			currentUsername[*cUsernameCounter] = 'W';
			*cUsernameCounter += 1;
		}
		else if(MSByte == XX){
			currentUsername[*cUsernameCounter] = 'X';
			*cUsernameCounter += 1;
		}
		else if(MSByte == YY){
			currentUsername[*cUsernameCounter] = 'Y';
			*cUsernameCounter += 1;
		}
		else if(MSByte == ZZ){
			currentUsername[*cUsernameCounter] = 'Z';
			*cUsernameCounter += 1;
		}
		else if(MSByte == ZERO){
			currentUsername[*cUsernameCounter] = '0';
			*cUsernameCounter += 1;
		}
		else if(MSByte == ONE){
			currentUsername[*cUsernameCounter] = '1';
			*cUsernameCounter += 1;
		}
		else if(MSByte == TWO){
			currentUsername[*cUsernameCounter] = '2';
			*cUsernameCounter += 1;
		}
		else if(MSByte == THREE){
			currentUsername[*cUsernameCounter] = '3';
			*cUsernameCounter += 1;
		}
		else if(MSByte == FOUR){
			currentUsername[*cUsernameCounter] = '4';
			*cUsernameCounter += 1;
		}
		else if(MSByte == FIVE){
			currentUsername[*cUsernameCounter] = '5';
			*cUsernameCounter += 1;
		}
		else if(MSByte == SIX){
			currentUsername[*cUsernameCounter] = '6';
			*cUsernameCounter += 1;
		}
		else if(MSByte == SEVEN){
			currentUsername[*cUsernameCounter] = '7';
			*cUsernameCounter += 1;
		}
		else if(MSByte == EIGHT){
			currentUsername[*cUsernameCounter] = '8';
			*cUsernameCounter += 1;
		}
		else if(MSByte == NINE){
			currentUsername[*cUsernameCounter] = '9';
			*cUsernameCounter += 1;
		}
		else if(MSByte == DELETE && *cUsernameCounter > 0)
			*cUsernameCounter -= 1;
	}
	else {
		if(MSByte == DELETE){
			*cUsernameCounter -= 1;
		}
	}
}

void drawLetters(char *currentUsername, int cUsernameCounter, projData *resources){
	int i;

	//coordenadas iniciais username
	unsigned short xUser = 350;
	unsigned short yUser = 410;

	for(i = 0; i < cUsernameCounter; i++){
		if(currentUsername[i] == 'A'){
			drawSecondBuffer(resources->bitmap.a, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'B'){
			drawSecondBuffer(resources->bitmap.b, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'C'){
			drawSecondBuffer(resources->bitmap.c, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'D'){
			drawSecondBuffer(resources->bitmap.d, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'E'){
			drawSecondBuffer(resources->bitmap.e, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'F'){
			drawSecondBuffer(resources->bitmap.f, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'G'){
			drawSecondBuffer(resources->bitmap.g, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'H'){
			drawSecondBuffer(resources->bitmap.h, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'I'){
			drawSecondBuffer(resources->bitmap.i, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'J'){
			drawSecondBuffer(resources->bitmap.j, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'K'){
			drawSecondBuffer(resources->bitmap.k, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'L'){
			drawSecondBuffer(resources->bitmap.l, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'M'){
			drawSecondBuffer(resources->bitmap.m, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'N'){
			drawSecondBuffer(resources->bitmap.n, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'O'){
			drawSecondBuffer(resources->bitmap.o, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'P'){
			drawSecondBuffer(resources->bitmap.p, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'Q'){
			drawSecondBuffer(resources->bitmap.q, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'R'){
			drawSecondBuffer(resources->bitmap.r, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'S'){
			drawSecondBuffer(resources->bitmap.s, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'T'){
			drawSecondBuffer(resources->bitmap.t, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'U'){
			drawSecondBuffer(resources->bitmap.u, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'V'){
			drawSecondBuffer(resources->bitmap.v, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'W'){
			drawSecondBuffer(resources->bitmap.w, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'X'){
			drawSecondBuffer(resources->bitmap.x, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'Y'){
			drawSecondBuffer(resources->bitmap.y, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == 'Z'){
			drawSecondBuffer(resources->bitmap.z, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '0'){
			drawSecondBuffer(resources->bitmap.zero, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '1'){
			drawSecondBuffer(resources->bitmap.one, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '2'){
			drawSecondBuffer(resources->bitmap.two, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '3'){
			drawSecondBuffer(resources->bitmap.three, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '4'){
			drawSecondBuffer(resources->bitmap.four, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '5'){
			drawSecondBuffer(resources->bitmap.five, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '6'){
			drawSecondBuffer(resources->bitmap.six, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '7'){
			drawSecondBuffer(resources->bitmap.seven, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '8'){
			drawSecondBuffer(resources->bitmap.eight, xUser, yUser);
			xUser += 20;
		}
		else if(currentUsername[i] == '9'){
			drawSecondBuffer(resources->bitmap.nine, xUser, yUser);
			xUser += 20;
		}
	}
}


void printLeaderBoard(gameData *game, projData *resources){
	int i, k;
	//score
	int zeros, digits, currentDigit, numberX, dataX, lineY;

	lineY = 255;
	for (i = 0; i < game->scoreCounter; i++)
	{
		printUsernameLeaderBoard(game, resources, 89, lineY, i);

		if (game->scores[i].valor != 0)
		{
			zeros  = 5 - (floor(log10(game->scores[i].valor)) + 1);
			digits = 5 - zeros;
		}
		else
		{
			zeros = 5;
			digits = -1;
		}
		numberX = 483;
		for (k = 0; k < zeros; k++)
		{
			drawSecondBuffer(resources->bitmap.zero, numberX, lineY);
			numberX += 20;
		}

		for (k = digits - 1; k >= 0; k--)
		{
			currentDigit = floor((game->scores[i].valor/(int)pow(10,k))%10);

			switch (currentDigit)
			{
			case 0:
				drawSecondBuffer(resources->bitmap.zero, numberX, lineY);
				break;
			case 1:
				drawSecondBuffer(resources->bitmap.one, numberX, lineY);
				break;
			case 2:
				drawSecondBuffer(resources->bitmap.two, numberX, lineY);
				break;
			case 3:
				drawSecondBuffer(resources->bitmap.three, numberX, lineY);
				break;
			case 4:
				drawSecondBuffer(resources->bitmap.four, numberX, lineY);
				break;
			case 5:
				drawSecondBuffer(resources->bitmap.five, numberX, lineY);
				break;
			case 6:
				drawSecondBuffer(resources->bitmap.six, numberX, lineY);
				break;
			case 7:
				drawSecondBuffer(resources->bitmap.seven, numberX, lineY);
				break;
			case 8:
				drawSecondBuffer(resources->bitmap.eight, numberX, lineY);
				break;
			case 9:
				drawSecondBuffer(resources->bitmap.nine, numberX, lineY);
				break;
			}

			numberX += 20;
		}

		//data
		dataX = 737;
		for (k = 0; k < 10; k++)
		{
			switch(game->scores[i].currentDate[k])
			{
			case 0:
				drawSecondBuffer(resources->bitmap.zero, dataX, lineY);
				break;
			case 1:
				drawSecondBuffer(resources->bitmap.one, dataX, lineY);
				break;
			case 2:
				drawSecondBuffer(resources->bitmap.two, dataX, lineY);
				break;
			case 3:
				drawSecondBuffer(resources->bitmap.three, dataX, lineY);
				break;
			case 4:
				drawSecondBuffer(resources->bitmap.four, dataX, lineY);
				break;
			case 5:
				drawSecondBuffer(resources->bitmap.five, dataX, lineY);
				break;
			case 6:
				drawSecondBuffer(resources->bitmap.six, dataX, lineY);
				break;
			case 7:
				drawSecondBuffer(resources->bitmap.seven, dataX, lineY);
				break;
			case 8:
				drawSecondBuffer(resources->bitmap.eight, dataX, lineY);
				break;
			case 9:
				drawSecondBuffer(resources->bitmap.nine, dataX, lineY);
				break;
			case '/':
				drawSecondBuffer(resources->bitmap.barra, dataX, lineY);
				break;
			}

			dataX += 20;
		}

		lineY += 40;
	}
}

void printUsernameLeaderBoard(gameData *game, projData *resources, int x, int y, int pos){
	int i;

	for(i = 0; i < game->scores[pos].usernameCounter; i++){
		if(game->scores[pos].username[i] == 'A'){
			drawSecondBuffer(resources->bitmap.a, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'B'){
			drawSecondBuffer(resources->bitmap.b, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'C'){
			drawSecondBuffer(resources->bitmap.c, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'D'){
			drawSecondBuffer(resources->bitmap.d, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'E'){
			drawSecondBuffer(resources->bitmap.e, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'F'){
			drawSecondBuffer(resources->bitmap.f, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'G'){
			drawSecondBuffer(resources->bitmap.g, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'H'){
			drawSecondBuffer(resources->bitmap.h, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'I'){
			drawSecondBuffer(resources->bitmap.i, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'J'){
			drawSecondBuffer(resources->bitmap.j, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'K'){
			drawSecondBuffer(resources->bitmap.k, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'L'){
			drawSecondBuffer(resources->bitmap.l, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'M'){
			drawSecondBuffer(resources->bitmap.m, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'N'){
			drawSecondBuffer(resources->bitmap.n, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'O'){
			drawSecondBuffer(resources->bitmap.o, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'P'){
			drawSecondBuffer(resources->bitmap.p, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'Q'){
			drawSecondBuffer(resources->bitmap.q, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'R'){
			drawSecondBuffer(resources->bitmap.r, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'S'){
			drawSecondBuffer(resources->bitmap.s, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'T'){
			drawSecondBuffer(resources->bitmap.t, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'U'){
			drawSecondBuffer(resources->bitmap.u, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'V'){
			drawSecondBuffer(resources->bitmap.v, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'W'){
			drawSecondBuffer(resources->bitmap.w, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'X'){
			drawSecondBuffer(resources->bitmap.x, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'Y'){
			drawSecondBuffer(resources->bitmap.y, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == 'Z'){
			drawSecondBuffer(resources->bitmap.z, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '0'){
			drawSecondBuffer(resources->bitmap.zero, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '1'){
			drawSecondBuffer(resources->bitmap.one, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '2'){
			drawSecondBuffer(resources->bitmap.two, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '3'){
			drawSecondBuffer(resources->bitmap.three, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '4'){
			drawSecondBuffer(resources->bitmap.four, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '5'){
			drawSecondBuffer(resources->bitmap.five, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '6'){
			drawSecondBuffer(resources->bitmap.six, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '7'){
			drawSecondBuffer(resources->bitmap.seven, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '8'){
			drawSecondBuffer(resources->bitmap.eight, x, y);
			x += 20;
		}
		else if(game->scores[pos].username[i] == '9'){
			drawSecondBuffer(resources->bitmap.nine, x, y);
			x += 20;
		}
	}
}
