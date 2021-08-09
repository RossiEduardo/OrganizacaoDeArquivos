#ifndef BTREE_H_

	#define BTREE_H_

	#include "structs.h"
	
	#define TAM_REGISTRO 77
	#define NO_PROMOTION 0
	#define ERROR -2
	

	//////// - Funções principais da árvore-B - ////////

	/* Gerencia uma inserção na árvore B, caso haja split na raiz essa função cuida disso */
	void driver (FILE *arquivo, BTREE_CABECALHO *cabecalho, int chave, long long byteOffset_chave);
	
	/* RECURSÃO DE INSERÇÃO NA ÁRVORE B 
	Irá realizar a busca e depois inserir ordenadamente a chave e caso seja necessário faz split
	*/
	short Insercao(FILE *arquivo, int chave, long long byteOffset_chave, int RRNatual, int *chavePromovida, long long *byteOffset_chave_promovido, int *RRNproxNO);
	
	/* SPLIT DA INSERÇÃO NA ÁRVORE B */
	BTREE_NO *split(BTREE_NO *NoAtual, int chave, long long byteOffset_chave, int ponteiroADireita, int *chavePromovida, long long *byteOffset_chave_promovido, int *RRNproxNo);

	/* Busca uma chave na árvore B e retorna o byteOffset no arquivo de dados da registro em que a chave está */
	long long pesquisa_btree(FILE *arquivo, int chave, int rrn);
	

#endif
