#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

// Initialized
int sizeX = 32;
int x[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 
				18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}; // 128 Bytes

// Not initialized
int y[4000]; // 16 KB
int z;

// Functions and the variables of the other modules
void func2();
void func3();
extern int sizeX2;
extern int x2[];
extern int y2[];
extern int sizeX3;
extern int x3[];
extern int y3[];


void func1() {
	for(int i = 0; i < sizeX; ++i){
		x[i] = x[i] * 2;
	}
}

// Recursive function
int rec_func(int i){
	printf("Address of i\t= 0x%016lx\n", (unsigned long int) &i);
	int a[12500] = {0}; // 50 KB

	if (i > 4){

		return i;
	}
	return rec_func(++i);
}


int main(int argc, char const *argv[]) {
	int step = 0;
	char ch = 'n';
	int* a;
	int* b;
	int* c;
	int* d;
	struct stat sb;
	char* mmappedData;
	while (1){
		if (ch == 'n'){
			++step;
			if (step == 1){
				printf("\n%s\n------\n", "Step 1");
	
				// Step 1
				printf("Address of sizeX\t= 0x%016lx\n", (unsigned long int) &sizeX);
				printf("Address of x\t\t= 0x%016lx\n", (unsigned long int) &x);
				printf("Address of y\t\t= 0x%016lx\n", (unsigned long int) &y);
				printf("Address of z\t\t= 0x%016lx\n", (unsigned long int) &z);
				printf("Address of sizeX2\t= 0x%016lx\n", (unsigned long int) &sizeX2);
				printf("Address of x2\t\t= 0x%016lx\n", (unsigned long int) &x2);
				printf("Address of y2\t\t= 0x%016lx\n", (unsigned long int) &y2);
				printf("Address of sizeX3\t= 0x%016lx\n", (unsigned long int) &sizeX3);
				printf("Address of x3\t\t= 0x%016lx\n", (unsigned long int) &x3);
				printf("Address of y3\t\t= 0x%016lx\n", (unsigned long int) &y3);
				
				printf("Address of main\t\t= 0x%016lx\n", (unsigned long int) &main);
				printf("Address of rec_func\t= 0x%016lx\n", (unsigned long int) &rec_func);
				printf("Address of func1\t= 0x%016lx\n", (unsigned long int) &func1);
				printf("Address of func2\t= 0x%016lx\n", (unsigned long int) &func2);
				printf("Address of func3\t= 0x%016lx\n", (unsigned long int) &func3);
				printf("Address of printf\t= 0x%016lx\n", (unsigned long int) &printf);

				func1();
				func2();
				func3();
			}
			else if (step == 2) {
				printf("\n%s\n------\n", "Step 2");

				// Step 2
				a = malloc(500000); // 0.5 MB
				b = malloc(500000); // 0.5 MB
				c = malloc(500000); // 0.5 MB
				d = malloc(500000); // 0.5 MB
				printf("Address of a\t= 0x%016lx\n", (void *) a);
				printf("Address of b\t= 0x%016lx\n", (void *) b);
				printf("Address of c\t= 0x%016lx\n", (void *) c);
				printf("Address of d\t= 0x%016lx\n", (void *) d);
			}
			else if (step == 3){
				printf("\n%s\n------\n", "Step 3");

				// Step 3
				rec_func(1);
			}
			else if (step == 4){
				printf("\n%s\n------\n", "Step 4");

				// Step 4
				int fd = open("./file", O_RDWR | O_CREAT, 0777);
				char buf[] = "munibemre\n";
				for(int i = 0; i < 110000; ++i)
					write(fd, buf, 10);

				fstat(fd, &sb);
			    mmappedData = mmap(NULL, sb.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
				printf("Address of mmapedData\t= 0x%016lx\n", mmappedData);

			}
			else if (step == 5){
				printf("\n%s\n------\n", "Step 5");

				// Step 5
				char buf[] = "\nsevilgen\n";
				char c;
				for(int i = 0; i < 100; ++i)
					mmappedData[i] = buf[i%10];
				for(int i = 0; i < 1000; ++i)
					c = mmappedData[i];
			}
			else if (step == 6){
				printf("\n%s\n------\n", "Step 6");
				
				// Step 6				
				unsigned long int address = &main;
				printf("Address of main\t= 0x%016lx\n", address);

				unsigned long int offset = address % 0xFA0;
				printf("Offset\t\t= 0x%016lx\n", offset);

				address = address - offset;
				printf("Page adress\t= 0x%016lx\n", address);

				printf("\nContent of the page: \n");
				unsigned char* val;
				for (unsigned long int i = 0; i < 0xFA0; ++i) {
					val = address + i;
					printf("0x%016lx:\t %02x\n", val, val[0]);
				}
			}
			else {
				break;
			}
		}
		if (step < 6){
			printf("\n%s: ", "Enter n to get the output of the next step");
			ch = getchar();
			if (ch != 'n')
				ch = getchar();
			else
				getchar();
			
		}
	}
	free(a);
	free(b);
	free(c);
	free(d);
	remove("./file");
	munmap(mmappedData, sb.st_size);
	return 0;
}