// Exemplo 6: Região paralela
// Compilar com: gcc ex06_regiao_paralela2.c -fopenmp -o ex06_regiao_paralela2 -Wall
// Executar por linha de comando: ./ex06_regiao_paralela2
// Acompanhar execução com comando htop (no linux)

#include <omp.h>
#include <stdio.h>

void funcao()
{
	int a = 0;
	for (int i = 0; i < 2000000000; i++)
	{
		a = (a + i) / 2;
	}
}

int main()
{
	// Construtor parallel
	#pragma omp parallel // Início da região paralela: todas as threads executam
	{
		printf("Início da thread %d\n", omp_get_thread_num());

		// Todas as threads chamam a função
		funcao(); // Consome tempo

		printf("Fim da thread %d\n", omp_get_thread_num());

	} // Fim da região paralela: barreira implícita

	return 0;
}
