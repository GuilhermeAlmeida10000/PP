// Exemplo 21b: Variáveis compartilhadas
// Compilar com: gcc ex21b_variaveis_compartilhadas.c -fopenmp -o ex21b_variaveis_compartilhadas -Wall
// Executar por linha de comando: ./ex21b_variaveis_compartilhadas

#include <omp.h>
#include <stdio.h>

int main()
{
	int n = 4, a[n], b[n]; // Por default: compartilhadas

	#pragma omp parallel num_threads(4) // Início da região paralela
	{
		#pragma omp for
		for (int i = 0; i < n; i++) // Por defaut: i privado
		{
			a[i] = omp_get_thread_num();
		} // Barreira implícita

		#pragma omp for nowait
		for (int i = 0; i < n; i++) // Por defaut: i privado
		{
			b[i] = a[n - i - 1];
		} // Barreira implícita removida
	} // Fim da região paralela: barreira implícita

	printf("Região sequencial:\n");
	for (int i = 0; i < n; i++)
	{
		printf("a[%d]=%d\t b[%d]=%d\n", i, a[i], i, b[i]);
	}

	return 0;
}
