#include <stdio.h>
#include <stdlib.h> 
#include "../include/structs.h"

//Imprime todos os dados da struct no arquivo de saída
void toBinRegistroLinha (DADOS_LINHA *registro, FILE *out) {
	fwrite(&registro->removido, 1, 1, out);
	fwrite(&registro->tamanhoRegistro, sizeof(int), 1, out);
	fwrite(&registro->codLinha, sizeof(int), 1, out);
	fwrite(&registro->aceitaCartao, 1, 1, out);
	fwrite(&registro->tamanhoNome, sizeof(int), 1, out);
	fwrite(&registro->nomeLinha, 1, registro->tamanhoNome, out);
	fwrite(&registro->tamanhoCor, sizeof(int), 1, out);
	fwrite(&registro->corLinha, 1, registro->tamanhoCor, out);
}

//Imprime todos os dados da struct no arquivo de saída
void toBinCabecalhoLinha (CABECALHO_LINHA *c, FILE *out) {
	fwrite(&c->status, 1, 1, out);
	fwrite(&c->byteProxReg, sizeof(long long int), 1, out);
	fwrite(&c->nroRegistros, sizeof(int), 1, out);
	fwrite(&c->nroRegRemovidos, sizeof(int), 1, out);
	fwrite(&c->descreveCodigo, 1, 15, out);
	fwrite(&c->descreveCartao, 1, 13, out);
	fwrite(&c->descreveNome, 1, 13, out);
	fwrite(&c->descreveCor, 1, 24, out);
}

//Analisa qual é o valor do caractere e imprime a string referente a ele
void print_aceita_cartao(char aceita_cartao){
    if(aceita_cartao == 'S')
        printf("Aceita cartao: PAGAMENTO SOMENTE COM CARTAO SEM PRESENCA DE COBRADOR\n");

    else if(aceita_cartao == 'N')
        printf("Aceita cartao: PAGAMENTO EM CARTAO E DINHEIRO\n");

    else
        printf("Aceita cartao: PAGAMENTO EM CARTAO SOMENTE NO FINAL DE SEMANA\n");
}



void print_dados_linha(DADOS_LINHA *registro_linha){
	//Campo do tipo int tem tamanho -1 se for vazio
	if(registro_linha->codLinha != -1)
		printf("Codigo da linha: %d\n", registro_linha->codLinha);
	else
		printf("Codigo da linha: campo com valor nulo\n");	

	//Para string de tam variável o tam do campo eh 0 
	if(registro_linha->tamanhoNome != 0)
		printf("Nome da linha: %.*s\n", registro_linha->tamanhoNome, registro_linha->nomeLinha);
	else
		printf("Nome da linha: campo com valor nulo\n");
	
	//string de tam variável o tam do campo eh 0 
	if(registro_linha->tamanhoCor != 0)
		printf("Cor que descreve a linha: %.*s\n", registro_linha->tamanhoCor, registro_linha->corLinha);
	else 
		printf("Cor que descreve a linha: campo com valor nulo\n");

	print_aceita_cartao(registro_linha->aceitaCartao);
}
