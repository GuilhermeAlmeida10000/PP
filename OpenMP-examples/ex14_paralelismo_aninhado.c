// Exemplo 14: Paralelismo aninhado
// Compilar com: gcc ex14_paralelismo_aninhado.c -fopenmp -o ex14_paralelismo_aninhado -Wall
// Executar por linha de comando: ./ex14_paralelismo_aninhado

#include <omp.h>
#include <stdio.h>

void funcao() // Consome tempo
{
	int a = 0;
	for (int i = 0; i < 100000000; i++)
	{
		a = (a + i) / 2;
	}
}

int main()
{
	// Região sequencial
	printf("Região sequencial ini:\t\t thread_id = %d\t nthreads = %d\n",
			 omp_get_thread_num(), omp_get_num_threads());

	omp_set_nested(1); // Habilita paralelismo aninhado

	// Início da região paralela externa
	#pragma omp parallel num_threads(3)
	{
		printf("Região paralela externa ini:\t thread_id = %d\t nthreads = %d\n",
				 omp_get_thread_num(), omp_get_num_threads());

		// Início da região paralela aninhada
		#pragma omp parallel num_threads(2)
		{
			printf("Região paralela aninhada:\t\t thread_id = %d\t nthreads = %d\n",
					omp_get_thread_num(), omp_get_num_threads());
			
			funcao(); // Consome tempo
		} // Fim da região paralela aninhada: barreira implícita

		printf("Região paralela externa fim:\t thread_id = %d\t nthreads = %d\n",
				 omp_get_thread_num(), omp_get_num_threads());
	} // Fim da região paralela externa: barreira implícita

	// Região sequencial
	printf("Região sequencial fin:\t\t thread_id = %d\t nthreads = %d\n",
			 omp_get_thread_num(), omp_get_num_threads());

	return 0;
}
