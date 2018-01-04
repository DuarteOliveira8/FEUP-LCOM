#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "lmlib.h"
#include "test5.h"
#include "vbe.h"
#include "video_gr.h"
#include "pixmap.h"


static void print_usage(char **argv);
static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);

int main(int argc, char *argv[]) {
	/* DO NOT FORGET TO initialize service */
	sef_startup();

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
    return 0;
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"init <unsigned short - mode, unsigned short - delay>\"\n"
			"\t service run %s -args \"square <unsigned short - x, unsigned short - y, unsigned short - size, unsigned long - color>\"\n"
			"\t service run %s -args \"line <unsigned short - xi, unsigned short - yi, unsigned short - xf, unsigned short - yf, unsigned long - color>\"\n"
			"\t service run %s -args \"xpm <char - *xpm[], unsigned short - xi, unsigned short - yi>\"\n"
			"\t service run %s -args \"move <char - *xpm[], unsigned short - xi, unsigned short - yi, unsigned short - xf, unsigned short - yf, short - s, unsigned short - f>\"\n"
			"\t service run %s -args \"controller\"\n",
			argv[0], argv[0], argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned short mode, delay, x, y, size, xi, yi, xf, yf, f;
	unsigned long color;
	char **xpm;
	short s;

	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if (argc != 4) {
			printf("video: wrong no of arguments for video_test_init(unsigned short mode, unsigned short delay)\n");
			return 1;
		}
		mode = parse_ulong(argv[2], 16);						/* Parses string to unsigned long */
		delay = parse_ulong(argv[3], 10);
		if ((mode == ULONG_MAX) || (delay == ULONG_MAX))
			return 1;
		return video_test_init(mode, delay);
	}
	else if (strncmp(argv[1], "square", strlen("square")) == 0) {
		if (argc != 6) {
			printf("video: wrong no of arguments for video_test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color)\n");
			return 1;
		}
		x = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		y = parse_ulong(argv[3], 10);
		size = parse_ulong(argv[4], 10);
		color = parse_ulong(argv[5], 10);
		if ((x == ULONG_MAX) || (y == ULONG_MAX) || (size == ULONG_MAX) || (color == ULONG_MAX))
			return 1;
		return video_test_square(x, y, size, color);
	}
	else if (strncmp(argv[1], "line", strlen("line")) == 0) {
		if (argc != 7) {
			printf("video: wrong no of arguments for video_test_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color)\n");
			return 1;
		}
		xi = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		yi = parse_ulong(argv[3], 10);
		xf = parse_ulong(argv[4], 10);						/* Parses string to unsigned long */
		yf = parse_ulong(argv[5], 10);
		color = parse_ulong(argv[6], 10);
		if ((xi == ULONG_MAX) || (yi == ULONG_MAX) || (xf == ULONG_MAX) || (yf == ULONG_MAX) || (color == ULONG_MAX))
			return 1;
		return video_test_line(xi, yi, xf, yf, color);
	}
	else if (strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
		if (argc != 5) {
			printf("video: wrong no of arguments for video_test_xpm(char *xpm[], unsigned short xi, unsigned short yi)\n");
			return 1;
		}

		if (strncmp(argv[2], "pic1", strlen("pic1")) == 0 )
		{
			xpm = pic1;
		}
		else if (strncmp(argv[2], "pic2", strlen("pic2")) == 0 )
		{
			xpm = pic2;
		}
		else if (strncmp(argv[2], "cross", strlen("cross")) == 0 )
		{
			xpm = cross;
		}
		else if (strncmp(argv[2], "pic3", strlen("pic3")) == 0 )
		{
			xpm = pic3;
		}
		else if (strncmp(argv[2], "penguin", strlen("penguin")) == 0 )
		{
			xpm = penguin;
		}
		else
		{
			printf("test5::Image not found\n");
			return 1;
		}

		xi = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
		yi = parse_ulong(argv[4], 10);						/* Parses string to unsigned long */
		if ((xi == ULONG_MAX) || (yi == ULONG_MAX))
			return 1;
		return test_xpm(xpm, xi, yi);
	}
	else if (strncmp(argv[1], "move", strlen("move")) == 0) {
		if (argc != 9) {
			printf("video: wrong no of arguments for video_test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short s, unsigned short f)\n");
			return 1;
		}

		if (strncmp(argv[2], "pic1", strlen("pic1")) == 0 )
		{
			xpm = pic1;
		}
		else if (strncmp(argv[2], "pic2", strlen("pic2")) == 0 )
		{
			xpm = pic2;
		}
		else if (strncmp(argv[2], "cross", strlen("cross")) == 0 )
		{
			xpm = cross;
		}
		else if (strncmp(argv[2], "pic3", strlen("pic3")) == 0 )
		{
			xpm = pic3;
		}
		else if (strncmp(argv[2], "penguin", strlen("penguin")) == 0 )
		{
			xpm = penguin;
		}
		else
		{
			printf("test5::Image not found\n");
			return 1;
		}

		xi = parse_ulong(argv[3], 10);						/* Parses string to unsigned long */
		yi = parse_ulong(argv[4], 10);
		xf = parse_ulong(argv[5], 10);						/* Parses string to unsigned long */
		yf = parse_ulong(argv[6], 10);
		s = parse_ulong(argv[7], 10);
		f = parse_ulong(argv[8], 10);
		if ((xi == ULONG_MAX) || (yi == ULONG_MAX) || (xf == ULONG_MAX) || (yf == ULONG_MAX) || (s == ULONG_MAX) || (f == ULONG_MAX))
			return 1;
		return test_move(xpm, xi, yi, xf, yf, s, f);
	}
	else if (strncmp(argv[1], "controller", strlen("controller")) == 0) {
		if (argc != 2) {
			printf("video: wrong no of arguments for int video_test_controller()\n");
			return 1;
		}
		return test_controller();
	}
	else {
		printf("video: %s - no valid function!\n", argv[1]);
		return 1;
	}
	return 0;
}

static unsigned long parse_ulong(char *str, int base)
{
	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("video: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
	return 0;
}
