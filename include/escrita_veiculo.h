#ifndef ESCRITA_VEICULO_H_
	#define ESCRITA_VEICULO_H_

	//Imprime todos os dados da struct no arquivo de saída (usualmente o .bin)
	//PARÂMETROS:
	//	1) struct referente ao dado que será impresso no arquivo
	//	2) FILE *arquivo: ponteiro para o arquivo em que deseja realizar a impressão
	void toBinRegistroVeiculo (DADOS_VEICULO *registro, FILE *out);
	void toBinCabecalhoVeiculo (CABECALHO_VEICULO *c, FILE *out);


	//Printa a data na forma: (dia) de (mês em extenso) de (ano)
	//PARÂMETROS:
	//	char *data: string da data no formato: AAAA-MM-DD
	void print_data(char *data);


	//Printa todos os dados do registro de dados do veiculo 
	//PARÂMETROS:
	//	DADOS_VEICULO *registro_veiculo: struct do registro de dados do veiculo
	void print_dados_veiculo(DADOS_VEICULO *registro_veiculo);
	

#endif 