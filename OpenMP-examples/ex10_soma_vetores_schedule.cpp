// Exemplo 10: Soma de 2 vetores e comparação de schedules
// Compilar com: g++ ex10_soma_vetores_schedule.cpp -fopenmp -o ex10_soma_vetores_schedule -Wall
// Executar por linha de comando: ./ex10_soma_vetores_schedule <número_de_elementos>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	if(argc != 2) {
		printf("O programa foi executado com parâmetros incorretos.\n");
		printf("Uso: ./ex10_soma_vetores_schedule <número_de_elementos>\n");
		exit(1);
	}

	// Testar valores:
	// n = 20, para observar relação entre id da thread e iteração i do laço
	// n = 100 milhões, para medir tempo de execução (sem printf)
	int n = atoi(argv[1]); 
	
	// Aloca vetores
	double *a = new double[n];
	double *b = new double[n];
	double *c = new double[n];

	// Inicializa vetores a e b
	srand(time(0));
	for (int i = 0; i < n; i++)
	{
		a[i] = ((double)rand())/RAND_MAX;
		b[i] = ((double)rand())/RAND_MAX;
	}

	double tini = omp_get_wtime();
	// -------------------------------------------------------------------------
	// Soma vetores a e b em paralelo: obtém resultado em c_par
	// Construtor combinado parallel for
	#pragma omp parallel for num_threads(4) // Testar cláusula schedule(static), schedule(static,1), schedule(static,2), schedule(dynamic,1), schedule(dynamic,2)
	for (int i = 0; i < n; i++)
	{
		c[i] = a[i] + b[i];

		// Observar relação entre id da thread e iteração i
		printf("thread_id = %d\t i = %d\n", omp_get_thread_num(), i);

	} // Fim da região paralela: barreira implícita

	double tfin = omp_get_wtime();
	double tpar = tfin - tini;

	printf("Soma vetores paralelo \t tempo: %f s\n", tpar);

	// -------------------------------------------------------------------------
	// Libera vetores
	delete[] a;
	delete[] b;
	delete[] c;

	return 0;
}
