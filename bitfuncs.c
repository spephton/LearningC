#include <stdio.h>
#include <stdlib.h>

int setbits(int x, int p, int n, int y);
unsigned getbits(unsigned x, int p, int n);
int invert(int x, int p, int n);

int main(int argc, char *argv[]) {
	char *orig_string = argv[1];
	
	// setbits sets x[p:p-n] to rightmost n bits of p
	// x = 0, p = n
	print("8: %i\n", setbits(0, 3, 3, 63)) // 8
	print("%i\n", setbits(0, 4, 3, 63)) // 16
								6
			


}


