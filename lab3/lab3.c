#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/driver.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "i8042.h"
#include "test3.h"
#include "keyboard.h"
#include "i8254.h"
//#include "timer.h"

static int proc_args(int argc, char **argv);
static unsigned long parse_ulong(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv)
{
	/* DO NOT FORGET TO initialize service */
    sef_startup();
    sys_enable_iop(SELF);

	if (argc == 1) {					/* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	}
	else return proc_args(argc, argv);
}

static void print_usage(char **argv)
{
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"scan <unsigned long - assembly>\"\n"
			"\t service run %s -args \"poll <void>\"\n"
			"\t service run %s -args \"timed <unsigned long - n>\"\n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv)
{
	unsigned long assembly, n;
	if (strncmp(argv[1], "scan", strlen("scan")) == 0) {
		if (argc != 3) {
			return 1;
		}
		assembly = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (assembly == ULONG_MAX)
			return 1;
		return kbd_test_scan(assembly);
	}
	else if (strncmp(argv[1], "poll", strlen("poll")) == 0) {
		return kbd_test_poll();
	}
	else if (strncmp(argv[1], "timed", strlen("timed")) == 0) {
		if (argc != 3) {
			printf("keyboard: wrong no of arguments for kbd_test_timed_scan()\n");
			return 1;
		}
		n = parse_ulong(argv[2], 10);						/* Parses string to unsigned long */
		if (n == ULONG_MAX)
			return 1;
		return kbd_test_timed_scan(n);
	}
	else {
		printf("keyboard: %s - no valid function!\n", argv[1]);
		return 1;
	}
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
		printf("keyboard: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}
