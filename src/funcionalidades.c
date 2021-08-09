#include "../include/funcionalidades.h"
#include "../include/structs.h"
#include "../include/btree.h"
#include "../include/leitura_e_escrita_btree.h"
#include "../include/auxiliares_btree.h"
#include "../include/escrita_veiculo.h"
#include "../include/escrita_linha.h"
#include "../include/leitura_veiculo.h"
#include "../include/leitura_linha.h"
#include "../include/funcao-fornecida.h"
#include "../include/auxiliares.h"


//A medida que lê os registros do csv vai escrevendo seus dados em um arquivo do nome desejado

void funcionalidade1 (FILE *csv, char *out_name) {
    //Abre o arquivo bin
    FILE *out = fopen(out_name, "wb");
    if(out == NULL) {
    	printf("Falha no processamento do arquivo.\n");
		fclose(csv);
    	exit(0);
    }

    //Lê os dados do cabecalho
    CABECALHO_VEICULO * c=lerCabecalhoVeiculo(csv);
	if(c == NULL) {
    	printf("Falha no processamento do arquivo.\n");
		fclose(csv);
		exit(0);
	}

    DADOS_VEICULO *registro;
    //Mantém o status do arquivo a escrever em 0
    c->status='0';

    //Escreve o status
    fwrite(&c->status, 1, 1, out);
    //Pula para a posição do 1° registro
    fseek(out, 175, SEEK_SET);

    //Loop para ler e escrever cada registro até o fim do csv
    for(registro = lerRegistroVeiculo(csv); registro!=NULL ; registro = lerRegistroVeiculo(csv)){
        //Imprime o registro lido
        toBinRegistroVeiculo(registro, out);
        //Adiciona na variável do cabeçalho que conta o n° de registros
        if(registro->removido=='1')
            c->nroRegistros++;
        else    c->nroRegRemovidos++;
        
        //Desaloca o atual registro para leitura do proximo
        free(registro);
    }
    //Guarda a posição atual do arquivo binário como disponivel para inserção de um novo registro
    c->byteProxReg=ftell(out);

    //Volta para o início do arquivo e escreve o cabeçalho
    fseek(out, 0, SEEK_SET);
    toBinCabecalhoVeiculo(c, out);

    //Muda o status para 1
    c->status = '1';
    fseek(out, 0, SEEK_SET);
    fwrite(&c->status, 1, 1, out);

    //Libera o cabeçalho e o arquivo
    free(c);
	fclose(out);
	
	fclose(csv);
}


//A medida que lê os registros do csv vai escrevendo seus dados em um arquivo do nome desejado
void funcionalidade2 (FILE *csv, char *out_name) {
    //Abre o arquivo bin
    FILE *out = fopen(out_name, "wb");
    if(out == NULL) {
    	printf("Falha no processamento do arquivo.\n");
		//Fecha o arquivo e finaliza o programa
		fclose(csv);
    	exit(0);
    }

    //Lê os dados do cabecalho
    CABECALHO_LINHA * c=lerCabecalhoLinha(csv);
	if(c == NULL) {
    	printf("Falha no processamento do arquivo.\n");
		//Fecha o arquivo e finaliza o programa
		fclose(csv);
		exit(0);
	}
	
    DADOS_LINHA *registro;
    //Mantém o status do arquivo a escrever em 0
    c->status='0';

    //Escreve o status
    fwrite(&c->status, 1, 1, out);
    //Pula para a posição do 1° registro
    fseek(out, 82, SEEK_SET);

    //Loop para ler e escrever cada registro até o fim do csv
    for(registro = lerRegistroLinha(csv); registro!=NULL ; registro = lerRegistroLinha(csv)){
        //Imprime o registro lido
        toBinRegistroLinha(registro, out);
        //Adiciona na variável do cabeçalho que conta o n° de registros
        if(registro->removido=='1')
            c->nroRegistros++;
        else    c->nroRegRemovidos++;
        
        //Desaloca o atual registro para leitura do proximo
        free(registro);
    }
    //Guarda a posição atual do arquivo binário como disponivel para inserção de um novo registro
    c->byteProxReg=ftell(out);

    //Volta para o início do arquivo e escreve o cabeçalho
    fseek(out, 0, SEEK_SET);
    toBinCabecalhoLinha(c, out);

    //Muda o status para 1
    c->status = '1';
    fseek(out, 0, SEEK_SET);
    fwrite(&c->status, 1, 1, out);

    //Libera o cabeçalho e o arquivo
    free(c);
    fclose(out);
		fclose(csv);
}


//Percorre o arquivo binário printando seus registro
void funcionalidade3(FILE *arquivo){
	DADOS_VEICULO *registro;
	int verifica_existencia_do_registro = 0;
	char valor_status;

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo);
	if(valor_status == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo);
		exit(0);
	}

	//Pulando o cabecalho do arquivo = 175 bytes
	fseek(arquivo, 175, SEEK_SET); 
	
	//Loop para recuperar os dados e em seguida printar na tela
	do{
		registro = recupera_dados_veiculo(arquivo);

		if(registro != NULL && registro->removido != '0'){
			//Como o registro existe e não foi removido, podemos printar
			print_dados_veiculo(registro);
			verifica_existencia_do_registro = 1;
		}
		free(registro);
	}while(registro != NULL);

	if(verifica_existencia_do_registro == 0){
		printf("Registro inexistente.\n");
	}
	
	//Fechando o arquivo
	fclose(arquivo);
}


