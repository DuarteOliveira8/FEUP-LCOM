#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include "timer.h"
#include "i8254.h"

//Variaveis Globais
int hook_id_timer = 0;
int counter = 0;

int timer_subscribe_int(void ) {
	//guarda o valor antigo do hook_id_timer
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

int timer_test_int(unsigned long time) {
	int ipc_status;
	message msg;
	int r;

	int returnbit = timer_subscribe_int();

	while(counter < time * 60) {
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & returnbit) {
					timer_int_handler();
				}
				break;
			default:
				break;
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	timer_unsubscribe_int();

	return 0;
}
