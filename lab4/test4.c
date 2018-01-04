#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"
#include "test4.h"


//variaveis globais
int counter = 0;

int mouse_test_packet(unsigned short cnt){
	unsigned char packet[3];
	int x = 0, y = 0;

	int returnbit = mouse_subscribe_int();

	unsigned long ack;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, STREAM_MODE);
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, ENABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;

	while (cnt > 0)
	{
		readMouse(packet, returnbit);

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

		printf("B1=0x%x B2=0x%x B3=0x%x LB=%lu MB=%lu RB=%lu XOV=%lu YOV=%lu X=%d Y=%d\n", packet[0], packet[1], packet[2], (packet[0] & BIT(0)), (packet[0] & BIT(2)) >> 2, (packet[0] & BIT(1)) >> 1, (packet[0] & BIT(6)) >> 6, (packet[0] & BIT(7)) >> 7, x, y);

		cnt--;
	}

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, DISABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;
	sys_inb(IN_BUF, &ack);
	if (ack != ACK)
		return -1;

	mouse_unsubscribe_int();

	return 0;
}	

int mouse_test_async(unsigned short idle_time){
	unsigned char packet[3];
	int x = 0, y = 0;

	int ipc_status, counter_packets = 0;
	message msg;
	char r;

	int returnbit_timer = timer_subscribe_int();
	int returnbit_mouse = mouse_subscribe_int();

	unsigned long ack;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, STREAM_MODE);
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, ENABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;


	while (counter < idle_time * 60) {
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & returnbit_mouse)
					{
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

							printf("B1=0x%x B2=0x%x B3=0x%x LB=%lu MB=%lu RB=%lu XOV=%lu YOV=%lu X=%d Y=%d\n", packet[0], packet[1], packet[2], (packet[0] & BIT(0)), (packet[0] & BIT(2)) >> 2, (packet[0] & BIT(1)) >> 1, (packet[0] & BIT(6)) >> 6, (packet[0] & BIT(7)) >> 7, x, y);

							counter_packets = 0;
						}

						counter = 0;
					}
					else if (msg.NOTIFY_ARG & returnbit_timer) {
						timer_int_handler();
					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		}
	}

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, DISABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;
	sys_inb(IN_BUF, &ack);
	if (ack != ACK)
		return -1;

	timer_unsubscribe_int();
	mouse_unsubscribe_int();

	return 0;
}	

int mouse_test_remote(unsigned long period, unsigned short cnt){
	unsigned char packet[3];
	int x = 0, y = 0;
	unsigned long ack;

	mouse_subscribe_int(); //para fazer disable do IH do Minix

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, DISABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, SET_REMOTE);
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;

	while (cnt > 0)
	{
		sys_outb(KBC_CMD_REG, KBC_COMMAND);
		sys_outb(IN_BUF, READ_DATA);
		sys_inb(OUT_BUF, &ack);
		if (ack != ACK)
			return -1;

		readMouse_poll(packet);

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

		printf("B1=0x%x B2=0x%x B3=0x%x LB=%lu MB=%lu RB=%lu XOV=%lu YOV=%lu X=%d Y=%d\n", packet[0], packet[1], packet[2], (packet[0] & BIT(0)), (packet[0] & BIT(2)) >> 2, (packet[0] & BIT(1)) >> 1, (packet[0] & BIT(6)) >> 6, (packet[0] & BIT(7)) >> 7, x, y);

		tickdelay(micros_to_ticks(period*1000));

		cnt--;
	}

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, DISABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;
	sys_inb(IN_BUF, &ack);
	if (ack != ACK)
		return -1;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, STREAM_MODE);
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;

	mouse_unsubscribe_int();

	return 0;
}	

int mouse_test_gesture(short length){
	unsigned char packet[3];
	int x = 0, y = 0;
	int distance = length;

	int returnbit = mouse_subscribe_int();

	unsigned long ack;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, STREAM_MODE);
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, ENABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if(ack != ACK)
		return -1;


	while (distance > 0)
	{
		readMouse(packet, returnbit);

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

		printf("B1=0x%x B2=0x%x B3=0x%x LB=%lu MB=%lu RB=%lu XOV=%lu YOV=%lu X=%d Y=%d\n", packet[0], packet[1], packet[2], (packet[0] & BIT(0)), (packet[0] & BIT(2)) >> 2, (packet[0] & BIT(1)) >> 1, (packet[0] & BIT(6)) >> 6, (packet[0] & BIT(7)) >> 7, x, y);

		if( (packet[0] & BIT(1)) && (y > 0))
			distance = distance - x;

		if ((x < 0) || (y < 0) || !(packet[0] & BIT(1)))
			distance = length;

	}

	sys_outb(KBC_CMD_REG, KBC_COMMAND);
	sys_outb(IN_BUF, DISABLE_STREAM);
	sys_inb(OUT_BUF, &ack);
	if (ack != ACK)
		return -1;
	sys_inb(IN_BUF, &ack);
	if (ack != ACK)
		return -1;

	mouse_unsubscribe_int();

	return 0;
}	