//Percorre o arquivo binário printando seus registro
void funcionalidade4(FILE *arquivo){
	DADOS_LINHA *registro;
	int verifica_existencia_do_registro = 0;
	char valor_status;

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo);
	if(valor_status == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo);
		exit(0);
	}

	//Pulando o cabecalho do arquivo == 82 bytes
	fseek(arquivo, 82, SEEK_SET); 
	
	//Loop para recuperar os dados e em seguida printar na tela
	do{
		registro = recupera_dados_linha(arquivo);

		if(registro != NULL && registro->removido != '0'){
			//Como o registro existe e não foi removido, podemos printar
			print_dados_linha(registro);
			verifica_existencia_do_registro = 1;
		}
		free(registro);
	}while(registro != NULL);

	if(verifica_existencia_do_registro == 0){
		printf("Registro inexistente.\n");
	}

	//Fechando o arquivo
	fclose(arquivo);
}

//Busca em cada registro a chave no campo determinados pelo usuário
void funcionalidade5(FILE *arquivo) {
	DADOS_VEICULO *registro;
	char nomeCampo[50], key[50];
	//Cada campo recebe um código, ex: prefixo = 1, modelo = 2 e etc.
	int codCampo = 0;
	int verifica_existencia_do_registro = 0;
	char valor_status;

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo);
	if(valor_status == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo);
		exit(0);
	}

	//Pulando o cabecalho do arquivo == 175 bytes
	fseek(arquivo, 175, SEEK_SET);

	//recebendo o nome do campo e a chave que o usuario deseja buscar
	scanf("%s", nomeCampo);
	scan_quote_string(key);

	//Convertendo o nomeCampo em codCampo
	if (strcmp(nomeCampo, "prefixo") == 0)
		codCampo = 1;
	else if (strcmp(nomeCampo, "data") == 0)
		codCampo = 2;
	else if (strcmp(nomeCampo, "quantidadeLugares") == 0)
		codCampo = 3;
	else if (strcmp(nomeCampo, "codLinha") == 0)
		codCampo = 4;
	else if (strcmp(nomeCampo, "modelo") == 0)
		codCampo = 5;
	else if (strcmp(nomeCampo, "categoria") == 0)
		codCampo = 6;

	do{
		registro = recupera_dados_veiculo(arquivo);

		if(registro != NULL && registro->removido != '0'){
			//Como o registro nao é nulo e nao foi removido, podemos verificar os campos
			if(buscaNoRegistroVeiculo(registro, codCampo, key)){
				//Encontramos o registro
				print_dados_veiculo(registro);
				verifica_existencia_do_registro = 1;
			}
		}
		//Liberando a memória
		free(registro);
	}while(registro != NULL);

	if(verifica_existencia_do_registro == 0){
		printf("Registro inexistente.\n");
	}
	
	//Fechando o arquivo
	fclose(arquivo);
}


//Busca em cada registro a chave no campo determinados pelo usuário
void funcionalidade6(FILE *arquivo) {
	DADOS_LINHA *registro;
	char nomeCampo[50], key[50];
	//Cada campo recebe um código, ex: codLinha = 1, aceitaCartao = 2 e etc.
	int codCampo = 0;
	int verifica_existencia_do_registro = 0;
	char valor_status;

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo);
	if(valor_status == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo);
		exit(0);
	}
	
	//Pulando o cabecalho do arquivo == 82 bytes
	fseek(arquivo, 82, SEEK_SET); 

	scan_quote_string(key);

	//Convertendo o nomeCampo em codCampo
	if (strcmp(nomeCampo, "codLinha") == 0)
		codCampo = 1;
	else if (strcmp(nomeCampo, "aceitaCartao") == 0)
		codCampo = 2;
	else if (strcmp(nomeCampo, "nomeLinha") == 0)
		codCampo = 3;
	else if (strcmp(nomeCampo, "corLinha") == 0)
		codCampo = 4;

	do{
		registro = recupera_dados_linha(arquivo);

		if(registro != NULL && registro->removido != '0'){
			//Como o registro não é nulo e nao foi removido, podemos verificar os campos
			if(buscaNoRegistroLinha(registro, codCampo, key)){
				//Encontramos o registro
				print_dados_linha(registro);
				verifica_existencia_do_registro = 1;
			}
		}
		free(registro);
	}while(registro != NULL);
	
	
	if(verifica_existencia_do_registro == 0){
		printf("Registro inexistente.\n");
	}
	
	//Fechando o arquivo
	fclose(arquivo);
}


