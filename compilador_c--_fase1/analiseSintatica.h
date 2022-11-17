void arrayToken(void); // Simula o array de token
void casamento(char *tokenEsperado); // Casa o token seguinte e avança a entrada de tokens
int testaPertence(char *c, char *conjunto[], int n);
void erro(char *tokenEsperado);

// 
// =======================================
// Início da análise recursiva descendente
// =======================================
// 

void declaracao(int token); // Executa a análise descendente no ramo da abstração termo
void declIf(int token); // Executa a análise descendente no ramo da abstração fator
void expr(int token); // Executa a análise descendente no ramo da abstração exp
void termo(int token);
void comparacao(int token);
void fator(int token);
void programa(int token);
void declaracao(int token);
void printDecl(int token);
void atribuicaoDecl(int token);
void readDecl(int token);
void whileDecl(int token);
void ifDecl(int token);
void declSequencia(int token);
void simplesExp(int token);
void mult(int token);
void listaFun(int token);
void fun(int token);
void funDecl(int token);
void tipoIdt(int token);
void varDecl(int token);
void param(int token);
void paramLista(int token);
void parametros(int token);
void soma(int token);

// 
// =======================================
// Fim da análise recursiva descendente
// =======================================
// 
