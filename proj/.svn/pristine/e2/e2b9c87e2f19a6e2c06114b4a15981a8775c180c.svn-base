#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "vbe.h"
#include "video_gr.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */

/* Private global variables */

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static char *secondBuffer;
static char *thirdBuffer;
int vram_size;

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}

void *vg_init(unsigned short mode) {
	struct reg86u reg86;
	reg86.u.w.ax = 0x4F02;
	reg86.u.w.bx = 1<<14|mode;
	reg86.u.b.intno = 0x10;

	if( sys_int86(&reg86) != OK ) {
		printf("set_vbe_mode: sys_int86() failed\n");
		return NULL;
	}

	vbe_mode_info_t vbeMode;
	vbe_get_mode_info(mode, &vbeMode);

	h_res = vbeMode.XResolution;
	v_res = vbeMode.YResolution;
	bits_per_pixel = vbeMode.BitsPerPixel;
	vram_size = h_res*v_res*(bits_per_pixel/8);

	int r;
	struct mem_range mr;
	unsigned int vram_base = vbeMode.PhysBasePtr;  /* VRAM's physical addresss */

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	   panic("sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

	if(video_mem == MAP_FAILED)
	   panic("couldn't map video memory");

	secondBuffer = (char *) malloc(vram_size);
	thirdBuffer = (char *) malloc(vram_size);

	return (void *) video_mem;
}

void drawMainBuffer(){
	memcpy(video_mem, secondBuffer, vram_size);
}

void drawSecondBuffer(Bitmap* bmp, int x, int y){
	drawBitmap(bmp, x, y, secondBuffer);
}

void drawThirdBuffer(){
	memcpy(thirdBuffer, secondBuffer, vram_size);
}

void copyThirdBuffer(){
	memcpy(secondBuffer, thirdBuffer, vram_size);
}
