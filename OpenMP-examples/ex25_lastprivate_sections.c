// Exemplo 25: Cláusula lastprivate com construtor sections
// Compilar com: gcc ex25_lastprivate_sections.c -fopenmp -o ex25_lastprivate_sections -Wall
// Executar por linha de comando: ./ex25_lastprivate_sections

#include <omp.h>
#include <stdio.h>

int main()
{
	int a = 1, b = 1, c = 1, d = 1; // Por default: compartilhadas

	printf("Região sequencial ini:\t %d %d %d %d\n\n", a, b, c, d);

	// Início da região paralela
	#pragma omp parallel sections num_threads(2) private(b) firstprivate(c) lastprivate(d)
	{
		#pragma omp section // Seção A
		{
			printf("Seção A ini: tid=%d\t %d %d %d %d\n", omp_get_thread_num(), a, b, c, d);
			a = b = c = d = 4;
			printf("Seção A fim: tid=%d\t %d %d %d %d\n", omp_get_thread_num(), a, b, c, d);
		}
		#pragma omp section // Seção B
		{
			printf("Seção B ini: tid=%d\t %d %d %d %d\n", omp_get_thread_num(), a, b, c, d);
			a = b = c = d = 8;
			printf("Seção B fim: tid=%d\t %d %d %d %d\n", omp_get_thread_num(), a, b, c, d);
		}
	} // Fim da região paralela: barreira implícita

	printf("\nRegião sequencial fim:\t %d %d %d %d\n", a, b, c, d);

	return 0;
}
