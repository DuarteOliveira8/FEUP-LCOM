#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "test5.h"
#include "video_gr.h"
#include "timer.h"
#include "keyboard.h"
#include "i8042.h"
#include "i8254.h"
#include "read_xpm.h"
#include "video_test.h"
#include "sprite.h"

int video_test_init(unsigned short mode, unsigned short delay) {
	vg_init(mode);
	timer_test_int(delay);
	vg_exit();
	return 0;
}


int video_test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {
	unsigned short Xmeio = 1024/2 + x;
	unsigned short Ymeio = 768/2 + y;
	unsigned short Xcanto = Xmeio - size/2;
	unsigned short Ycanto = Ymeio - size/2;

	char* video_mem_orig = (char*) vg_init(0x105);

	if (Xcanto + 1024*Ycanto <= 1024*768)
	{
		int ix;
		int iy;
		for (iy = 0; iy < size; iy++)
		{
			for (ix = 0; ix < size; ix++)
			{
				if (Xcanto + 1024*(Ycanto + iy) + ix < 1024 + 1024*(Ycanto + iy))
					video_mem_orig[Xcanto + 1024*(Ycanto + iy) + ix] = (char) color;
			}
		}
	}

    int ipc_status;
    message msg;
    char r;
    unsigned char MSByte = 0;

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
						while(MSByte != ESC){
						  printScancodeC(&MSByte);
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
    vg_exit();

    keyboard_unsubscribe_int();
	
	return 0;
}

int video_test_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color) {
	unsigned int pixeli = xi + yi*1024;
	unsigned int pixelf = xf + yf*1024;

	if (pixeli > pixelf)
	{
		unsigned int temp;
		temp = xi;
		xi = xf;
		xf = temp;
		temp = yi;
		yi = yf;
		yf = temp;
		temp = pixeli;
		pixeli = pixelf;
		pixelf = temp;
	}

	char* video_mem_orig = (char*) vg_init(0x105);

	if(pixeli > 1024*768) {
		vg_exit();
		return 0;
	}

	unsigned int i;
	unsigned int k;
	int x = xi;
	if (xi == xf) //VERTICAL
	{
		for (i = pixeli; i <= pixelf; i += 1024)
		{
			if (i < 1024*768)
				video_mem_orig[i] = (char) color;
		}
	}
	else if (yi == yf) //HORIZONTAL
	{
		for (i = pixeli; i <= pixelf; ++i)
		{
			if (i < 1024 + 1024*yi)
				video_mem_orig[i] = (char) color;
		}
	}
	else if (abs(yf - yi) >= abs(xf - xi)) //DIAGONAL CASO 1
	{
		double declive = abs(yf - yi)/abs(xf - xi);
		if (xf > xi)
		{
			for (i = pixeli; i <= pixelf; i++, x++)
			{
				for (k = 0; k < declive; k++, i += 1024)
				{
					if ((i <= 1024*768) && (x < 1024) && (x >= 0))
						video_mem_orig[i] = (char) color;
				}
			}
		}
		else if (xi > xf)
		{
			for (i = pixeli; i <= pixelf; i--, x--)
			{
				for (k = 0; k < declive; k++, i += 1024)
				{
					if ((i <= 1024*768) && (x < 1024) && (x >= 0))
						video_mem_orig[i] = (char) color;
				}
			}
		}
	}
	else if (abs(yf - yi) < abs(xf - xi)) //DIAGONAL CASO 2
	{
		double declive = abs(xf - xi)/abs(yf - yi);
		if (xf > xi)
		{
			for (i = pixeli; i <= pixelf; i += 1024)
			{
				for (k = 0; k < declive; k++, i++, x++)
				{
					if ((i <= 1024*768) && (x < 1024) && (x >= 0))
						video_mem_orig[i] = (char) color;
				}
			}
		}
		else if (xi > xf)
		{
			for (i = pixeli; i <= pixelf; i += 1024)
			{
				for (k = 0; k < declive; k++, i--, x--)
				{
					if ((i <= 1024*768) && (x < 1024) && (x >= 0))
						video_mem_orig[i] = (char) color;
				}
			}
		}
	}

	int ipc_status;
	message msg;
	char r;
	unsigned char MSByte = 0;

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
						while(MSByte != ESC){
						  printScancodeC(&MSByte);
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
	vg_exit();

	keyboard_unsubscribe_int();
	
	return 0;
}
	
int test_xpm(char *xpm[], unsigned short xi, unsigned short yi) {
	char* video_mem_orig = (char*) vg_init(0x105);

	//lê a info da imagem
	int width, height, i, j;
	char *image;
	image = read_xpm(xpm, &width, &height);

	//associa cada pixel da imagem a um no ecrã, com o canto superior esquerdo da imagem a começar no pixel (xi, yi)
	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			video_mem_orig[xi + i + 1024 * (yi + j)] = image[i + j*width];
		}
	}
	video_dump_fb();

	int ipc_status;
	message msg;
	char r;
	unsigned char MSByte = 0;

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
						while(MSByte != ESC) {
						  printScancodeC(&MSByte);
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
	vg_exit();

	keyboard_unsubscribe_int();

	return 0;
}	

