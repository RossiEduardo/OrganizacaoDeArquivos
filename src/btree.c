#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/leitura_e_escrita_btree.h"
#include "../include/auxiliares_btree.h"
#include "../include/btree.h"
#include "../include/structs.h"


BTREE_NO *split (BTREE_NO *NoAtual, int chave, long long byteOffset_chave, int ponteiroADireita, int *chavePromovida, 
		long long *byteOffset_chave_promovido, int *RRNproxNo) {
	BTREE_NO *novoNo = malloc(sizeof(BTREE_NO));
	//Definem-se vetores maiores que os da struct, para ser possivel inserir um valor a mais
	int C_aux[5];
	long long Pr_aux[5];
	int P_aux[6];

	int i, pos, aux;

	//INSERIR ORDENADO
	//Copiando as chaves do fim até ser menor que a chave
	// do nó atual para um vetor auxiliar, já shiftando as chaves para a direita
	for(pos = 3; pos >= 0 && NoAtual->C[pos] > chave; pos--) {
		C_aux[pos+1] = NoAtual->C[pos];
		Pr_aux[pos+1] = NoAtual->Pr[pos];       
		P_aux[pos+2] = NoAtual->P[pos+1];
	}
	//Inserindo a chave no lugar correto do vetor auxiliar
	C_aux[pos+1] = chave;
	Pr_aux[pos+1] = byteOffset_chave;
	P_aux[pos+2] = ponteiroADireita;

	//Continua copiando o resto
	for (; pos>=0; pos--) {
		C_aux[pos] = NoAtual->C[pos];
		Pr_aux[pos] = NoAtual->Pr[pos];
		P_aux[pos+1] = NoAtual->P[pos+1];
	}
	P_aux[0] = NoAtual->P[0];

	//Copiando o vetor auxiliar para o nó atual e pro novo nó
	memcpy(NoAtual->C, C_aux, 2 * sizeof(int));
	memcpy(NoAtual->Pr, Pr_aux, 2 * sizeof(long long));
	memcpy(NoAtual->P, P_aux, 3 * sizeof(int));
	//  0 1 2 3 4     -> chave
	// 0 1 2 3 4 5    -> ponteiros
	
	memcpy(novoNo->C, &C_aux[3], 2 * sizeof(int));
	memcpy(novoNo->Pr, &Pr_aux[3], 2 * sizeof(long long));
	memcpy(novoNo->P, &P_aux[3], 3 * sizeof(int));

	//Inicializar as posicoes nao ocupadas no novo_no e as posicoes que deixaram de ser ocupadas em no_atual
	for(i = 2; i < 4; i++) {
		NoAtual->C[i] = -1;
		NoAtual->Pr[i] = -1;
		NoAtual->P[i+1] = -1;

		novoNo->C[i] = -1;
		novoNo->Pr[i] = -1;
		novoNo->P[i+1] = -1;
	}

	NoAtual->nroDeChavesIndexadas = 2;

	novoNo->nroDeChavesIndexadas = 2;
	novoNo->RRNdoNo = *RRNproxNo;
	novoNo->folha = NoAtual->folha;

	//Promovendo sempre a chave do meio
	*chavePromovida = C_aux[2];
	*byteOffset_chave_promovido = Pr_aux[2];

	return novoNo;
	
}

short Insercao (FILE *arquivo, int chave, long long byteOffset_chave, int RRNatual, int *chavePromovida,
		long long *byteOffset_chave_promovido, int *RRNproxNO) {

	//Lendo a página da árvore atual
	BTREE_NO *NoAtual = readPage(arquivo, RRNatual);

	BTREE_NO *novoNo;
	short pos, ponteiroADireita = -1;

	//Descendo a árvore até os nós folhas
	if(NoAtual->folha == '0') {
		pos = buscarChaveNoVetor(NoAtual->C, NoAtual->nroDeChavesIndexadas, chave);
		//pos que a chave deve ser inserida

		//Não podemos encontrar a chave no nó e os ponteiros não podem ser -1
		if( (pos < NoAtual->nroDeChavesIndexadas) && ( NoAtual->C[pos] == chave || NoAtual->P[pos] == -1 ) ) {
			//Free no nó atual e return
			free(NoAtual);
			return ERROR;
		}
		
		//INSERIR CHAVE PROMOVIDA
		ponteiroADireita = Insercao(arquivo, chave, byteOffset_chave, NoAtual->P[pos], chavePromovida, byteOffset_chave_promovido, RRNproxNO);
		
		chave = *chavePromovida;
		byteOffset_chave = *byteOffset_chave_promovido;
		
	}
	//Chegamos no nó folha
	//variável 'ponteiroADireita' funcionando como operação realizada anteriormente
	if(ponteiroADireita == ERROR || ponteiroADireita == NO_PROMOTION) {
		//Free no nó atual e return
		free(NoAtual);
		return ponteiroADireita;
	}

	pos = buscarChaveNoVetor(NoAtual->C, NoAtual->nroDeChavesIndexadas, chave);
	if(pos < NoAtual->nroDeChavesIndexadas && NoAtual->C[pos] == chave) {
		//Retorna erro se a chave já está no vetor
		//Free no nó atual e return
		free(NoAtual);
		return ERROR;
	}

	//Nó folha, com espaço sobrando
	if(NoAtual->nroDeChavesIndexadas < 4) {
		//Somente inserir
		inserirChaveOrdenada(NoAtual, NoAtual->nroDeChavesIndexadas, chave, byteOffset_chave, ponteiroADireita);

		NoAtual->nroDeChavesIndexadas += 1;
		escreveNaArvoreB(arquivo, NoAtual, NoAtual->RRNdoNo);
		
		//Free no nó atual e return
		free(NoAtual);
		return NO_PROMOTION;
	}

	//Se não entrou no if, significa que não tem espaço no nó, deve ser feito split
	novoNo = split(NoAtual, chave, byteOffset_chave, ponteiroADireita, chavePromovida, byteOffset_chave_promovido, RRNproxNO);

	*RRNproxNO += 1;
	
	//Escreve a newpage e page atual
	escreveNaArvoreB(arquivo, NoAtual, NoAtual->RRNdoNo);
	escreveNaArvoreB(arquivo, novoNo, novoNo->RRNdoNo);

	//Ponteiro a direita da chave promovida recebe o rrn do novo nó criado no split
	ponteiroADireita = novoNo->RRNdoNo;
	free(novoNo);
	//Free no nó atual e return
	free(NoAtual);

	//return PROMOTION;
	return ponteiroADireita;
}


