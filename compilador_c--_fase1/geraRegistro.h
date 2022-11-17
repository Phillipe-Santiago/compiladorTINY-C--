typedef enum // Definem os token da linguagem C-- adaptada
	{RESERVADA, SIMBOLO, ERRO, ID, NUMINT, NUMFLOAT}
	TokenTipo;

// TokenRegistro é a estrutura de dados responsável pela lista de tokens lidos
typedef struct
	{ TokenTipo tokenVal;
	  char *stringValor;
	  int tokenProxPos;
	} TokenRegistro;

extern TokenRegistro * GetRegistroDeTokens(char* pathDoArquivo, TokenRegistro *registro, int print);