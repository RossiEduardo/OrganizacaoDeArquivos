#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "../include/structs.h"
#include "../include/auxiliares.h"

//Imprime todos os dados da struct no arquivo de saída
void toBinRegistroVeiculo (DADOS_VEICULO *registro, FILE *out) {
	fwrite(&registro->removido, 1, 1, out);
	fwrite(&registro->tamanhoRegistro, sizeof(int), 1, out);
	fwrite(&registro->prefixo, 1, 5, out);

	//Se a data for campo nulo imprime o lixo
	if(registro->data[0] =='\0')	printLixo(out, 10);
	else	fwrite(&registro->data, 1, 10, out);
	fwrite(&registro->quantidadeLugares, sizeof(int), 1, out);
	fwrite(&registro->codLinha, sizeof(int), 1, out);
	fwrite(&registro->tamanhoModelo, sizeof(int), 1, out);
	fwrite(&registro->modelo, 1, registro->tamanhoModelo, out);
	fwrite(&registro->tamanhoCategoria, sizeof(int), 1, out);
	fwrite(&registro->categoria, 1, registro->tamanhoCategoria, out);
}

//Imprime todos os dados da struct no arquivo de saída
void toBinCabecalhoVeiculo (CABECALHO_VEICULO *c, FILE *out) {
	fwrite(&c->status, 1, 1, out);
	fwrite(&c->byteProxReg, sizeof(long long int), 1, out);
	fwrite(&c->nroRegistros, sizeof(int), 1, out);
	fwrite(&c->nroRegRemovidos, sizeof(int), 1, out);
	fwrite(&c->descrevePrefixo, 1, 18, out);
	fwrite(&c->descreveData, 1, 35, out);
	fwrite(&c->descreveLugares, 1, 42, out);
	fwrite(&c->descreveLinha, 1, 26, out);
	fwrite(&c->descreveModelo, 1, 17, out);
	fwrite(&c->descreveCategoria, 1, 20, out);
}

void print_data(char *data){
	//formato da data eh: AAAA-MM-DD
	int ano = 0, mes_int = 0;
	char mes[10], dia[3];
	//A variável 'data' não tem '\0' no final, então é criada a variável mydata como
	//	auxiliar, essa sim conterá o '\0' não prejudicando ações futuras
	char mydata[11];
	strncpy(mydata, data, 10);
	mydata[10] = '\0';

   	char *token = strtok(mydata, "-");
    ano = atoi(token);

    token = strtok(NULL, "-");
	mes_int = atoi(token);

	//Seleciona a string do mês
	if(mes_int == 1)
		strcpy(mes, "janeiro");
	else if(mes_int == 2)
		strcpy(mes, "fevereiro");
	else if(mes_int == 3)
		strcpy(mes, "março");
	else if(mes_int == 4)
		strcpy(mes, "abril");
	else if(mes_int == 5)
		strcpy(mes, "maio");
	else if(mes_int == 6)
		strcpy(mes, "junho");
	else if(mes_int == 7)
		strcpy(mes, "julho");
	else if(mes_int == 8)
		strcpy(mes, "agosto");
	else if(mes_int == 9)
		strcpy(mes, "setembro");
	else if(mes_int == 10)
		strcpy(mes, "outubro");
	else if(mes_int == 11)
		strcpy(mes, "novembro");
	else if(mes_int == 12)
		strcpy(mes, "dezembro");

	token = strtok(NULL, "-");
	strcpy(dia, token);
	
	printf("Data de entrada do veiculo na frota: %s de %s de %d\n", dia, mes, ano);
}

void print_dados_veiculo(DADOS_VEICULO *registro_veiculo){
	//Sabemos que valores de tam fixo do tipo string tem o seguinte formato: '\0@@@@@@...', ou seja, string[2] sempre == '@'
	if(registro_veiculo->prefixo[2] != '@')
		printf("Prefixo do veiculo: %.*s\n", 5, registro_veiculo->prefixo);
	else
		printf("Prefixo do veiculo: campo com valor nulo\n");
		
	//Para string de tam variável o tam do campo eh 0 
	if(registro_veiculo->tamanhoModelo != 0)
		printf("Modelo do veiculo: %.*s\n", registro_veiculo->tamanhoModelo, registro_veiculo->modelo);
	else
		printf("Modelo do veiculo: campo com valor nulo\n");
	
	//string de tam variável o tam do campo é 0 
	if(registro_veiculo->tamanhoCategoria != 0)
		printf("Categoria do veiculo: %.*s\n", registro_veiculo->tamanhoCategoria, 						registro_veiculo->categoria);
	else 
		printf("Categoria do veiculo: campo com valor nulo\n");

	//string de tam fixo
	if(registro_veiculo->data[2] != '@')
		print_data(registro_veiculo->data);
	else 
		printf("Data de entrada do veiculo na frota: campo com valor nulo\n");

	//campo do tipo int tem tamanho -1 se for vazio
	if(registro_veiculo->quantidadeLugares != -1)
		printf("Quantidade de lugares sentados disponiveis: %d\n", registro_veiculo->quantidadeLugares);
	else 
		printf("Quantidade de lugares sentados disponiveis: campo com valor nulo\n");
}
