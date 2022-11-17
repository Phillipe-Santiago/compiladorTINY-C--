# GRAMÁTICA DA C--
1. *programa* → *lista-fun* **main ( ) {** *decl-sequência* **}**
2. *lista-fun* → *lista-fun fun* | *fun*
3. *fun* → *fun-decl* **{** *decl-sequência* | *decl-sequência* **return identificador}**
4. *fun-decl* → *tipo-idt* **identificador (** *parametros* **)**
5. *parâmetros* → *param-lista* | **void**
6. *param-lista* → *param-lista* , *param* | *param*
7. *param* → *tipo-idt* **identificador**
8. *decl-sequência* → *declaração* | *declaração* ; *declaração*
9. *declaração* → *var-decl* | *if-decl* | *atribuição-decl* | *while-decl* | *read-decl* | *print-decl*
10.var-decl → tipo-idt identificador
11.tipo-idt → int | float | void
12.if-decl → if exp { decl-sequência } [ else { decl-sequência } ]
13.atribuição-decl → identificador = exp
14.while-decl → while exp { decl-sequência }
15.read-decl → read identificador
16.print-decl → print exp
17.exp → simples-exp [ comparação-op simples-exp ]
18.comparação-op → < | > | == | != | <= | >=
19.simples-exp → termo | termo soma termo
20.soma → + | -
21.termo → fator | fator mult fator
22.mult → * | /
23.fator → ( exp ) | número | identificador
