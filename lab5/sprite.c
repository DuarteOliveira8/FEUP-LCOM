/** Creates a new sprite with pixmap "pic", with specified
* position (within the screen limits) and speed;
* Does not draw the sprite on the screen
* Returns NULL on invalid pixmap.
*/

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "sprite.h"
#include "read_xpm.h"


Sprite *create_sprite(char *pic[], int x, int y, int xspeed, int yspeed) {
	//allocate space for the "object"
	Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
	if( sp == NULL )
	return NULL;
	// read the sprite pixmap
	sp->map = read_xpm(pic, &(sp->width), &(sp->height));
	if( sp->map == NULL ) {
	free(sp);
	return NULL;
	}
	sp->x = x;
	sp->y = y;
	sp->xspeed = xspeed;
	sp->yspeed = yspeed;
	return sp;
}

void destroy_sprite(Sprite *sp) {
	if( sp == NULL )
	return;
	if( sp ->map )
	free(sp->map);
	free(sp);
	sp = NULL; // XXX: pointer is passed by value
	// should do this @ the caller
}

//int animate_sprite(Sprite *sp) {
//
//}
///* Some useful non-visible functions */
//static int draw_sprite(Sprite *sp, char *base) {
//
//}
//static int check_collision(Sprite *sp, char *base) {
//
//}
