# Makefile for proj

COMPILER_TYPE= gnu

CC= gcc

PROG= proj
SRCS= proj.c vbe.c video_gr.c game.c keyboard.c timer.c mouse.c bitmap.c rtc.c pixelWings.c graphics.c

CFLAGS= -Wall 

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys -llm

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>
