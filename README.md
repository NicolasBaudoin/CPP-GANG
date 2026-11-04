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