void driver (FILE *arquivo, BTREE_CABECALHO *cabecalho, int chave, long long byteOffset_chave) {
	short retorno;
	BTREE_NO *novoNoRaiz;
	//Definem-se variáveis locais

	int *chave_promovida = (int *) malloc(sizeof(int) * 1);
	long long *byteOffset_chave_promovido = (long long *) malloc(sizeof(long long) * 1);
	int *RRNproxNO = (int *) malloc(sizeof(int) * 4);
	//Alocam-se variáveis não locais, que serão usadas na recursão da inserção
	*RRNproxNO = cabecalho->RRNproxNo;

	//Caso o arquivo da arvore B esteja vazio
	if(cabecalho->noRaiz == -1) {
		//Nesse caso não haverá busca para onde deve ser inserida a chave
		//O algoritimo será o mesmo de quando há um split no nó folha
		retorno = -1;
		//O RRNproxNo se inicia com -1, mas na verdade é 0
		*RRNproxNO = 0;
		//Como será executado o mesmo quando há um split no nó folha, as chaves promovidas são as chaves atuais
		*chave_promovida = chave;
		*byteOffset_chave_promovido = byteOffset_chave;
	}

	else {
		//Recursão da inserção
		//Retorna o ponteiro a direita, ou ERROR ou NO_PROMOTION
		retorno = Insercao(arquivo, chave, byteOffset_chave, cabecalho->noRaiz, chave_promovida, byteOffset_chave_promovido, RRNproxNO);
	}

	//Caso retorne PROMOTION, deve ser feito um split do nó raiz
	if (retorno != ERROR && retorno != NO_PROMOTION) {
		//Aloca-se a nova raiz
		novoNoRaiz = criaNovaRaiz();
		
		novoNoRaiz->C[0] = *chave_promovida;
		//O ponteiro a esquerda aponta para o antigo nó raiz
		novoNoRaiz->P[0] = cabecalho->noRaiz;
		//O ponteiro a direita aponta para o novo nó (resultado do split do antigo nó raiz)
		novoNoRaiz->P[1] = retorno;

		novoNoRaiz->Pr[0] = *byteOffset_chave_promovido; 

		//Se ao invés de ser um split na raiz for a primeira inserção da árvore, a nova raiz é o único nó da árvore,
		// logo é folha 
		if(cabecalho->noRaiz != -1)
			novoNoRaiz->folha = '0';
		else
			novoNoRaiz->folha = '1';
		
		//Inicializam-se outras variáveis do novo nó
		novoNoRaiz->nroDeChavesIndexadas = 1;
		novoNoRaiz->RRNdoNo = *RRNproxNO;

		//Escreve no arquivo de índice
		escreveNaArvoreB(arquivo, novoNoRaiz, novoNoRaiz->RRNdoNo);

		//RRNproxNO é atualizado, pois escrevemos um nó na posição em que apontava
		*RRNproxNO += 1;
		//O RRN do nó raiz também é atualizado no cabeçalho
		cabecalho->noRaiz = novoNoRaiz->RRNdoNo;

		free(novoNoRaiz);
	}

	
	//RRNproxNO é atualizado no cabeçalho também, mesmo se não houve split na raiz, pois pode ter ocorrido split
	// em nó folha
	cabecalho->RRNproxNo = *RRNproxNO;
	
	free(chave_promovida);
	free(byteOffset_chave_promovido);
	free(RRNproxNO);
}


long long pesquisa_btree(FILE *arquivo, int chave, int rrn){
	BTREE_NO *no_atual = readPage(arquivo, rrn);
	int byteoffset;
	int pos = buscarChaveNoVetor(no_atual->C, no_atual->nroDeChavesIndexadas, chave);
	
	//Caso nao consiga ler o nó (pode acontecer se a btree nao tiver nó), o no_atual recebe NULL
	if(no_atual == NULL){
		return -2;
	}
	
	//Encontrou a chave
	if(no_atual->C[pos] == chave){
		byteoffset = no_atual->Pr[pos];
	}
	//Não achou: vai procurar no nó filho
	else{
		if(no_atual->P[pos] != -1)
			byteoffset = pesquisa_btree(arquivo, chave, no_atual->P[pos]);
		else{
			//Não há mais filho, nó não encontrado
			free(no_atual);
			return -1;
		}
	}
	
	free(no_atual);
	return byteoffset;
}