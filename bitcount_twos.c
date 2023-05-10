#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int x = atoi(argv[1]);
	
	// moved commentary below
	
	int bitcount = 0;

	while (x != 0) {
		x &= (x - 1);
		bitcount++;
	}
	printf("%i\n", bitcount);
	return 0;
}	

	// in two's complement, we express a negative number
	// by subtracting by 2^N-1 if the top (most sig) bit 
	// is set. 
	//
	// then, we can turn a postive number into a negative
	// two's complement number of equal magnitude by:
	//
	// 1. Invert every bit
	// 2. Add one, ignoring overflow
	//
	// Now, we consider x &= (x - 1).
	// Expanding just the expression:
	// 
	// x & (x - 1)
	//
	// Just consider postive numbers e.g. x = 9
	//
	//          8 4 2 1
	// then x = 1 0 0 1
	//  x - 1 = 1 0 0 0
	//      & = 1 0 0 0
	//
	//      x = 1 0 0 0
	//  x - 1 = 0 1 1 1
	//      & = 0 0 0 0
	//
	// i.e. each time you do this you'll delete the rightmost set bit, 
	// eventually reaching zero
	//
	// And it's clear that there's nothing special about positive numbers here
	// 
	// just replace the 8 column above with a -8 column, as though it's 4-bit
	// two's complement - the mechanics are the same and we go 
	//
	//     x = -7
	// x - 1 = -8
	//     & = -8
	//
	//     x = -8
	// x - 1 =  7
	//     & =  0
	// 
	// Why is this true for "two's complement". What about if we had a diff
	// format? This would come into play as we cross zero, right?
	//
	// In this case, three bit int + sign bit:
	//
	//         s 4 2 1
	//     x = 0 0 0 0
	// x - 1 = 1 0 0 1
	//     $ = 0 0 0 0
	//
	//     (this would work in one's complement too, actually!)
	//
	// No, that's fine, what about the underflow case?
	//
	//
	//         s 4 2 1
	//     x = 1 1 1 1 (-7)
	// x - 1 = 0 0 0 0 (+0) // not totally sure how overflow would be handled
	//     & = 0 0 0 0      // here but regardless of whether it's +/-0 or +7
	//                      // it's not fitting the pattern
	//
	// Aha! And maybe something similar applies to one's complement?
	//
	// 
	//     x = 1 0 0 0 (-7)
	// x - 1 = 0 1 1 1 (7)
	//     & = 0 0 0 0 
	//
	// Nah that worked, what about a normal negative number w/o underflow?
	//
	//     x = 1 0 1 0 (-5)
	// x - 1 = 1 0 0 1 (-6)
	//     & = 1 0 0 1
	//
	// That worked OK actually, maybe it works if you forbit -0?
	//
	//     x = 1 1 1 1 (-0)
	// x - 1 = 1 1 1 0 (-1)
	//     & = 1 1 1 0
	//
	// Yeah it doesn't work for -0. It's possible it works for one's complement
	// if -0 is verboten. 
	//
	// anyway I digress. x &= (x - 1) strips the lowest zero in all cases on 
	// two's complement because subtracting one will either flip the one bit
	// or flip every bit up to and including the next one bit, which means that
	// when you AND it with the original number all of those bits will be set
	// to zero (and the rest will stay the same), in effect deleting the lowest
	// set bit. We can use this to write a faster bitcount:
