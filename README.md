# CPP-GANG

![C++](https://img.shields.io/badge/C++-98-00599C?style=flat-square&logo=cplusplus&logoColor=white)

Parcours C++ à 42 : tous les modules dans un seul repo, un dossier par module.

📘 [**CPP-GUIDE.md**](CPP-GUIDE.md) — guide pour apprendre les concepts C++ nécessaires et enchaîner les Modules 00 à 04 rapidement. Les sujets sont dans [`doc/`](doc).

## Travailler

```sh
git clone https://github.com/NicolasBaudoin/CPP-GANG.git
cd CPP-GANG/Module-02/ex00
# code, make, test...
git add . && git commit -m "Module-02 ex00" && git push
```

## Rendre un module sur la Vogsphere

```sh
./vog.sh Module-02 <url-du-repo-vogsphere>
```

Le script copie la version **commitée** du module dans le repo Vogsphere (sans PDF, `.o` ni binaires), affiche la liste des fichiers et demande confirmation avant de pousser.

## Tester un exercice

`cpptest` vérifie les **règles des sujets** (pas la logique de tes exos) : fichiers attendus et leur casse, Makefile (règles, flags, relink, `fclean`, `re`), compilation, `*printf`/`*alloc`/`free`, `using namespace`, `friend`, STL avant le Module 08, include guards, headers qui compilent seuls, forme canonique à partir du Module 02 (en WARN), et les sorties données par le sujet quand elles sont dans `tester/cases/`. Chaque KO est suivi d'une piste (→), et le bilan se termine par la **prochaine étape** : le premier KO à corriger, sinon l'exercice suivant à attaquer, sinon le rendu du module.

Pour le lancer de n'importe où dans le repo, ajoute dans ton `~/.bashrc` :

```sh
alias cpptest='"$(git rev-parse --show-toplevel)"/cpptest'
```

```sh
cpptest            # dans Module-01/ex00 : cet exercice ; dans Module-01 : le module ; ailleurs : tout
cpptest 02         # tout le Module-02
cpptest 02 ex01    # un exercice
cpptest -v ...     # affiche aussi les OK
```

Ajouter un test de sortie : `tester/cases/Module-0X/exYY/NN.args` (un argument par ligne, fichier vide = aucun argument) et `NN.out` (sortie attendue). Si `valgrind` est installé, chaque cas est aussi passé en détection de fuites.
