// Exemplo 22: Cláusulas private e firstprivate
// Compilar com: gcc ex22_private_firstprivate.c -fopenmp -o ex22_private_firstprivate
// Compilação gera warning
// Executar por linha de comando: ./ex22_private_firstprivate

#include <omp.h>
#include <stdio.h>

void funcao()
{
	int x = 0;
	for (int i = 0; i < 1000000; i++)
	{
		x = (x + i) / 2;
	}
}

int main()
{
	int a = -1, b = -1, c = -1; // Por default: compartilhadas

	printf("Região sequencial ini:\t\t a=%d\t b=%d\t c=%d\n\n", a, b, c);

	// Início da região paralela
	#pragma omp parallel num_threads(4) private(b) firstprivate(c) // Modifica compartilhamento de b e c
	{
		funcao(); // Consome tempo

		printf("Região paralela ini: t_id=%d\t a=%d\t b=%d\t c=%d\n",
				 omp_get_thread_num(), a, b, c);

		a = omp_get_thread_num();
		b = omp_get_thread_num();
		c = omp_get_thread_num();

		printf("Região paralela fim: t_id=%d\t a=%d\t b=%d\t c=%d\n",
				 omp_get_thread_num(), a, b, c);

	} // Fim da região paralela: barreira implícita

	printf("\nRegião sequencial fim:\t\t a=%d\t b=%d\t c=%d\n", a, b, c);

	return 0;
}
