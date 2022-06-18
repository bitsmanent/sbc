/* simple base converter */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[]) {
	unsigned long n;
	int len, base = 0, i, s;

	if(argc < 2 || argc > 3) {
		printf("Usage: %s <value> [base]\n", argv[0]);
		return 1;
	}
	if(!strcmp("-v", argv[1])) {
		printf("sbc-%s\n", VERSION);
		return 1;
	}
	if(argv[2])
		base = atoi(argv[2]);
	else {
		len = strlen(argv[1]);
		if(argv[1][len-1] == 'b' && argv[1][1] != 'x')
			base = 2;
	}
	n = strtoul(argv[1], NULL, base);
	if(errno == ERANGE || errno == EINVAL)
		return -1;
	printf("%lu %#04lx %lo ", n, n, n);
	for(s = 64 - 8; s > 0 && !(n >> s); s -= 8);
	for(i = 0; i < 8 && s >= 0; i++) {
		printf("%d", ((n >> s) << i) & 0x80 ? 1 : 0);
		if(i == 8 - 1) {
			s -= 8;
			i = -1;
			printf(" ");
		}
	}
	printf("\n");
	return 0;
}
