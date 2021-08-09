//Alunos:
//Ádrio Oliveira Alves - nºUSP: 11796830
//Eduardo Vinicius Barbosa Rossi - nºUSP: 10716887

#include <stdio.h>
#include <stdlib.h>
#include "include/structs.h"
#include "include/funcionalidades.h"
#include "include/funcao-fornecida.h"

//OBS.: os fclose serão feitos dentro das funcionalidades

int main(void){
    FILE *fp, *fp2, *fp3;
	FILE *fp_btree;
    short in;
    char inName[40], outName[40], inName2[40];
	char inBtreeName[40];

    //lendo a funcionalidade e o nome do arquivo de entrada
    scanf("%hd", &in);
	scanf("%s", inName);
	
	//funcionalidade 1
    if (in==1) {
    	scanf("%s", outName);
    	
		//abrindo o arquivo de entrada com o modo de leitura
    	fp = fopen(inName, "r");
    	if(fp == NULL) {
        	printf("Falha no processamento do arquivo.\n");
        	return 0;
    	}
        funcionalidade1(fp, outName);
		binarioNaTela(outName);
    }
    //funcionalidade 2
	else if(in==2) {
    	scanf("%s", outName);
        
        //abrindo o arquivo de entrada com o modo de leitura
    	fp = fopen(inName, "r");
    	if(fp == NULL) {
        	printf("Falha no processamento do arquivo.\n");
        	return 0;
    	}
        funcionalidade2(fp, outName);
		binarioNaTela(outName);
    }
    //funcionalidade 3
	else if(in == 3){
        //abrindo o arquivo de entrada com o modo de leitura em binario
        fp = fopen(inName, "rb");
        if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
		funcionalidade3(fp);
    }
    //funcionalidade 4
    else if(in == 4){
        //abrindo o arquivo de entrada com o modo de leitura em binario
        fp = fopen(inName, "rb");
        if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        funcionalidade4(fp);
    }
    //funcionalidade 5
	else if(in == 5){
        //abrindo o arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
		funcionalidade5(fp);
	}
	//funcionalidade 6
	else if(in == 6){
        //Abrindo o arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
		funcionalidade6(fp);
	}
	//funcionalidade 7
	else if(in == 7){
		//Abrindo o arquivo de entrada com o modo de leitura para binário
		fp = fopen(inName, "r+b");
		if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
		funcionalidade7(fp);
		binarioNaTela(inName);
	}
	//funcionalidade 8
	else if(in == 8){
		//Abrindo o arquivo de entrada com o modo de leitura para binário 
		fp = fopen(inName, "r+b");
		if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
		funcionalidade8(fp);
		binarioNaTela(inName);
	}
	//funcionalidade 9
	else if(in == 9){
		scanf("%s", outName);
		
		//Abrindo o arquivo de entrada com o modo de leitura para binário
		fp = fopen(inName, "rb");
		if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
		funcionalidade9(fp, outName);
		binarioNaTela(outName);
	}
	//funcionalidade 9
	else if(in == 9){
		scanf("%s", outName);
		
		//Abrindo o arquivo de entrada com o modo de leitura para binário
		fp = fopen(inName, "rb");
		if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
		funcionalidade9(fp, outName);
		binarioNaTela(outName);
    }
    //funcionalidade 10
    else if (in == 10) {
        scanf("%s", outName);

        //Abrindo o arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        funcionalidade10(fp, outName);
        binarioNaTela(outName);
    }
    else if(in == 11){
		//Abrindo o arquivo de entrada de veiculos com o modo de leitura para binário
		fp = fopen(inName, "rb");
		if(fp == NULL){
        printf("Falha no processamento do arquivo.\n");
        return 0;
    }

		scanf("%s", inBtreeName);
		//Abrindo o arquivo de entrada da btree com o modo de leitura para binário
		fp_btree = fopen(inBtreeName, "rb");
		if(fp_btree == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

		funcionalidade11(fp, fp_btree);
	}
	else if(in == 12){
		//Abrindo o arquivo de entrada de linhas com o modo de leitura para binário
		fp = fopen(inName, "rb");
		if(fp == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

		scanf("%s", inBtreeName);
		//Abrindo o arquivo de entrada da btree com o modo de leitura para binário
		fp_btree = fopen(inBtreeName, "rb");
		if(fp_btree == NULL){
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

		funcionalidade12(fp, fp_btree);
	}
	//funcionalidade 13
    else if (in == 13) {
        //Abrindo o arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "r+b");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        funcionalidade13(fp);
    }
    //funcionalidade 14
    else if (in == 14) {
        //Abrindo o arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "r+b");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        funcionalidade14(fp);
    }
	//funcionalidade 15
    else if (in == 15) {
        //Abrindo os arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

		scanf("%s", inName2);
		fp2 = fopen(inName2, "rb");
        if (fp2 == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        funcionalidade15(fp, fp2);
    }
	//funcionalidade 16
    else if (in == 16) {
        //Abrindo os arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

		scanf("%s", inName2);
		fp2 = fopen(inName2, "rb");
        if (fp2 == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

		
        funcionalidade16(fp, fp2);
    }
    //funcionalidade 17
    else if (in == 17) {
        //Abrindo o arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        funcionalidade17(fp);
    }
    //funcionalidade 18
    else if (in == 18) {
        //Abrindo o arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }
        funcionalidade18(fp);
    }
	//funcionalidade 19
    else if (in == 19) {
        //Abrindo os arquivo de entrada com o modo de leitura para binário
        fp = fopen(inName, "rb");
        if (fp == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

		scanf("%s", inName2);
		fp2 = fopen(inName2, "rb");
        if (fp2 == NULL) {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        funcionalidade19(fp, fp2);
    }
    else {
        printf("Operacao invalida\n");
        //fecha o programa
        return 0;
    }

	
    
    return 0;
}