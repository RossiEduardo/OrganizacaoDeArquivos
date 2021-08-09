#ifndef LEITURA_VEICULO_H_
	#define LEITURA_VEICULO_H_


	//Lê a primeira linha do arquivo csv de veículos e atribui os valores lidos aos campos da struct CABECALHO_VEICULO
	//PARAMETROS:
	//	FILE *fp: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	// ponteiro para a struct CABECALHO_VEICULO
	CABECALHO_VEICULO *lerCabecalhoVeiculo(FILE *fp);


	//Lê a linha do arquivo csv de veículos e atribui os valores lidos aos campos da struct CABECALHO_VEICULO
	//PARAMETROS:
	//	FILE *fp: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	// ponteiro para a struct CABECALHO_VEICULO
	DADOS_VEICULO *lerRegistroVeiculo(FILE *fp);


	//Lê a linha do arquivo BINARIO de veículos e atribui os valores lidos aos campos da struct DADOS_VEICULO
	//PARAMETROS:
	//	FILE *arquivo: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	// ponteiro para a struct DADOS_VEICULO
	DADOS_VEICULO *recupera_dados_veiculo(FILE *arquivo);	
	
	
	//Lê o cabecalho do arquivo BINARIO de veículos e atribui os valores lidos aos campos da struct CABECALHO_VEICULO
	//PARAMETROS:
	//	FILE *arquivo: ponteiro para o arquivo em que deseja realizar a leitura
	//RETORNO:
	//  ponteiro para a struct CABECALHO_VEICULO
	CABECALHO_VEICULO *recupera_cabecalho_veiculo(FILE *arquivo);


	//Recebe os dados do stdin passados pelo usuário e atribui às variáveis da struct de dados do veículo
	//RETORNO :
	//	DADOS_VEICULO * -> ponteiro para a struct obtida 
	DADOS_VEICULO *leituraDoTecladoVeiculos();

#endif