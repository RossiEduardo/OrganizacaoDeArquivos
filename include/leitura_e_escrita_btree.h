#ifndef LEITURA_E_ESCRITA_BTREE_H_

	#define LEITURA_E_ESCRITA_BTREE_H_

	#include "structs.h"
	
	#define TAM_REGISTRO 77
	#define NO_PROMOTION 0
	#define ERROR -2


	/* Irá criar uma variável struct cabeçalho ler o cabeçalho do arquivo de índice e atribuir às variáves da struct */
	BTREE_CABECALHO *lerCabecalho_arvoreB(FILE *arquivo);

	/* Escreve o cabeçalho passado no arquivo de índice passado */
	void escreveCabecalho_arvoreB (FILE *arquivo,  BTREE_CABECALHO *c);

	/* Lê o nó no do RRN passado no arquivo de índice passado */
	BTREE_NO *readPage(FILE *arquivo, int RRN);
	
	/* Escreve o nó no RRN do arquivo de índice passados */
	void escreveNaArvoreB(FILE *arquivo, BTREE_NO *no, int RRN);

#endif