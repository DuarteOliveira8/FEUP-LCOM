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

int initPixelWings(gameData *game, projData *resources){

	resources->bitmap.menu = loadBitmap("/home/lcom/proj/bitmaps/menu.bmp");
	resources->bitmap.cursor = loadBitmap("/home/lcom/proj/bitmaps/cursor.bmp");
	resources->bitmap.dragon1 = loadBitmap("/home/lcom/proj/bitmaps/dragao1.bmp");
	resources->bitmap.dragon2 = loadBitmap("/home/lcom/proj/bitmaps/dragao2.bmp");
	resources->bitmap.dragon3 = loadBitmap("/home/lcom/proj/bitmaps/dragao3.bmp");
	resources->bitmap.dragon4 = loadBitmap("/home/lcom/proj/bitmaps/dragao4.bmp");
	resources->bitmap.dragon11 = loadBitmap("/home/lcom/proj/bitmaps/dragao11.bmp");
	resources->bitmap.dragon22 = loadBitmap("/home/lcom/proj/bitmaps/dragao22.bmp");
	resources->bitmap.dragon33 = loadBitmap("/home/lcom/proj/bitmaps/dragao33.bmp");
	resources->bitmap.dragon44 = loadBitmap("/home/lcom/proj/bitmaps/dragao44.bmp");
	resources->bitmap.dragon1die = loadBitmap("/home/lcom/proj/bitmaps/dragao1die.bmp");
	resources->bitmap.dragon11die = loadBitmap("/home/lcom/proj/bitmaps/dragao11die.bmp");
	resources->bitmap.fundo = loadBitmap("/home/lcom/proj/bitmaps/fundo.bmp");
	resources->bitmap.fundo1 = loadBitmap("/home/lcom/proj/bitmaps/fundo1.bmp");
	resources->bitmap.fundo2 = loadBitmap("/home/lcom/proj/bitmaps/fundo2.bmp");
	resources->bitmap.fundo3 = loadBitmap("/home/lcom/proj/bitmaps/fundo3.bmp");
	resources->bitmap.fundo4 = loadBitmap("/home/lcom/proj/bitmaps/fundo4.bmp");
	resources->bitmap.fundo5 = loadBitmap("/home/lcom/proj/bitmaps/fundo5.bmp");
	resources->bitmap.fundo6 = loadBitmap("/home/lcom/proj/bitmaps/fundo6.bmp");
	resources->bitmap.fundo7 = loadBitmap("/home/lcom/proj/bitmaps/fundo7.bmp");
	resources->bitmap.fundo8 = loadBitmap("/home/lcom/proj/bitmaps/fundo8.bmp");
	resources->bitmap.fundo9 = loadBitmap("/home/lcom/proj/bitmaps/fundo9.bmp");
	resources->bitmap.fire = loadBitmap("/home/lcom/proj/bitmaps/fire.bmp");
	resources->bitmap.firehit1 = loadBitmap("/home/lcom/proj/bitmaps/firehit1.bmp");
	resources->bitmap.firehit2 = loadBitmap("/home/lcom/proj/bitmaps/firehit2.bmp");
	resources->bitmap.ice = loadBitmap("/home/lcom/proj/bitmaps/ice.bmp");
	resources->bitmap.icehit1 = loadBitmap("/home/lcom/proj/bitmaps/icehit1.bmp");
	resources->bitmap.icehit2 = loadBitmap("/home/lcom/proj/bitmaps/icehit2.bmp");
	resources->bitmap.bat = loadBitmap("/home/lcom/proj/bitmaps/bat.bmp");
	resources->bitmap.batdie1 = loadBitmap("/home/lcom/proj/bitmaps/batdie1.bmp");
	resources->bitmap.batdie2 = loadBitmap("/home/lcom/proj/bitmaps/batdie2.bmp");
	resources->bitmap.zero = loadBitmap("/home/lcom/proj/bitmaps/numbers/0.bmp");
	resources->bitmap.one = loadBitmap("/home/lcom/proj/bitmaps/numbers/1.bmp");
	resources->bitmap.two = loadBitmap("/home/lcom/proj/bitmaps/numbers/2.bmp");
	resources->bitmap.three = loadBitmap("/home/lcom/proj/bitmaps/numbers/3.bmp");
	resources->bitmap.four = loadBitmap("/home/lcom/proj/bitmaps/numbers/4.bmp");
	resources->bitmap.five = loadBitmap("/home/lcom/proj/bitmaps/numbers/5.bmp");
	resources->bitmap.six = loadBitmap("/home/lcom/proj/bitmaps/numbers/6.bmp");
	resources->bitmap.seven = loadBitmap("/home/lcom/proj/bitmaps/numbers/7.bmp");
	resources->bitmap.eight = loadBitmap("/home/lcom/proj/bitmaps/numbers/8.bmp");
	resources->bitmap.nine = loadBitmap("/home/lcom/proj/bitmaps/numbers/9.bmp");
	resources->bitmap.score = loadBitmap("/home/lcom/proj/bitmaps/score.bmp");
	resources->bitmap.gameover = loadBitmap("/home/lcom/proj/bitmaps/gameover.bmp");
	resources->bitmap.pause = loadBitmap("/home/lcom/proj/bitmaps/pause.bmp");
	resources->bitmap.a = loadBitmap("/home/lcom/proj/bitmaps/letters/a.bmp");
	resources->bitmap.b = loadBitmap("/home/lcom/proj/bitmaps/letters/b.bmp");
	resources->bitmap.c = loadBitmap("/home/lcom/proj/bitmaps/letters/c.bmp");
	resources->bitmap.d = loadBitmap("/home/lcom/proj/bitmaps/letters/d.bmp");
	resources->bitmap.e = loadBitmap("/home/lcom/proj/bitmaps/letters/e.bmp");
	resources->bitmap.f = loadBitmap("/home/lcom/proj/bitmaps/letters/f.bmp");
	resources->bitmap.g = loadBitmap("/home/lcom/proj/bitmaps/letters/g.bmp");
	resources->bitmap.h = loadBitmap("/home/lcom/proj/bitmaps/letters/h.bmp");
	resources->bitmap.i = loadBitmap("/home/lcom/proj/bitmaps/letters/i.bmp");
	resources->bitmap.j = loadBitmap("/home/lcom/proj/bitmaps/letters/j.bmp");
	resources->bitmap.k = loadBitmap("/home/lcom/proj/bitmaps/letters/k.bmp");
	resources->bitmap.l = loadBitmap("/home/lcom/proj/bitmaps/letters/l.bmp");
	resources->bitmap.m = loadBitmap("/home/lcom/proj/bitmaps/letters/m.bmp");
	resources->bitmap.n = loadBitmap("/home/lcom/proj/bitmaps/letters/n.bmp");
	resources->bitmap.o = loadBitmap("/home/lcom/proj/bitmaps/letters/o.bmp");
	resources->bitmap.p = loadBitmap("/home/lcom/proj/bitmaps/letters/p.bmp");
	resources->bitmap.q = loadBitmap("/home/lcom/proj/bitmaps/letters/q.bmp");
	resources->bitmap.r = loadBitmap("/home/lcom/proj/bitmaps/letters/r.bmp");
	resources->bitmap.s = loadBitmap("/home/lcom/proj/bitmaps/letters/s.bmp");
	resources->bitmap.t = loadBitmap("/home/lcom/proj/bitmaps/letters/t.bmp");
	resources->bitmap.u = loadBitmap("/home/lcom/proj/bitmaps/letters/u.bmp");
	resources->bitmap.v = loadBitmap("/home/lcom/proj/bitmaps/letters/v.bmp");
	resources->bitmap.w = loadBitmap("/home/lcom/proj/bitmaps/letters/w.bmp");
	resources->bitmap.x = loadBitmap("/home/lcom/proj/bitmaps/letters/x.bmp");
	resources->bitmap.y = loadBitmap("/home/lcom/proj/bitmaps/letters/y.bmp");
	resources->bitmap.z = loadBitmap("/home/lcom/proj/bitmaps/letters/z.bmp");
	resources->bitmap.blank = loadBitmap("/home/lcom/proj/bitmaps/letters/blank.bmp");
	resources->bitmap.saved = loadBitmap("/home/lcom/proj/bitmaps/saved.bmp");
	resources->bitmap.leaderboard = loadBitmap("/home/lcom/proj/bitmaps/leaderboard.bmp");
	resources->bitmap.logodragon1 = loadBitmap("/home/lcom/proj/bitmaps/logodragon1.bmp");
	resources->bitmap.logodragon2 = loadBitmap("/home/lcom/proj/bitmaps/logodragon2.bmp");
	resources->bitmap.logodragon3 = loadBitmap("/home/lcom/proj/bitmaps/logodragon3.bmp");
	resources->bitmap.logodragon4 = loadBitmap("/home/lcom/proj/bitmaps/logodragon4.bmp");
	resources->bitmap.botoes2 = loadBitmap("/home/lcom/proj/bitmaps/botoes2.bmp");
	resources->bitmap.botoes4 = loadBitmap("/home/lcom/proj/bitmaps/botoes4.bmp");
	resources->bitmap.botoes6 = loadBitmap("/home/lcom/proj/bitmaps/botoes6.bmp");
	resources->bitmap.botoes8 = loadBitmap("/home/lcom/proj/bitmaps/botoes8.bmp");
	resources->bitmap.barra = loadBitmap("/home/lcom/proj/bitmaps/letters/barra.bmp");
	resources->bitmap.colon = loadBitmap("/home/lcom/proj/bitmaps/letters/colon.bmp");
	resources->bitmap.options = loadBitmap("/home/lcom/proj/bitmaps/options.bmp");
	resources->bitmap.power04 = loadBitmap("/home/lcom/proj/bitmaps/power0_4.bmp");
	resources->bitmap.power14 = loadBitmap("/home/lcom/proj/bitmaps/power1_4.bmp");
	resources->bitmap.power24 = loadBitmap("/home/lcom/proj/bitmaps/power2_4.bmp");
	resources->bitmap.power34 = loadBitmap("/home/lcom/proj/bitmaps/power3_4.bmp");
	resources->bitmap.power44 = loadBitmap("/home/lcom/proj/bitmaps/power4_4.bmp");
	resources->bitmap.hoverplay = loadBitmap("/home/lcom/proj/bitmaps/playbutton.bmp");
	resources->bitmap.hoverstats = loadBitmap("/home/lcom/proj/bitmaps/statsbutton.bmp");
	resources->bitmap.hoveroptions = loadBitmap("/home/lcom/proj/bitmaps/optionsbutton.bmp");
	resources->bitmap.hoverexit = loadBitmap("/home/lcom/proj/bitmaps/exitbutton.bmp");
	resources->bitmap.hoverexit2 = loadBitmap("/home/lcom/proj/bitmaps/exitbutton2.bmp");
	resources->bitmap.hoverexit3 = loadBitmap("/home/lcom/proj/bitmaps/exitbutton3.bmp");
	resources->bitmap.hoverexit4 = loadBitmap("/home/lcom/proj/bitmaps/exitbutton4.bmp");
	resources->bitmap.hoverexit5 = loadBitmap("/home/lcom/proj/bitmaps/exitbutton5.bmp");
	resources->bitmap.hoverok = loadBitmap("/home/lcom/proj/bitmaps/okbutton.bmp");
	resources->bitmap.hoverretry = loadBitmap("/home/lcom/proj/bitmaps/retrybutton.bmp");
	resources->bitmap.hovercontinue = loadBitmap("/home/lcom/proj/bitmaps/continuebutton.bmp");
	resources->bitmap.hoverrestart = loadBitmap("/home/lcom/proj/bitmaps/restartbutton.bmp");

	resources->currentDate.day = (unsigned long) malloc(sizeof(unsigned long));
	resources->currentDate.month = (unsigned long) malloc(sizeof(unsigned long));
	resources->currentDate.year = (unsigned long) malloc(sizeof(unsigned long));
	resources->currentDate.hour = (unsigned long) malloc(sizeof(unsigned long));
	resources->currentDate.min = (unsigned long) malloc(sizeof(unsigned long));
	resources->currentDate.sec = (unsigned long) malloc(sizeof(unsigned long));

	loadScores(game);

	//main buffer
	vg_init(0x117);

	intro(game, resources);

	unsigned long ack;

	mouse_irq_disable();

	if(sys_outb(KBC_CMD_REG, KBC_COMMAND) != OK)
		return -1;
	if(sys_outb(IN_BUF, ENABLE_STREAM) != OK)
		return -1;
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;

	if(sys_outb(KBC_CMD_REG, KBC_COMMAND) != OK)
		return -1;
	if(sys_outb(IN_BUF, STREAM_MODE) != OK)
		return -1;
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;

	mouse_irq_enable();

	resources->returnbit.timer = timer_subscribe_int();
	resources->returnbit.keyboard = keyboard_subscribe_int();
	resources->returnbit.mouse = mouse_subscribe_int();

	return 0;
}

