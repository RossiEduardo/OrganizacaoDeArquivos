#ifndef AUXILIARES_BTREE_H_

	#define AUXILIARES_BTREE_H_

	#include "structs.h"
	
	/* Irá inicializar uma struct de no da árvore B com os valores -1, já que inicializa vazio */
	BTREE_NO *criaNovaRaiz();

	/* Busca um valor nos conteúdo do vetor passado é retorna a posição encontrada */
	short buscarChaveNoVetor(int *vec, int tam, int chave);
	
	/* Insere uma nova chave ordenadamente em um nó da árvore B que tem espaço */
	BTREE_NO *inserirChaveOrdenada(BTREE_NO *no, int tam, int chave, long long byteOffset_chave, int novoPonteiro);

#endif