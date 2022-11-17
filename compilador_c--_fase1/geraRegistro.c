/*
Disciplina: Linguagens Formais e Compiladores
Professor: Clayton J A Silva
Alunos: Gustavo Braga,
        Daniel Carlier,
        João Pedro Martinez,
        Phillipe Santiago,
        Henrique Sartori.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geraRegistro.h"
#define MAX_REG 100
#define NMAX 31
#define TRUE 1
#define FALSE 0

char letra[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char digito[] = {'0','1','2','3','4','5','6','7','8','9'};
char especial[] = {',', '+','–','*','/','<','<=','>','>=', '=', '==', '!=','/*','*/', ';', '{', '}', '.', '(', ')'};
int lenLetraArray = 52;
int lenDigitoArray = 10;
int lenEspecialArray = 20;
int foundComent = FALSE;

FILE *fp;

TokenTipo getToken(int pos,char linha[NMAX], int nToken, int k, TokenRegistro *registro);

// Declaração dos diferentes tipos de token
char *getTokenValType(TokenRegistro tokenRegistro) {
	switch (tokenRegistro.tokenVal)
	{
	case RESERVADA:
		return "RESERVADA";
		break;
	case SIMBOLO:
		return "SIMBOLO";
		break;
	case ID:
		return "ID";
		break;
	case NUMINT:
		return "NUMINT";
		break;
	case NUMFLOAT:
		return "NUMFLOAT";
		break;
	
	default:
		return "ERRO";
		break;
	}
}

void imprimeRegistroDeTokens(TokenRegistro *registro, int nToken) {
	FILE *fptr;

   	fptr = fopen("listaTokens.txt","w");
	if(fptr == NULL) {
    	printf("Error!");   
      	exit(1);             
   	}

	fprintf(fptr, "%s", "===================================\n");
	for (int i=0;i<nToken;i++){
		fprintf(fptr, "REGISTRO: %i\n",i);
		fprintf(fptr, "%s\n", getTokenValType(registro[i]));
		fprintf(fptr, "%s\n",registro[i].stringValor);
		fprintf(fptr, "%i\n",registro[i].tokenProxPos);
		fprintf(fptr, "%s", "===================================\n");
	}
   		fclose(fptr);
}

// GetRegistroDeTokens lê o código fonte de um arquivo e retorna uma estrutura de registro
TokenRegistro * GetRegistroDeTokens(char* pathDoArquivo, TokenRegistro * registro, int print) {
	char cadeia[NMAX];
	int prox, nToken=0, tamCadeia;

	if ((fp=fopen (pathDoArquivo,"rt")) != NULL)
		while (fgets(cadeia,NMAX,fp)!=NULL){
			prox = 0;
			tamCadeia = strlen(cadeia);
			while (prox<tamCadeia){
				getToken(prox,cadeia,nToken,tamCadeia, registro);
				prox = registro[nToken].tokenProxPos;
				nToken++;
			}
		}

	if (print)
		imprimeRegistroDeTokens(registro, nToken);

	fclose(fp);
	return registro;
}

// charIsInArray verifica se um caractere está dentro de um vetor de caracteres
int charIsInArray(char charToBeFound, char array[], int lenArray) {
	for(int i = 0; i < lenArray; i++) {
		if (charToBeFound == array[i]) {
			return TRUE;
		}
	}
	return FALSE;
}

