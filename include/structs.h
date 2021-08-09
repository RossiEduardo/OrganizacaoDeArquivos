#ifndef STRUCTS_H_
    #define STRUCTS_H_

	//Define todas as struct de dados que serão usados nas funcionalidades
	//Os campos de tamanho variáveis são representados aqui como strings de tamanho 100

	typedef struct {
		char status;

		long long byteProxReg;
		int nroRegistros;
		int nroRegRemovidos;

		char descrevePrefixo[18];
		char descreveData[35];
		char descreveLugares[42];
		char descreveLinha[26];
		char descreveModelo[17];
		char descreveCategoria[20];
	}CABECALHO_VEICULO;

	typedef struct dados_veiculo {
		char removido;
		int tamanhoRegistro;
		
		char prefixo[5];
		char data[10];
		int quantidadeLugares;
		int codLinha;
		int tamanhoModelo;
		char modelo[100];
		int tamanhoCategoria;
		char categoria[100];
	} DADOS_VEICULO;

	typedef struct registro_de_cabecalho_linha{
		char status;

		long long int byteProxReg;
		int nroRegistros;
		int nroRegRemovidos;

		char descreveCodigo[15];
		char descreveCartao[13];
		char descreveNome[13];
		char descreveCor[24];

	}CABECALHO_LINHA; 

	typedef struct registro_de_dados_linha{
		char removido;
		int tamanhoRegistro;
		
		int codLinha;
		char aceitaCartao;
		int tamanhoNome;
		char nomeLinha[100];
		int tamanhoCor;
		char corLinha[100]; 
	} DADOS_LINHA;




////////////////STRUCTS DA BTREE/////////////

	typedef struct {
		char status;
		int noRaiz;
		int RRNproxNo;
	}BTREE_CABECALHO;


	typedef struct {
		char folha;
		int nroDeChavesIndexadas;
		int RRNdoNo;
		int P[5]; //Ponteiros
		int C[4]; //Chaves
		long long Pr[4]; //Referência para o arquivo de dados (RRN)
	}BTREE_NO;

#endif