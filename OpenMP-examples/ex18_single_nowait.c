// Exemplo 18: Região paralela com single com cláusula nowait
// Compilar com: gcc ex18_single_nowait.c -fopenmp -o ex18_single_nowait -Wall
// Executar por linha de comando: ./ex18_single_nowait

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	printf("----- Região sequencial inicial -----\n");
	srand(time(0));

	// Construtor parallel
	#pragma omp parallel // Início da região paralela: todas as threads executam
	{
		printf("Início da região paralela:\t thread_id = %d\n", omp_get_thread_num());

		// Nem todas as threads entram no if
		if ((rand() % 100) < 10)
		{
			printf("Dentro do if:\t\t\t thread_id = %d\n", omp_get_thread_num());
			
			// Testar sem e com nowait
			#pragma omp single // Apenas uma thread (qualquer) executa (COM barreira implícita)
			//#pragma omp single nowait // Apenas uma thread (qualquer) executa (barreira implícita removida)
			{
				printf("DENTRO do single:\t thread_id = %d\n", omp_get_thread_num());
			} // Fim do construtor single: barreira implícita (removida ?)
		}
		printf("Fim da região paralela:\t\t thread_id = %d\n", omp_get_thread_num());

	} // Fim da região paralela: barreira implícita

	printf("----- Região sequencial final -----\n");
	return 0;
}
