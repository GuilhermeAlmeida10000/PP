// Exemplo 11: Balanceamento de carga e schedule
// Compilar com: gcc ex11_balanceamento_carga.c -fopenmp -o ex11_balanceamento_carga -Wall
// Executar por linha de comando: ./ex11_balanceamento_carga <número_de_elementos>

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void trabalho_iteracao(int i)
{
	// Laço simula trabalho da iteração i proporcional a i
	int j = 0;
	while (j < i)
		j++;

	return;
}

int main(int argc, char** argv)
{
	if(argc != 2) {
		printf("O programa foi executado com parâmetros incorretos.\n");
		printf("Uso: ./ex11_balanceamento_carga <número_de_elementos>\n");
		exit(1);
	}

	// Testar valores: n = 120 mil, para medir tempo de execução
	int n = atoi(argv[1]); 
	
	// -------------------------------------------------------------------------
	// Realiza iterações do laço em paralelo
	// Cada iteração realiza trabalho proporcional a i
	double tini = omp_get_wtime();

	// Construtor combinado parallel for
	#pragma omp parallel for // Testar cláusula schedule(static), schedule(static,1), schedule(dynamic,1)
	for (int i = 0; i < n; i++)
	{
		// Carga de trabalho da iteração i é proporcional a i
		trabalho_iteracao(i);

	} // Fim da região paralela: barreira implícita

	double tfin = omp_get_wtime();
	double tpar = tfin - tini;

	printf("Tempo: %f s\n", tpar);

	return 0;
}
