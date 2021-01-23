#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Initialized
int sizeX3 = 32;
int x3[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 
				18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}; // 128 Bytes

// Not initialized
int y3[4000]; // 16 KB

void func3() {
	for(int i = 0; i < sizeX3; ++i){
		x3[i] = x3[i] * 2;
	}
}