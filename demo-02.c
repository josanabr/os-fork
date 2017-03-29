#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, 
         char** argv) {
	int a,b;
	pid_t pid;

	b = 6;
	a = 4 + b;
	pid = fork();
	if (pid == 0) { // es el hijo
		b = 4 - a;
		printf("PID: %d\n",getpid());
	} else { // es el padre
		printf("a: %d b: %d\n",a, b);
		printf("PID: %d mi hijo: %d\n",getpid(), pid);
	}
}
