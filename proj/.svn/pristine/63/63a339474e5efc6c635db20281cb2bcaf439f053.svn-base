#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

#include "bitmap.h"

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

/**
 *	@brief copies the second buffer to the video memory.
 */
void drawMainBuffer();

/**
 *	@brief draws the bitmap on the second buffer on the specified coordinates.
 *	@param bmp bitmap pointer to the bitmap.
 *	@param x x coordinate to the start of the bitmap.
 *	@param y y coordinate to the start of the bitmap.
 */
void drawSecondBuffer(Bitmap* bmp, int x, int y);

/**
 *	@brief copies the second buffer to the third buffer.
 */
void drawThirdBuffer();

/**
 *	@brief copies the third buffer to the second buffer.
 */
void copyThirdBuffer();

 /** @} end of video_gr */
 
#endif /* __VIDEO_GR_H */
