/*
 ============================================================================
 Nome      : entradaCodigo.c
 Autor     : Prof Clayton J A Silva - Compiladores princípios e práticas, Louden K
 Descrição : Lê código fonte de um arquivo .txt
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_REG 40
#define NMAX 31

char* RESERVADAS[] = {"else", "if", "int", "float", "return", "void", "while", "main"};
char* SIMBOLOS[] = {"+", "-", "*", "/", "=", "<", ">", "(", "(\n", ")", ")\n", ";", ";\n", "{", "{\n", "}", "}\n", "<=", "==", ">=", "!=", ".", "/*", "*/", "*/\n"};
char DIGITOS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char LETRAS[] =  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','u','v','w','x','y','z', 
                    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','U','V','W','X','Y','Z'};
int TAM_RESERVADAS = 8;
int TAM_SIMBOLOS = 25;
int TAM_DIGITOS = 10;
int TAM_LETRAS = 50;

int comentario = 0;

typedef enum // Definem os token da linguagem TINY adaptada
	{RESERVADA,SIMBOLO,ID,NUMINT,NUMFLOAT}
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
		while (fgets(cadeia,NMAX,fp) != NULL){
			prox = 0;
			tamCadeia = strlen(cadeia);
			while (prox<tamCadeia){
				if (cadeia[prox] == '/' && cadeia[prox + 1] == '*'){
					comentario = 1;
					prox += 2;
				} else if (comentario == 1) {
					if (cadeia[prox] == '*' && cadeia[prox + 1] == '/' && cadeia[prox + 2] == '\n') {
						comentario = 0;
						prox += 3;
					} else if (cadeia[prox] == '*' && cadeia[prox + 1] == '/') {
						comentario = 0;
						prox += 2;
					} else {
						prox += 1;
					}
				} else {
					getToken(prox,cadeia,nToken,tamCadeia);
					prox = registro[nToken].tokenProxPos;
					nToken++;
				}
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
	printf("DIGITE ENTER PARA ENCERRAR ");
	getch();
	return EXIT_SUCCESS;
}

int isPalavraReservada(char* palavra) {

	for (int i = 0; i < TAM_RESERVADAS; i++) {
		if (strcmp(palavra, RESERVADAS[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int isLetra(char letra) {
	
	for (int i = 0; i < TAM_LETRAS; i++) {
		if (letra == LETRAS[i]) {
			return 1;
		}
	}
	return 0;
}

int isDigito(char digito) {

	for (int i = 0; i < TAM_DIGITOS; i++) {
		if (digito == DIGITOS[i]) {
			
			return 1;
		}
	}
	return 0;
}

int isSimbolo(char* simbolo) {

	for (int i = 0; i < TAM_SIMBOLOS; i++) {
		if (strcmp(simbolo, SIMBOLOS[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int getDFA(char* tokenVal) {
	int count = 0;
	int estado = 0;

	/*
	Estados:
	0 - START
	1 - RESERVADA
	2 - SIMBOLO
	3 - ID 
	4 - NUMINT
	5 - NUMFLOAT
	6 - COMENTARIO
	*/

	if (isPalavraReservada(tokenVal)) {
		return RESERVADA;
	} else if (isSimbolo(tokenVal)) {
		return SIMBOLO;
	}
	while (tokenVal[count] != '\0'){
		if (comentario == 1) {
			count++;
			continue;
		}else if (count == 0) {
			if (isLetra(tokenVal[count])) {
				estado = 3;
			} else if (isDigito(tokenVal[count])) {
				estado = 4;
			}
		}

		else {
			switch (estado){
				case 3: //ID
					if (!isDigito(tokenVal[count]) && !isLetra(tokenVal[count])) {
						return -1;
					}
					break;
				
				case 4: //NUMINT
					if (tokenVal[count] == '.') { // Se for . muda estado para NUMFLOAT
						estado = 5;
					} else if (!isDigito(tokenVal[count])) { // Não digito retorna ERRO
						return -1;
					}
					break;

				case 5: //NUMFLOAT
					if (!isDigito(tokenVal[count])) {
						return -1;
					}
					break;
			}
		}

		count++;
	}

	//printf("ESTADO: %d\n\n", estado);
	switch (estado) {

		case 3:
			return ID;
			break;
		case 4:
			return NUMINT;
		case 5:
			return NUMFLOAT;
			break;
		default:
			return -1;
			break;
	}
}


TokenTipo getToken(int pos,char linha[NMAX], int nToken, int k){
	int i,j=0;
	char tokenValor[NMAX];

	for (i=pos;i<k;i++){
		
		if (linha[i]!=' '){
			tokenValor[j] = linha[i];
			j++;
		}
		else break;
	}
	tokenValor[j] = '\0';
	registro[nToken].tokenVal = getDFA(tokenValor);

	if (registro[nToken].tokenVal == -1) {
		printf("Erro\n\n");
	}
	registro[nToken].stringValor = malloc(NMAX*sizeof(char));
	strcpy(registro[nToken].stringValor,tokenValor);
	registro[nToken].tokenProxPos = i+1;

	return registro[nToken].tokenVal;
}