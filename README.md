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

### Tests d'exécution

Repris **uniquement des exemples des sujets** : megaphone (00/ex00), harlFilter (01/ex06), Fixed (02/ex00 à ex02, avec le `main` du sujet compilé avec tes classes), btc, RPN et PmergeMe (09). Quand le sujet dit « something similar », seul ce qui doit être exact est comparé : les valeurs, les niveaux `[ ... ]` de Harl, le tri de PmergeMe. Le texte libre des messages ne compte pas.

Ces tests ne prouvent pas que ton exercice est juste : ils vérifient les exemples du sujet, pas les cas limites que l'évaluateur va essayer. À toi d'ajouter tes propres cas dans `tester/cases/Module-0X/exYY/` :

| Fichier | Rôle |
|---|---|
| `NN.args` | arguments, un par ligne (vide = aucun) |
| `NN.out` | sortie attendue (stdout + stderr) |
| `NN.keep` / `NN.ignore` | regex : ne comparer que / ignorer ces lignes |
| `NN.check` | script de vérif (sortie sur stdin) à la place de `NN.out` |
| `NN.gen` | script qui génère les arguments |
| `NN.dir/` | fichiers à placer à côté du binaire |
| `NN.needs` | fichier requis dans ton exercice (ex : `data.csv`) |
| `subject_main.cpp` | main du sujet, compilé à la place du tien |

Si `valgrind` est installé, chaque cas est aussi passé en détection de fuites.
