// Exemplo 17: Região paralela com single (INCOMPLETO)
// Compilar com: gcc ex17_single2.c -fopenmp -o ex17_single2 -Wall
// Executar por linha de comando: ./ex17_single2 <número_de_elementos>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("O programa foi executado com parâmetros incorretos.\n");
		printf("Uso: ./ex17_single2 <número_de_elementos>\n");
		exit(1);
	}

	// Testar valores: n = 10 e n =100
	int n = atoi(argv[1]);

	// Aloca vetores
	int *a = new int[n];

	// Construtor parallel
	#pragma omp parallel // Início da região paralela: todas as threads executam
	{
		// Construtor for: distribui iterações do laço entre threads
		#pragma omp for
		for (int i = 0; i < n; i++)
		{
			// Calcula resultados parciais ...
			a[i] = i ;
		} // Fim do construtor for: barreira implícita

		// Construtor single: apenas uma thread executa
		#pragma omp single // Usar cláusula nowait?
		{
			// Imprime resultados parciais ...
			for (int i = 0; i < n; i++)
				printf("%d ", a[i]);
			printf("\n");
		} // Fim do construtor single: barreira implícita (remover ou não?)

		// Construtor for: distribui iterações do laço entre threads
		#pragma omp for nowait
		for (int i = 0; i < n; i++)
		{
			// Calcula resultados finais ...
			a[i] = a[i]*100;
		} // Fim do construtor for: barreira implícita REMOVIDA
	} // Fim da região paralela: barreira implícita

	return 0;
}
