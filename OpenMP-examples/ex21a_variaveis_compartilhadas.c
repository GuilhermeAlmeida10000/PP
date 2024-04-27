// Exemplo 21a: Variáveis compartilhadas
// Compilar com: gcc ex21a_variaveis_compartilhadas.c -fopenmp -o ex21a_variaveis_compartilhadas -Wall
// Executar por linha de comando: ./ex21a_variaveis_compartilhadas

#include <omp.h>
#include <stdio.h>

int main()
{
	int n = 8, a[n]; // Por default: compartilhadas

	#pragma omp parallel for // Início da região paralela
	for (int i = 0; i < n; i++) // Por defaut: i privado
	{
		a[i] = omp_get_thread_num();
	} // Fim da região paralela: barreira implícita

	printf("Região sequencial:\n");
	for (int i = 0; i < n; i++)
	{
		printf("a[%d]=%d\n", i, a[i]);
	}

	return 0;
}
