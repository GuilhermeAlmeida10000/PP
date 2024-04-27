// Exemplo 9: Cláusula nowait
// Compilar com: g++ ex09_clausula_nowait.cpp -fopenmp -o ex09_clausula_nowait -Wall -lm
// Executar por linha de comando: ./ex09_clausula_nowait

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	int n = 1000000; 
	int m = 100000;
	
	// Aloca vetores
	double *a = new double[n];
	double *b = new double[n];
	double *y = new double[m];

	// Inicializa vetores a e x
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = ((double)rand())/RAND_MAX;
	}

	// -------------------------------------------------------------------------
	#pragma omp parallel // Construtor parallel: início da região paralela
	{
		#pragma omp for // Construtor for: distribui iterações do laço entre threads
		for (int i = 1; i < n; i++)
		{
			b[i] = (a[i] + a[i-1]) / 2.0;

		} // Fim do construtor for: barreira implícita

		#pragma omp for nowait // Construtor for: distribui iterações do laço entre threads
		for (int j = 0; j < m; j++)
		{
			y[j] = sqrt(b[j]);

		} // Fim do construtor for: barreira implícita REMOVIDA

	} // Fim da região paralela: barreira implícita

	// -------------------------------------------------------------------------
	// Libera vetores
	delete[] a;
	delete[] b;
	delete[] y;

	return 0;
}
