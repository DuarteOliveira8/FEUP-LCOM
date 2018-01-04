#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "i8042.h"
#include "i8254.h"
#include "mouse.h"
#include "test4.h"

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
			"\t service run %s -args \"packet <unsigned short - cnt>\"\n"
			"\t service run %s -args \"async <unsigned short - idle_time>\"\n"
			"\t service run %s -args \"remote <unsigned long - period unsigned short - cnt>\"\n"
			"\t service run %s -args \"gesture <short - length>\"\n",
			argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned long period;
	unsigned short cnt, idle_time;
	short length;

	if (strncmp(argv[1], "packet", strlen("packet")) == 0) {
		if (argc != 3) {
			printf("mouse: wrong no of arguments for mouse_test_packet(cnt)\n");
			return 1;
		}
		cnt = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (cnt == ULONG_MAX)
			return 1;
		return mouse_test_packet(cnt);
	}
	else if (strncmp(argv[1], "async", strlen("async")) == 0) {
		if (argc != 3) {
			printf("mouse: wrong no of arguments for mouse_test_async(idle_time)\n");
			return 1;
		}
		idle_time = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (idle_time == ULONG_MAX)
			return 1;
		return mouse_test_async(idle_time);
	}
	else if (strncmp(argv[1], "remote", strlen("remote")) == 0) {
		if (argc != 4) {
			printf("mouse: wrong no of arguments for mouse_test_remote(period, cnt)\n");
			return 1;
		}
		period = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		cnt = parse_ulong(argv[3], 10);
		if ((period == ULONG_MAX) || (cnt == ULONG_MAX))
			return 1;
		return mouse_test_remote(period, cnt);
	}
	else if (strncmp(argv[1], "gesture", strlen("gesture")) == 0) {
		if (argc != 3) {
			printf("mouse: wrong no of arguments for mouse_test_gesture(length)\n");
			return 1;
		}
		length = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (length == ULONG_MAX)
			return 1;
		return mouse_test_gesture(length);
	}
	else {
		printf("keyboard: %s - no valid function!\n", argv[1]);
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
		printf("mouse: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
	return 0;
}