int leavePixelWings(gameData *game, projData *resources){
	deleteBitmap(resources->bitmap.menu);
	deleteBitmap(resources->bitmap.cursor);
	deleteBitmap(resources->bitmap.fundo);
	deleteBitmap(resources->bitmap.fundo1);
	deleteBitmap(resources->bitmap.fundo2);
	deleteBitmap(resources->bitmap.fundo3);
	deleteBitmap(resources->bitmap.fundo4);
	deleteBitmap(resources->bitmap.fundo5);
	deleteBitmap(resources->bitmap.fundo6);
	deleteBitmap(resources->bitmap.fundo7);
	deleteBitmap(resources->bitmap.fundo8);
	deleteBitmap(resources->bitmap.fundo9);
	deleteBitmap(resources->bitmap.dragon1);
	deleteBitmap(resources->bitmap.dragon2);
	deleteBitmap(resources->bitmap.dragon3);
	deleteBitmap(resources->bitmap.dragon4);
	deleteBitmap(resources->bitmap.dragon11);
	deleteBitmap(resources->bitmap.dragon22);
	deleteBitmap(resources->bitmap.dragon33);
	deleteBitmap(resources->bitmap.dragon44);
	deleteBitmap(resources->bitmap.dragon1die);
	deleteBitmap(resources->bitmap.dragon11die);
	deleteBitmap(resources->bitmap.fire);
	deleteBitmap(resources->bitmap.firehit1);
	deleteBitmap(resources->bitmap.firehit2);
	deleteBitmap(resources->bitmap.ice);
	deleteBitmap(resources->bitmap.icehit1);
	deleteBitmap(resources->bitmap.icehit2);
	deleteBitmap(resources->bitmap.bat);
	deleteBitmap(resources->bitmap.batdie1);
	deleteBitmap(resources->bitmap.batdie2);
	deleteBitmap(resources->bitmap.zero);
	deleteBitmap(resources->bitmap.one);
	deleteBitmap(resources->bitmap.two);
	deleteBitmap(resources->bitmap.three);
	deleteBitmap(resources->bitmap.four);
	deleteBitmap(resources->bitmap.five);
	deleteBitmap(resources->bitmap.six);
	deleteBitmap(resources->bitmap.seven);
	deleteBitmap(resources->bitmap.eight);
	deleteBitmap(resources->bitmap.nine);
	deleteBitmap(resources->bitmap.score);
	deleteBitmap(resources->bitmap.gameover);
	deleteBitmap(resources->bitmap.pause);
	deleteBitmap(resources->bitmap.a);
	deleteBitmap(resources->bitmap.b);
	deleteBitmap(resources->bitmap.c);
	deleteBitmap(resources->bitmap.d);
	deleteBitmap(resources->bitmap.e);
	deleteBitmap(resources->bitmap.f);
	deleteBitmap(resources->bitmap.g);
	deleteBitmap(resources->bitmap.h);
	deleteBitmap(resources->bitmap.i);
	deleteBitmap(resources->bitmap.j);
	deleteBitmap(resources->bitmap.k);
	deleteBitmap(resources->bitmap.l);
	deleteBitmap(resources->bitmap.m);
	deleteBitmap(resources->bitmap.n);
	deleteBitmap(resources->bitmap.o);
	deleteBitmap(resources->bitmap.p);
	deleteBitmap(resources->bitmap.q);
	deleteBitmap(resources->bitmap.r);
	deleteBitmap(resources->bitmap.s);
	deleteBitmap(resources->bitmap.t);
	deleteBitmap(resources->bitmap.u);
	deleteBitmap(resources->bitmap.v);
	deleteBitmap(resources->bitmap.w);
	deleteBitmap(resources->bitmap.x);
	deleteBitmap(resources->bitmap.y);
	deleteBitmap(resources->bitmap.z);
	deleteBitmap(resources->bitmap.blank);
	deleteBitmap(resources->bitmap.leaderboard);
	deleteBitmap(resources->bitmap.options);
	deleteBitmap(resources->bitmap.saved);
	deleteBitmap(resources->bitmap.logodragon1);
	deleteBitmap(resources->bitmap.logodragon2);
	deleteBitmap(resources->bitmap.logodragon3);
	deleteBitmap(resources->bitmap.logodragon4);
	deleteBitmap(resources->bitmap.botoes2);
	deleteBitmap(resources->bitmap.botoes4);
	deleteBitmap(resources->bitmap.botoes6);
	deleteBitmap(resources->bitmap.botoes8);
	deleteBitmap(resources->bitmap.barra);
	deleteBitmap(resources->bitmap.colon);
	deleteBitmap(resources->bitmap.power04);
	deleteBitmap(resources->bitmap.power14);
	deleteBitmap(resources->bitmap.power24);
	deleteBitmap(resources->bitmap.power34);
	deleteBitmap(resources->bitmap.power44);
	deleteBitmap(resources->bitmap.hoverplay);
	deleteBitmap(resources->bitmap.hoverstats);
	deleteBitmap(resources->bitmap.hoveroptions);
	deleteBitmap(resources->bitmap.hoverexit);
	deleteBitmap(resources->bitmap.hoverexit2);
	deleteBitmap(resources->bitmap.hoverexit3);
	deleteBitmap(resources->bitmap.hoverexit4);
	deleteBitmap(resources->bitmap.hoverexit5);
	deleteBitmap(resources->bitmap.hoverok);
	deleteBitmap(resources->bitmap.hoverretry);
	deleteBitmap(resources->bitmap.hoverrestart);
	deleteBitmap(resources->bitmap.hovercontinue);

	saveScores(game);

	unsigned long ack;

	if(sys_outb(KBC_CMD_REG, KBC_COMMAND) != OK)
		return -1;
	if(sys_outb(IN_BUF, DISABLE_STREAM) != OK)
		return -1;
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;
	sys_inb(IN_BUF, &ack);
	if (ack != ACK)
		return -1;

	//limpar outbuf
	unsigned long stat, data;

	sys_inb(STAT_REG, &stat);

	if( stat & OBF ) {
		sys_inb(OUT_BUF, &data);
	}

	keyboard_unsubscribe_int();
	timer_unsubscribe_int();
	mouse_unsubscribe_int();

	vg_exit();

	return 0;
}


