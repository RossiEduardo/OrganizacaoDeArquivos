#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "../include/structs.h"
#include "../include/auxiliares.h"
#include "../include/funcao-fornecida.h"

CABECALHO_LINHA *lerCabecalhoLinha (FILE *fp) {
	char *str, *campo;

  	str = readline(fp);
	if(str == NULL)
		return NULL;

  	CABECALHO_LINHA *cabecalho = (CABECALHO_LINHA * ) malloc(sizeof(CABECALHO_LINHA));

	//Cada campo é atribuido a sua devida variável
	//Processo feito destrinchando a linha lida a partir do caractere ','
	campo = strtok(str, ",");
	strcpy(cabecalho->descreveCodigo, campo);
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveCartao, campo);
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveNome, campo);	
	campo = strtok(NULL, ",");
	strcpy(cabecalho->descreveCor, campo);

	free(str);

	//As demais variáveis também são inicializadas
	cabecalho->status='0';
	cabecalho->byteProxReg=0;
	cabecalho->nroRegistros=0;
	cabecalho->nroRegRemovidos=0;

  	return cabecalho;
}

DADOS_LINHA *lerRegistroLinha (FILE *fp) {
	char *str, *campo;

	str = readline(fp);

	//Caso a leitura chegue no fim do arquivo, para a função
	if(str==NULL)
		return NULL;

	DADOS_LINHA *linha = (DADOS_LINHA *)malloc(sizeof(DADOS_LINHA));

	//Verifica se é removido e atribui corretamente o prefixo
	campo = strtok(str, ",");
	if(campo[0]=='*') {
		linha->removido = '0';
		linha->codLinha = atoi (&campo[1]);
	}
	else {
		linha->removido = '1';
		linha->codLinha = atoi (campo);
	}
	
	//Cada campo é atribuido a sua devida variável
	//Processo feito destrinchando a linha lida a partir do caractere ','
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
        linha->aceitaCartao = '\0';
	else	linha->aceitaCartao = campo[0];
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
		linha->tamanhoNome = 0;
	else{
		linha->tamanhoNome = strlen(campo);
		strncpy(linha->nomeLinha, campo, linha->tamanhoNome);
	}	
	campo = strtok(NULL, ",");
	if(strcmp(campo, "NULO")==0)
		linha->tamanhoCor = 0;
	else{
		linha->tamanhoCor = strlen(campo);
		strncpy(linha->corLinha, campo, linha->tamanhoCor);
	}

	free(str);

	//O tamanho do registro é calculado somando o tamanho dos campos variados e o tamanho dos campos fixos(13)
	linha->tamanhoRegistro = 13+linha->tamanhoCor+linha->tamanhoNome;

	return linha;
}


//leitura de dados para arquivo binario
DADOS_LINHA *recupera_dados_linha(FILE *arquivo){	
	DADOS_LINHA *dados = (DADOS_LINHA *) malloc(sizeof(DADOS_LINHA));

	//lendo o byte que diz se foi removido
	if(fread(&dados->removido, sizeof(char), 1, arquivo) == 0){
		//se n conseguir ler o primeiro campo significa que chegamos no fim do arquivo
		free(dados);
		return NULL;
	}

	//lendo o tamanho do registro
	fread(&dados->tamanhoRegistro, sizeof(int), 1, arquivo);

	//lendo o prefixo do veiculo
	fread(&dados->codLinha, sizeof(int), 1, arquivo);
		
	//lendo a data de entrada do veiculo na frota
	fread(&dados->aceitaCartao, sizeof(char), 1, arquivo);
		
	//lendo a qauntidade de lugares disponiveis do veiculo
	fread(&dados->tamanhoNome, sizeof(int), 1, arquivo);

	//lendo o codigo da linha
	fread(&dados->nomeLinha, sizeof(char), dados->tamanhoNome, arquivo);

	//lendo o tamanho do campo modelo
	fread(&dados->tamanhoCor, sizeof(int), 1, arquivo);

	//lendo o modelo do veiculo
	fread(&dados->corLinha, sizeof(char), dados->tamanhoCor, arquivo);

	return dados;
}


CABECALHO_LINHA *recupera_cabecalho_linha(FILE *arquivo) {
	CABECALHO_LINHA *c = (CABECALHO_LINHA *)malloc(sizeof(CABECALHO_LINHA));

	//Volta para o começo do arquivo, onde está o cabeçalho
	fseek(arquivo, 0, SEEK_SET);

	//Lê todos os dados e atribuí a variável correspondente
	fread(&c->status, sizeof(char), 1, arquivo);
	fread(&c->byteProxReg, sizeof(long long), 1, arquivo);
	fread(&c->nroRegistros, sizeof(int), 1, arquivo);
	fread(&c->nroRegRemovidos, sizeof(int), 1, arquivo);

	fread(&c->descreveCodigo, sizeof(char), 15, arquivo);
	fread(&c->descreveCartao, sizeof(char), 13, arquivo);
	fread(&c->descreveNome, sizeof(char), 13, arquivo);
	fread(&c->descreveCor, sizeof(char), 24, arquivo);

	return c;
}

//Utiliza da função scan_quote_string para ler os campos passados do usuário e depois atribui na
//	struct de dados da linha
DADOS_LINHA *leituraDoTecladoLinha() {
	char campo[100];

	DADOS_LINHA *linha = malloc(sizeof(DADOS_LINHA));
	
	//codLinha
	scan_quote_string(campo);
	if(strlen(campo) == 0) {
		free(linha);
		return NULL;
	}
	
	if(campo[0] == '*') {
		linha->removido = '0';
		linha->codLinha = atoi(&campo[1]);
	} 
	else {
		linha->removido = '1';
		linha->codLinha = atoi(campo);
		}

	//aceitaCartao
	scan_quote_string(campo);
	if(strcmp(campo, "") == 0){
		linha->aceitaCartao = '\0';
	}
	else
		linha->aceitaCartao = campo[0];

	//Nome da linha
	scan_quote_string(campo);
	if(strlen(campo) == 0)
		linha->tamanhoNome = 0;
	else{
		linha->tamanhoNome = strlen(campo);
		strncpy(linha->nomeLinha, campo, linha->tamanhoNome);
	}
	//corLinha
	scan_quote_string(campo);
	if(strlen(campo) == 0)
		linha->tamanhoCor = 0;
	else{
		linha->tamanhoCor = strlen(campo);
		strncpy(linha->corLinha, campo, linha->tamanhoCor);
	}	

	//O tamanho do registro é calculado somando o tamanho dos campos variados e o tamanho dos campos fixos(13)
	linha->tamanhoRegistro = 13 + linha->tamanhoNome + linha->tamanhoCor;
	
	return linha;
}