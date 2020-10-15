#include <stdio.h>
#define NEWLINE 10 // presumably change this to 13 on a non-Unix-like OS.

static int parseDecimalString(char number[], int lastIndex); // string -> int
static int power(int a, int x, unsigned char y); // calcs a*x^y
static void printFib(int n);

int main() {
	
	int c;
	int argLen = 0;
	int argMaxSize = 2; // fib(94) overflows a long long: floats are for wusses
	char argStr[argMaxSize + 1]; // add an entry for null terminator
	
	printf("How many Fibonacci numbers would you like? (max. 93)\n");
	
	while ((c = getchar()) != NEWLINE) {
		
		if (argLen == argMaxSize) {
			// can't accept arguments greater than 93, fib(94) overflows %llu
			printf("ERROR: Input must be 93 or less\n");
			return 1;
			
		} else if (c < '0' || c > '9') {
			printf("ERROR: Input must be in decimal numeral format.\n");
			return 1;
			
		} else {
			argStr[argLen] = c;
			argLen++;
		}
	}
	argStr[argLen] = 0; // null terminate the string NOTE: idk how safe this \
	is, do we risk having un-anchored, allocated memory? I imagine we might? \
	Strings just being a pointer to an array? I wanna learn more about this. 
	
	int argAsInt = parseDecimalString(argStr, argLen);
	if (argAsInt > 93) {
		printf("ERROR: Input must be 93 or less\n");
		return 1;
	}
	
	printf("\n\nPrinting the first %i elements of the Fibonacci sequence:\n",
	 argAsInt);
	printFib(argAsInt);
	return 0;
}

// returns a*x^y. naive, performs y multiplications. 
// take care not to overflow int (limit: (2^15 - 1) = 32,767)
static int power(int a, int x, unsigned char y) { // unsigned y ensures halt
	if (y == 0) {
		return a;
	} else if (y == 1) {
		return a * x;
	} else {
		return power(a * x,  x,  y - 1);
	}
}

// convert a string containing a decimal integer to an int
static int parseDecimalString(char number[], int lastIndex) {
	// Limitations: OOB input (int cannot store numbers greater than 32,767)
	//				bad stuff happens if input isn't char[] of 48...57
	int decimalStringAsInt = 0;
	
	// string[lastIndex] should == 0
	if (number[lastIndex] != 0) {
		printf("ERROR in parseDecimalString(): literal at last index of string\
		should be zero for well-formed strings.\n");
		return -1;
	}
	
	// meaning that we have lastIndex significant digits
	// therefore most significant digit represents 10^(lastIndex-1)s
	int highestPowerOfTen = lastIndex - 1;
	
	// O(n^2) on lastIndex (I think...?)
	for (int i = 0; i < lastIndex; i++) {
		decimalStringAsInt += power(number[i] - '0', 10, highestPowerOfTen - i);
	}
	
	return decimalStringAsInt;
}

// Print N terms of Fibonacci sequence
static void printFib(int n) {
	unsigned long long n0 = 1;
	unsigned long long n1 = 1;
	printf("1\n");
	if (n > 1) {
		// do it as a flip-flop for loop, the theory being that only one var
		// needs to change each iteration
		for (int i = 2; i <= n; i++) {
			if (i % 2) {
				printf("%llu\n", n1);
				n0 += n1;
			} else {
				printf("%llu\n", n0);
				n1 += n0;
			}
		}
	}
}
