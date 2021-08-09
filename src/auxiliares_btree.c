#include <stdlib.h>
#include <stdio.h>
#include "../include/auxiliares_btree.h"
#include "../include/btree.h"
#include "../include/leitura_e_escrita_btree.h"

//Busca chave no vetor de chaves e retorna sua posição ou a posicao em que deveria estar
short buscarChaveNoVetor(int *vec, int tam, int chave) {
	short pos;
	
	//Loop que roda até quando a chave é maior que a posição corrente do vetor
	for (pos = 0; pos < tam && vec[pos] < chave; pos++) {}

	return pos;
}

BTREE_NO *inserirChaveOrdenada(BTREE_NO *no, int tam, int chave, long long byteOffset_chave, int novoPonteiro) {
	short pos;

	//Translada todos da direita da chave
	for (pos = tam - 1; pos >= 0 && no->C[pos] > chave; pos--) {
		no->C[pos + 1] = no->C[pos];
		no->Pr[pos + 1] = no->Pr[pos];
		no->P[pos + 2] = no->P[pos + 1];
	}

	//Insere a chave na posição encontrada
	no->C[pos + 1] = chave;
	no->Pr[pos + 1] = byteOffset_chave;
	no->P[pos + 2] = novoPonteiro;

	return no;
}

/* Irá inicializar uma struct de no da árvore B com os valores -1, já que inicializa vazio */
BTREE_NO *criaNovaRaiz(){
	BTREE_NO *no = (BTREE_NO *) malloc(sizeof(BTREE_NO));
	
	for(int i = 0; i < 4; i++) {
		no->C[i] = -1;
		no->Pr[i] = -1;
		no->P[i] = -1;
	}
	no->P[4] = -1;

	return no;
}