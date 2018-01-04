#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"
#include "test4.h"

//Variaveis globais
int hook_id = 1;
int mouse_hook_id = 2;
long contador;
int hook_id_timer;
int counter;

//FUNCOES LAB2 (TIMER)

int timer_subscribe_int(void) {
	//guarda o valor antigo do hook_id
	int oldhook = hook_id_timer;

	if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id_timer) != OK)
		return 1;

	if(sys_irqenable(&hook_id_timer) != OK)
		return 1;

	//retorna o bit de indice oldhook
	return BIT(oldhook);
}

int timer_unsubscribe_int() {
	if(sys_irqdisable(&hook_id_timer) != OK)
		return 1;

	if(sys_irqrmpolicy(&hook_id_timer) != OK)
		return 1;

	return 0;
}

void timer_int_handler() {
	counter++;
}

//FUNCOES LAB4 (MOUSE)

int mouse_subscribe_int() {
    //guarda o valor antigo do hook_id
    int oldhook = mouse_hook_id;

    if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != OK)
        return 1;

    if(sys_irqenable(&mouse_hook_id) != OK)
        return 1;

    //retorna o bit de indice oldhook
    return BIT(oldhook);
}

int mouse_unsubscribe_int() {
    if(sys_irqdisable(&mouse_hook_id) != OK)
        return 1;

    if(sys_irqrmpolicy(&mouse_hook_id) != OK)
        return 1;

    return 0;
}

void mouseHandler(unsigned char *bytepointer){
	unsigned long statreg, byte;

	while (1)
	{
		sys_inb(STAT_REG, &statreg);

		if (statreg & (BIT(5) | BIT(0)))
		{
			if (sys_inb(OUT_BUF, &byte) != OK)
				continue;

			if((statreg & (PAR_ERR | TO_ERR)) == 0)
			{
				*bytepointer = byte;
				return;
			}
		}
	}

	return;
}

int readMouse(unsigned char *packet, int mouseIRQ) {
	int ipc_status;
	message msg;
	int r;
	int contador1 = 0;

	while(contador1 < 3)
	{
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 )
		{
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source))
			{
				case HARDWARE:
					if (msg.NOTIFY_ARG & mouseIRQ)
					{
						mouseHandler(&packet[contador1]);

						contador1++;

						if(!(packet[0] & BIT(3)))
						{
							contador1 = 0;
						}
					}
					break;
				default:
					break;
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	return 0;
}


int readMouse_poll(unsigned char *packet) {
	int contador1 = 0;

	while(contador1 < 3) {
		mouseHandler(&packet[contador1]);

		contador1++;

		if(!(packet[0] & BIT(3)))
		{
			contador1 = 0;
		}
	}

	return 0;
}
