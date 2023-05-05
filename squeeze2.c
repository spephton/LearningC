#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("invalid number of arguments (require 2)");
		return 1;
	}
	squeeze(argv[1], argv[2]);
	printf("%s, %s\n", argv[1], argv[2]);
	return 0;
}

void squeeze(char s1[], char s2[]) {
	// lazy here, should put s2 in a diff data structure
	int i, j, inS2;
	for(i = j = 0; s1[i] != '\0'; i++) {
		inS2 = 0;
		for(int k = 0; s2[k] != '\0'; k++) {
			if (s1[i] == s2[k]){
				inS2 = 1;
				break;
			}
		}
		if (!inS2) {
			s1[j++] = s1[i];
		}
	}
	s1[j] = '\0';
}
