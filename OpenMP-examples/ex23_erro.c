// Exemplo 23: O que está errado? Como corrigir?
// Compilar com: gcc ex23_erro.c -fopenmp -o ex23_erro -Wall
// Executar por linha de comando: ./ex23_erro

#include <omp.h>
#include <stdio.h>

int main()
{
	int i, j, n = 4, a[n][n], b[n][n]; // Por default: compartilhadas

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			a[i][j] = i; 
			b[i][j] = -1; 
		}
	}

	printf("Matriz a\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	}

	#pragma omp parallel for num_threads(4) // Início da região paralela
	for (i = 0; i < n; i++) // Por default: i privado
	{
		for (j = 0; j < n; j++)
		{
			b[i][j] = a[i][j]; 
		}
	} // Fim da região paralela: barreira implícita

	printf("\nMatriz b\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d\t", b[i][j]);
		}
		printf("\n");
	}

	return 0;
}
