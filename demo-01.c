#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, 
         char** argv) {
	int a,b;

	b = 6;
	a = 4 + b;
	fork();
	b = 4 - a;
	printf("a: %d b: %d\n",a, b);
}
