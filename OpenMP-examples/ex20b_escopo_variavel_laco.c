// Exemplo 20b: Escopo default da variável de controle de laço for
// Compilar com: gcc ex20b_escopo_variavel_laco.c -fopenmp -o ex20b_escopo_variavel_laco -Wall
// Executar por linha de comando: ./ex20b_escopo_variavel_laco

#include <omp.h>
#include <stdio.h>

int main()
{
	int i = -1, n = 8; // Por defaut: compartilhadas

	printf("Região sequencial ini: i=%d\n\n", i);

	#pragma omp parallel for num_threads(4) // Início da região paralela
	for (i = 0 ; i < n ; i++) // Por defaut: i privado
	{
		printf("Região paralela: thread_id=%d\t i=%d\n",
				 omp_get_thread_num(), i);
	}  // Fim da região paralela: barreira implícita

	printf("\nRegião sequencial fim: i=%d\n", i);

	return 0;
}