void funcionalidade7(FILE *fp) {
	DADOS_VEICULO *dados;
	int n_registros, num_insercoes;
	char valor_status;
	long long byteProxReg;

	//Lendo o n° de registros que o usário quer inserir
	scanf("%d", &num_insercoes);

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, fp);
	if(valor_status == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		exit(0);
	}

	//Retornando para o início do arquivo
	fseek(fp, 0, SEEK_SET);

	//Mudando o status para 0
	fwrite("0", 1, 1, fp);
	//Pula o campo de byteProxReg no arquivo
	fseek(fp, 8, SEEK_CUR);
	//Obtém o número de registros antes das inserções
	fread(&n_registros, sizeof(int), 1, fp);

	//Pula para o fim do arquivo, onde serão feitas as inserções
	fseek(fp, 0, SEEK_END);

	for(int i = 0; i < num_insercoes; i++) {
		//Ler dados passados no teclado
		dados = leituraDoTecladoVeiculos();
		//Print dos dados no binário
		toBinRegistroVeiculo(dados, fp);
		
		free(dados);
	}

	//Obtendo o byte offset onde o proximo registro deve ser inserido
	byteProxReg = ftell(fp);

	//mudando para o campo do byteProxReg no cabeçalho do arquivo	
	fseek(fp, 1, SEEK_SET);
	
	//atualizando o byteProxReg do cabeçalho
	fwrite(&byteProxReg, sizeof(long long), 1, fp);
	
	//Atualiza o número de registros no arquivo
	n_registros += num_insercoes;
	fwrite(&n_registros, sizeof(int), 1, fp);

	//Mudando o status para 1 novamente
	fseek(fp, 0, SEEK_SET);
	fwrite("1", 1, 1, fp);
	
	//Fechando o arquivo
	fclose(fp);
}


void funcionalidade8(FILE *fp) {
	DADOS_LINHA *dados;
	int n_registros, n;
	char valor_status;
	long long byteProxReg;

	//Lendo o n° de registros que o usário quer inserir
	scanf("%d", &n);

	//verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, fp);
	if(valor_status == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		exit(0);
	}

	//Retornando para o início do arquivo
	fseek(fp, 0, SEEK_SET);
	
	//Mudando o status para 0
	fwrite("0", 1, 1, fp);
	//Pula o campo de byteProxReg no arquivo
	fseek(fp, 8, SEEK_CUR);
	//Obtém o número de registros antes das inserções
	fread(&n_registros, sizeof(int), 1, fp);

	//Pula para o fim do arquivo, onde serão feitas as inserções
	fseek(fp, 0, SEEK_END);


	for(int i = 0; i < n; i++) {
		//Ler dados passados no teclado
		dados = leituraDoTecladoLinha();
		//Print dos dados no binário
		toBinRegistroLinha(dados, fp);

		free(dados);
	}

	//Obtendo o byte offset onde o proximo registro deve ser inserido
	byteProxReg = ftell(fp);

	//mudando para o campo do byteProxReg no cabeçalho do arquivo	
	fseek(fp, 1, SEEK_SET);
	
	//atualizando o byteProxReg do cabeçalho
	fwrite(&byteProxReg, sizeof(long long), 1, fp);
	
	//Atualiza o número de registros no arquivo
	n_registros += n;
	fwrite(&n_registros, sizeof(int), 1, fp);

	//Mudando o status para 1 novamente
	fseek(fp, 0, SEEK_SET);
	fwrite("1", 1, 1, fp);

	//Fechando o arquivo
	fclose(fp);
}


void funcionalidade9(FILE *arquivo_veiculo, char *nome_btree){
	char valor_status;
	int chave;
	//inicia com 175 pois é  o byteOffset do primeiro registro
	long long byteOffset = 175;
	DADOS_VEICULO *registro;
	BTREE_CABECALHO *cabecalho_btree;

	//Cria um arquivo de índice árvore B binário
    FILE *btree_arquivo = fopen(nome_btree, "w+b");
    if(btree_arquivo == NULL) {
    	printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
    	exit(0);
    }

	//Verificando se o arquivo de veiculos está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_veiculo);
	if(valor_status == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		exit(0);
	}


	//Criando e escrevendo o cabeçalho da árvore B
	cabecalho_btree = (BTREE_CABECALHO *) malloc(sizeof(BTREE_CABECALHO));
	cabecalho_btree->status = '0';
	cabecalho_btree->noRaiz = -1;
	cabecalho_btree->RRNproxNo = -1;
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	//Pulando o cabecalho do arquivo de dados (veículos)
	fseek(arquivo_veiculo, 175, SEEK_SET);

	//Loop para ler cada registro do arquivo de dados e inserir na árvore B
	do {
		registro = recupera_dados_veiculo(arquivo_veiculo);

		if (registro != NULL && registro->removido != '0') {
			//Convertendo o prefixo na chave de inserção da árvore B
			chave = convertePrefixo(registro->prefixo);

			if (chave != -1) {
				//Insere na arvore B chamando a função driver
				//OBS.: os fwrites da árvore B estão contidos nessa função 
				driver(btree_arquivo, cabecalho_btree, chave, byteOffset);
			}
		}

		free(registro);
		//Obtendo o novo byteOffset do arquivo de dados
		byteOffset = ftell(arquivo_veiculo);
	} while (registro != NULL);

	//Mudando o status do arquivo para consistente (1)
	cabecalho_btree->status = '1';
	//Escrevendo o novo cabeçalho após todas as inserções
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	free(cabecalho_btree);
	fclose(arquivo_veiculo);
	fclose(btree_arquivo);
}

