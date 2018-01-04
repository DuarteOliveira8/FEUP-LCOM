#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "timer.h"
#include "i8254.h"

//Variaveis Globais
int hook_id = 0;
int counter = 0;

int timer_set_frequency(unsigned char timer, unsigned long freq) {
	//verifica se o valor de timer e valido
	if (timer < 0 || timer > 2)
	{
		return 1;
	}

	//calcula valor do contador
	unsigned long counterTimer = TIMER_FREQ / freq;
	//determina o valor que vai ser associado a TIMER_CTRL para o Timer 0
	unsigned char comando = TIMER_SEL0 | TIMER_SQR_WAVE | TIMER_LSB_MSB;

	//associa o do contador a lsb e msb
	unsigned long lsb = counterTimer;
	//neste ultimo fazendo shift
	unsigned long msb = counterTimer >>= 8;


	//escreve em TIMER_CTRL o comando e associa o contador ao timer correto
	if (timer == 0)
	{
		sys_outb(TIMER_CTRL, comando);
		sys_outb(TIMER_0, lsb);
		sys_outb(TIMER_0, msb);
		return 0;
	}
	else if (timer == 1)
	{
		comando = TIMER_SEL1 | TIMER_SQR_WAVE | TIMER_LSB_MSB;
		sys_outb(TIMER_CTRL, comando);
		sys_outb(TIMER_1, lsb);
		sys_outb(TIMER_1, msb);
		return 0;
	}
	else if (timer == 2)
	{
		comando = TIMER_SEL2 | TIMER_SQR_WAVE | TIMER_LSB_MSB;
		sys_outb(TIMER_CTRL, comando);
		sys_outb(TIMER_2, lsb);
		sys_outb(TIMER_2, msb);
		return 0;
	}
}

int timer_subscribe_int(void ) {
	//guarda o valor antigo do hook_id
	int oldhook = hook_id;

	if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK)
		return 1;

	if(sys_irqenable(&hook_id) != OK)
		return 1;

	//retorna o bit de indice oldhook
	return BIT(oldhook);
}

int timer_unsubscribe_int() {
	if(sys_irqdisable(&hook_id) != OK)
		return 1;

	if(sys_irqrmpolicy(&hook_id) != OK)
		return 1;

	return 0;
}

void timer_int_handler() {
	counter++;
}

int timer_get_conf(unsigned char timer, unsigned char *st) {
	//Verifica se o valor de timer e valido
	if (timer < 0 || timer > 2)
	{
		return 1;
	}

	unsigned long stTEMP = *st;

	//associa a TIMER_CTRL o valor correto dependendo do timer e escreve em
	//e escreve em stTEMP a configuraçao obtida
	if(timer == '0')
	{
		sys_outb(TIMER_CTRL, 0xE2);
		sys_inb(TIMER_0, &stTEMP);
		return 0;
	}
	else if(timer == '1')
	{
		sys_outb(TIMER_CTRL, 0xE4);
		sys_inb(TIMER_1, &stTEMP);
		return 0;
	}
	else if(timer == '2')
	{
		sys_outb(TIMER_CTRL, 0xE8);
		sys_inb(TIMER_2, &stTEMP);
		return 0;
	}
}

int timer_display_conf(unsigned char conf) {
	if(conf & TIMER_SEL2)
	{
		printf("output is at high\n");
	}
	else
	{
		printf("output is at low\n");
	}
	

	//Counter:
	if(conf & TIMER_SEL1)
	{
		printf("counter is null\n");
	}
	else
	{
		printf("counter is not null\n");
	}

	//Type Of Access:
	if(!(conf & TIMER_MSB) && (conf & TIMER_LSB))
	{
		printf("type of access: LSB\n");
	}
	else if((conf & TIMER_MSB) && !(conf & TIMER_LSB))
	{
		printf("type of access: MSB\n");
	}
	else if((conf & TIMER_MSB) && (conf & TIMER_LSB))
	{
		printf("type of access: LSB followed by MSB\n");
	}

	//Operating mode:
	if(!(conf & TIMER_BIT3) && !(conf & TIMER_RATE_GEN) && !(conf & TIMER_BIT1))
	{
		printf("operating mode 0\n");
	}
	else if(!(conf & TIMER_BIT3) && !(conf & TIMER_RATE_GEN) && (conf & TIMER_BIT1))
	{
		printf("operating mode 1\n");
	}
	else if((conf & TIMER_BIT3) && !(conf & TIMER_RATE_GEN) && (conf & TIMER_BIT1) || (conf & TIMER_BIT3) && (conf & TIMER_RATE_GEN) && !(conf & TIMER_BIT1))
	{
		printf("operating mode 2\n");
	}
	else if(!(conf & TIMER_BIT3) && (conf & TIMER_RATE_GEN) && (conf & TIMER_BIT1) || (conf & TIMER_BIT3) && (conf & TIMER_RATE_GEN) && (conf & TIMER_BIT1))
	{
		printf("operating mode 3\n");
	}
	else if((conf & TIMER_BIT3) && !(conf & TIMER_RATE_GEN) && !(conf & TIMER_BIT1))
	{
		printf("operating mode 4\n");
	}
	else if((conf & TIMER_BIT3) && !(conf & TIMER_RATE_GEN) && (conf & TIMER_BIT1))
	{
		printf("operating mode 5\n");
	}

	//Counting mode:
	if(conf & TIMER_BIT0)
	{
		printf("counting mode is BCD\n");
	}
	else
	{
		printf("counting mode is binary\n");
	}


	return 0;
}

int timer_test_time_base(unsigned long freq) {
	
	if(timer_set_frequency(0, freq) == 0)
		return 0;
	else
	{
		return 1;
	}
}

int timer_test_int(unsigned long time) {
	int ipc_status;
	message msg;
	char *r;

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
					if(counter % 60 == 0)
					{
						printf("A full second has passed\n");
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

	timer_unsubscribe_int();

	return 0;
}

int timer_test_config(unsigned char timer) {
	unsigned char st;
	if(timer_get_conf(timer, &st) == 0)
	{
		if(timer_display_conf(st) == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 1;
	}
}
