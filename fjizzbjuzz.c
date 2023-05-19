#include <stdio.h>

void fizzbuzz(int n);
void f2zzb2zz(int n);

int main() {
	f2zzb2zz(100);
}

void fizzbuzz(int n) {
	int i, p;
	for (i = 0; i < n; i++) {
		p = 0;
		if (i % 3 == 0)
			p += printf("Fizz");
		if (i % 5 == 0)
			p += printf("Buzz");
		if (!p)
			printf("%i", i);
		printf("\n");
	}
}

void f2zzb2zz(int n) {
	int i;
	for(i = 0; i < n; i++) {
		switch (((i % 3) == 0) | ((i % 5) == 0) * 2) {
			case 0:
				printf("%i", i);
				break;
			case 1:
				printf("Fizz");
				break;
			case 2:
				printf("Buzz");
				break;
			case 3:
				printf("FizzBuzz");
		}
		printf("\n");
	}
}
