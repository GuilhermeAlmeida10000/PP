// Exemplo 15a: Merge sort recursivo
// Compilar com: g++ ex15a_mergesort.cpp -fopenmp -o ex15a_mergesort -Wall
// Executar por linha de comando: ./ex15a_mergesort

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------------------------------------------------------------------------
void intercala(int *a, int i, int m, int f, int *tmp)
{
	int p = i;
	int q = m+1;
	int t = i;

	while ((p <= m) && (q <= f))
	{
		if (a[p] < a[q])
		{
			tmp[t] = a[p];
			t++;
			p++;
		} else
		{
			tmp[t] = a[q];
			t++; 
			q++;
		}
	}
	while (p <= m)
	{
		tmp[t] = a[p];
		t++;
		p++;
	}
	while (q <= f)
	{
		tmp[t] = a[q];
		t++; 
		q++;
	}

	memcpy(&(a[i]), &(tmp[i]), (f-i+1)*sizeof(int));
}
// -------------------------------------------------------------------------
void merge_sort_paralelo(int *a, int i, int f, int *tmp)
{
	if (i < f) // Se não chegou na base da recursão
	{
		int m = (i+f)/2;

		// Ordena metades esquerda e direita do vetor, em paralelo
		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section
			merge_sort_paralelo(a, i, m, tmp);

			#pragma omp section
			merge_sort_paralelo(a, m+1, f, tmp);
		} // Barreira implícita

		intercala(a, i, m, f, tmp);
	}
}
// -------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("O programa foi executado com parâmetros incorretos.\n");
		printf("Uso: ./ex15a_mergesort <número_de_elementos>\n");
		exit(1);
	}

	int n = atoi(argv[1]); // Testar valores: n = 10.000, n = 100.000
	
	// Aloca vetores
	int *a   = new int[n];
	int *tmp = new int[n];

	// Inicializa vetor a
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = (int)(rand()/RAND_MAX);
	}
	// ----------------------------------------------------------------------
	// Ordena vetor a em paralelo

	double tini = omp_get_wtime();

	omp_set_nested(1); // Habilita paralelismo aninhado

	merge_sort_paralelo(a, 0, n-1, tmp);

	double tfin = omp_get_wtime();
	double tpar = tfin - tini;
	// ----------------------------------------------------------------------
	// Checa resultado
	int i = 0;
	bool correto = true;
	while (i < (n-1) && correto)
	{
		if (a[i] > a[i+1])
			correto = false;
		i++;
	}
	printf("Merge sort paralelo   \t tempo: %f s\t correto: %s\n", tpar, (correto ? "SIM" : "NÃO"));
	// ----------------------------------------------------------------------
	// Libera vetores
	delete[] a;
	delete[] tmp;

	return 0;
}
