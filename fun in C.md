# fun !

Tout ce qui suit vient de *Hacker's delight* de **Henry S. Warren, Jr.**

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

## `nlz` 

Cette fonction retourne le nombre de bits de poids fort à 0.

```C
int nlz32(unsigned x) {
    int n;
    if (x == 0) {
        return(32);
    } else {
        n = 1;
        if ((x >> 16) == 0) {n = n +16; x = x <<16;}
        if ((x >> 24) == 0) {n = n + 8; x = x << 8;}
        if ((x >> 28) == 0) {n = n + 4; x = x << 4;}
        if ((x >> 30) == 0) {n = n + 2; x = x << 2;}
        n = n - (x >> 31);
        return n;
    }
}
```

Bien faite pour 32 bits, qu'en est-il pour des mots de plus grande taille?

## multiplication overflow

```C
bool has_mul32_ovf(unsigned x, unsigned y) {
    unsigned z, m, n, t;
    m = nlz(x);
    n = nlz(y);
    if (m + n <= 30) {
        return false;
    }
    t = x*(y >> 1);
    if ((int)t < 0) {
        return false;
    }
    z = t*2;
    if (y & 1) {
        z = z + x;
        if (z < x) {
            return false;
        }
    }
	// z is the correct product of x and y.
    return true;
}
```

