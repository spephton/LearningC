#include <stdio.h>
#include <stdlib.h>

int setbits(int x, int p, int n, int y);
unsigned getbits(unsigned x, int p, int n);
int invert(int x, int p, int n);
int bit_string(int x, char string[], int bounds);

int main(int argc, char *argv[]) {
	int i = atoi(argv[1]);
	// x = 0, p = n
//	print("8: %i\n", setbits(0, 3, 3, 63)); // 8
//	print("16: %i\n", setbits(0, 4, 3, 63)); // 16
	char string[32];
	int len = bit_string(i, string, 32);
	printf("%s has length %i\n", string, len);
	return 0;	
}

int setbits(int x, int p, int n, int y) {
	// setbits sets x[p:p-n] to rightmost n bits of y
	//
	// x & MASK should unset every bit not set in the mask
	// our MASK should be ones initially: ~0
	// shift right by p-n, fill those with zeros
	// we want the n lowest bits to be set though, so invert again, shift
	// right by n, invert once more?
	return 0;
}

int bit_string(int x, char string[], int bounds) {
	// copies bits of x into string, in order from low bit to high.
	//
	// i.e. 2 would be 01\0
	// bounds gives size of string arr.
	// always null-terminates. returns length (max bounds-1)
	// truncation may have occurred if length == bounds -1.
	int j;
	for (j = 0; x && j < bounds - 1; j++) {
		string[j] = x & 1 ? '1' : '0';
		x >>= 1;
	}
	string[j] = '\0';
	printf("%s\n", string);
	return j;
}

