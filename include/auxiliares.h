#ifndef AUXILIARES_H_
    #define AUXILIARES_H_
    
	//Realiza a leitura de linha de um arquivo qualquer
	//PARÂMETROS: 
	//	FILE *arquivo: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	//	ponteiro para a string contendo a linha lida
    char *readline(FILE *arquivo);


	//Printa o lixo definido(\0@@@@@@) no arquivo desejado
	//PARÂMETROS: 
	//	1) FILE *arquivo: ponteiro para o arquivo em que deseja realizar a impressão do lixo
	//	2) int tamanho: numero de bytes do lixo
    void printLixo(FILE *file, int tamanho);

	//Busca a chave no campo determinado pelo codigo_campo no registro de dados do veiculo 
	//PARÂMETROS:
	//	1) DADOS_VEICULO *registro -> ponteiro para a struct de dados do veiculo 
	//	2) int codigo_campo -> código do campo a ser buscado
	//	3) char *key -> string da chave a ser buscada
	//RETORNO:
	//	1 -> Retorna 1 se encontrar
	// 	0 -> Retorna 0 se não encontrar
	int buscaNoRegistroVeiculo(DADOS_VEICULO *registro, int codigo_campo, char *key);


	//Busca a chave no campo determinado pelo codigo_campo no registro de dados da linha 
	//PARÂMETROS:
	//	1) DADOS_LINHA *registro: ponteiro para a struct de dados da linha 
	//	2) int codigo_campo: código do campo a ser buscado
	//	3) char *key: string da chave a ser buscada
	//RETORNO:
	//	1 -> Retorna 1 se encontrar
	// 	0 -> Retorna 0 se não encontrar
	int buscaNoRegistroLinha(DADOS_LINHA *registro, int codigo_campo, char *key);

	//Cria um arquivo binário ordenado e sem registros removidos de veículos e retorna o ponteiro para ele
	//PARÂMETROS:
	//	1) FILE *desordenado: ponteiro para o arquivo .bin desordenado base 
	//	2) char *nome_ordenado: string do nome do arquivo ordenado que será criado
	//RETORNO: 
	//	ponteiro para o arquivo ordenado criado
	FILE *ordenaVeiculo(FILE *desordenado, char *nome_ordenado);
	

	//Cria um arquivo binário ordenado e sem registros removidos de linhas e retorna o ponteiro para ele
	//PARÂMETROS:
	//	1) FILE *desordenado: ponteiro para o arquivo .bin desordenado base 
	//	2) char *nome_ordenado: string do nome do arquivo ordenado que será criado
	//RETORNO: 
	//	ponteiro para o arquivo ordenado criado
	FILE *ordenaLinha(FILE *desordenado, char *nome_ordenado);


#endif