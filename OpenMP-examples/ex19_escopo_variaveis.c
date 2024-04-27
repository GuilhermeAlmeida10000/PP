// Exemplo 19: Escopo default das variáveis
// Compilar com: gcc ex19_escopo_variaveis.c -fopenmp -o ex19_escopo_variaveis -Wall
// Executar por linha de comando: ./ex19_escopo_variaveis

#include <omp.h>
#include <stdio.h>

void funcao()
{
	int x = 0;
	for (int i = 0; i < 1000000; i++)
	{
		x = (x + i) / 2;
	}
	return;
}

int main()
{
	int a = -1; // Por default: compartilhada

	printf("Região sequencial ini: a=%d\n\n", a);

	#pragma omp parallel num_threads(4) // Início da região paralela
	{
		int b = -2; // Por default: privada

		printf("Região paralela ini: thread_id=%d\t a=%d\t b=%d\n",
				 omp_get_thread_num(), a, b);

		a = omp_get_thread_num();
		b = omp_get_thread_num();

		funcao(); // Consome tempo

		printf("Região paralela fim: thread_id=%d\t a=%d\t b=%d\n",
				 omp_get_thread_num(), a, b);

	} // Fim da região paralela: barreira implícita

	printf("\nRegião sequencial fim: a=%d\n", a);

	return 0;
}
