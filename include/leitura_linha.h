#ifndef LEITURA_LINHA_H_
	#define LEITURA_LINHA_H_

	//Lê a primeira linha do arquivo csv de linhas e atribui os valores lidos aos campos da struct CABECALHO_LINHA
	//PARAMETROS:
	//	FILE *fp: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	// ponteiro para a struct CABECALHO_LINHA
	CABECALHO_LINHA *lerCabecalhoLinha (FILE *fp);
	
	
	//Lê a linha do arquivo csv de linhas e atribui os valores lidos aos campos da struct DADOS_LINHA
	//PARAMETROS:
	//	FILE *fp: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	// ponteiro para a struct DADOS_LINHA
	DADOS_LINHA *lerRegistroLinha (FILE *fp);


	//Lê a linha do arquivo BINARIO de linhas e atribui os valores lidos aos campos da struct DADOS_LINHA
	//PARAMETROS:
	//	FILE *arquivo: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	// ponteiro para a struct DADOS_LINHA
	DADOS_LINHA *recupera_dados_linha(FILE *arquivo);
	
	
	//Lê o cabecalho do arquivo BINARIO de linhas e atribui os valores lidos aos campos da struct CABECALHO_LINHA
	//PARAMETROS:
	//	FILE *arquivo: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	//  ponteiro para a struct CABECALHO_LINHA
	CABECALHO_LINHA *recupera_cabecalho_linha(FILE *arquivo);

	
	//Recebe os dados do stdin passados pelo usuário e atribui às variáveis da struct de dados da linha
	//RETORNO :
	//	DADOS_LINHA * -> ponteiro para a struct obtida
	DADOS_LINHA *leituraDoTecladoLinha();

#endif