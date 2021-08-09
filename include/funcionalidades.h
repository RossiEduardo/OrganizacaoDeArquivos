#ifndef FUNCIONALIDADES_H_
    #define FUNCIONALIDADES_H_
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	//OBS.: os fclose serão feitos dentro das funcionalidades
    
	//A medida que lê os registros do csv de veículos vai escrevendo seus dados em um 
	//	arquivo do nome desejado
	//PARÂMETROS:
	// 1) FILE *csv -> arquivo .csv
	// 2) char *out_name -> nome do arquivo a ser escrito com os dados (usualmente .bin)
    void funcionalidade1 (FILE *csv, char *out_name);


	//A medida que lê os registros do csv de linha vai escrevendo seus dados em um 
	//	arquivo do nome desejado
	//PARÂMETROS:
	// 1) FILE *csv -> arquivo .csv
	// 2) char *out_name -> nome do arquivo a ser escrito com os dados (usualmente .bin)
    void funcionalidade2 (FILE *csv, char *out_name);


	//A medida que lê o arquivo binário de veículos vai printando os dados do veículo na tela
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de veículos em que deseja realizar a leitura 
	void funcionalidade3(FILE *arquivo);


	//A medida que lê o arquivo binário de linhas vai printando os dados da linha na tela
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de linhas em que deseja realizar a leitura
	void funcionalidade4(FILE *arquivo);


	//A medida que lê o arquivo binário de veículos vai bsucando pelo campo com o mesmo valor passado, se encontrar printa os dados do veículo na tela
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de veículos em que deseja realizar a leitura
	void funcionalidade5(FILE *arquivo);


	//A medida que lê o arquivo binário de linhas vai busucando pelo campo com o mesmo valor passado, se encontrar printa os dados da linha na tela
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de linhas em que deseja realizar a leitura
	void funcionalidade6(FILE *arquivo);


	//Insere n registros passados pelo usário no fim do arquivo binário de veículos
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de veículos onde será feita a inserção
	void funcionalidade7(FILE *arquivo);


	//Insere n registros passados pelo usário no fim do arquivo binário de linhas
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de linhas onde será feita a inserção
	void funcionalidade8(FILE *arquivo);


	//Cria um arquivo de índice baseado na árvore-B do arquivo de dados passado
	//PARÂMETROS:
	//	FILE *arquivo_veiculo: ponteiro para o arquivo .bin de veículos que será usado de base para criar o
	//      arquivo de índice
	//	char *nome_btree: nome do arquivo .bin de índice que será criado
	void funcionalidade9(FILE *arquivo_veiculo, char *nome_btree);


	//Cria um arquivo de índice baseado na árvore-B do arquivo de dados passado
	//PARÂMETROS:
	//	FILE *arquivo_linha: ponteiro para o arquivo .bin de linhas que será usado de base para criar o
	//      arquivo de índice
	//	char *nome_btree: nome do arquivo .bin de índice que será criado
	void funcionalidade10(FILE *arquivo_linha, char *nome_btree);


	//Busca por uma chave passada pelo 'stdin' no arquivo índice passado, baseado na árvore B
	//PARÂMETROS:
	//	FILE *arquivo_veiculo: ponteiro para o arquivo .bin de veículos com os dados
	//	FILE *arquivo_btree: ponteiro para o arquivo .bin de índice baseado na árvore-B
	void funcionalidade11(FILE *arquivo_veiculo, FILE *arquivo_btree);


	//Busca por uma chave passada pelo 'stdin' no arquivo índice passado, baseado na árvore B
	//PARÂMETROS:
	//	FILE *arquivo_linha: ponteiro para o arquivo .bin de linhas com os dados
	//	FILE *arquivo_btree: ponteiro para o arquivo .bin de índice baseado na árvore-B
	void funcionalidade12(FILE *arquivo_linha, FILE *arquivo_btree);


	//Extensão da funcionalidade7, além das inserções no arquivo de dados, será inserida também a chave
	//  na árvore B
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de veículos onde será feita a inserção
	void funcionalidade13(FILE *arquivo_veiculo);
	

	//Extensão da funcionalidade8, além das inserções no arquivo de dados, será inserida também a chave
	//  na árvore B
	//PARÂMETROS:
	//	FILE *arquivo: ponteiro para o arquivo .bin de veículos onde será feita a inserção
	void funcionalidade14(FILE *arquivo_linha);


	//realiza a junção dos registros de dados de veículo e de linhas que possuem o mesmo valor para codLinha, utilizando o algoritmo de junção de loop aninhado
	//PARÂMETROS:
	//	FILE *arquivo_veiculo: ponteiro para o arquivo de dados de veículos
	//	FILE *arquivo_linha: ponteiro para o arquivo de dados de linha
	void funcionalidade15(FILE *arquivo_veiculo, FILE *arquivo_linha);


	//realiza a junção dos registros de dados de veículo e de linhas que possuem o mesmo valor para codLinha, utilizando o algoritmo de junção de loop único, através de um arquivo de indices(b-tree)
	//PARÂMETROS:
	//	FILE *arquivo_veiculo: ponteiro para o arquivo de dados de veículos
	//	FILE *arquivo_linha: ponteiro para o arquivo de dados de linha
	void funcionalidade16(FILE *arquivo_veiculo, FILE *arquivo_linha);


	//Cria um arquivo binário ordenado e sem registros removidos de veículos
	//PARÂMETROS:
	//	FILE *desordenado: ponteiro para o arquivo .bin de veículos que será usado como base para ordenação
	void funcionalidade17(FILE *desordenado);


	//Cria um arquivo binário ordenado e sem registros removidos de linhas
	//PARÂMETROS:
	//	FILE *desordenado: ponteiro para o arquivo .bin de linhas que será usado como base para ordenação
	void funcionalidade18(FILE *desordenado);


	//Faz a ordenação/intercalação de um arquivo binário de veículos com um binário de linhas e imprime essa intercalação
	//PARÂMETROS:
	//	FILE *veiculos: ponteiro para o arquivo .bin de veículos que vai ser ordenado/intercalado
	//	FILE *linhas: ponteiro para o arquivo .bin de linhas que vai ser ordenado/intercalado
	void funcionalidade19(FILE *veiculos, FILE *linhas);

#endif