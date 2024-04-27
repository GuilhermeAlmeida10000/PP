// Exemplo 2: Criação de threads e identificação
// Compilar com: gcc ex02_criacao_threads.c -fopenmp -o ex02_criacao_threads -Wall
// Executar por linha de comando: ./ex02_criacao_threads

#include <omp.h>
#include <stdio.h>

int main()
{
	// Região sequencial: apenas thread mestre executa

	// Obtém id da thread, no. de threads executando região sequencial e
	// no. de threads que executarão região paralela ao mesmo tempo
	printf("Região sequencial: thread_id = %d\t nthreads = %d\t max_threads = %d\n",
			 omp_get_thread_num(), omp_get_num_threads(), omp_get_max_threads());

	// Construtor parallel
	#pragma omp parallel // Início da região paralela: todas as threads executam
	{
		// Obtém id da thread, no. de threads executando região paralela
		printf("Região paralela  : thread_id = %d\t nthreads = %d\n",
				 omp_get_thread_num(), omp_get_num_threads());
		
	} // Fim da região paralela: barreira implícita

	// Região sequencial: apenas thread mestre executa

	// Obtém id da thread, no. de threads executando região sequencial
	printf("Região sequencial: thread_id = %d\t nthreads = %d\n",
			 omp_get_thread_num(), omp_get_num_threads());

	return 0;
}
