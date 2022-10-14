/*
 ============================================================================
 Nome      : entrada.c
 Autor     : Daniel Carlier, Phillipe Secondo e Gustavo Braga
 Descrição : Lê código fonte de um arquivo .txt e imprime vetor de registro
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_REG 40
#define NMAX 31
#define TRUE 1
#define FALSE 0

char letra[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char digito[] = {'0','1','2','3','4','5','6','7','8','9'};
char especial[] = {'+','-','*','/','<','<=','>','>=', '=', '==', '!=','/*','*/', ';', '{', '}', '.', '(', ')'};
int lenLetraArray = 52;
int lenDigitoArray = 10;
int lenEspecialArray = 18;
int foundComent = FALSE;

typedef enum // Definem os token da linguagem C-- adaptada
	{RESERVADA, SIMBOLO, ERRO, ID, NUMINT, NUMFLOAT}
	TokenTipo;

typedef struct
	{ TokenTipo tokenVal;
	  char *stringValor;
	  int tokenProxPos;
	} TokenRegistro;

TokenRegistro registro[MAX_REG];

FILE *fp;

TokenTipo getToken(int pos,char linha[NMAX], int nToken, int k);

int main(void) {
	char cadeia[NMAX];
	int prox, nToken=0, tamCadeia;

	if ((fp=fopen ("codigofonte.txt","rt")) != NULL)
		while (fgets(cadeia,NMAX,fp)!=NULL){
			prox = 0;
			tamCadeia = strlen(cadeia);
			while (prox<tamCadeia){
				getToken(prox,cadeia,nToken,tamCadeia);
				prox = registro[nToken].tokenProxPos;
				nToken++;
			}
		}


	printf("===================================\n");
	for (int i=0;i<nToken;i++){
		printf("REGISTRO: %i\n",i);
		printf("%i\n",registro[i].tokenVal);
		printf("%s\n",registro[i].stringValor);
		printf("%i\n",registro[i].tokenProxPos);
		printf("===================================\n");
	}

	fclose(fp);
	return EXIT_SUCCESS;
}

// charIsInArray Verifica se um determinado char está no array
int charIsInArray(char charToBeFound, char array[], int lenArray) {
	for(int i = 0; i < lenArray; i++) {
		if (charToBeFound == array[i]) {
			return TRUE;
		}
	}
	return FALSE;
}

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
            if (!strcmp(tokenString, ".")){
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
        returnValue = NUMFLOAT;
    }

	// Verifica se alguma condição é verdadeira, caso seja é um erro
	if(foundLetraOnString && foundEspecialOnString || foundDigitoOnString && foundEspecialOnString || foundDigitoOnFirst && foundLetraOnString || foundDigitoOnFirst && foundEspecialOnString) {
		returnValue = ERRO;
	}

	// Verifica palavras RESERVADAS ou caracteres ESPECIAIS ou SIMBOLO ou NUMINT ou ID.
    if (!strcmp(tokenString, "else") || !strcmp(tokenString, "if") || !strcmp(tokenString, "int") || !strcmp(tokenString, "float") || !strcmp(tokenString, "return")|| !strcmp(tokenString, "void")|| !strcmp(tokenString, "while")|| !strcmp(tokenString, "main")){
		returnValue = RESERVADA;
	} else if (!strcmp(tokenString, "+") || !strcmp(tokenString, "-") || !strcmp(tokenString, "*") || !strcmp(tokenString, "/") || !strcmp(tokenString, "=") || !strcmp(tokenString, "<") || !strcmp(tokenString, "<=") || !strcmp(tokenString, ">") || !strcmp(tokenString, ">=") || !strcmp(tokenString, "==") || !strcmp(tokenString, "!=") || !strcmp(tokenString, "/*") || !strcmp(tokenString, "*/") || !strcmp(tokenString, "*/\n") || !strcmp(tokenString, ";\n") || !strcmp(tokenString, "{\n") || !strcmp(tokenString, "}\n") || !strcmp(tokenString, ".") || !strcmp(tokenString, "(") || !strcmp(tokenString, ")") || !strcmp(tokenString, "(\n") || !strcmp(tokenString, ")\n")) {
		returnValue = SIMBOLO;
	} else if (foundDigitoOnString && !foundLetraOnString && !foundEspecialOnString){
		returnValue = NUMINT;
	} else if (foundLetraOnString && !foundDigitoOnFirst){
		returnValue = ID;
	}

	return returnValue;
}

TokenTipo getToken(int pos,char linha[NMAX], int nToken, int k){
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
            foundComent = FALSE;
            tokenValor[j] = linha[i];
            j++;
            tokenValor[j] = linha[i+1];
			i++;
			j++;
        } else if (foundComent == TRUE) {
			continue;
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
