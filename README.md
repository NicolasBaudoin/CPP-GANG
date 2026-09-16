# CPP-GANG

![C++](https://img.shields.io/badge/C++-98-00599C?style=flat-square&logo=cplusplus&logoColor=white)

Parcours C++ à 42, organisé en un module par sous-repo (git submodule).

## Modules

| Module | Repo |
|---|---|
| 00 | [CPP-Module-00](https://github.com/NicolasBaudoin/CPP-Module-00) |
| 01 | [CPP-Module-01](https://github.com/NicolasBaudoin/CPP-Module-01) |
| 02 | [CPP-Module-02](https://github.com/NicolasBaudoin/CPP-Module-02) |
| 03 | [CPP-Module-03](https://github.com/NicolasBaudoin/CPP-Module-03) |
| 04 | [CPP-Module-04](https://github.com/NicolasBaudoin/CPP-Module-04) |
| 05 | [CPP-Module-05](https://github.com/NicolasBaudoin/CPP-Module-05) |
| 06 | [CPP-Module-06](https://github.com/NicolasBaudoin/CPP-Module-06) |
| 07 | [CPP-Module-07](https://github.com/NicolasBaudoin/CPP-Module-07) |
| 08 | [CPP-Module-08](https://github.com/NicolasBaudoin/CPP-Module-08) |
| 09 | [CPP-Module-09](https://github.com/NicolasBaudoin/CPP-Module-09) |

## Cloner avec les submodules

```sh
git clone --recurse-submodules https://github.com/NicolasBaudoin/CPP-GANG.git
```

Ou, si déjà cloné :

```sh
git submodule update --init --recursive
```

## Mettre à jour un module

```sh
cd Module-00
git pull origin main
cd ..
git add Module-00
git commit -m "Update Module-00"
```
