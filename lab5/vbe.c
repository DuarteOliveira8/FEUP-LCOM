#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14
#define SIZE_MODE  256

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {
	mmap_t map_t;

	lm_init();
	lm_alloc(sizeof(vbe_mode_info_t), &map_t);

	struct reg86u reg86;
	reg86.u.w.ax = 0x4F01;
	reg86.u.w.es = PB2BASE(map_t.phys);
	reg86.u.w.di = PB2OFF(map_t.phys);
	reg86.u.w.cx = mode;
	reg86.u.b.intno = 0x10;

	if( sys_int86(&reg86) != OK ) {
		printf("set_vbe_mode: sys_int86() failed\n");
		return 1;
	}

	memcpy(vmi_p, map_t.virtual, SIZE_MODE);

	lm_free(&map_t);
  
	return 1;
}


