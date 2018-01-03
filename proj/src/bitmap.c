#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <limits.h>
#include <errno.h>
#include "lmlib.h"
#include "vbe.h"
#include "video_gr.h"
#include "game.h"
#include "bitmap.h"

#define GREEN      0x07E2

Bitmap* loadBitmap(const char* filename) {
    // allocating necessary size
    Bitmap* bmp = (Bitmap*) malloc(sizeof(Bitmap));

    // open filename in read binary mode
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    // read the bitmap file header
    BitmapFileHeader bitmapFileHeader;
    fread(&bitmapFileHeader, 2, 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.type != 0x4D42) {
        fclose(filePtr);
        return NULL;
    }

    int rd;
    do {
        if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
            break;
    } while (0);

    if (rd != 1) {
        fprintf(stderr, "Error reading file\n");
        exit(-1);
    }

    // read the bitmap info header
    BitmapInfoHeader bitmapInfoHeader;
    fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

    // move file pointer to the begining of bitmap data
    fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

    // allocate enough memory for the bitmap image data
    unsigned char* bitmapImage = (unsigned char*) malloc(
            bitmapInfoHeader.imageSize);

    // verify memory allocation
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        fclose(filePtr);
        return NULL;
    }

    // close file and return bitmap image data
    fclose(filePtr);

    bmp->bitmapData = bitmapImage;
    bmp->bitmapInfoHeader = bitmapInfoHeader;

    return bmp;
}

void drawBitmap(Bitmap* bmp, int x, int y, char *video_mem_orig) {
    if (bmp == NULL)
        return;

    int width = bmp->bitmapInfoHeader.width;
    int drawWidth = width;
    int height = bmp->bitmapInfoHeader.height;

    int xCorrection = 0;
    if (x < 0) {
        xCorrection = -x;
        drawWidth -= xCorrection;
        x = 0;

        if (drawWidth > 1024)
            drawWidth = 1024;
    } else if (x + drawWidth >= 1024) {
        drawWidth = 1024 - x;
    }

    unsigned short* bufferStartPos;
    unsigned short* imgStartPos;

    int i;
    for (i = 0; i < height; i++) {
        int pos = y + height - 1 - i;

        if (pos < 0 || pos >= 768)
            continue;

        bufferStartPos = (unsigned short*) video_mem_orig;
        bufferStartPos += x + pos * 1024;

        imgStartPos = ((unsigned short*) bmp->bitmapData) + xCorrection + i * width;

        int k;
        for (k = 0; k < drawWidth; k++){
			if (imgStartPos[k] != GREEN)
				bufferStartPos[k] = imgStartPos[k];
        }
    }
}

void deleteBitmap(Bitmap* bmp) {
    if (bmp == NULL)
        return;

    free(bmp->bitmapData);
    free(bmp);
}

const char* getPath(char* file){
	char num[256];

	sprintf(num, file);

	char* path = (char *) malloc(256);
	strcpy(path, num);
	return path;
}
