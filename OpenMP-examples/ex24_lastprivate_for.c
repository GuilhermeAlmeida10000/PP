// Exemplo 24: Cláusula lastprivate com construtor for
// Compilar com: gcc ex24_lastprivate_for.c -fopenmp -o ex24_lastprivate_for
// Executar por linha de comando: ./ex24_lastprivate_for

#include <omp.h>
#include <stdio.h>

int main()
{
	int n = 4, a = -1, b = -1; // Por default: compartilhadas

	#pragma omp parallel for num_threads(4) lastprivate(b) // Região paralela
	for (int i = 0; i < n; i++) // Por defaut: i privado
	{
		a = i;
		b = i;
	} // Barreira implícita

	printf("Região sequencial final: a=%d\t b=%d\n", a, b);

	return 0;
}