void funcionalidade10(FILE *arquivo_linha, char *nome_btree) {
	char valor_status;
	int chave;
	//inicia com 82 pois é  o byteOffset do primeiro registro
	long long byteOffset = 82;
	DADOS_LINHA *registro;
	BTREE_CABECALHO *cabecalho_btree;

	//Cria um arquivo de índice árvore B binário
	FILE *btree_arquivo = fopen(nome_btree, "w+b");
	if (btree_arquivo == NULL) {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_linha);
		exit(0);
	}

	//Verificando se o arquivo de linhas está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_linha);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_linha);
		exit(0);
	}


	//Criando e escrevendo o cabeçalho da árvore B
	cabecalho_btree = (BTREE_CABECALHO *)malloc(sizeof(BTREE_CABECALHO));
	cabecalho_btree->status = '0';
	cabecalho_btree->noRaiz = -1;
	cabecalho_btree->RRNproxNo = -1;
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	//Pulando o cabecalho do arquivo de dados (veículos)
	fseek(arquivo_linha, 82, SEEK_SET);

	//Loop para ler cada registro do arquivo de dados e inserir na árvore B
	do {
		registro = recupera_dados_linha(arquivo_linha);

		if (registro != NULL && registro->removido != '0') {
			//Convertendo o prefixo na chave de inserção da árvore B
			chave = registro->codLinha;

			if (chave != -1) {
				//Insere na arvore B chamando a função driver
				//OBS.: os fwrites da árvore B estão contidos nessa função
				driver(btree_arquivo, cabecalho_btree, chave, byteOffset);
			}
		}

		free(registro);
		//Obtendo o novo byteOffset do arquivo de dados
		byteOffset = ftell(arquivo_linha);

	} while (registro != NULL);

	//Mudando o status do arquivo para consistente (1)
	cabecalho_btree->status = '1';
	//Escrevendo o novo cabeçalho após todas as inserções
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	free(cabecalho_btree);
	fclose(arquivo_linha);
	fclose(btree_arquivo);
}


//procura por um registro no arquivo de dados dos veiculos dada a chave, usando um arquivo de indice (arvore B) para obter o byteOffset desse registro no arquivo de dados
void funcionalidade11(FILE *arquivo_veiculo, FILE *arquivo_btree){
	BTREE_CABECALHO *cabecalho;
	DADOS_VEICULO *registro_veiculo;
	char valor_status, valor_status_btree;
	char nomeCampo[50], key[50];
	long long byteoffset;

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_veiculo);
	fread(&valor_status_btree, sizeof(char), 1, arquivo_btree);
	if(valor_status == '0' || valor_status_btree == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		exit(0);
	}

	//recebendo o nome do campo e a chave que o usuario deseja buscar
	scanf("%s", nomeCampo);
	scan_quote_string(key);
	
	//lendo o cabecalho
	cabecalho = lerCabecalho_arvoreB(arquivo_btree);

	//iniciando a pesquisa da raiz da btree
	byteoffset = pesquisa_btree(arquivo_btree, convertePrefixo(key), cabecalho->noRaiz);

	//caso o registro não seja encontrado
	if(byteoffset == -1)
		printf("Registro inexistente.\n");
	else if(byteoffset == -2)
		printf("Falha no processamento do arquivo.\n");
	else{
		//posicionando o cursor no byteOffset do registro da chave buscada
		fseek(arquivo_veiculo, byteoffset, SEEK_SET);
	
		//le o registro buscado
		registro_veiculo = recupera_dados_veiculo(arquivo_veiculo);

		//caso o registro esteja marcado como removido
		if(registro_veiculo->removido == '0')
			printf("Registro inexistente.\n");
		else
			print_dados_veiculo(registro_veiculo);
		
		free(registro_veiculo);
	}

	free(cabecalho);
	fclose(arquivo_veiculo);
	fclose(arquivo_btree);
}


