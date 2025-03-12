#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc != 2 || strlen(argv[1]) != 1) {
		printf("invalid char\n");
		exit(1);
	}

	int c = (unsigned char)argv[1][0];

	printf("%d\n", c);

	printf("digittoint: %d\n", digittoint(c));
	printf("isalnum: %d\n", isalnum(c));
	printf("isalpha: %d\n", isalpha(c));
	printf("isascii: %d\n", isascii(c));
	printf("iscntrl: %d\n", iscntrl(c));
	printf("isdigit: %d\n", isdigit(c));
	printf("isgraph: %d\n", isgraph(c));
	printf("ishexnumber: %d\n", ishexnumber(c));
	printf("isideogram: %d\n", isideogram(c));
	printf("islower: %d\n", islower(c));
	printf("isnumber: %d\n", isnumber(c));
	printf("isphonogram: %d\n", isphonogram(c));
	printf("isspecial: %d\n", isspecial(c));
	printf("isprint: %d\n", isprint(c));
	printf("ispunct: %d\n", ispunct(c));
	printf("isrune: %d\n", isrune(c));
	printf("isspace: %d\n", isspace(c));
	printf("isupper: %d\n", isupper(c));
	printf("isxdigit: %d\n", isxdigit(c));
	printf("toascii: %d\n", toascii(c));
	printf("tolower: %d\n", tolower(c));
	printf("toupper: %d\n", toupper(c));

	printf("LANG=%s\n", getenv("LANG"));
	printf("LC_ALL=%s\n", getenv("LC_ALL"));
	printf("LC_COLLATE=%s\n", getenv("LC_COLLATE"));
	printf("LC_CTYPE=%s\n", getenv("LC_CTYPE"));
	printf("LC_MESSAGES=%s\n", getenv("LC_MESSAGES"));
	printf("LC_MONETARY=%s\n", getenv("LC_MONETARY"));
	printf("LC_NUMERIC=%s\n", getenv("LC_NUMERIC"));
	printf("LC_TIME=%s\n", getenv("LC_TIME"));
}
