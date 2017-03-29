/**
---- findprime2b.c ----
1- Programa que muestra como contar la cantidad de numeros primos que se 
   encuentra en un rango de numeros, desde LOW hasta HIGH.
2- En esta version se usan dos procesos para dividir el trabajo de contar 
   cuantos primos hay en el rango LOW hasta HIGH.
3- En esta version se obliga a que el proceso padre espere por la terminacion de
   la ejecucion de su hijo.
4- En esta version el hijo le envia de vuelta la cantidad de primos que encontro
   y el padre suma los dos valores y se obtiene el total de primos en el rango
   LOW - HIGH

El metodo usado para determinar si un numero N es primo es buscar un
numero en el rango 2..N/2 que divida exactamente a N. De existir dicho numero 
entonces N no es primo, de otra forma N es primo.

Autor: John Sanabria
Fecha: Marzo 13, 2017

**/

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define LOW 500000
#define HIGH 600000

// Funcion usada para determinar si un numero 'p' es primo o no
// Esta funcion retorna '1' si 'p' es primo, de otra forma '0'
int isprime(int);
 
int main(int argc, char** argv) {
	int i, count;
	int length = HIGH - LOW;
	int pid;
	int fd[2];
	count = 0;
	
	pipe(fd);
	if ((pid = fork())) {
		int counth;
		close(fd[1]);
		for ( i = LOW; i < (LOW + length/2); i++)
			if (isprime(i))
				count++;
		printf("[%d] conto %d\n",getpid(),count);
		printf("Esperando por %d\n",pid);
		read(fd[0],&counth,sizeof(counth));
		printf("%d + %d = %d\n", counth, count, counth + count);
	} else {
		close(fd[0]);
		for ( i = (LOW + length/2); i <= HIGH; i++)
			if (isprime(i))
				count++;
		printf("[%d] conto %d\n",getpid(),count);
		write(fd[1],&count,sizeof(count));
	}
}

int isprime(int p) {
	int i,tope;

	// Si es un numero entre 2 y 5, entonces es primo
	if (p >= 2 && p <= 5)
		return 1;
	// Determinamos cual es la mitad de 'p'
	tope = (int)(p/2);
	// Recorremos los numeros desde 2 hasta p/2
	for (i = 2; i <= tope; i++) 
		if (p%i == 0) // si 'p' es divido exactamente por i, no es primo
			break;
	// si 'i' toma el valor 'tope+1' entonces quiere decir que no se 
	// encontro un numero que dividiera exactamente a 'p' luego 'p' es primo
	if (i == tope + 1)
		return 1;
	return 0;
}
