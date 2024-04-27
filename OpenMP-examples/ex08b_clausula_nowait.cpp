// Exemplo 8b: Cláusula nowait
// Compilar com: g++ ex08b_clausula_nowait.cpp -fopenmp -o ex08b_clausula_nowait -Wall -lm
// Executar por linha de comando: ./ex08b_clausula_nowait

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
	double *x = new double[m];
	double *y = new double[m];

	// Inicializa vetores a e x
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = ((double)rand())/RAND_MAX;
	}
	for (int j = 0; j < m; j++)
	{
		x[j] = ((double)rand())/RAND_MAX;
	}

	// -------------------------------------------------------------------------

	#pragma omp parallel // Construtor parallel: início da única região paralela
	{
		#pragma omp for nowait // Construtor for: distribui iterações do laço entre threads
		for (int i = 1; i < n; i++)
		{
			b[i] = (a[i] + a[i-1]) / 2.0;

		} // Fim do construtor for: barreira implícita REMOVIDA

		#pragma omp for nowait
		for (int j = 0; j < m; j++) // Construtor for: distribui iterações do laço entre threads
		{
			y[j] = sqrt(x[j]);

		} // Fim do construtor for: barreira implícita REMOVIDA

	} // Fim da região paralela: barreira implícita

	// -------------------------------------------------------------------------
	// Libera vetores
	delete[] a;
	delete[] b;
	delete[] x;
	delete[] y;

	return 0;
}
