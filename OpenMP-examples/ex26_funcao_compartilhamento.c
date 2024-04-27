// Exemplo 26: Compartilhamento de variáveis em função chamada dentro de região paralela
// Compilar com: gcc ex26_funcao_compartilhamento.c -fopenmp -o ex26_funcao_compartilhamento -Wall
// Executar por linha de comando: ./ex26_funcao_compartilhamento

#include <omp.h>
#include <stdio.h>

void funcao(int aa, int *bb, int cc, int *dd)
{
	int id = omp_get_thread_num();

	printf("Thread %d ini:\t aa=%d\t bb=%p\t *bb=%d\t cc=%d\t dd=%p\t *dd=%d\n",
			 id, aa, bb, *bb, cc, dd, *dd);

	aa    = id;
	(*bb) = id;
	cc    = id;
	(*dd) = id;

	printf("Thread %d fin:\t aa=%d\t bb=%p\t *bb=%d\t cc=%d\t dd=%p\t *dd=%d\n",
			 id, aa, bb, *bb, cc, dd, *dd);
}

int main()
{
	int a = -1, b = -1; // Por default: compartilhadas

	printf("Região sequencial ini: a=%d\t b=%d\n\n", a, b);

	#pragma omp parallel num_threads(2) // Início da região paralela
	{
		int c = -1, d = -1; // Por default: privadas

		funcao(a, &b, c, &d);

	} // Fim da região paralela: barreira implícita

	printf("\nRegião sequencial fim: a=%d\t b=%d\n", a, b);

	return 0;
}
