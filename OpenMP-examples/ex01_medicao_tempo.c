// Exemplo 1: Medição de tempo de execução (INCOMPLETO)
// Compilar com: gcc ex01_medicao_tempo.c -fopenmp -o ex01_medicao_tempo -Wall
// Executar por linha de comando: ./ex01_medicao_tempo

#include <stdio.h>
#include <omp.h> // Cabeçalho da biblioteca OpenMP

int main()
{
	double tini = omp_get_wtime(); // Na 1a. região sequencial do programa

	//...

	//#pragma omp ...

	//...

	double tfin = omp_get_wtime(); // Na ultima região sequencial do programa
	double texec = tfin - tini; // Calcula tempo de execução (em segundos)
	printf("Tempo de execução: %f segundos\n", texec);
	
	return 0;
}
