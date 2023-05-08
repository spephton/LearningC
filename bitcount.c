#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	unsigned x = atoi(argv[1]);

	int b;
	
	for (b = 0; x != 0; x >>= 1) {
		if (x & 01)
			b++;
	}
	printf("%i", b);
	return 0;
}
