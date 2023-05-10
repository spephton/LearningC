#include <stdio.h>
#include <stdlib.h>

char lower(char c);

int main(int argc, char *argv[]) {
	char *orig_string = argv[1];

	// we will convert orig_string to lower-case
	char result_string[1024];
	int c, i;
	for (i = 0; (c = orig_string[i]) != 0; i++) {
		result_string[i] = lower(c);
	}
	result_string[i] = '\0';

	printf("%s\n", result_string);

	return 0;
}

char lower(char c) {
	char difference = 'a' - 'A';
	return (c >= 'A' && c <= 'Z') ? c + difference : c;
}

