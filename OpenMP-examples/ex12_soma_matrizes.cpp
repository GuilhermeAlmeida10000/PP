// Exemplo 12: Soma de 2 matrizes e uso de collapse
// Compilar com: g++ ex12_soma_matrizes.cpp -fopenmp -o ex12_soma_matrizes -Wall
// Executar por linha de comando: ./ex12_soma_matrizes <n_linhas> <n_colunas>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	if(argc != 3) {
		printf("O programa foi executado com parâmetros incorretos.\n");
		printf("Uso: ./ex12_soma_matrizes <n_linhas> <n_colunas>\n");
		exit(1);
	}

	// Testar valores: n = 8 e m = 100 mil, para medir tempo de execução
	int n = atoi(argv[1]); // Número de linhas das matrizes
	int m = atoi(argv[2]); // Número de colunas das matrizes
	
	// Aloca matrizes
	double **a = new double*[n];
	for (int i = 0; i < n; i++)
		a[i] = new double[m];
	double **b = new double*[n];
	for (int i = 0; i < n; i++)
		b[i] = new double[m];
	double **c = new double*[n];
	for (int i = 0; i < n; i++)
		c[i] = new double[m];
	// Inicializa matrizes a e b
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			a[i][j] = ((double)rand())/RAND_MAX;
			b[i][j] = ((double)rand())/RAND_MAX;
		}
	}

	// -------------------------------------------------------------------------
	// Construtor combinado parallel for

	#pragma omp parallel for collapse (2) // Paraleliza iterações combinadas dos dois laços
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	} // Fim da região paralela: barreira implícita

	// -------------------------------------------------------------------------
	// Libera matrizes
	for (int i = 0; i < n; i++)
	{
		delete[] a[i];
		delete[] b[i];
		delete[] c[i];
	}
	delete[] a;
	delete[] b;
	delete[] c;

	return 0;
}