//procura por um registro no arquivo de dados das linhas dada a chave, usando um arquivo de indice (arvore B) para obter o byteOffset desse registro no arquivo de dados
void funcionalidade12(FILE *arquivo_linha, FILE *arquivo_btree){
	BTREE_CABECALHO *cabecalho;
	DADOS_LINHA *registro_linha;
	char valor_status, valor_status_btree;
	char nomeCampo[50];
	int key;
	long long byteoffset;

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_linha);
	fread(&valor_status_btree, sizeof(char), 1, arquivo_btree);
	if(valor_status == '0' || valor_status_btree == '0'){
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_linha);
		exit(0);
	}

	//recebendo o nome do campo e a chave que o usuario deseja buscar
	scanf("%s", nomeCampo);
	scanf("%d", &key);
	
	//lendo o cabecalho
	cabecalho = lerCabecalho_arvoreB(arquivo_btree);

	//iniciando a pesquisa da raiz da btree
	byteoffset = pesquisa_btree(arquivo_btree, key, cabecalho->noRaiz);

	//caso o registro não seja encontrado
	if(byteoffset == -1)
		printf("Registro inexistente.\n");
	else if(byteoffset == -2)
		printf("Falha no processamento do arquivo.\n");
	else{
		//posicionando o cursor no byteOffset do registro da chave buscada
		fseek(arquivo_linha, byteoffset, SEEK_SET);
	
		//le o registro buscado
		registro_linha = recupera_dados_linha(arquivo_linha);

		//caso o registro esteja marcado como removido
		if(registro_linha->removido == '0')
			printf("Registro inexistente.\n");
		else
			print_dados_linha(registro_linha);
		
		free(registro_linha);
	}

	free(cabecalho);
	fclose(arquivo_linha);
	fclose(arquivo_btree);
}


//A medida que lê dados de um novo registro passados pelo 'stdin' insere no arquivo .bin de dados e de índice
void funcionalidade13(FILE *arquivo_veiculo) {
	DADOS_VEICULO *dados;
	int n_registros, num_insercoes, chave, b_offset;
	char valor_status;
	char indice_nome[30];
	long long byteProxReg;
	BTREE_CABECALHO *cabecalho_btree;

	//Lendo o nome do arquivo de índice e o n° de registros que o usário quer inserir
	scanf("%s %d", indice_nome, &num_insercoes);

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_veiculo);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		exit(0);
	}

	FILE *btree_arquivo = fopen(indice_nome, "r+b");

	if(btree_arquivo == NULL) {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		exit(0);
	}

	//Retornando para o início do arquivo
	fseek(arquivo_veiculo, 0, SEEK_SET);

	//Mudando o status para 0
	fwrite("0", 1, 1, arquivo_veiculo);
	//Pula o campo de byteProxReg no arquivo
	fseek(arquivo_veiculo, 8, SEEK_CUR);
	//Obtém o número de registros antes das inserções
	fread(&n_registros, sizeof(int), 1, arquivo_veiculo);

	//Pula para o fim do arquivo de dados, onde serão feitas as inserções
	fseek(arquivo_veiculo, 0, SEEK_END);


	//Lendo o cabeçalho do arquivo de índice
	cabecalho_btree = lerCabecalho_arvoreB (btree_arquivo);
	//Verifica-se a integrudade do arquivo de índice
	if(cabecalho_btree->status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		fclose(btree_arquivo);
		free(cabecalho_btree);
		exit(0);
	}
	//Muda o status do arquivo de índice e escreve isso no arquivo também
	cabecalho_btree->status = '0';
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	//Loop roda o n° de inserções vezes
	for (int i = 0; i < num_insercoes; i++) {
		//Ler dados passados no teclado
		dados = leituraDoTecladoVeiculos();
		//Print dos dados no binário de dados
		toBinRegistroVeiculo(dados, arquivo_veiculo);
		//Adiciona na árvore B
		byteProxReg = ftell(arquivo_veiculo);
		//Obtendo o novo byteProxReg do arquivo de dados devido à inserção

		b_offset = byteProxReg - (dados->tamanhoRegistro + 5);
		//Calcula-se o byteoffset usando o byteoffset do registro de dados anterior, subtrai-se o tamanho do registro
		//  mais *cinco do byteoffset anterior
		// *mais cinco pois a variável tamanhoRegistro não contém 1 byte referente à "removido" e 4 bytes referente à
		//   tamanhoRegistro
		chave = convertePrefixo(dados->prefixo);
		//Obtém o byte offset do registro que foi lido e a chave para poder inserir na árvore B

		driver(btree_arquivo, cabecalho_btree, chave, b_offset);

		free(dados);
	}

	//Obtendo o byteOffset onde o próximo registro deve ser inserido
	byteProxReg = ftell(arquivo_veiculo);

	//Mudando para o campo do byteProxReg no cabeçalho do arquivo
	fseek(arquivo_veiculo, 1, SEEK_SET);

	//Atualizando o byteProxReg do cabeçalho
	fwrite(&byteProxReg, sizeof(long long), 1, arquivo_veiculo);

	//Atualiza o número de registros no arquivo
	n_registros += num_insercoes;
	fwrite(&n_registros, sizeof(int), 1, arquivo_veiculo);

	//Mudando o status para 1 novamente
	fseek(arquivo_veiculo, 0, SEEK_SET);
	fwrite("1", 1, 1, arquivo_veiculo);


	//Escrevendo o cabecalho na árvore B novamente
	cabecalho_btree->status = '1';
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	free(cabecalho_btree);
	//Fechando o arquivo
	fclose(arquivo_veiculo);
	fclose(btree_arquivo);

	//binarioNaTela da árvore B
	binarioNaTela(indice_nome);
}


