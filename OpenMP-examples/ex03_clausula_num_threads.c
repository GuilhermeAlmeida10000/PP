// Exemplo 3: Cláusula num_threads
// Compilar com: gcc ex03_clausula_num_threads.c -fopenmp -o ex03_clausula_num_threads -Wall
// Executar por linha de comando: ./ex03_clausula_num_threads

#include <omp.h>
#include <stdio.h>

int main()
{
	printf("Região sequencial: nthreads = %d\t\t max_threads = %d\n",
			 omp_get_num_threads(), omp_get_max_threads());

	// Construtor parallel
	#pragma omp parallel num_threads(2) // Início da região paralela com apenas 2 threads
	{
		printf("Região paralela  : thread_id = %d\t nthreads = %d\n",
				 omp_get_thread_num(), omp_get_num_threads());
		
	} // Fim da região paralela: barreira implícita

	printf("Região sequencial: nthreads = %d\t\t max_threads = %d\n", 
			 omp_get_num_threads(), omp_get_max_threads());

	return 0;
}
