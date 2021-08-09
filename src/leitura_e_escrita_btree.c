#include <stdio.h>
#include <stdlib.h>
#include "../include/leitura_e_escrita_btree.h"
#include "../include/structs.h"


/* Irá criar uma variável struct cabeçalho ler o cabeçalho do arquivo de índice e atribuir às variáves da struct */
BTREE_CABECALHO *lerCabecalho_arvoreB(FILE *arquivo) {
	BTREE_CABECALHO *cabecalho = (BTREE_CABECALHO *) malloc(sizeof(BTREE_CABECALHO));
	
	fseek(arquivo, 0, SEEK_SET);

	fread(&cabecalho->status, sizeof(char),  1, arquivo);
	fread(&cabecalho->noRaiz, sizeof(int), 1, arquivo);
	fread(&cabecalho->RRNproxNo, sizeof(int), 1, arquivo);
	
	return cabecalho;
}

// Escreve o cabeçalho
void escreveCabecalho_arvoreB (FILE *arquivo, BTREE_CABECALHO *c) {
	//Volta para o início do arquivo
	fseek(arquivo, 0, SEEK_SET);
	//Lixo como variável, para ser printada
	char lixo[69] = "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

	//Escreve o status do arquivo para 0
	fwrite(&c->status, sizeof(char), 1, arquivo);

	//Escreve as variáveis do cabeçalho
	fwrite(&c->noRaiz, 1, sizeof(int), arquivo);
	fwrite(&c->RRNproxNo, 1, sizeof(int), arquivo);

	//Escreve lixo
	fwrite(lixo, 68, sizeof(char), arquivo);
}


BTREE_NO *readPage(FILE *arquivo, int RRN) {
	//Aloca na memória
	BTREE_NO *no = (BTREE_NO *) malloc (sizeof(BTREE_NO));

	//Indo para o RRN passado
	fseek(arquivo, ((RRN + 1) * TAM_REGISTRO), SEEK_SET);

	//Lê as variáveis na ordem em questão
	if(fread(&no->folha, sizeof(char), 1, arquivo) == 0){
		//se n conseguir ler o primeiro campo significa que não temos nó na btree, retorna NULL
		free(no);
		return NULL;
	}
	fread(&no->nroDeChavesIndexadas, sizeof(int), 1, arquivo);
	fread(&no->RRNdoNo, sizeof(int), 1, arquivo);
	
	fread(&no->P[0], sizeof(int), 1, arquivo);
	fread(&no->C[0], sizeof(int), 1, arquivo);
	fread(&no->Pr[0], sizeof(long long), 1, arquivo);
	
	fread(&no->P[1], sizeof(int), 1, arquivo);
	fread(&no->C[1], sizeof(int), 1, arquivo);
	fread(&no->Pr[1], sizeof(long long), 1, arquivo);
	
	fread(&no->P[2], sizeof(int), 1, arquivo);
	fread(&no->C[2], sizeof(int), 1, arquivo);
	fread(&no->Pr[2], sizeof(long long), 1, arquivo);
	
	fread(&no->P[3], sizeof(int), 1, arquivo);
	fread(&no->C[3], sizeof(int), 1, arquivo);
	fread(&no->Pr[3], sizeof(long long), 1, arquivo);
	
	fread(&no->P[4], sizeof(int), 1, arquivo);
	
	return no;
}

void escreveNaArvoreB(FILE *arquivo, BTREE_NO *no, int RRN) {
	//Indo para o RRN passado
	fseek(arquivo, ((RRN + 1) * TAM_REGISTRO), SEEK_SET);

	//Escreve no arquivo na ordem em questão
	fwrite(&no->folha, sizeof(char), 1, arquivo);
	fwrite(&no->nroDeChavesIndexadas, sizeof(int), 1, arquivo);
	fwrite(&no->RRNdoNo, sizeof(int), 1, arquivo);
	
	fwrite(&no->P[0], sizeof(int), 1, arquivo);
	fwrite(&no->C[0], sizeof(int), 1, arquivo);
	fwrite(&no->Pr[0], sizeof(long long), 1, arquivo);
	
	fwrite(&no->P[1], sizeof(int), 1, arquivo);
	fwrite(&no->C[1], sizeof(int), 1, arquivo);
	fwrite(&no->Pr[1], sizeof(long long), 1, arquivo);
	
	fwrite(&no->P[2], sizeof(int), 1, arquivo);
	fwrite(&no->C[2], sizeof(int), 1, arquivo);
	fwrite(&no->Pr[2], sizeof(long long), 1, arquivo);
	
	fwrite(&no->P[3], sizeof(int), 1, arquivo);
	fwrite(&no->C[3], sizeof(int), 1, arquivo);
	fwrite(&no->Pr[3], sizeof(long long), 1, arquivo);

	fwrite(&no->P[4], sizeof(int), 1, arquivo);
}