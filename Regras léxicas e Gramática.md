# **C͟͟͟O͟͟͟N͟͟͟V͟͟͟E͟͟͟N͟͟͟Ç͟͟͟Õ͟͟͟E͟͟͟S͟͟͟ L͟͟͟É͟͟͟X͟͟͟I͟͟͟C͟͟͟A͟͟͟S͟͟͟ D͟͟͟E͟͟͟ C͟͟͟--**

## 1. P͟a͟l͟a͟v͟r͟a͟s͟-c͟h͟a͟v͟e͟
As palavras-chave da linguagem são as seguintes: 
```
{else if int float return void while main read print}  
```
Todas as palavras-chave são reservadas e devem ser escritas com caixa baixa

## 2. S͟í͟m͟b͟o͟l͟o͟s͟ e͟s͟p͟e͟c͟i͟a͟i͟s͟
Os símbolos especiais são os seguintes:  
```
{‘+’,’ –‘,’*’, ‘/’, ‘<’, ‘<=’, ‘>’, ‘>=’, ‘==’, ‘!=’,’/*’,’*/’, ‘;’, ‘{‘, ‘}’, ‘.’, ‘(‘, ‘)’, ‘,’}
```

## 3. T͟o͟k͟e͟n͟s͟
Utiliza os _tokens_ SIMBOLO e RESERVADA, para descrever os símbolos
especiais e palavras-chave. Utiliza, ainda, os _tokens_ ID, NUMINT e
NUMFLOAT, que são definidos pelas expressões regulares a seguir  

##

ID = letra(letra|digito)*  

NUMINT = dígito dígito*  

NUMFLOAT = NUMINT . NUMINT*  

letra = a|...|z|A|...|Z  

dígito = 0|1|...|9

##
Existe diferença entre caixa baixa e caixa alta.  

