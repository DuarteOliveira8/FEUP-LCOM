#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"

//Variaveis globais
int mouse_hook_id = 2;
long contador;

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

int mouse_irq_disable(){
	if(sys_irqdisable(&mouse_hook_id) != OK)
		return 1;

	return 0;
}

int mouse_irq_enable(){
	if(sys_irqenable(&mouse_hook_id) != OK)
		return 1;

	return 0;
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
