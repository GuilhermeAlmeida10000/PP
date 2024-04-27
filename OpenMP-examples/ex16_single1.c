// Exemplo 16: Região paralela com single
// Compilar com: gcc ex16_single1.c -fopenmp -o ex16_single1 -Wall
// Executar por linha de comando: ./ex16_single1

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("----- Região sequencial inicial -----\n");

	// Construtor parallel
	#pragma omp parallel // Início da região paralela: todas as threads executam
	{
		// Obtém id da thread
		printf("Antes do single:  thread_id = %d\n", omp_get_thread_num());

		// Construtor single: apenas uma thread (qualquer) executa
		#pragma omp single // Testar sem e com cláusula nowait
		{
			// Obtém id da thread
			printf("DENTRO do single: thread_id = %d\n", omp_get_thread_num());
		} // Fim do construtor single: barreira implícita (removida ?)

		// Obtém id da thread
		printf("Depois do single: thread_id = %d\n", omp_get_thread_num());

	} // Fim da região paralela: barreira implícita

	printf("----- Região sequencial final -----\n");
	return 0;
}
