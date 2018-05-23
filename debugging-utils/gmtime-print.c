#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
	bool do_posix = false;
	int c;

	while ((c = getopt(argc, argv, "p")) != -1) {
		switch (c) {
			case 'p':
				do_posix = true;
				break;
		}
	}
	argc -= optind;

	if (argc != 1) {
		printf("usage: %s: time_t\n", argv[0]);
		exit(1);
	}
	time_t orig_time = atoi(argv[1]);

	struct tm *info;

	info = gmtime(&orig_time );
   
	printf(
	"	year=%i\n"\
	"	mon=%i\n"\
	"	mday=%i\n"\
	"	hour=%i\n"\
	"	min=%i\n"\
	"	sec=%i\n"\
	"	wday=%i\n"\
	"	yday=%i\n"\
	"	dst=%i\n"\
	"	tzone=%s\n"\
	"	gmoff=%ld\n",
	info->tm_year,
	info->tm_mon, 
	info->tm_mday,
	info->tm_hour,
	info->tm_min,
	info->tm_sec,
	info->tm_wday,
	info->tm_yday,
	info->tm_isdst, 
	info->tm_zone,
	info->tm_gmtoff);
}