int mainMenu(){
	//dados do jogo
	gameData game;
	projData resources;
	int gameState;
	game.currentDragon = 0;

	//keyboard
	unsigned char MSByte = 0;

	//mouse
	unsigned char packet[3];
	int counter_packets = 0;

	//cursor coords
	unsigned short cursorX = 495;
	unsigned short cursorY = 382;
	unsigned short x;
	unsigned short y;

	//machine states
	button option = NOTHING;
	hoverbutton hover = HOVERNOTHING;

	if (initPixelWings(&game, &resources) == -1)
		return -1;

	int ipc_status;
	message msg;
	char r;

	while (1)
	{
		cursorX = 495;
		cursorY = 382;

		//while((opcao != PLAY) && (opcao != EXIT)) {
		while(option == NOTHING) {

			if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
				printf("driver_receive failed with: %d", r);
				continue;
			}

			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
					if (msg.NOTIFY_ARG & resources.returnbit.keyboard) {
						changeScancode(&MSByte);
					}
					if (msg.NOTIFY_ARG & resources.returnbit.timer){
						//desenhar rato
						drawSecondBuffer(resources.bitmap.menu, 0, 0);
						displayTime(&game, &resources);
						if(hover == HOVERPLAY)
							drawSecondBuffer(resources.bitmap.hoverplay, 95, 367);
						else if(hover == HOVERSTATS)
							drawSecondBuffer(resources.bitmap.hoverstats, 559, 367);
						else if(hover == HOVEROPTIONS)
							drawSecondBuffer(resources.bitmap.hoveroptions, 95, 530);
						else if(hover == HOVEREXIT)
							drawSecondBuffer(resources.bitmap.hoverexit, 559, 530);
						drawSecondBuffer(resources.bitmap.cursor, cursorX, cursorY);
						drawMainBuffer();
					}
					if (msg.NOTIFY_ARG & resources.returnbit.mouse){
						//desenhar personagem
						mouseHandler(&packet[counter_packets]);

						counter_packets++;

						if(!(packet[0] & BIT(3)))
						{
							counter_packets = 0;
						}

						if (counter_packets == 3)
						{
							if (packet[0] & BIT(4))
							{
								x = -(256 - packet[1]);
							}
							else
								x = packet[1];

							if (packet[0] & BIT(5))
							{
								y = -(256 - packet[2]);
							}
							else
								y = packet[2];

							moveCursor(x, y, &cursorX, &cursorY);


							if ((cursorX >= 95) && (cursorX <= 465) && (cursorY >= 367) && (cursorY <= 508))
							{
								hover = HOVERPLAY;
								if (packet[0] & BIT(0))
									option = PLAYBUTTON;
							}
							else if ((cursorX >= 559) && (cursorX <= 929) && (cursorY >= 367) && (cursorY <= 508))
							{
								hover = HOVERSTATS;
								if (packet[0] & BIT(0))
									option = STATSBUTTON;
							}
							else if ((cursorX >= 95) && (cursorX <= 465) && (cursorY >= 530) && (cursorY <= 671))
							{
								hover = HOVEROPTIONS;
								if (packet[0] & BIT(0))
									option = OPTIONSBUTTON;
							}
							else if ((cursorX >= 559) && (cursorX <= 929) && (cursorY >= 530) && (cursorY <= 671))
							{
								hover = HOVEREXIT;
								if (packet[0] & BIT(0))
									option = EXITBUTTON;
							}
							else
								hover = HOVERNOTHING;

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

		if (option == PLAYBUTTON)
		{
			gameState = 1;
			while (gameState == 1)
			{
				gameState = openGame(&game, &resources);
			}
			option = NOTHING;
			hover = HOVERNOTHING;
		}
		else if (option == STATSBUTTON)
		{
			leaderboardDisplay(&game, &resources);
			option = NOTHING;
			hover = HOVERNOTHING;
		}
		else if (option == OPTIONSBUTTON)
		{
			options(&game, &resources);
			option = NOTHING;
			hover = HOVERNOTHING;
		}
		else if(option == EXITBUTTON)
		{
			break;
		}
	}

	if (leavePixelWings(&game, &resources) == -1)
		return -1;

	return 0;
}


int pauseMenu(gameData *game, projData *resources){
	//interrupts
	int ipc_status;
	message msg;
	char r;

	//keyboard
	unsigned char MSByte = 0;

	//mouse
	unsigned char packet[3];
	int counter_packets = 0;

	//cursor coords
	unsigned short cursorX = 495;
	unsigned short cursorY = 382;
	unsigned short x;
	unsigned short y;

	//machine states
	button option = NOTHING;
	hoverbutton hoverpausemenu = HOVERNOTHING;

	while(option == NOTHING) {

		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & resources->returnbit.keyboard) {
					changeScancode(&MSByte);
				}
				if (msg.NOTIFY_ARG & resources->returnbit.timer){
					//desenhar rato
					copyThirdBuffer();
					drawSecondBuffer(resources->bitmap.pause, 0, 0);

					if(hoverpausemenu == HOVERRESTART)
						drawSecondBuffer(resources->bitmap.hoverrestart, 288, 429);
					else if(hoverpausemenu == HOVERCONTINUE)
							drawSecondBuffer(resources->bitmap.hovercontinue, 288, 268);
					else if(hoverpausemenu == HOVEREXIT5)
							drawSecondBuffer(resources->bitmap.hoverexit5, 288, 595);

					drawSecondBuffer(resources->bitmap.cursor, cursorX, cursorY);
					drawMainBuffer();
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
						if (packet[0] & BIT(4))
						{
							x = -(256 - packet[1]);
						}
						else
							x = packet[1];

						if (packet[0] & BIT(5))
						{
							y = -(256 - packet[2]);
						}
						else
							y = packet[2];

						moveCursor(x, y, &cursorX, &cursorY);

						if (packet[0] & BIT(0)) //Left Click
						{
							if ((cursorX >= 290) && (cursorX <= 741) && (cursorY >= 267) && (cursorY <= 408))
							{
								option = PLAYBUTTON;
							}
							else if ((cursorX >= 290) && (cursorX <= 741) && (cursorY >= 431) && (cursorY <= 572))
							{
								option = RESTARTBUTTON;
							}
							else if ((cursorX >= 290) && (cursorX <= 741) && (cursorY >= 596) && (cursorY <= 736))
							{
								option = EXITBUTTON;
							}
						}

						if ((cursorX >= 290) && (cursorX <= 741) && (cursorY >= 267) && (cursorY <= 408))
							hoverpausemenu = HOVERCONTINUE;
						else if ((cursorX >= 290) && (cursorX <= 741) && (cursorY >= 431) && (cursorY <= 572))
							hoverpausemenu = HOVERRESTART;
						else if ((cursorX >= 290) && (cursorX <= 741) && (cursorY >= 596) && (cursorY <= 736))
							hoverpausemenu = HOVEREXIT5;
						else
							hoverpausemenu = HOVERNOTHING;

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

	if (option == PLAYBUTTON)
	{
		return 0;
	}
	else if (option == RESTARTBUTTON)
	{
		return 1;
	}
	else if(option == EXITBUTTON)
	{
		return 2;
	}

	return 2;
}


int gameOver(gameData *game, projData *resources){
	//username
	int usernameSaved = 0; //0 - gameover antes de por username | 1 - depois de guardar username
	char currentUsername[12];
	int cUsernameCounter = 0;

	//interrupts
	int ipc_status;
	int j, m;
	message msg;
	char r;

	//keyboard
	unsigned char MSByte = 0;

	//mouse
	unsigned char packet[3];
	int counter_packets = 0;

	//cursor coords
	unsigned short cursorX = 495;
	unsigned short cursorY = 382;
	unsigned short x;
	unsigned short y;

	//machine states
	button option = NOTHING;
	hoverbutton hovergameover = HOVERNOTHING;

	//score
	int posScore = 10;
	if (game->scoreCounter < 10) //mudar de sitio
	{
		game->scores[game->scoreCounter].valor = -1;
		game->scoreCounter++;
	}

	for (j = 0; j < game->scoreCounter; j++)
	{
		if (game->scoreAtual > game->scores[j].valor)
		{
			posScore = j;
			for (m = game->scoreCounter - 1; m > j; m--)
			{
				game->scores[m] = game->scores[m-1];
			}
			game->scores[j].valor = game->scoreAtual;
			break;
		}
	}

	game->scores[posScore].currentDate[0] = (char) floor(((int)resources->currentDate.day/(int)pow(10,1))%10);
	game->scores[posScore].currentDate[1] = (char) floor(((int)resources->currentDate.day/(int)pow(10,0))%10);
	game->scores[posScore].currentDate[2] = '/';
	game->scores[posScore].currentDate[3] = (char) floor(((int)resources->currentDate.month/(int)pow(10,1))%10);
	game->scores[posScore].currentDate[4] = (char) floor(((int)resources->currentDate.month/(int)pow(10,0))%10);
	game->scores[posScore].currentDate[5] = '/';
	game->scores[posScore].currentDate[6] = (char) 2;
	game->scores[posScore].currentDate[7] = (char) 0;
	game->scores[posScore].currentDate[8] = (char) floor(((int)resources->currentDate.year/(int)pow(10,1))%10);
	game->scores[posScore].currentDate[9] = (char) floor(((int)resources->currentDate.year/(int)pow(10,0))%10);

	game->scores[posScore].usernameCounter = 0;

	while(option == NOTHING) {

		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & resources->returnbit.keyboard) {
					changeScancode(&MSByte);
					if (usernameSaved == 0)
						addLetterUsername(currentUsername, &cUsernameCounter, MSByte);
				}
				if (msg.NOTIFY_ARG & resources->returnbit.timer){
					//desenhar rato
					copyThirdBuffer();
					drawSecondBuffer(resources->bitmap.gameover, 0, 0);
					drawLetters(currentUsername, cUsernameCounter, resources);
					if(usernameSaved == 1)
						drawSecondBuffer(resources->bitmap.saved, 0, 0);

					if(hovergameover == HOVERRETRY)
						drawSecondBuffer(resources->bitmap.hoverretry, 110, 556);
					else if(hovergameover == HOVEREXIT4)
							drawSecondBuffer(resources->bitmap.hoverexit4, 544, 556);
					else if(hovergameover == HOVEROK)
							drawSecondBuffer(resources->bitmap.hoverok, 629, 393);

					drawSecondBuffer(resources->bitmap.cursor, cursorX, cursorY);
					drawMainBuffer();
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
						if (packet[0] & BIT(4))
						{
							x = -(256 - packet[1]);
						}
						else
							x = packet[1];

						if (packet[0] & BIT(5))
						{
							y = -(256 - packet[2]);
						}
						else
							y = packet[2];

						moveCursor(x, y, &cursorX, &cursorY);

						if (packet[0] & BIT(0)) //Left Click
						{
							if ((cursorX >= 110) && (cursorX <= 481) && (cursorY >= 556) && (cursorY <= 698))
							{
								option = RESTARTBUTTON;
							}
							else if ((cursorX >= 545) && (cursorX <= 916) && (cursorY >= 556) && (cursorY <= 698))
							{
								option = EXITBUTTON;
							}
							else if ((cursorX >= 630) && (cursorX <= 697) && (cursorY >= 393) && (cursorY <= 450))
							{
								//OK (guardar username e score)
								usernameSaved = 1;

								if (cUsernameCounter != 0)
								{
									for (j = 0; j < cUsernameCounter; j++)
									{
										game->scores[posScore].username[j] = currentUsername[j];
									}
									game->scores[posScore].usernameCounter = cUsernameCounter;
								}
							}
						}

						if ((cursorX >= 110) && (cursorX <= 481) && (cursorY >= 556) && (cursorY <= 698))
							hovergameover = HOVERRETRY;
						else if ((cursorX >= 545) && (cursorX <= 916) && (cursorY >= 556) && (cursorY <= 698))
							hovergameover = HOVEREXIT4;
						else if ((cursorX >= 630) && (cursorX <= 697) && (cursorY >= 393) && (cursorY <= 450))
							hovergameover = HOVEROK;
						else
							hovergameover = HOVERNOTHING;

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

	if (game->scores[posScore].usernameCounter == 0)
	{
		game->scores[posScore].username[0] = 'U';
		game->scores[posScore].username[1] = 'N';
		game->scores[posScore].username[2] = 'K';
		game->scores[posScore].username[3] = 'N';
		game->scores[posScore].username[4] = 'O';
		game->scores[posScore].username[5] = 'W';
		game->scores[posScore].username[6] = 'N';
		game->scores[posScore].usernameCounter = 7;
	}

	if (option == RESTARTBUTTON)
	{
		return 1;
	}
	else if(option == EXITBUTTON)
	{
		return 2;
	}

	return 2;
}


void options(gameData *game, projData *resources){
	//interrupts
	int ipc_status;
	message msg;
	char r;

	//keyboard
	unsigned char MSByte;

	//mouse
	unsigned char packet[3];
	int counter_packets = 0;

	//cursor coords
	unsigned short cursorX = 495;
	unsigned short cursorY = 382;
	unsigned short x;
	unsigned short y;

	int counterdragon = 1;
	int counter = 0;

	//machine states
	int exit = 0;
	hoverbutton hoveroptionsmenu = HOVERNOTHING;

	//while((opcao != PLAY) && (opcao != EXIT)) {
	while(exit != 1) {

		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & resources->returnbit.keyboard) { //debug
					changeScancode(&MSByte);
				}
				if (msg.NOTIFY_ARG & resources->returnbit.timer){
					//desenhar rato
					drawSecondBuffer(resources->bitmap.options, 0, 0); //menu stats

					if(counterdragon == 1){
						drawSecondBuffer(resources->bitmap.dragon1, 240, 361);
						drawSecondBuffer(resources->bitmap.dragon11, 609, 361);
					}
					else if(counterdragon == 2){
						drawSecondBuffer(resources->bitmap.dragon2, 240, 361);
						drawSecondBuffer(resources->bitmap.dragon22, 609, 361);
					}
					else if(counterdragon == 3){
						drawSecondBuffer(resources->bitmap.dragon3, 240, 361);
						drawSecondBuffer(resources->bitmap.dragon33, 609, 361);
					}
					else if(counterdragon == 4){
						drawSecondBuffer(resources->bitmap.dragon4, 240, 361);
						drawSecondBuffer(resources->bitmap.dragon44, 609, 361);
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

					if(game->currentDragon == 0)
						drawSecondBuffer(resources->bitmap.fire, 306, 552);
					else if(game->currentDragon == 1)
						drawSecondBuffer(resources->bitmap.ice, 675, 552);

					if(hoveroptionsmenu == HOVEREXIT2)
						drawSecondBuffer(resources->bitmap.hoverexit2, 433, 565);


					drawSecondBuffer(resources->bitmap.cursor, cursorX, cursorY);
					drawMainBuffer();
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
						if (packet[0] & BIT(4))
						{
							x = -(256 - packet[1]);
						}
						else
							x = packet[1];

						if (packet[0] & BIT(5))
						{
							y = -(256 - packet[2]);
						}
						else
							y = packet[2];

						moveCursor(x, y, &cursorX, &cursorY);

						if (packet[0] & BIT(0)) //Left Click
						{
							if ((cursorX >= 433) && (cursorX <= 592) && (cursorY >= 565) && (cursorY <= 627))
							{
								exit = 1;
								return;
							}
							else if ((cursorX >= 215) && (cursorX <= 442) && (cursorY >= 313) && (cursorY <= 536))
							{
								if(game->currentDragon == 1)
									game->currentDragon = 0;
							}
							else if ((cursorX >= 583) && (cursorX <= 810) && (cursorY >= 313) && (cursorY <= 536))
							{
								if(game->currentDragon == 0)
									game->currentDragon = 1;
							}
						}

						if ((cursorX >= 433) && (cursorX <= 592) && (cursorY >= 565) && (cursorY <= 627))
							hoveroptionsmenu = HOVEREXIT2;
						else
							hoveroptionsmenu = HOVERNOTHING;

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
}


void leaderboardDisplay(gameData *game, projData *resources){
	//interrupts
	int ipc_status;
	message msg;
	char r;

	//keyboard
	unsigned char MSByte;

	//mouse
	unsigned char packet[3];
	int counter_packets = 0;

	//cursor coords
	unsigned short cursorX = 495;
	unsigned short cursorY = 382;
	unsigned short x;
	unsigned short y;

	//machine states
	int exit = 0;
	hoverbutton hoverstatsmenu = HOVERNOTHING;

	//while((opcao != PLAY) && (opcao != EXIT)) {
	while(exit != 1) {

		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & resources->returnbit.keyboard) { //debug
					changeScancode(&MSByte);
				}
				if (msg.NOTIFY_ARG & resources->returnbit.timer){
					//desenhar rato
					drawSecondBuffer(resources->bitmap.leaderboard, 0, 0); //menu stats
					printLeaderBoard(game, resources);
					if(hoverstatsmenu == HOVEREXIT3)
						drawSecondBuffer(resources->bitmap.hoverexit3, 453, 692);
					drawSecondBuffer(resources->bitmap.cursor, cursorX, cursorY);
					drawMainBuffer();
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
						if (packet[0] & BIT(4))
						{
							x = -(256 - packet[1]);
						}
						else
							x = packet[1];

						if (packet[0] & BIT(5))
						{
							y = -(256 - packet[2]);
						}
						else
							y = packet[2];

						moveCursor(x, y, &cursorX, &cursorY);

						if (packet[0] & BIT(0)) //Left Click
						{
							if ((cursorX >= 453) && (cursorX <= 612) && (cursorY >= 693) && (cursorY <= 755))
							{
								exit = 1;
								return;
							}
						}

						if ((cursorX >= 453) && (cursorX <= 612) && (cursorY >= 693) && (cursorY <= 755))
							hoverstatsmenu = HOVEREXIT3;
						else
							hoverstatsmenu = HOVERNOTHING;


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
}


void loadScores(gameData *game){
	FILE *scoresFile = fopen("/home/lcom/proj/src/scores.txt", "r");

	int d, m, y, usernameCounter, k = 0;
	while (1)
	{
		fscanf(scoresFile, "%d[^-]", &usernameCounter);
		if (usernameCounter == 13)
		{
			break;
		}
		game->scores[k].usernameCounter = usernameCounter;
		fscanf(scoresFile, "%[^-]", game->scores[k].username);
		fscanf(scoresFile, "-%d[^-]", &game->scores[k].valor);
		fscanf(scoresFile, "%d/%d/%d", &d, &m, &y);
		game->scores[k].currentDate[0] = (char) floor((d/(int)pow(10,1))%10);
		game->scores[k].currentDate[1] = (char) floor((d/(int)pow(10,0))%10);
		game->scores[k].currentDate[2] = '/';
		game->scores[k].currentDate[3] = (char) floor((m/(int)pow(10,1))%10);
		game->scores[k].currentDate[4] = (char) floor((m/(int)pow(10,0))%10);
		game->scores[k].currentDate[5] = '/';
		game->scores[k].currentDate[6] = (char) floor((y/(int)pow(10,3))%10);;
		game->scores[k].currentDate[7] = (char) floor((y/(int)pow(10,2))%10);;
		game->scores[k].currentDate[8] = (char) floor((y/(int)pow(10,1))%10);
		game->scores[k].currentDate[9] = (char) floor((y/(int)pow(10,0))%10);
		k++;
	}
	game->scoreCounter = k;

	fclose(scoresFile);
}

void saveScores(gameData *game){
	FILE *scoresFile = fopen("/home/lcom/proj/src/scores.txt", "w");
	int i, k;

	for(i = 0; i < game->scoreCounter; i++){

		//name
		fprintf(scoresFile, "%d", game->scores[i].usernameCounter);
		fprintf(scoresFile, "%c", '-');

		for(k = 0; k < game->scores[i].usernameCounter; k++){
			fprintf(scoresFile, "%c", game->scores[i].username[k]);
		}
		fprintf(scoresFile, "%c", '-');

		//score
		fprintf(scoresFile, "%d", game->scores[i].valor);
		fprintf(scoresFile, "%c", '-');

		//date
		for(k = 0; k < 10; k++){
			switch (game->scores[i].currentDate[k])
			{
			case 0:
				fprintf(scoresFile, "%c", '0');
				break;
			case 1:
				fprintf(scoresFile, "%c", '1');
				break;
			case 2:
				fprintf(scoresFile, "%c", '2');
				break;
			case 3:
				fprintf(scoresFile, "%c", '3');
				break;
			case 4:
				fprintf(scoresFile, "%c", '4');
				break;
			case 5:
				fprintf(scoresFile, "%c", '5');
				break;
			case 6:
				fprintf(scoresFile, "%c", '6');
				break;
			case 7:
				fprintf(scoresFile, "%c", '7');
				break;
			case 8:
				fprintf(scoresFile, "%c", '8');
				break;
			case 9:
				fprintf(scoresFile, "%c", '9');
				break;
			case '/':
				fprintf(scoresFile, "%c", '/');
				break;
			}
		}

		fprintf(scoresFile, "%c", '\n');

	}
	fprintf(scoresFile, "%d%c", 13, '-');
	fclose(scoresFile);
}
