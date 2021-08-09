#ifndef ESCRITA_LINHA_H_
	#define ESCRITA_LINHA_H_

	//Escreve todos os dados da struct no arquivo de saída (usualmente o .bin)
	//PARÂMETROS:
	//	1) struct referente ao dado que será printado
	//	2) Arquivo onde será escrito (normalmente o .bin)
	void toBinRegistroLinha (DADOS_LINHA *registro, FILE *out);
	void toBinCabecalhoLinha (CABECALHO_LINHA *c, FILE *out);


	//Escreve na saída padrão os dados referentes a cada código/letra que representa 
	//	sobre a aceitação de cartão da linha
	//PARÂMETROS: 
	// char aceita_cartao -> campo da struct da linha que representa o código sobre a 
	//							aceitação de cartão
	void print_aceita_cartao(char aceita_cartao);


	//Escreve na saída padrão todos os dados de um registro de linha
	//PARÂMETROS: 
	//	DADOS_LINHA *registro_linha -> ponteiro para a struct de dados de registro de 
	//									linha a ser escrita
	void print_dados_linha(DADOS_LINHA *registro_linha);
	
#endif