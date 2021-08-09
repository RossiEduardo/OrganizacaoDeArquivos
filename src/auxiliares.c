#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/leitura_veiculo.h"
#include "../include/escrita_veiculo.h"
#include "../include/leitura_linha.h"
#include "../include/escrita_linha.h"


//Lê uma linha do arquivo desejado
char *readline(FILE *arquivo){
    char *string = NULL;
    int pos = 0;
    do{
		//Aloca dinamicamente a string
        if (pos % 4096 == 0){
            string = (char *) realloc(string, pos + 4960);
        }
	//fscanf de um char, testa se o caractere não é o fim da linha e o fim do arquivo
	//Caso seja o fim do arquivo, acaba o loop
    } while(fscanf(arquivo, "%c", &string[pos]) == 1 && string[pos] != '\n' && ++pos);

	//Caso a leitura não ocorreu corretamente (ou seja, chegou ao fim do arquivo), retorna-se NULL
    if (pos == 0)  {
      free(string);
      return NULL;
    }

	if(string[pos-1]=='\r')
		string[pos-1] = '\0';

    string[pos] = '\0';

	//Realoca a string para um tamanho ótimo
    string = (char *)realloc(string, pos + 1);

    return string;
}

void printLixo(FILE *file, int tamanho) {
	char barraZero = '\0';
	char arroba = '@';

	//Imprime o '\0'
	fwrite (&barraZero, 1, 1, file);
	//Loop para imprimir os '@'
	for (int i=0; i<tamanho-1; i++)
		fwrite (&arroba, 1, 1, file);
}


//Switch case para o código campo e depois compara
int buscaNoRegistroVeiculo(DADOS_VEICULO *registro, int codigo_campo, char *key){
	//Compara com o campo que coincide com o código do campo

	//Se a key concidir com o campo retorna 1
	switch(codigo_campo) {
		case 1: //prefixo
			if(strncmp(registro->prefixo, key, 5) == 0)
				return 1;
			break;

		case 2: //data
			if(strncmp(registro->data, key, 10) == 0)
				return 1;
			break;

		case 3: //quantidade de lugares
			if(registro->quantidadeLugares == atoi(key))
				return 1;
			break;

		case 4: //codigo linha
			if(registro->codLinha == atoi(key))
				return 1;
			break;

		case 5: //modelo
			if(registro->tamanhoModelo!=0 && strncmp(registro->modelo, key,
			 registro->tamanhoModelo) == 0)
				return 1;
			break;

		case 6: //categoria
			if(registro->tamanhoCategoria!=0 && strncmp(registro->categoria, key, registro->tamanhoCategoria)==0)
				return 1;
			break;
	}

	return 0;
}


int buscaNoRegistroLinha(DADOS_LINHA *registro, int codigo_campo, char *key) {
	//Se a key concidir com o campo retorna 1
	switch(codigo_campo) {
		case 1: //codigo linha
			if(registro->codLinha == atoi(key))
				return 1;
			break;

		case 2: //aceita cartão
			if(registro->aceitaCartao == key[0])
				return 1;
			break;

		case 3: //nome linha
			if(registro->tamanhoNome!=0 && strncmp(registro->nomeLinha, key, 	registro->tamanhoNome)== 0) {
				printf("%s\n%d\n\n", registro->nomeLinha, registro->tamanhoNome);

				return 1;
			}

			break;

		case 4: //cor linha
			if(registro->tamanhoCor!=0 && strncmp(registro->corLinha, key, registro->tamanhoCor)== 0)
				return 1;
			break;
	}

	return 0;
}


//Função utilizada na qsort
int comparaVeiculos(const void *reg1, const void *reg2) {
	DADOS_VEICULO *A = *(DADOS_VEICULO **)reg1;
	DADOS_VEICULO *B = *(DADOS_VEICULO **)reg2;

	int comp = A->codLinha - B->codLinha;

	return comp;
}

