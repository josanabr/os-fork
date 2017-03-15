/**
---- findprime2.c ----
1- Programa que muestra como contar la cantidad de numeros primos que se 
   encuentra en un rango de numeros, desde LOW hasta HIGH.
2- En esta version se usan dos procesos para dividir el trabajo de contar 
   cuantos primos hay en el rango LOW hasta HIGH.
3- En esta version se obliga a que el proceso padre espere por la terminacion de
   la ejecucion de su hijo.

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

#define LOW 500000
#define HIGH 600000

// Funcion usada para determinar si un numero 'p' es primo o no
// Esta funcion retorna '1' si 'p' es primo, de otra forma '0'
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

int main(int argc, char** argv) {
	int i, count;
	int length = HIGH - LOW;
	int pid;
	count = 0;
	
	if ((pid = fork())) {
		for ( i = LOW; i < (LOW + length/2); i++)
			if (isprime(i))
				count++;
		printf("Esperando por %d\n",pid);
		waitpid(pid,NULL,WUNTRACED);
	} else {
		for ( i = (LOW + length/2); i <= HIGH; i++)
			if (isprime(i))
				count++;
		
	}
	printf("[%d]: %d\n", getpid(),count);
}