// getNFA atribui aos tokens os diferentes tipos presentes na convenção da linguagem
TokenTipo getNFA(char* tokenString) {
	int foundDigitoOnString = FALSE;
	int foundEspecialOnString = FALSE;
	int foundLetraOnString = FALSE;
    int foundDigitoOnFirst = FALSE;
    int dotCount = 0;
	TokenTipo returnValue = ERRO;

	for(unsigned int i = 0; i < strlen(tokenString); i++) {
		// Verifica se há um número no meio ou final de uma variável, o que gera um ERRO
		int foundDigito = charIsInArray(tokenString[i], digito, lenDigitoArray);
        if(foundDigito == TRUE && i == 0){
            foundDigitoOnFirst = TRUE;
        }

		if (foundDigito == TRUE) {
			foundDigitoOnString = TRUE;
		}

		// Verifica se há um especial no meio ou final de uma variável, o que gera um ERRO
		int foundEspecial = charIsInArray(tokenString[i], especial, lenEspecialArray);
		if (foundEspecial == TRUE) {
			for(int i = 0; i < strlen(tokenString); i++) {
				if (tokenString[i] == '.')
					dotCount++;
			}
			foundEspecialOnString = TRUE;
		}

		int foundLetra = charIsInArray(tokenString[i], letra, lenLetraArray);
		if (foundLetra == TRUE) {
			foundLetraOnString = TRUE;
		}
	}

    
    //Verifica exclusivamente NUMFLOAT
    if(foundDigitoOnFirst && foundDigitoOnString && !foundLetraOnString && dotCount == 1){
        return NUMFLOAT;
    }

	// Verifica se alguma condição é verdadeira, caso seja é um erro
	if(foundLetraOnString && foundEspecialOnString || foundDigitoOnString && foundEspecialOnString || foundDigitoOnFirst && foundLetraOnString || foundDigitoOnFirst && foundEspecialOnString) {
		returnValue = ERRO;
	}

	// Verifica palavras RESERVADAS ou caracteres ESPECIAIS ou SIMBOLO ou NUMINT ou ID.
    if (!strcmp(tokenString, "else") || !strcmp(tokenString, "if") || !strcmp(tokenString, "int") || !strcmp(tokenString, "float") || !strcmp(tokenString, "return")|| !strcmp(tokenString, "void")|| !strcmp(tokenString, "while")|| !strcmp(tokenString, "main")|| !strcmp(tokenString, "read")|| !strcmp(tokenString, "print")){
		returnValue = RESERVADA;
	} else if (!strcmp(tokenString, "+") || !strcmp(tokenString, "-") || !strcmp(tokenString, "*") || !strcmp(tokenString, "/") || !strcmp(tokenString, "=") || !strcmp(tokenString, "<") || !strcmp(tokenString, "<=") || !strcmp(tokenString, ">") || !strcmp(tokenString, ">=") || !strcmp(tokenString, "==") || !strcmp(tokenString, "!=") || !strcmp(tokenString, "/*") || !strcmp(tokenString, "*/") || !strcmp(tokenString, "*/\n") || !strcmp(tokenString, ";\n") || !strcmp(tokenString, "{\n") || !strcmp(tokenString, "}\n") || !strcmp(tokenString, "}") || !strcmp(tokenString, ".") || !strcmp(tokenString, "(") || !strcmp(tokenString, ")") || !strcmp(tokenString, "(\n") || !strcmp(tokenString, ")\n")|| !strcmp(tokenString, ",")) {
		returnValue = SIMBOLO;
	} else if (foundDigitoOnString && !foundLetraOnString && !foundEspecialOnString){
		returnValue = NUMINT;
	} else if (foundLetraOnString && !foundDigitoOnFirst){
		returnValue = ID;
	} 

	return returnValue;
}

// getToken adiciona à lista de registros os tokens lidos
TokenTipo getToken(int pos,char linha[NMAX], int nToken, int k, TokenRegistro *registro){
	int i,j=0;
	char tokenValor[NMAX];
    
	for (i=pos;i<k;i++){
        if (linha[i] == '/' && linha[i+1] == '*') {
            foundComent = TRUE;
            tokenValor[j] = linha[i];
			j++;
            tokenValor[j] = linha[i+1];
			i++;
            j++;
			break;
        } else if (linha[i] == '*' && linha[i+1] == '/') {
			char c = linha[i];
			char cc = linha[i+1];
            foundComent = FALSE;
            tokenValor[j] = linha[i];
            j++;
            tokenValor[j] = linha[i+1];
			i++;
			j++;
        } else if (foundComent == TRUE) {
			i++;
        } else if (linha[i] != ' ') {
            tokenValor[j] = linha[i];
            j++;
        } else break;
	}

	tokenValor[j] = '\0';
	registro[nToken].tokenVal = getNFA(tokenValor);
	registro[nToken].stringValor = malloc(20*sizeof(char));
	strcpy(registro[nToken].stringValor,tokenValor);
	registro[nToken].tokenProxPos = i+1;

	return registro[nToken].tokenVal;
}