//Lê todos os registros de dados e guarda num vetor, depois ordena esse vetor e escreve ele em um novo arquivo
//OBS.: Essa função não fecha o arquivo que retorna
FILE *ordenaVeiculo (FILE *desordenado, char *nome_ordenado) {
	DADOS_VEICULO *registro;
	DADOS_VEICULO **vetor;
	//vetor -> vetor em que será feita a ordenação
	int i=0, tamanho;

	//Abre o novo arquivo
	FILE *ordenado = fopen(nome_ordenado, "w+b");

	//Teste de integridade
	if(ordenado==NULL){
		printf("Falha no processamento do arquivo.\n");
		fclose(desordenado);
		exit(0);
	}

	//Obtém o cabeçalho do arquivo desordenado
	CABECALHO_VEICULO *c = recupera_cabecalho_veiculo(desordenado);

	//Aloca o vetor com tamanho igual ao n° de registros não removidos
	vetor = (DADOS_VEICULO **)malloc( (c->nroRegistros)*sizeof(DADOS_VEICULO *) );

	//Loop para cada registro no arquvio desordenado
	for(registro = recupera_dados_veiculo(desordenado); registro != NULL; registro = recupera_dados_veiculo(desordenado)) {
		//Verifica se o registro não é removido
		if(registro->removido != '0')
			//Se não for removido insere no vetor
			vetor[i++] = registro;
		else
			//Se for removido libera da memória
			free(registro);
	}

	//Tamanho final é igual ao índice do loop anterior
	tamanho = i;

	//Usa a função comparaVeiculos e qsort para ordenar vetor
	qsort(vetor, tamanho, sizeof(DADOS_VEICULO *), comparaVeiculos);

	//Define o status como 0
	c->status = 0;
	//Escreve um cabeçalho incompleto inicialmente
	toBinCabecalhoVeiculo(c, ordenado);
	//Loop para cada elemento de vetor
	for(i = 0; i<tamanho; i++) {
		//Escreve o elemento atual do vetor no arquivo
		toBinRegistroVeiculo( vetor[i], ordenado );
		free(vetor[i]);
	}

	//Obtém novos valores (agora corretos) do cabeçalho
	c->status = '1';
	c->byteProxReg = ftell(ordenado);
	c->nroRegistros = tamanho;
	c->nroRegRemovidos = 0;
	//Retorna ao início do arquivo ordenado e escreve o novo cabeçalho
	fseek(ordenado, 0, SEEK_SET);
	toBinCabecalhoVeiculo(c, ordenado);

	free(c);
	free(vetor);

	//Retorna o arquivo ordenado sem fechá-lo
	return ordenado;
}


//Função utilizada na qsort
int comparaLinhas(const void *reg1, const void *reg2) {
	DADOS_LINHA *A = *(DADOS_LINHA **)reg1;
	DADOS_LINHA *B = *(DADOS_LINHA **)reg2;

	int comp = A->codLinha - B->codLinha;

	return comp;
}

//Lê todos os registros de dados e guarda num vetor, depois ordena esse vetor e escreve ele em um novo arquivo
//OBS.: Essa função não fecha o arquivo que retorna
FILE *ordenaLinha(FILE *desordenado, char *nome_ordenado) {
	DADOS_LINHA *registro;
	DADOS_LINHA **vetor;
	//vetor -> vetor em que será feita a ordenação
	int i = 0, tamanho;

	//Abre o novo arquivo
	FILE *ordenado = fopen(nome_ordenado, "w+b");

	//Teste de integridade
	if (ordenado == NULL) {
		printf("Falha no processamento do arquivo.\n");
		fclose(desordenado);
		exit(0);
	}

	//Obtém o cabeçalho do arquivo desordenado
	CABECALHO_LINHA *c = recupera_cabecalho_linha(desordenado);

	//Aloca o vetor com tamanho igual ao n° de registros não removidos
	vetor = (DADOS_LINHA **)malloc((c->nroRegistros) * sizeof(DADOS_LINHA *));

	//Loop para cada registro no arquvio desordenado
	for (registro = recupera_dados_linha(desordenado); registro != NULL; registro = recupera_dados_linha(desordenado)) {
		//Verifica se o registro não é removido
		if (registro->removido != '0')
			//Se não for removido insere no vetor
			vetor[i++] = registro;
		else
			//Se for removido libera da memória
			free(registro);
	}

	//Tamanho final é igual ao índice do loop anterior
	tamanho = i;

	//Usa a função comparaLinhas e qsort para ordenar vetor
	qsort(vetor, tamanho, sizeof(DADOS_LINHA *), comparaLinhas);

	//Define o status como 0
	c->status = '0';
	//Escreve um cabeçalho incompleto inicialmente
	toBinCabecalhoLinha(c, ordenado);
	//Loop para cada elemento de vetor
	for (i = 0; i < tamanho; i++) {
		//Escreve o elemento atual do vetor no arquivo
		toBinRegistroLinha(vetor[i], ordenado);
		free(vetor[i]);
	}

	//Obtém novos valores (agora corretos) do cabeçalho
	c->status = '1';
	c->byteProxReg = ftell(ordenado);
	c->nroRegistros = tamanho;
	c->nroRegRemovidos = 0;
	//Retorna ao início do arquivo ordenado e escreve o novo cabeçalho
	fseek(ordenado, 0, SEEK_SET);
	toBinCabecalhoLinha(c, ordenado);

	free(c);
	free(vetor);

	//Retorna o arquivo ordenado sem fechá-lo
	return ordenado;
}
