#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "../include/structs.h"
#include "../include/auxiliares.h"
#include "../include/funcao-fornecida.h"

//Lê a primeira linha do arquivo csv de veiculos
CABECALHO_VEICULO *lerCabecalhoVeiculo (FILE *fp) {
	char *str, *campo;

  	str = readline(fp);
	if(str == NULL)
		return NULL;

  	CABECALHO_VEICULO *cabecalho = (CABECALHO_VEICULO * ) malloc(sizeof(CABECALHO_VEICULO));

	//Cada campo é atribuido a sua devida variável
	//Processo feito destrinchando a linha lida a partir do caractere ','
	campo = strtok(str, ",");
	strcpy(cabecalho->descrevePrefixo, campo);
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveData, campo);
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveLugares, campo);	
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveLinha, campo);	
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveModelo, campo);	
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveCategoria, campo);

	free(str);

	//As demais variáveis também são inicializadas
	cabecalho->status='0';
	cabecalho->byteProxReg=0;
	cabecalho->nroRegistros=0;
	cabecalho->nroRegRemovidos=0;

  	return cabecalho;
}

DADOS_VEICULO *lerRegistroVeiculo(FILE *fp) {
	char *str, *campo;

	str = readline(fp);

	//Caso a leitura chegue no fim do arquivo, para a função
	if(str==NULL) {
		return NULL;
	}

	DADOS_VEICULO *veiculo = malloc(sizeof(DADOS_VEICULO));

	//Verifica se é removido e atribui corretamente o prefixo
	campo = strtok(str, ",");
	if(campo[0]=='*') {
		veiculo->removido = '0';
		strncpy(veiculo->prefixo, &campo[1], 5);
	}
	else {
		veiculo->removido = '1';
		strncpy(veiculo->prefixo, campo, 5);
	}
	
	//Cada campo é atribuido a sua devida variável
	//Processo feito destrinchando a linha lida a partir do caractere ','
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
		strncpy(veiculo->data, "\0@@@@@@@@@", 10);
	else	strncpy(veiculo->data, campo, 10);
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
		veiculo->quantidadeLugares = -1;
	else	veiculo->quantidadeLugares = atoi(campo);	
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
		veiculo->codLinha = -1;
	else	veiculo->codLinha = atoi(campo);
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
		veiculo->tamanhoModelo = 0;
	else{
		veiculo->tamanhoModelo = strlen(campo);
		strncpy(veiculo->modelo, campo, veiculo->tamanhoModelo);
	}	
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
		veiculo->tamanhoCategoria = 0;
	else{
		veiculo->tamanhoCategoria = strlen(campo);
		strncpy(veiculo->categoria, campo, veiculo->tamanhoCategoria);
	}

	free(str);

	//O tamanho do registro é calculado somando o tamanho dos campos variados e o tamanho dos campos fixos(31)
	veiculo->tamanhoRegistro = 31+veiculo->tamanhoCategoria+veiculo->tamanhoModelo;

	return veiculo;
}

DADOS_VEICULO *recupera_dados_veiculo(FILE *arquivo){	
	DADOS_VEICULO *dados = (DADOS_VEICULO *) malloc(sizeof(DADOS_VEICULO));

	//lendo o byte que diz se foi removido
	if(fread(&dados->removido, sizeof(char), 1, arquivo) == 0){
		//se n conseguir ler o primeiro campo significa que chegamos no fim do arquivo, retorna NULL
		free(dados);
		return NULL;
	}

	//lendo o tamanho do registro
	fread(&dados->tamanhoRegistro, sizeof(int), 1, arquivo);

	//lendo o prefixo do veiculo
	fread(&dados->prefixo, sizeof(char), 5, arquivo);
		
	//lendo a data de entrada do veiculo na frota
	fread(&dados->data, sizeof(char), 10, arquivo);
		
	//lendo a qauntidade de lugares disponiveis do veiculo
	fread(&dados->quantidadeLugares, sizeof(int), 1, arquivo);

	//lendo o codigo da linha
	fread(&dados->codLinha, sizeof(int), 1, arquivo);

	//lendo o tamanho do campo modelo
	fread(&dados->tamanhoModelo, sizeof(int), 1, arquivo);

	//lendo o modelo do veiculo
	fread(&dados->modelo, sizeof(char), dados->tamanhoModelo, arquivo);

	//lendo o tamanho do campo categoria
	fread(&dados->tamanhoCategoria, sizeof(int), 1, arquivo);

	//lendo a categoria do veiculo
	fread(&dados->categoria, sizeof(char), dados->tamanhoCategoria, arquivo);

	return dados;
}

