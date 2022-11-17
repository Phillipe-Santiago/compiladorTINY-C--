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
#include "analiseSintatica.h"
#include "geraRegistro.h"
#define MAX_REG 100

TokenRegistro registro[MAX_REG];
int tokenProximo = 0;
char *num[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
char *idt[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
char *oplog[] = {">","<","==","!=", "<=", ">="};
char *oparitm[] = {"+","-","*","/"};

int main(void) {
    // Análise léxica
	arrayToken();

	// Análise Sintática
	programa(0);

    printf("Programa compilado\n");
	return EXIT_SUCCESS;
}

// arrayToken obtem uma lista Registro de tokens
void arrayToken(void){
    char path[256];
    printf("Insira caminho do arquivo a ser lido como codigo fonte\n");
    scanf("%s", &path);

	// Array de tokens produzido na análise léxica
    GetRegistroDeTokens(path, registro, 1);

    // Verifica existência de erros léxicos antes da análise sintática
    int foundError = 0;
    for(int i = 0; i < MAX_REG; i++) {
        if(registro[i].tokenVal == 2) {
            erroLexico(registro[i]);
            foundError = 1;
        }
    }

    if (foundError) {
        printf("Um ou mais erros lexicos foram encontrados\n");
        exit(1);
    }
}

// 
// =======================================
// Início da análise recursiva descendente
// =======================================
// 

void soma(int token){
	if(!strcmp(registro[token].stringValor,"+") ||
    !strcmp(registro[token].stringValor,"-")){
        casamento(registro[token].stringValor);
    }
}

void whileDecl(int token){
    if(!strcmp(registro[token].stringValor,"while")){
        casamento("while");
        expr(tokenProximo);
        casamento("{\n");
        declSequencia(tokenProximo);
        casamento("}\n");
    }
}

void tipoIdt(int token) {
    if (!strcmp(registro[token].stringValor, "int") ||
    !strcmp(registro[token].stringValor, "float") ||
    !strcmp(registro[token].stringValor, "void")) {
        casamento(registro[token].stringValor);
    } 
}

void varDecl(int token) {
    param(token);
}

void param(int token) {
    tipoIdt(token);
    casamento(registro[tokenProximo].stringValor);
}

void paramLista(int token) {
    if (!strcmp(registro[tokenProximo + 1].stringValor,",")) {
        paramLista(token);
        casamento(",");
        param(tokenProximo);
    } else {
        param(token);
    }
}

void parametros(int token) {
    if (!strcmp(registro[token].stringValor, "void")) {
        casamento("void");
    } else {
        paramLista(token);
    }
}

void funDecl(int token) {
    tipoIdt(token);
    casamento(registro[tokenProximo].stringValor);
    casamento("(");
    parametros(tokenProximo);
    casamento(")");
}

void fun(int token) {
    funDecl(token);
    casamento("{\n");
    if (!strcmp(registro[tokenProximo + 1].stringValor,"return")) {
        declSequencia(tokenProximo);
        casamento("return");
        casamento(registro[tokenProximo].stringValor);
    } else {
        declSequencia(tokenProximo);
    }
    casamento("}\n");
}

void listaFun(int token) {
    if(registro[tokenProximo + 1].tokenVal == 3) {
        fun(token);
        if(!strcmp(registro[tokenProximo + 1].stringValor, "main")) {
            return;
        } else {
            fun(tokenProximo);
        }
    }
}

void ifDecl(int token){ 
    if (!strcmp(registro[token].stringValor,"if")){
        casamento("if");
		expr(tokenProximo);
		casamento("{\n");
        declSequencia(tokenProximo);
        casamento("}\n");
        if (strcmp(registro[tokenProximo].stringValor,"else")==0){
			casamento("else");
            casamento("{\n");
            declSequencia(tokenProximo);
            casamento("}\n");
		}
    }
}

void atribuicaoDecl(int token){
    if (registro[token].tokenVal == 3){
		casamento(registro[token].stringValor);
        casamento("=");
        expr(tokenProximo);
    }
}

void comparacao(int token) {
    if (!strcmp(registro[token].stringValor, "<")){
        casamento("<");
    } else if (!strcmp(registro[token].stringValor, ">")) {
        casamento(">");
    } else if (!strcmp(registro[token].stringValor, "==")) {
        casamento("==");
    } else if (!strcmp(registro[token].stringValor, "!=")) {
        casamento("!=");
    } else if (!strcmp(registro[token].stringValor, ">=")) {
        casamento(">=");
    } else if (!strcmp(registro[token].stringValor, "<=")) {
        casamento("<=");
    } 
}

void fator(int token) {
    if (!strcmp(registro[token].stringValor, "(")) {
        casamento("(");
        expr(tokenProximo);
        casamento(")");
    } else if (registro[token].tokenVal == 4 || registro[token].tokenVal == 5) {
        casamento(registro[token].stringValor);
    } else if (registro[token].tokenVal == 3) {
        casamento(registro[token].stringValor);
    } 
}

void programa(int token) {
    listaFun(token);
    if (!strcmp(registro[tokenProximo + 1].stringValor, "main") &&
    !strcmp(registro[tokenProximo + 2].stringValor, "(") &&
    !strcmp(registro[tokenProximo + 3].stringValor, ")") &&
    !strcmp(registro[tokenProximo + 4].stringValor, "{\n")) {
        tipoIdt(tokenProximo);
        casamento("main");
        casamento("(");
        casamento(")");
        casamento("{\n");
        declSequencia(tokenProximo);
        casamento("}\n");
    }
}

void printDecl(int token){
    if (!strcmp(registro[token].stringValor, "print")) {
        casamento("print");
        expr(tokenProximo);
    } 
}

void declSequencia(int token) {
    declaracao(token);
    
    if (!strcmp(registro[tokenProximo].stringValor, ";\n")) {
        casamento(";\n");
        if(strcmp(registro[tokenProximo].stringValor, "}\n")) {
            declSequencia(tokenProximo);
        }
    }
}

void mult(int token){
    if(!strcmp(registro[token].stringValor, "*") || !strcmp(registro[token].stringValor, "/")) {
        casamento(registro[token].stringValor);
    } 
}

void termo(int token) {
	if(!strcmp(registro[tokenProximo].stringValor, "*") || !strcmp(registro[tokenProximo].stringValor, "/")) {
		fator(token);
		mult(tokenProximo);
		fator(tokenProximo);
	} else {
		fator(token);
	}
}

void simplesExp(int token) {
    if(!strcmp(registro[tokenProximo + 1].stringValor, "+") || !strcmp(registro[tokenProximo + 1].stringValor, "-")) {
        termo(token);
        soma(tokenProximo);
        termo(tokenProximo);
    } else {
        termo(token);
    }
}

void readDecl(int token) {
	if(!strcmp(registro[token].stringValor, "read")) {
		casamento("read");
		if(registro[tokenProximo].tokenVal == 3) {
			casamento(registro[tokenProximo].stringValor);
		}
	} 
}

void declaracao(int token) {
    if (!strcmp(registro[token].stringValor, "if")){
        ifDecl(tokenProximo);
    } else if (!strcmp(registro[token].stringValor, "while")) {
        whileDecl(tokenProximo);
    } else if (!strcmp(registro[token].stringValor, "read")) {
        readDecl(tokenProximo);
    } else if (!strcmp(registro[token].stringValor, "print")) {
        printDecl(tokenProximo);
    } else if (registro[token].tokenVal == 3) {
        atribuicaoDecl(tokenProximo);
    } else if (!strcmp(registro[token].stringValor, "int") || !strcmp(registro[token].stringValor, "float") || !strcmp(registro[token].stringValor, "void")) {
        varDecl(token);
    } 
}

void declIf (int token){
	if (strcmp(registro[token].stringValor,"if")==0){
		casamento("if");
		casamento("(");
		expr(tokenProximo);
		casamento(")");
		declaracao(tokenProximo);
		if (strcmp(registro[tokenProximo].stringValor,"else")==0){
			casamento("else");
			declaracao(tokenProximo);
		}
	}
}

void expr(int token){
    simplesExp(token);
    if (testaPertence(registro[tokenProximo].stringValor,oplog,6)){
        comparacao(tokenProximo);
        simplesExp(tokenProximo);
    }
}

// 
// =======================================
// Fim da análise recursiva descendente
// =======================================
// 

// casamento tem como objetivo comparar o token esperado com o recebido
void casamento(char *tokenEsperado){
	if (strcmp(registro[tokenProximo].stringValor,tokenEsperado)==0){
		tokenProximo++;
	}
	else
		erro(tokenEsperado);
}

// testaPertence tem como objetivo encontrar um caracter em um conjunto
int testaPertence(char *c, char *conjunto[], int n){
		// Busca sequencial
		int flag=0;
		for(int i=0;i<n;i++)
			if (strcmp(c,conjunto[i])==0)
				flag = 1;
		return flag;
}

// erro tem como objetivo tratar casos de erro sintático
void erro(char *tokenEsperado){
    FILE *fptr;

   	fptr = fopen("listaErro.txt","a");
	if(fptr == NULL) {
    	printf("Error!");   
      	exit(1);             
   	}

    fprintf(fptr, "Erro na coluna: %d\n", registro[tokenProximo].tokenProxPos);
    fprintf(fptr, "Token recebido: %s\n", registro[tokenProximo].stringValor);
    fprintf(fptr, "Token esperado: %s\n", tokenEsperado);
    fprintf(fptr, "%s", "===================================\n");
    fclose(fptr);

	tokenProximo++; // Avança na análise
}

// erroLexico tem como objetivo tratar casos de erro léxico
void erroLexico(TokenRegistro registro){
    FILE *fptr;

   	fptr = fopen("listaErro.txt","a");
	if(fptr == NULL) {
    	printf("Error!");   
      	exit(1);             
   	}

    fprintf(fptr, "Erro lexico na coluna: %d\n", registro.tokenProxPos);
    fprintf(fptr, "Token invalido: %s\n", registro.stringValor);
    fprintf(fptr, "%s", "===================================\n");
    fclose(fptr);
}
