// Exemplo 5: Região paralela
// Compilar com: gcc ex05_regiao_paralela1.c -fopenmp -o ex05_regiao_paralela1 -Wall
// Executar por linha de comando: ./ex05_regiao_paralela1

#include <omp.h>
#include <stdio.h>

int main()
{
	// Construtor parallel
	#pragma omp parallel // Início da região paralela: todas as threads executam
	{
		// Todas as threads executam todas as iterações do laço
		for (int i = 0; i < 5; i++)
		{
			printf("thread_id = %d\t i = %d\n", omp_get_thread_num(), i);
		}

	} // Fim da região paralela: barreira implícita

	return 0;
}