//A medida que lê dados de um novo registro passados pelo 'stdin' insere no arquivo .bin de dados e de índice
void funcionalidade14(FILE *arquivo_linha) {
	DADOS_LINHA *dados;
	int n_registros, num_insercoes, chave, b_offset;
	char valor_status;
	char indice_nome[30];
	long long byteProxReg;
	BTREE_CABECALHO *cabecalho_btree;

	//Lendo o n° de registros que o usário quer inserir
	scanf("%s %d", indice_nome, &num_insercoes);

	//Verificando se o arquivo está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_linha);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_linha);
		exit(0);
	}

	FILE *btree_arquivo = fopen(indice_nome, "r+b");

	if (btree_arquivo == NULL) {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_linha);
		exit(0);
	}

	//Retornando para o início do arquivo
	fseek(arquivo_linha, 0, SEEK_SET);

	//Mudando o status para 0
	fwrite("0", 1, 1, arquivo_linha);
	//Pula o campo de byteProxReg no arquivo
	fseek(arquivo_linha, 8, SEEK_CUR);
	//Obtém o número de registros antes das inserções
	fread(&n_registros, sizeof(int), 1, arquivo_linha);

	//Pula para o fim do arquivo, onde serão feitas as inserções
	fseek(arquivo_linha, 0, SEEK_END);


	//Lendo o cabeçalho do arquivo de índice
	cabecalho_btree = lerCabecalho_arvoreB(btree_arquivo);
	//Verifica-se a integrudade do arquivo de índice
	if (cabecalho_btree->status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_linha);
		fclose(btree_arquivo);
		free(cabecalho_btree);
		exit(0);
	}
	//Muda o status do arquivo de índice e escreve isso no arquivo também
	cabecalho_btree->status = '0';
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	for (int i = 0; i < num_insercoes; i++) {
		//Ler dados passados no teclado
		dados = leituraDoTecladoLinha();
		//Print dos dados no binário de dados
		toBinRegistroLinha(dados, arquivo_linha);
		//Adiciona na árvore B
		byteProxReg = ftell(arquivo_linha);
		//Obtendo o novo byteProxReg do arquivo de dados devido à inserção

		b_offset = byteProxReg - (dados->tamanhoRegistro + 5);
		//Calcula-se o byteoffset usando o byteoffset do registro de dados anterior, subtrai-se o tamanho do registro
		//  mais *cinco do byteoffset anterior
		// *mais cinco pois a variável tamanhoRegistro não contém 1 byte referente à "removido" e 4 bytes referente à
		//   tamanhoRegistro
		chave = dados->codLinha;
		//Obtém o byte offset do registro que foi lido e a chave para poder inserir na árvore B

		driver(btree_arquivo, cabecalho_btree, chave, b_offset);

		free(dados);
	}

	//Obtendo o byteOffset onde o proximo registro deve ser inserido
	byteProxReg = ftell(arquivo_linha);

	//Mudando para o campo do byteProxReg no cabeçalho do arquivo
	fseek(arquivo_linha, 1, SEEK_SET);

	//Atualizando o byteProxReg do cabeçalho
	fwrite(&byteProxReg, sizeof(long long), 1, arquivo_linha);

	//Atualiza o número de registros no arquivo
	n_registros += num_insercoes;
	fwrite(&n_registros, sizeof(int), 1, arquivo_linha);

	//Mudando o status para 1 novamente
	fseek(arquivo_linha, 0, SEEK_SET);
	fwrite("1", 1, 1, arquivo_linha);

	//Escrevendo o cabecalho na árvore B novamente
	cabecalho_btree->status = '1';
	escreveCabecalho_arvoreB(btree_arquivo, cabecalho_btree);

	free(cabecalho_btree);
	//Fechando o arquivo
	fclose(arquivo_linha);
	fclose(btree_arquivo);

	//binarioNaTela da árvore B
	binarioNaTela(indice_nome);
}


void funcionalidade15(FILE *arquivo_veiculo, FILE *arquivo_linha){
	DADOS_VEICULO *registro_veiculo;
	DADOS_LINHA *registro_linha;
	int	verifica_existencia_do_registro = 0;
	char valor_status;
	char nome_campo[30], nome_campo2[30];

	//Lendo o nome do campo que está sendo utilizado para junção 
	scanf("%s %s", nome_campo, nome_campo2);

	//se os nomes dos campos forem diferentes ou forem diferentes de codLinha
	if(strcmp(nome_campo, nome_campo2) != 0 || strcmp(nome_campo, "codLinha") != 0){
		printf("Registro inexistente.\n");	
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
		exit(0);
	}

	//Verificando se o arquivo de veiculos está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_veiculo);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
		exit(0);
	}

	//Verificando se o arquivo de linhas está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_linha);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
		exit(0);
	}

	//Pulando o cabecalho do arquivo de veiculos == 175 bytes
	fseek(arquivo_veiculo, 175, SEEK_SET);

	
	//recuperando os registros
	do{
		registro_veiculo = recupera_dados_veiculo(arquivo_veiculo);
		
		if(registro_veiculo != NULL && registro_veiculo->removido != '0'){
			//Pulando o cabecalho do arquivo de linhas == 82 bytes
			fseek(arquivo_linha, 82, SEEK_SET);
			do{
				registro_linha = recupera_dados_linha(arquivo_linha);
		
				if(registro_linha != NULL && registro_linha->removido != '0'){
					//verificando se dá pra fazer a junção
					if(registro_veiculo->codLinha == registro_linha->codLinha){
						//faz a junção
						print_dados_veiculo(registro_veiculo);
						print_dados_linha(registro_linha);
						printf("\n");
						verifica_existencia_do_registro = 1;
					}
				} 

				free(registro_linha);
			}while(registro_linha != NULL);
		}

		free(registro_veiculo);
	}while(registro_veiculo != NULL);


	if(verifica_existencia_do_registro == 0){
		printf("Registro inexistente.\n");
	}

	fclose(arquivo_veiculo);
	fclose(arquivo_linha);
}