CABECALHO_VEICULO *recupera_cabecalho_veiculo(FILE *arquivo) {
	CABECALHO_VEICULO *c = (CABECALHO_VEICULO *)malloc(sizeof(CABECALHO_VEICULO));

	//Volta para o começo do arquivo, onde está o cabeçalho
	fseek(arquivo, 0, SEEK_SET);

	//Lê todos os dados e atribuí a variável correspondente
	fread(&c->status, sizeof(char), 1, arquivo);
	fread(&c->byteProxReg, sizeof(long long), 1, arquivo);
	fread(&c->nroRegistros, sizeof(int), 1, arquivo);
	fread(&c->nroRegRemovidos, sizeof(int), 1, arquivo);

	fread(&c->descrevePrefixo, sizeof(char), 18, arquivo);
	fread(&c->descreveData, sizeof(char), 35, arquivo);
	fread(&c->descreveLugares, sizeof(char), 42, arquivo);
	fread(&c->descreveLinha, sizeof(char), 26, arquivo);
	fread(&c->descreveModelo, sizeof(char), 17, arquivo);
	fread(&c->descreveCategoria, sizeof(char), 20, arquivo);

	return c;
}

//Utiliza da função scan_quote_string para ler os campos passados do usuário e depois atribui na
//	struct de dados do veículo
DADOS_VEICULO *leituraDoTecladoVeiculos() {
	char campo[100];

	DADOS_VEICULO *veiculo = malloc(sizeof(DADOS_VEICULO));

	scan_quote_string(campo);
	if (strlen(campo) == 0){
		free(veiculo);
		return NULL;
	}
	//Prefixo
	if(strlen(campo)==0)
		strncpy(veiculo->prefixo, "\0@@@@", 5);
	else
		strcpy(veiculo->prefixo, campo);
	//Data
	scan_quote_string(campo);
	if(strlen(campo)==0)
		strncpy(veiculo->data, "\0@@@@@@@@@", 10);
	else	strcpy(veiculo->data, campo);
	//Quantidade de Lugares
	scan_quote_string(campo);
	if(strlen(campo)==0)
		veiculo->quantidadeLugares = -1;
	else	veiculo->quantidadeLugares = atoi(campo);
	//Código da Linha
	scan_quote_string(campo);
	if(strlen(campo)==0)
		veiculo->codLinha = -1;
	else	veiculo->codLinha = atoi(campo);
	//Modelo
	scan_quote_string(campo);
	if(strlen(campo)==0)
		veiculo->tamanhoModelo = 0;
	else{
		veiculo->tamanhoModelo = strlen(campo);
		strncpy(veiculo->modelo, campo, veiculo->tamanhoModelo);
	}
	//Categoria
	scan_quote_string(campo);
	if(strlen(campo)==0)
		veiculo->tamanhoCategoria = 0;
	else{
		veiculo->tamanhoCategoria = strlen(campo);
		strncpy(veiculo->categoria, campo, veiculo->tamanhoCategoria);
	}

	//O tamanho do registro é calculado somando o tamanho dos campos variados e o tamanho dos campos fixos(31)
	veiculo->tamanhoRegistro = 31+veiculo->tamanhoCategoria+veiculo->tamanhoModelo;
	//A variável 'removido' também é inicializada
	veiculo->removido = '1';

	return veiculo;
}