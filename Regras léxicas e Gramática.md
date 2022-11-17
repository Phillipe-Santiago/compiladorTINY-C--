# **C͟͟͟͟͟͟͟O͟͟͟͟͟͟͟N͟͟͟͟͟͟͟V͟͟͟͟͟͟͟E͟͟͟͟͟͟͟N͟͟͟͟͟͟͟Ç͟͟͟͟͟͟͟Õ͟͟͟͟͟͟͟E͟͟͟͟͟͟͟S͟͟͟͟͟͟͟ L͟͟͟͟͟͟͟É͟͟͟͟͟͟͟X͟͟͟͟͟͟͟I͟͟͟͟͟͟͟C͟͟͟͟͟͟͟A͟͟͟͟͟͟͟S͟͟͟͟͟͟͟ D͟͟͟͟͟͟͟A͟ C͟͟͟͟͟͟͟--**

### 1. P͟a͟l͟a͟v͟r͟a͟s͟-c͟h͟a͟v͟e͟
As palavras-chave da linguagem são as seguintes: 
```
{else if int float return void while main read print}  
```
Todas as palavras-chave são reservadas e devem ser escritas com caixa baixa

### 2. S͟í͟m͟b͟o͟l͟o͟s͟ e͟s͟p͟e͟c͟i͟a͟i͟s͟
Os símbolos especiais são os seguintes:  
```
{‘+’,’ –‘,’*’, ‘/’, ‘<’, ‘<=’, ‘>’, ‘>=’, ‘==’, ‘!=’,’/*’,’*/’, ‘;’, ‘{‘, ‘}’, ‘.’, ‘(‘, ‘)’, ‘,’}
```

### 3. T͟o͟k͟e͟n͟s͟
Utiliza os _tokens_ SIMBOLO e RESERVADA, para descrever os símbolos
especiais e palavras-chave. Utiliza, ainda, os _tokens_ ID, NUMINT e
NUMFLOAT, que são definidos pelas expressões regulares a seguir  


ID = letra(letra|digito)*  

NUMINT = dígito dígito*  

NUMFLOAT = NUMINT . NUMINT*  

letra = a|...|z|A|...|Z  

dígito = 0|1|...|9

Existe diferença entre caixa baixa e caixa alta.  

E͟s͟p͟a͟ç͟o͟s͟ e͟m͟ b͟r͟a͟n͟c͟o͟  
Compostos por brancos, mudanças de linha e tabulações. O espaço em branco
é ignorado, exceto como separador de IDs, NUMs e palavras-chave.  

### 4. C͟o͟m͟e͟n͟t͟á͟r͟i͟o͟s͟
São cercados pela notação usual de C /*...*/. Os comentários podem ser
colocados em qualquer lugar que possa ser ocupado por um espaço em branco
e só podem incluir uma linha. Comentários não podem ser aninhados.  

##

# **G͟͟͟R͟͟͟A͟͟͟M͟͟͟Á͟͟͟T͟͟͟I͟͟͟C͟͟͟A͟͟͟ D͟͟͟A͟͟͟ C͟͟͟--**
1. *programa* → *lista-fun* **main ( ) {** *decl-sequência* **}**
2. *lista-fun* → *lista-fun fun* | *fun*
3. *fun* → *fun-decl* **{** *decl-sequência* | *decl-sequência* **return identificador}**
4. *fun-decl* → *tipo-idt* **identificador (** *parametros* **)**
5. *parâmetros* → *param-lista* | **void**
6. *param-lista* → *param-lista* , *param* | *param*
7. *param* → *tipo-idt* **identificador**
8. *decl-sequência* → *declaração* | *declaração* ; *declaração*
9. *declaração* → *var-decl* | *if-decl* | *atribuição-decl* | *while-decl* | *read-decl* | *print-decl*
10. *var-decl* → *tipo-idt* **identificador**
11. *tipo-idt* → **int** | **float** | **void*
12. *if-decl* → **if** *exp* **{** *decl-sequência* **}** [ **else** **{** *decl-sequência* **}** ]
13. *atribuição-decl* → **identificador =** *exp*
14. *while-decl* → **while** *exp* **{** *decl-sequência* **}**
15. *read-decl* → **read identificador**
16. *print-decl* → **print** *exp*
17. *exp* → *simples-exp* [ *comparação-op simples-exp* ]
18. *comparação-op* → **<** | **>** | **==** | **!=** | **<=** | **>=**
19. *simples-exp* → *termo* | *termo soma termo*
20. *soma* → **+** | **-**
21. *termo* → *fator* | *fator mult fator*
22. *mult* → * | **/**
23. *fator* → **(** *exp* **)** | **número** | **identificador**