void funcionalidade16(FILE *arquivo_veiculo, FILE *arquivo_linha){
	DADOS_VEICULO *registro_veiculo;	
	DADOS_LINHA *registro_linha;
	BTREE_CABECALHO *cabecalho;
	char valor_status;
	char nome_campo[30], nome_campo2[30], nome_arquivo_indices[40];
	FILE *fp_indices;
	long long byteoffset;
	int verifica_existencia_do_registro = 0;

	//Lendo o nome do campo que está sendo utilizado para junção 
	scanf("%s %s %s", nome_campo, nome_campo2, nome_arquivo_indices);

	//se os nomes dos campos forem diferentes ou forem diferentes de codLinha
	if(strcmp(nome_campo, nome_campo2) != 0 || strcmp(nome_campo, "codLinha") != 0){
		printf("Registro inexistente.\n");	
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
		exit(0);
	}

	//abrindo o arquivo de indices para leitura
	scanf("%s", nome_arquivo_indices);
	fp_indices = fopen(nome_arquivo_indices, "r+b");
    if (fp_indices == NULL) {
        printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
        exit(0);
    }	

	//Verificando se o arquivo de veiculos está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_veiculo);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
		fclose(fp_indices);
		exit(0);
	}

	//Verificando se o arquivo de linhas está com status 0
	fread(&valor_status, sizeof(char), 1, arquivo_linha);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
		fclose(fp_indices);
		exit(0);
	}

	//Verificando se o arquivo de indices está com status 0
	fread(&valor_status, sizeof(char), 1, fp_indices);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculo);
		fclose(arquivo_linha);
		fclose(fp_indices);
		exit(0);
	}

	//Pulando o cabecalho do arquivo de veiculos == 175 bytes
	fseek(arquivo_veiculo, 175, SEEK_SET);

	//recuperando os registros
	do{
		registro_veiculo = recupera_dados_veiculo(arquivo_veiculo);
		
		if(registro_veiculo != NULL && registro_veiculo->removido != '0'){
			//lendo o cabeçalho da btree
			cabecalho = lerCabecalho_arvoreB(fp_indices);

			byteoffset = pesquisa_btree(fp_indices, registro_veiculo->codLinha, cabecalho->noRaiz);

			//caso de erro na pesquisa
			if(byteoffset == -2)
				printf("Falha no processamento do arquivo.\n");
			else if(byteoffset != -1){
				//posicionando o cursor no byteOffset do registro da chave buscada
				fseek(arquivo_linha, byteoffset, SEEK_SET);
	
				//le o registro buscado
				registro_linha = recupera_dados_linha(arquivo_linha);

				//caso o registro esteja marcado como removido
				if(registro_linha->removido != '0'){
					//fazendo a junção
					verifica_existencia_do_registro = 1;
					print_dados_veiculo(registro_veiculo);
					print_dados_linha(registro_linha);
					printf("\n");
				}
				
				free(registro_linha);
			}
			free(cabecalho);
		}

		free(registro_veiculo);
	}while(registro_veiculo != NULL);

	
	if(verifica_existencia_do_registro == 0){
		printf("Registro inexistente.\n");
	}

	fclose(arquivo_veiculo);
	fclose(arquivo_linha);
	fclose(fp_indices);
}


//A partir de um .bin de veículos desordenado gera um .bin ordenado e sem registros removidos
void funcionalidade17 (FILE *desordenado) {
	char status;
	char nome_ordenado[50], campo_chave[30];

	//Obtém-se as outras entradas pelo stdin
	scanf("%s %s", nome_ordenado, campo_chave);

	//Verifica se o campo digitado foi 'codLinha' e a integridade do arquivo desordenado
	if( strcmp(campo_chave, "codLinha") != 0 || desordenado == NULL) {
		printf("Falha no processamento do arquivo.\n");
		fclose(desordenado);
		exit(0);
	}

	fread(&status, sizeof(char), 1, desordenado);
	if(status != '1') {
		printf("Falha no processamento do arquivo.\n");
		fclose(desordenado);
		exit(0);
	}

	//Usa a função ordenaVeiculo para gerar o arquivo desejado
	FILE *arquivo_ordenado = ordenaVeiculo(desordenado, nome_ordenado);

	//Fecham os arquivos
	fclose(desordenado);
	fclose(arquivo_ordenado);

	binarioNaTela(nome_ordenado);
}


