#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// yolo
	int n = atoi(argv[1]);
	int number = 1;

	for (int i = 0; i < n; i++) {
		printf("%i\n", number);
		number <<= 1;
	}
	return 0;
}