int test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short s, unsigned short f) {
	float ticks = 60/f;
	int vertical = 0, horizontal = 0;
	if (xi == xf)
		vertical = 1;
	else if (yi == yf)
		horizontal = 1;
	else
		return 0;

	char* video_mem_orig = (char*) vg_init(0x105);

	int i, j;

	int ipc_status;
	message msg;
	char r;
	unsigned char MSByte = 0;

	int returnbitK = keyboard_subscribe_int();
	int returnbitT = timer_subscribe_int();

	if(horizontal)
	{
		Sprite *sp = create_sprite(xpm, xi, yi, s, 0);
		while(MSByte != ESC) {

		  if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			  printf("driver_receive failed with: %d", r);
			  continue;
		  }

		  if (is_ipc_notify(ipc_status)) { /* received notification */
			  switch (_ENDPOINT_P(msg.m_source)) {
				  case HARDWARE:
					  if (msg.NOTIFY_ARG & returnbitK) {
						  printScancodeC(&MSByte);
					  }
					  else if (msg.NOTIFY_ARG & returnbitT)
					  {
						  if (xf >= xi)
						  {
							    for(j = 0; j < sp->height; j++)
								{
									for(i = 0; i < sp->width; i++)
									{
										if (((xi + i + 1024 * (yi + j)) < 1024*768) && (xi + i < 1024))
											video_mem_orig[xi + i + 1024 * (yi + j)] = sp->map[i + j*sp->width];
									}
								}
								video_dump_fb();
								tickdelay(ticks);
								if (xi + s < xf)
								{
									for(j = 0; j < sp->height; j++)
									{
										for(i = 0; i < sp->width; i++)
										{
											if (((xi + i + 1024 * (yi + j)) < 1024*768) && (xi + i < 1024))
												video_mem_orig[xi + i + 1024 * (yi + j)] = 0x000000;
										}
									}
								}
								xi += s;
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
		destroy_sprite(sp);
	}
	else if(vertical)
	{
		Sprite *sp = create_sprite(xpm, xi, yi, 0, s);
		while(MSByte != ESC) {

		  if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			  printf("driver_receive failed with: %d", r);
			  continue;
		  }

		  if (is_ipc_notify(ipc_status)) { /* received notification */
			  switch (_ENDPOINT_P(msg.m_source)) {
				  case HARDWARE:
					  if (msg.NOTIFY_ARG & returnbitK) {
							  printScancodeC(&MSByte);
					  }
					  else if (msg.NOTIFY_ARG & returnbitT)
					  {
						  if (yf >= yi)
						  {
							    for(j = 0; j < sp->height; j++)
								{
									for(i = 0; i < sp->width; i++)
									{
										if (((xi + i + 1024 * (yi + j)) < 1024*768) && (xi + i < 1024))
											video_mem_orig[xi + i + 1024 * (yi + j)] = sp->map[i + j*sp->width];
									}
								}
								video_dump_fb();
								tickdelay(ticks);
								if (yi + s < yf)
								{
									for(j = 0; j < sp->height; j++)
									{
										for(i = 0; i < sp->width; i++)
										{
											if (((xi + i + 1024 * (yi + j)) < 1024*768) && (xi + i < 1024))
												video_mem_orig[xi + i + 1024 * (yi + j)] = 0x000000;
										}
									}
								}
								yi += s;
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
		destroy_sprite(sp);
	}


	vg_exit();

	keyboard_unsubscribe_int();
	timer_unsubscribe_int();

	return 0;
}	

int test_controller() {
	return 0;
}	
	
