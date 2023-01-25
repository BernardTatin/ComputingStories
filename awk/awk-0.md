# `awk`, version *GNU*

C'est un *vieux* truc, `awk`, j'en ai écrit, des lignes et des lignes. C'était il y a bien 35 ans de ça, alors j'ai oublié.

## structure d'un script `awk`

Il y a trois parties, toutes optionnelles. Voici un descriptif rapide:

```awk
BEGIN {
	# du code pour l'initialisation
}
pattern, condition ou rien {
	# du code pour le cas pris en compte
}
END {
	# du code exécuté à la fin du traitement du fichier en entrée
}
```

## les variables importantes

L'intérêt de `awk` est qu'il est très souple. Voici quelques points importants.

### `FS`, `OFS`

#### `FS`

Cette variable contient le séparateur de champs. Par défaut, c'est l'espace. Mais on peut le modifier comme par exemple ici pour le traitement de fichiers CSV ayant le `';'` comme séparateur.

#### `OFS`

Ici, c'est le séparateur de sortie, utilisé par `print`.

#### exemple



```awk
#! /usr/bin/gawk -f

BEGIN {
	FS = ";"
	OFS = ";"
	total = 0.0
	val = 0.0
}
/^=/ {
	}
/^date_comptabilisation/ {
		print $1 " " $3
	}
/^[0-9]/ {
	val = gensub(/,/, ".", "1", $3)
	print $1, val
	total = total + val
}
END {
	print "Total: ", total
}
```

