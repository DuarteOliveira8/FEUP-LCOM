#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "i8042.h"
#include "keyboard.h"
#include "test3.h"
#include "i8254.h"

//Variaveis globais
int hook_id = 1;
long contador;
int hook_id_timer;
int counter;
unsigned char currentByte;

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
#ifdef LAB3
		contador++;
#endif

		if( stat & OBF ) {
			sys_inb(OUT_BUF, &data);
#ifdef LAB3
			contador++;
#endif

			if ( (stat &(PAR_ERR | TO_ERR)) == 0 ){
				currentByte = data;
				return;
			}
		}

		tickdelay(micros_to_ticks(DELAY_US));
	}
}


void printScancodeAssembly(unsigned char *MSByte)
{
	unsigned char first_byte, second_byte;

	//kbc_handler_ass();
	first_byte = currentByte;
	if(first_byte == MSB_2BYTES)
	{
		//kbc_handler_ass();
		second_byte = currentByte;
		if(second_byte & BIT(7))
		{
			printf("Breakcode: 0x%x 0x%x\n", first_byte, second_byte);
			*MSByte = first_byte;
		}
		else
		{
			printf("Makecode: 0x%x 0x%x\n", first_byte, second_byte);
			*MSByte = first_byte;
		}
	}
	else
	{
		if(first_byte & BIT(7))
		{
			printf("Breakcode: 0x%x\n", first_byte);
			*MSByte = first_byte;
		}
		else
		{
			printf("Makecode: 0x%x\n", first_byte);
			*MSByte = first_byte;
		}
	}
}


void printScancodeC(unsigned char *MSByte)
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
			printf("Breakcode: 0x%x 0x%x\n", first_byte, second_byte);
			*MSByte = first_byte;
		}
		else
		{
			printf("Makecode: 0x%x 0x%x\n", first_byte, second_byte);
			*MSByte = first_byte;
		}
	}
	else
	{
		if(first_byte & BIT(7))
		{
			printf("Breakcode: 0x%x\n", first_byte);
			*MSByte = first_byte;
		}
		else
		{
			printf("Makecode: 0x%x\n", first_byte);
			*MSByte = first_byte;
		}
	}
}
