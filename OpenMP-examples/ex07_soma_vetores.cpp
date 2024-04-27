// Exemplo 7: Soma de 2 vetores
// Compilar com: g++ ex07_soma_vetores.cpp -fopenmp -o ex07_soma_vetores -Wall
// Executar por linha de comando: ./ex07_soma_vetores <número_de_elementos>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("O programa foi executado com parâmetros incorretos.\n");
		printf("Uso: ./ex07_soma_vetores <número_de_elementos>\n");
		exit(1);
	}

	// Testar valores: n = 50000000, para medir speedup
	int n = atoi(argv[1]); 
	
	// Aloca vetores
	double *a = new double[n];
	double *b = new double[n];
	double *c_seq = new double[n];
	double *c_par = new double[n];

	// Inicializa vetores a e b
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = ((double)rand())/RAND_MAX;
		b[i] = ((double)rand())/RAND_MAX;
	}

	// -------------------------------------------------------------------------
	// Soma vetores a e b sequencialmente: obtém resultado em c_seq
	double tini = omp_get_wtime();

	for (int i = 0; i < n; i++)
	{
		c_seq[i] = a[i] + b[i];
	}

	double tfin = omp_get_wtime();
	double tseq = tfin - tini;
	printf("Soma vetores sequencial \t tempo: %f s\n", tseq);

	// -------------------------------------------------------------------------
	// Soma vetores a e b em paralelo: obtém resultado em c_par
	tini = omp_get_wtime();

	// Construtor combinado parallel for
	#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		c_par[i] = a[i] + b[i];
	} // Fim da região paralela: barreira implícita

	tfin = omp_get_wtime();
	double tpar = tfin - tini;

	// -------------------------------------------------------------------------
	// Compara resultados c_seq e c_par
	int i = 0;
	bool correto = true;
	while (i < n && correto)
	{
		if (c_seq[i] != c_par[i])
			correto = false;
		i++;
	}

	printf("Soma vetores paralelo   \t tempo: %f s\t speedup: %.2f \t correto: %s\n", tpar, (tseq/tpar), (correto ? "SIM" : "NÃO"));

	// -------------------------------------------------------------------------
	// Libera vetores
	delete[] a;
	delete[] b;
	delete[] c_seq;
	delete[] c_par;

	return 0;
}
