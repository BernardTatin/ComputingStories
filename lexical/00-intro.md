# analyse lexicale

Il y a beaucoup d'outil permettant de le faire. Par exemple ` lex` et ses clones comme ` flex` . Et il y a la nouvelle génération avec `lemon`, `ANTLR`, ` ragel` et bien d'autres encore. Ce qui m'intéresse c'est une génération de code en *C*, une facilité d'apprentissage et, si possible, un minimum d'aide à l'analyse syntaxique.

- ***Flex***: a besoin de ***Bison*** pour fonctionner, mais j'ai ***LE*** livre qui va bien avec,
- ***Ragel***: mon problème actuel, c'est la documentation,
- ***Lemon***: comme ***Ragel***, c'est la documentation,
- ***PackCC***: comme les précédents, la documentation est pas simple,
- ***ANTLR***: en *Java*, et ne produit plus de C depuis la version 4.11.1, le *C++* généré est trop compliqué, 8 fichiers/4 classes pour un exemple d'introduction,
- ***Coco/R***: la génération de code *C* semble abandonnée,
- ***Prolog***: c'est un autre sujet mais ça pourrait aider.