# fun !

Tout ce qui suit vient de *Hacker's delight* de *Henry S. Warren, Jr.**

## quelques trucs simples et bêtes mais tellement utiles

### tester les limites

C'est vérifier qu'un entier $x$ est bien entre les limites $a$ et $b$ (les trois étant des entiers *signés*):
$$
a \leq x \leq b
$$
Cette double inégalité peut être remplacée par la simple inégalité *non signée*:
$$
x - a \leq^{u} b - a
$$
De plus, on peut noter que si $a, b$ sont signés, que, de plus, $a \leq b$, alors la valeur *non signée* $b - a$ représente bien la valeur arithmétique $b - a$. En ***C***, cela donne quelque chose comme:

```C
int a = computeA();
int b = computeB();
unsigned int delta = (unsigned)(b - a);
// delta contient la bonne valeur
```

