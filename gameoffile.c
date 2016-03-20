#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define linha 50
#define coluna 50

/* 
Qualquer célula viva com menos de dois vizinhos vivos morre de solidão.
Qualquer célula viva com mais de três vizinhos vivos morre de superpopulação.
Qualquer célula morta com exatamente três vizinhos vivos se torna uma célula viva.
Qualquer célula viva com dois ou três vizinhos vivos continua no mesmo estado para a próxima geração.
*/

typedef struct{
	int atual;
	int aux;
}tab;

int iteracoes = 0;

int quantidade_vizinhos(tab (*tabuleiro)[coluna], int linha_pos, int coluna_pos)
{
	int contador = 0;

	if(linha_pos-1>=0)
	{
		if(coluna_pos-1>=0 && tabuleiro[linha_pos-1][coluna_pos-1].atual)
			contador++;
		if(tabuleiro[linha_pos-1][coluna_pos].atual)
			contador++;
		if(coluna_pos+1<=coluna && tabuleiro[linha_pos-1][coluna_pos+1].atual)
			contador++;		
	}

	if(coluna_pos-1>=0 && tabuleiro[linha_pos][coluna_pos-1].atual)
		contador++;
	if(coluna_pos+1<=coluna && tabuleiro[linha_pos][coluna_pos+1].atual)
		contador++;

	if(linha_pos+1<=linha)
	{
		if(coluna_pos-1>=0 && tabuleiro[linha_pos+1][coluna_pos-1].atual)
			contador++;
		if(tabuleiro[linha_pos+1][coluna_pos].atual)
			contador++;
		if(coluna_pos+1<=coluna && tabuleiro[linha_pos+1][coluna_pos+1].atual)
			contador++;
	}

	return contador;
}

void atualiza_tabuleiro(tab (*tabuleiro)[coluna])
{
	int i, j;
	for(i=0;i<linha;i++)
		for(j=0;j<coluna;j++)
		{
			tabuleiro[i][j].atual = tabuleiro[i][j].aux;
			tabuleiro[i][j].aux = 0;
		}
}

void verifica_tabuleiro(tab (*tabuleiro)[coluna])
{
	int i, j, contador;
	for(i=0;i<linha;i++)
	{
		for(j=0;j<coluna;j++)
		{
			contador = quantidade_vizinhos(tabuleiro, i, j);
			if(tabuleiro[i][j].atual)
			{
				if(contador<2 || contador>3)
					tabuleiro[i][j].aux = 0;
				else
					tabuleiro[i][j].aux = 1;
			}
			else
				if(contador==3)
					tabuleiro[i][j].aux = 1;
				else
					tabuleiro[i][j].aux = 0;
		}
	}

}

void tabuleiro_zerado(tab (*tabuleiro)[coluna])
{
	int i, j;
	for(i=0;i<linha;i++)
		for(j=0;j<coluna;j++)
			tabuleiro[i][j].atual = tabuleiro[i][j].aux = 0;
}

void free_tabuleiro(tab (*tabuleiro)[coluna])
{
	int i;
	for(i=0;i<linha;i++)
	{
		free(tabuleiro[i]);
	}
	free(tabuleiro);
}

void imprime_tabuleiro(tab (*tabuleiro)[coluna])
{
	int i, j;
	
	printf("Iteracao %d\n", iteracoes);
	iteracoes++;
	for(i=0;i<linha;i++)
	{
		for(j=0;j<coluna;j++)
		{
			if(tabuleiro[i][j].atual == 1)
				printf(".");
			else
				printf(" ");
		}
		printf("\n");

	}
}

int main()
{
	//int tabuleiro[linha][coluna];
	tab tabuleiro[linha][coluna];
	int i, j;
	//int **tabuleiro;
	/*
	tabuleiro = malloc(sizeof(int *)*linha);
	for(i=0;i<linha;i++)
		tabuleiro[i] = malloc(sizeof(int)*coluna);
	*/
	tabuleiro_zerado(tabuleiro);
	/*
	tabuleiro[13][13].atual = 1;
	tabuleiro[13][14].atual = 1;
	tabuleiro[13][15].atual = 1;

	tabuleiro[14][13].atual = 1;
	tabuleiro[15][14].atual = 1;
	*/

	tabuleiro[33][13].atual = 1;
	tabuleiro[33][14].atual = 1;
	tabuleiro[33][15].atual = 1;
	tabuleiro[33][16].atual = 1;
	tabuleiro[33][17].atual = 1;
	tabuleiro[34][14].atual = 1;
	tabuleiro[34][15].atual = 1;
	tabuleiro[34][16].atual = 1;
	tabuleiro[35][14].atual = 1;
	tabuleiro[35][15].atual = 1;
	tabuleiro[35][16].atual = 1;
	tabuleiro[36][14].atual = 1;
	tabuleiro[36][15].atual = 1;
	tabuleiro[36][16].atual = 1;


	while(1)
	{
		usleep(90000);
		imprime_tabuleiro(tabuleiro);
		verifica_tabuleiro(tabuleiro);
		atualiza_tabuleiro(tabuleiro);
	}

	//free_tabuleiro(tabuleiro);


	return 0;
}