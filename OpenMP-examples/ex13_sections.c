// Exemplo 13: Região paralela com sections
// Compilar com: gcc ex13_sections.c -fopenmp -o ex13_sections -Wall
// Executar por linha de comando: ./ex13_sections

#include <omp.h>
#include <stdio.h>

void funcaoA()
{
	printf("Thread %d de %d executa função A\n", omp_get_thread_num(), omp_get_num_threads());
	int a = 0;
	for (int i = 0; i < 1000000; i++) // Consome tempo
	{
		a = (a + i) / 2;
	}
	return;
}

void funcaoB()
{
	printf("Thread %d de %d executa função B\n", omp_get_thread_num(), omp_get_num_threads());
	int b = 0;
	for (int i = 0; i < 1000000; i++) // Consome tempo
	{
		b = (b + i) / 2;
	}
	return;
}

void funcaoC()
{
	printf("Thread %d de %d executa função C\n", omp_get_thread_num(), omp_get_num_threads());
	int c = 0;
	for (int i = 0; i < 1000000; i++) // Consome tempo
	{
		c = (c + i) / 2;
	}
	return;
}

void funcaoD()
{
	printf("Thread %d de %d executa função D\n", omp_get_thread_num(), omp_get_num_threads());
	int d = 0;
	for (int i = 0; i < 1000000; i++) // Consome tempo
	{
		d = (d + i) / 2;
	}
	return;
}

int main()
{
	// Construtor combinado parallel sections: início da região paralela e distribui blocos entre as threads
	#pragma omp parallel sections // Testar cláusula num_threads(2)
	{
		#pragma omp section
		{
			funcaoA();
		}
		#pragma omp section
		{
			funcaoB();
		}
		#pragma omp section
		{
			funcaoC();
		}
		#pragma omp section // Testar remover essa seção
		{
			funcaoD();
		}
	} // Fim da região paralela: barreira implícita

	return 0;
}
