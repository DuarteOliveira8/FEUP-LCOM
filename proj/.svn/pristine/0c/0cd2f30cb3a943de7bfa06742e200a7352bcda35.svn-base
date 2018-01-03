#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "i8042.h"
#include "keyboard.h"
#include "game.h"
#include "i8254.h"

//Variaveis globais
int hook_id = 1;
long contador;
int counter;
unsigned char currentByte;

int keyboard_subscribe_int() {
    //guarda o valor antigo do hook_id
    int oldhook = hook_id;
    
    if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != OK)
        return 1;
    
    if(sys_irqenable(&hook_id) != OK)
        return 1;
    
    //retorna o bit de indice oldhook
    return BIT(oldhook);
}

int keyboard_unsubscribe_int() {
    if(sys_irqdisable(&hook_id) != OK)
        return 1;
    
    if(sys_irqrmpolicy(&hook_id) != OK)
        return 1;
    
    return 0;
}



void kbc_handler(){
	unsigned long stat;
	unsigned long data;

	while( 1 ) {
		sys_inb(STAT_REG, &stat);

		if( stat & OBF ) {
			sys_inb(OUT_BUF, &data);

			if ( (stat &(PAR_ERR | TO_ERR)) == 0 ){
				currentByte = data;
				return;
			}
		}

		tickdelay(micros_to_ticks(DELAY_US));
	}
}

void changeScancode(unsigned char *MSByte)
{
	unsigned char first_byte, second_byte;

	kbc_handler();
	first_byte = currentByte;
	if(first_byte == MSB_2BYTES)
	{
		kbc_handler();
		second_byte = currentByte;
		if(second_byte & BIT(7))
		{
			*MSByte = first_byte;
		}
		else
		{
			*MSByte = first_byte;
		}
	}
	else
	{
		if(first_byte & BIT(7))
		{
			*MSByte = first_byte;
		}
		else
		{
			*MSByte = first_byte;
		}
	}
}