//A partir de um .bin de linhas desordenado gera um .bin ordenado e sem registros removidos
void funcionalidade18(FILE *desordenado)
{
	char status;
	char nome_ordenado[50], campo_chave[30];

	//Obtém-se as outras entradas pelo stdin
	scanf("%s %s", nome_ordenado, campo_chave);

	//Verifica se o campo digitado foi 'codLinha' e a integridade do arquivo desordenado
	if (strcmp(campo_chave, "codLinha") != 0 || desordenado == NULL)
	{
		printf("Falha no processamento do arquivo.\n");
		fclose(desordenado);
		exit(0);
	}

	fread(&status, sizeof(char), 1, desordenado);
	if (status != '1')
	{
		printf("Falha no processamento do arquivo.\n");
		fclose(desordenado);
		exit(0);
	}

	//Usa a função ordenaLinha para gerar o arquivo desejado
	FILE *arquivo_ordenado = ordenaLinha(desordenado, nome_ordenado);

	//Fecham os arquivos
	fclose(desordenado);
	fclose(arquivo_ordenado);

	binarioNaTela(nome_ordenado);
}

//Obtém a interceção de dois arquivos (um de veículos outro de linhas) fazendo a comparação dos códigos de linha
//E depois imprime essa interceção
void funcionalidade19(FILE *arquivo_veiculos, FILE *arquivo_linhas) {
	DADOS_VEICULO *registro_veiculo;
	DADOS_LINHA *registro_linha;
	int verifica_existencia_do_registro = 0;
	char valor_status;
	char nome_campo[30], nome_campo2[30];
	FILE *veiculos_ordenado;
	FILE *linhas_ordenado;

	//Verificando se o arquivo de veiculos está com status 1
	fread(&valor_status, sizeof(char), 1, arquivo_veiculos);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculos);
		fclose(arquivo_linhas);
		exit(0);
	}

	//Verificando se o arquivo de linhas está com status 1
	fread(&valor_status, sizeof(char), 1, arquivo_linhas);
	if (valor_status == '0') {
		printf("Falha no processamento do arquivo.\n");
		fclose(arquivo_veiculos);
		fclose(arquivo_linhas);
		exit(0);
	}
	
	//Lendo o nome do campo que está sendo utilizado para junção 
	scanf("%s %s", nome_campo, nome_campo2);

	//se os nomes dos campos forem diferentes ou forem diferentes de codLinha
	if(strcmp(nome_campo, nome_campo2) != 0 || strcmp(nome_campo, "codLinha") != 0){
		printf("Registro inexistente.\n");	
		fclose(arquivo_veiculos);
		fclose(arquivo_linhas);
		exit(0);
	}

	//Ordenando os arquivos de dados
	veiculos_ordenado = ordenaVeiculo(arquivo_veiculos, "aux_veiculos_ordenado.bin");
	linhas_ordenado = ordenaLinha(arquivo_linhas, "aux_linha_ordenado.bin");

	//Pulando o cabeçalho dos arquivos de dados	
	fseek(veiculos_ordenado, 175, SEEK_SET);
	fseek(linhas_ordenado, 82, SEEK_SET);

	//Obtendo os primeiros registros dos arquivo ordenados
	registro_veiculo = recupera_dados_veiculo(veiculos_ordenado);
	registro_linha = recupera_dados_linha(linhas_ordenado);

	//Loop até o fim de algum dos arquivos
	while(registro_linha != NULL && registro_veiculo!= NULL) {	
		
		//Testa o match
		if (registro_linha->codLinha == registro_veiculo->codLinha){
			//Se houve match, faz a junção (print)
			print_dados_veiculo(registro_veiculo);
			print_dados_linha(registro_linha);
			printf("\n");
			verifica_existencia_do_registro = 1;

			//Após fazer a junção pega o novo registro de veículos, pois pode haver mais de um veículo associado a mesma linha
			free(registro_veiculo);
			registro_veiculo = recupera_dados_veiculo(veiculos_ordenado);
		}
		else if(registro_linha->codLinha > registro_veiculo->codLinha) {
			//Se não houve match e o código da linha é maior, então anda no registro de veículos
			free(registro_veiculo);
			registro_veiculo = recupera_dados_veiculo(veiculos_ordenado);
		}
		else {
			//Se não houve match e o código do veículo é maior, então anda no registro de linhas
			free(registro_linha);
			registro_linha = recupera_dados_linha(linhas_ordenado);
		}
	}

	//Verifica se houve alguma junção
	if(verifica_existencia_do_registro == 0){
		printf("Registro inexistente.\n");
	}

	//Libera os dados da heap
	free(registro_veiculo);
	free(registro_linha);

	fclose(veiculos_ordenado);
	fclose(linhas_ordenado);
	fclose(arquivo_veiculos);
	fclose(arquivo_linhas);
}