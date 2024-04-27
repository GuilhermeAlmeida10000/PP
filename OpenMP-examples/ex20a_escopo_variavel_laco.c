// Exemplo 20a: Escopo default da variável de controle de laço for
// Compilar com: gcc ex20a_escopo_variavel_laco.c -fopenmp -o ex20a_escopo_variavel_laco -Wall
// Executar por linha de comando: ./ex20a_escopo_variavel_laco

#include <omp.h>
#include <stdio.h>

int main()
{
	int n = 8; // Por defaut: compartilhada

	#pragma omp parallel for num_threads(4) // Início da região paralela
	for (int i = 0 ; i < n ; i++) // Por defaut: i privado
	{
		printf("Região paralela: thread_id=%d\t i=%d\n",
				 omp_get_thread_num(), i);
	}  // Fim da região paralela: barreira implícita

	return 0;
}
