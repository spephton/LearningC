#include <stdio.h>

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);
unsigned getbits(unsigned x, int p, int n);
int invert(int x, int p, int n);
int bit_string(int x, char string[], int bounds);
int mystrlen(char *string);
void rev_str(char *dst, char *string);
void bit_stringh(int x, char *bitstr, int bounds);
unsigned uc_setbits(unsigned x, unsigned p, unsigned n, unsigned y);


int main(int argc, char *argv[]) {

    char *normal = "a dog a panic in a pagoda";
	char reversed[32];
	rev_str(reversed, normal);
	printf("%s\n", normal);
	printf("%s\n", reversed);
	
	int nums[] = {1, 2, 3, 4};
	int nums_length = 4;

	int i;
	int bounds = 32;
	char backwards_bitstring[bounds];
	char corrected_bitstring[bounds];
	for (i = 0; i < nums_length; i++) {
		bit_string(nums[i], backwards_bitstring, bounds);
		rev_str(corrected_bitstring, backwards_bitstring);
		printf("%s\n", backwards_bitstring);
		printf("%s\n", corrected_bitstring);
		bit_stringh(nums[i], corrected_bitstring, bounds);
		printf("%s\n", corrected_bitstring);
	}
	printf("ok sweet we worked that out and we can now get the bit ");
	printf("representation of a number in a sane order\n");
	
	// work on setbits here:
	// x, p, n, y -> int
	unsigned m = ~0; // 111...
	m <<= 3; // 1111...1000
	// let's check
	char print_buffer[bounds]; 
	bit_stringh(m, print_buffer, bounds);
	printf("Checking m should have three trailing zeros: %s\n",
			print_buffer);
	// cool, m is 1111...11000
	// let's invert it then add another region
	m = ~m;
	m <<= 2;
	m = ~m;
	bit_stringh(m, print_buffer, bounds);
	printf("Checking m should end with 00011: %s\n",
			print_buffer);
	// dank, that worked. We have our bitmask, x & m should
	// unset the region we want to write.	
	
	// now we mask y, unset all but the rightmost n bits
	unsigned y = 63; // a bunch of ones
	y &= ~((unsigned)~0 << 3); // unset all but the last three
	bit_stringh(y, print_buffer, bounds);
	printf("Checking y should end with 00111: %s\n",
			print_buffer);
	
	// let's shift right by p-n (assume this is positive e.g. 2
	y <<= 2;
	bit_stringh(y, print_buffer, bounds);
	printf("Checking y should end with 0011100: %s\n",
			print_buffer);
	// Cool, we have everything we need. Let's take an x like 128, so we
	// can see our insertion clearly:
	unsigned x = 128;
	x &= m; // unsets bits 2-4 (right-indexed)
			// (they're already zero though)
	x |= y;  // copy our y into the trimmed bits
	// result should be a 1 in the 128's col,
	// and three 1s in the 16, 8, 4 cols
	bit_stringh(x, print_buffer, bounds);
	printf("Checking x should end with 10011100: %s\n",
			print_buffer);
	// that works, sweet, let's write our function!
	

	printf("7: %i\n", setbits(0, 3, 3, 63)); // 7
	printf("14: %i\n", setbits(0, 4, 3, 63)); // 14
	
	x = 245;
	y = 523;
	bit_stringh(x, print_buffer, bounds);
	printf("x:   %s\n", print_buffer);
	bit_stringh(y, print_buffer, bounds);
	printf("y: %s\n", print_buffer);
	// this should really be a function dude
	//
	// anyway that prints:
	// x:   11110101
	// y: 1000001011
	//
	// so if p = 5, n = 3, we copy 011 from y and put it:
	// 11110101
	//    ^^^
	//    here
	// 
	// yielding
	// 11101101
	//
	// what is that in decimal? I'll let the computer work it out:
	x = setbits(x, 5, 3, y);
	printf("Turns out it's %i\n", x);
	printf("And let's check the bits actually are 11101101:\n");
	bit_stringh(x, print_buffer, bounds);
	printf("%s\n", print_buffer);
	// Let's check I didn't blow up anything important:
	x = 245;
	x = uc_setbits(x, 5, 3, y);
	printf("%i\n", x);
	return 0;	
}

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
	// setbits sets [p:p-n] from the right of x to rightmost n bits of y
	//
	// ASSUME:
	// p >= n
	// x & MASK should unset every bit not set in the mask
	// our MASK should be ones initially: ~0
	// shift right by n, fill those with zeros
	unsigned m = ~0;
	m <<= n;
	// we want the n lowest bits to be set though, so invert again, shift
	// right by p - n, invert once more?
	m = ~(~m << (p - n));
	// now we can unset the region concerned: 
	x &= m;

	// the region we're copying into is now zeroed. We can now prepare the
	// rightmost n bits of y to be copied into our target region
	// first truncate to rightmost n:
	y &= ~(~0 << n);
	// then shift right by p - n:
	y <<= (p - n);

	// finally, we can copy the target region of y into the cleared region
	// of x:
	x |= y;
	return x;
}

//Kinda want to see this with less comments:
unsigned uc_setbits(unsigned x, unsigned p, unsigned n, unsigned y) {
	unsigned m = ~0;
	m <<= n;
	m = ~(~m << (p - n));
	x &= m;
	y &= ~(~0 << n);
	y <<= (p - n);
	x |= y;
	return x;
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
	return j;
}

void rev_str(char *dst, char *string) {
	// Reverse string, put result in dst.
	// dst must have enough memory
	// string must be a valid string (\0 terminated)
	int len = mystrlen(string);
	
	int i;
	for (i = 0; i < len; i++) {
		dst[i] = string[len - i - 1];
	}
	dst[i] = '\0';
}

int mystrlen(char *string) {
	int i;
	for (i = 0; string[i] != 0; i++) {}
	return i;
}

void bit_stringh(int x, char *bitstr, int bounds) {
	// the 'h' is alluding to e.g. ls -lh
	// bit string returned in human readable order
	char reversed[bounds];
	bit_string(x, reversed, bounds);
	rev_str(bitstr, reversed);
}
