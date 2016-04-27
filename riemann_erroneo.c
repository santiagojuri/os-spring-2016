/**
* FILE: riemann_erroneo.c
* DESCRIPTION:
* 	Implementacion de la suma de Riemann para calcular el area bajo la
*	curva. Este codigo esta errado, usted debe hacer los ajustes para que
*	funcionen correctamente.
* AUTHOR: John Sanabria - john.sanabria@correounivalle.edu.co
* LAST REVISED: 14/04/16
* REFERENCES: http://mathinsight.org/calculating_area_under_curve_riemann_sums
******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define MAXRECT 1000000000
#define MAXTHREAD 8
#define BASE 0.0
#define LIMIT 1.0

double result[MAXTHREAD];
double length = LIMIT - BASE;
double numRectxThread = (double)(MAXRECT/MAXTHREAD);
double base_length = 0;
/* aqui defino el semaforo*/
double sumFinal = 0;


double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
	long id = (long) arg;
	double lowlimit = id*base_length*numRectxThread;
	double sumTotal = 0;

	for (int i = 0; i < numRectxThread; i++) {
		/*sem wait*/
		sumTotal += function(lowlimit + i*base_length) * base_length;
		/*sem signal*/
	}

	result[id]=sumTotal;
	return NULL;
}

int main(int argc, char** argv) {
	pthread_t threads[MAXTHREAD];
	long taskids[MAXTHREAD];

	base_length = length/MAXRECT;
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);
	/*------ crear aqui el semaforo*/
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
		pthread_create(&threads[i], NULL, calcular, (void*)taskids[i]);
	}

	for (int i = 0; i < MAXTHREAD; ++i)
  	{
  	  	pthread_join(threads[i], NULL);
  	}

	for (int i = 0; i < MAXTHREAD; ++i)
  	{
  	  	sumFinal = sumFinal + result[i];
  	}
	printf("Suma total %lf\n",sumFinal);
	pthread_exit(NULL);
}
