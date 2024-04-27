// Exemplo 4: Cláusula if
// Compilar com: gcc ex04_clausula_if.c -fopenmp -o ex04_clausula_if -Wall
// Executar por linha de comando: ./ex04_clausula_if

#include <omp.h>
#include <stdio.h>

int main()
{
	int n = 10; // Testar com n = 10 e depois com n = 101

	// Construtor parallel
	#pragma omp parallel if(n > 100) // Início da região paralela, apenas se n > 100
	{
		printf("Região paralela  : thread_id = %d\t nthreads = %d\n",
				 omp_get_thread_num(), omp_get_num_threads());
		
	} // Fim da região paralela: barreira implícita

	return 0;
}
