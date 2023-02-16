# profilage et optimisation avec *clang*

Il y a *Valgrind*, qui permet aussi bien d'autres choses. Mais, il y a un énorme ***mais***, il ne supporte pas les informations de debug de *clang*, tout au moins pour les versions 14 et 15. Si le bug semble connu, voire corrigé,, il ne l'est pas pour les versions des dépôts de *PopOS*.

En attendant, *clang* est accompagné de nombreux outils extrêmement puissants pour  l'analyse de code et plus intéressant que les classiques utilitaires de *gcc*, peut-être au prix d'un peu de souplesse.

## code coverage

Il faut compiler avec des options spécifiques à *clang*, lancer le binaire et lire le résultat. Voici un exemple:

```sh
clang -fprofile-instr-generate -fcoverage-mapping \
	-O2 \
	-o code code.c
./code
llvm-profdata merge -output=code.profdata default.profraw
llvm-cov show  ./hack-delights.bin -instr-profile=code.profdata code.c
```



## l'option `Rpass`

Cette option permet l'affichage de diagnostics du type:

```sh
In file included from ../safe-arithmetic/sai-string.c:14:
In file included from ../safe-arithmetic/safe-int-arith.h:20:
../safe-arithmetic/sai-definitions.h:25:34: warning: overflow in expression; result is -170141183460469231731687303715884105728 with type '__int128' [-Winteger-overflow]
SCONST SA_INT sa_imin  = sa_imax + 1;
                                 ^
../safe-arithmetic/sai-string.c:48:12: remark: 'divm10' inlined into 'kern_istr' with (cost=-14995, threshold=325) at callsite kern_istr:14:12; [-Rpass=inline]
    while (divm10(n, &d, &m)) {
           ^
../safe-arithmetic/sai-string.c:65:16: remark: 'kern_istr' inlined into 'sa_int_to_str' with (cost=-14830, threshold=250) at callsite sa_int_to_str:4:16; [-Rpass=inline]
        return kern_istr(n);
```

Si c'est (très) intéressant, c'est rapidement illisible.