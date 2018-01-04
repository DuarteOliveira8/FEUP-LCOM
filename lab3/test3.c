#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include "test3.h"
#include "i8042.h"
#include "keyboard.h"
#include "i8254.h"



//Variaveis globais
long contador=0;
int hook_id_timer = 0;
int counter = 0;

int kbd_test_scan(unsigned short assembly) {
    int ipc_status;
    message msg;
    char r;
    unsigned char MSByte = 0; //MSByte vai guardar
    
    int returnbit = keyboard_subscribe_int();
    
    while(MSByte != ESC) {

        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.NOTIFY_ARG & returnbit) {
                            if(assembly) // se assembly = 1
                            {
                            		//printScancodeAssembly(&MSByte) nao funciona o handler
                            }
                            else // se assembly = 0
                            {
                               while(MSByte != ESC){
                                    //chamar a funcao de print escrita em assembly
                                    printScancodeC(&MSByte);
                                }
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
    
    keyboard_unsubscribe_int();
    
    return 0;

}


int kbd_test_poll() {
    unsigned long KBCoriginal;

    sys_outb(KBC_CMD_REG, KBC_CMD_READ);
    sys_inb(OUT_BUF, &KBCoriginal);

    sys_outb(KBC_CMD_REG, KBC_CMD_WRITE);
    sys_outb(IN_BUF, (KBCoriginal & 0xfe));

    unsigned char MSByte = 0;

    while(MSByte != ESC) {

		printScancodeC(&MSByte);
    }

    	sys_outb(KBC_CMD_REG, KBC_CMD_WRITE);
    	sys_outb(IN_BUF, KBCoriginal);
#ifdef LAB3
    	printf("contador de sys_inb: %ld", contador);
#endif

    	return 0;
}


int kbd_test_timed_scan(unsigned short n) {
	int ipc_status;
	message msg;
    char r;
    unsigned char MSByte = 0; //MSByte vai guardar

    int returnbit_timer = timer_subscribe_int();
    int returnbit_kbd = keyboard_subscribe_int();

    while (counter < n * 60) {
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & returnbit_kbd) {
						printScancodeC(&MSByte);
						if (MSByte == ESC){
							counter = n * 60;
							break;
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


	timer_unsubscribe_int();
	keyboard_unsubscribe_int();

	return 0;
}
