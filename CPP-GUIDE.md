# Guide C++ — de zéro aux Modules 00→09

Ce guide n'est pas un cours exhaustif : c'est le strict nécessaire pour comprendre ce que chaque module te demande **avant** de l'attaquer, pour ne pas perdre de temps à découvrir un concept en plein milieu d'un exercice. Les exemples utilisent des classes génériques (`Vehicle`, `Shape`...) — jamais celles des sujets — à toi d'appliquer le principe sur `Zombie`, `Fixed`, `ClapTrap`, etc.

> Compile toujours tes essais avec `c++ -Wall -Wextra -Werror -std=c++98`. Un warning ignoré aujourd'hui est une note à 0 pendant l'évaluation.

---

## Sommaire

1. [C++98 : le cadre](#1-c98--le-cadre)
2. [Module 00 — Classes de base](#2-module-00--classes-de-base)
3. [Module 01 — Mémoire, pointeurs, références](#3-module-01--mémoire-pointeurs-références)
4. [Module 02 — Orthodox Canonical Form & opérateurs](#4-module-02--orthodox-canonical-form--opérateurs)
5. [Module 03 — Héritage](#5-module-03--héritage)
6. [Module 04 — Polymorphisme & classes abstraites](#6-module-04--polymorphisme--classes-abstraites)
7. [Module 05 — Exceptions](#7-module-05--exceptions)
8. [Module 06 — Casts C++](#8-module-06--casts-c)
9. [Module 07 — Templates](#9-module-07--templates)
10. [Module 08 — Containers, itérateurs, algorithmes](#10-module-08--containers-itérateurs-algorithmes)
11. [Module 09 — STL en pratique](#11-module-09--stl-en-pratique)
12. [Méthode pour aller vite](#12-méthode-pour-aller-vite)
13. [Ressources](#13-ressources)

---

## 1. C++98 : le cadre

- Pas de `auto`, pas de `nullptr` (utilise `NULL` ou `0`), pas de `for (auto x : v)`, pas de lambdas.
- Pas de `<vector>`/`<map>`/`<algorithm>` avant les Modules 08/09 — tout se fait avec des tableaux C et des boucles classiques.
- `using namespace std;` est interdit : écris `std::cout`, `std::string`, etc. en toutes lettres.
- Chaque `new` doit avoir un `delete` (ou `new[]` / `delete[]`) qui lui correspond quelque part — même sur un chemin d'erreur.

```cpp
#include <iostream>
#include <string>

int main(void)
{
    std::string message = "hello";
    std::cout << message << std::endl;
    return 0;
}
```

---

## 2. Module 00 — Classes de base

### Une classe minimale

```cpp
class Vehicle
{
    private:
        std::string _brand;   // jamais accessible depuis l'extérieur

    public:
        Vehicle(std::string brand) : _brand(brand) {}   // liste d'initialisation

        std::string getBrand(void) const { return _brand; }
        void setBrand(std::string brand) { _brand = brand; }
};
```

- **Encapsulation** : les attributs sont `private`, on y accède via des getters/setters `public`. C'est la règle par défaut de tous les modules.
- **Liste d'initialisation** (`: _brand(brand)`) : à préférer à une affectation dans le corps du constructeur — c'est la seule façon d'initialiser un attribut `const` ou une référence.
- **`const` en fin de méthode** (`std::string getBrand(void) const`) : promet que la méthode ne modifie pas l'objet. Indispensable pour qu'un objet `const` (ou une référence `const&`) puisse l'appeler.

### Formater un affichage avec `<iomanip>`

```cpp
#include <iomanip>

std::cout << std::setw(10) << std::right << "abc" << "|" << std::endl;
//            ^largeur fixe   ^aligné à droite
```

`std::setw(n)` ne s'applique qu'à la **prochaine** insertion — il faut le répéter avant chaque colonne.

### `static`

```cpp
class Counter
{
    private:
        static int _count;   // une seule variable, partagée par toutes les instances
    public:
        Counter(void) { _count++; }
        static int getCount(void) { return _count; }   // appelable sans instance : Counter::getCount()
};
int Counter::_count = 0;   // obligatoire : définition hors classe
```

---

## 3. Module 01 — Mémoire, pointeurs, références

### Pile (stack) vs tas (heap)

```cpp
void onStack(void)
{
    Vehicle car("Toyota");     // détruite automatiquement à la fin de la fonction
}

Vehicle* onHeap(void)
{
    Vehicle* car = new Vehicle("Toyota");   // survit à la fonction
    return car;                             // l'appelant DEVIENT responsable du delete
}
```

Règle simple : si l'objet doit **survivre** à la fonction qui le crée, ou si sa taille n'est connue qu'à l'exécution (ex. `new Vehicle[n]`), il va sur le tas. Sinon, la pile suffit et évite tout risque de fuite.

### Pointeur vs référence

```cpp
Vehicle car("Toyota");
Vehicle* p = &car;   // pointeur : peut être NULL, peut être réaffecté, s'écrit avec -> ou (*p).
Vehicle& r = car;    // référence : ne peut PAS être NULL, doit être initialisée, jamais réaffectée après coup.

p->setBrand("Honda");
r.setBrand("Mazda");   // même syntaxe qu'un objet normal
```

Utilise une **référence** quand l'objet existe forcément (paramètre obligatoire) ; un **pointeur** quand il peut être absent (`NULL`) ou remplacé plus tard.

### Pointeurs sur fonctions membres

C'est le point dur du module (`Harl`) : au lieu d'une cascade de `if/else`, on stocke des pointeurs vers des méthodes et on les appelle dynamiquement.

```cpp
class Shape
{
    public:
        void drawCircle(void) { std::cout << "circle" << std::endl; }
        void drawSquare(void) { std::cout << "square" << std::endl; }
};

void (Shape::*fn)(void) = &Shape::drawCircle;   // déclaration + affectation
Shape s;
(s.*fn)();          // appel via un objet
Shape* ptr = &s;
(ptr->*fn)();        // appel via un pointeur — parenthèses obligatoires
```

Un tableau `void (Shape::*tab[2])(void) = { &Shape::drawCircle, &Shape::drawSquare };` permet de choisir la méthode par un simple index.

---

## 4. Module 02 — Orthodox Canonical Form & opérateurs

### Les 4 fonctions canoniques

À partir de ce module, **toute** classe doit les avoir (sauf mention contraire) :

```cpp
class Box
{
    private:
        int _size;
    public:
        Box(void);                       // constructeur par défaut
        Box(Box const & src);            // constructeur par copie
        Box & operator=(Box const & rhs); // opérateur d'affectation
        ~Box(void);                       // destructeur
};

Box::Box(void) : _size(0) {}
Box::Box(Box const & src) { *this = src; }
Box & Box::operator=(Box const & rhs)
{
    if (this != &rhs)          // se protéger de l'auto-affectation (a = a;)
        _size = rhs._size;
    return *this;               // permet d'enchaîner : a = b = c;
}
Box::~Box(void) {}
```

Header (`.hpp`) = déclarations seulement ; source (`.cpp`) = implémentation. Toute méthode codée dans le header (hors template) → note à 0.

### Surcharger des opérateurs

```cpp
class Box
{
    public:
        bool operator==(Box const & rhs) const { return _size == rhs._size; }
        Box operator+(Box const & rhs) const { Box r; r._size = _size + rhs._size; return r; }

        Box & operator++(void) { _size++; return *this; }        // pré-incrément : ++a
        Box operator++(int) { Box tmp(*this); _size++; return tmp; }  // post-incrément : a++ (le int est un marqueur muet)

        friend std::ostream & operator<<(std::ostream & o, Box const & b); // voir note ci-dessous
};
```

> `friend` est interdit dans les modules sauf mention explicite du sujet. Pour surcharger `<<`, préfère une fonction libre qui utilise un getter public plutôt qu'un ami.

### Nombres à virgule fixe (le concept derrière `Fixed`)

Un entier stocke une valeur **décalée** de N bits : `raw = valeur_réelle * 2^N`. Pour repasser en flottant : `valeur_réelle = raw / 2^N` (`2^N` s'écrit `1 << N`). Toute la classe du Module 02 tourne autour de ce seul principe.

---

## 5. Module 03 — Héritage

### Héritage simple et chaînage constructeur/destructeur

```cpp
class Vehicle
{
    public:
        Vehicle(std::string name) : _name(name) { std::cout << "Vehicle built" << std::endl; }
        ~Vehicle(void) { std::cout << "Vehicle destroyed" << std::endl; }
    protected:
        std::string _name;
};

class Car : public Vehicle
{
    public:
        Car(std::string name) : Vehicle(name) { std::cout << "Car built" << std::endl; }
        ~Car(void) { std::cout << "Car destroyed" << std::endl; }
};
```

Sortie de `Car c("Tesla");` puis destruction :

```
Vehicle built
Car built
Car destroyed
Vehicle destroyed
```

**La base est toujours construite avant le dérivé, et détruite après lui** — comme des poupées russes : on ne peut pas fermer l'enveloppe extérieure avant l'intérieure.

### Héritage multiple et le problème du diamant

```cpp
class A { public: A(void) { std::cout << "A" << std::endl; } };
class B : public A {};
class C : public A {};
class D : public B, public C {};   // D contient DEUX sous-objets A !
```

Pour n'avoir qu'un seul `A`, il faut de l'**héritage virtuel** :

```cpp
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};   // un seul A, partagé
```

C'est exactement ce que demande l'exercice du diamant : sans `virtual`, deux instances de la classe de base coexistent (et deux fois plus de messages de construction).

---

## 6. Module 04 — Polymorphisme & classes abstraites

### Pourquoi `virtual` change tout

```cpp
class Shape
{
    public:
        void draw(void) { std::cout << "shape" << std::endl; }          // sans virtual
        virtual void drawV(void) { std::cout << "shape" << std::endl; } // avec virtual
};
class Circle : public Shape
{
    public:
        void draw(void) { std::cout << "circle" << std::endl; }
        void drawV(void) { std::cout << "circle" << std::endl; }
};

Shape* s = new Circle();
s->draw();    // affiche "shape"  — résolu au TYPE DU POINTEUR (statique)
s->drawV();   // affiche "circle" — résolu au TYPE RÉEL DE L'OBJET (dynamique, via vtable)
```

Sans `virtual`, le compilateur choisit la méthode **à la compilation**, selon le type déclaré du pointeur. Avec `virtual`, il choisit **à l'exécution**, selon le type réel de l'objet pointé. C'est tout le sujet de l'exercice `WrongAnimal`/`WrongCat`.

### Classe abstraite (= interface partielle)

```cpp
class Shape
{
    public:
        virtual void draw(void) const = 0;   // "= 0" : fonction virtuelle PURE
        virtual ~Shape(void) {}                // toujours un destructeur virtuel dans une base polymorphe
};
// Shape s;              // ERREUR de compilation : classe abstraite
Shape* s = new Circle();  // OK : utilisable comme type de base
```

Une seule méthode `= 0` suffit à rendre toute la classe non instanciable.

### Copie profonde vs copie superficielle

```cpp
class Owner
{
    private:
        int* _data;
    public:
        Owner(void) : _data(new int(0)) {}
        Owner(Owner const & src) : _data(new int(*src._data)) {}   // copie profonde : nouveau bloc mémoire
        // Owner(Owner const & src) : _data(src._data) {}          // copie superficielle : même bloc, DANGER
        ~Owner(void) { delete _data; }
};
```

Avec une copie superficielle, deux objets pointent sur le même bloc mémoire : le premier `delete` le libère, le second `delete` plante (double free). Toujours `new` un nouveau bloc dans le constructeur par copie / l'opérateur d'affectation dès qu'un attribut est un pointeur possédé par la classe.

---

## 7. Module 05 — Exceptions

### Créer sa propre exception

Une exception doit hériter de `std::exception` et redéfinir `what()` :

```cpp
class TooHeavyException : public std::exception
{
    public:
        virtual const char * what(void) const throw()
        {
            return "this box is too heavy to lift";
        }
};
```

`throw()` après `what()` déclare que la fonction ne lève jamais d'exception elle-même (obligatoire en C++98 pour respecter la signature de `std::exception::what`). Les classes d'exception n'ont **pas** besoin d'être en Orthodox Canonical Form.

### Lever et attraper

```cpp
class Box
{
    public:
        void lift(int weight) const
        {
            if (weight > 50)
                throw TooHeavyException();
            std::cout << "lifted!" << std::endl;
        }
};

try
{
    Box b;
    b.lift(80);
}
catch (std::exception const & e)   // catch par référence : marche pour N'IMPORTE quelle exception dérivée
{
    std::cerr << e.what() << std::endl;
}
```

Attraper par **référence sur `std::exception`** (et non par valeur) permet d'intercepter n'importe quelle exception standard sans connaître son type exact — pratique quand plusieurs classes (`GradeTooHighException`, `GradeTooLowException`...) peuvent être levées au même endroit.

### Éviter la cascade de `if/else` (pattern répété dans le module)

Une classe abstraite qui centralise la vérification, déléguée à une méthode virtuelle pure dans chaque classe concrète, évite le `if (name == "a") ... else if (name == "b")` explicitement interdit dans l'exercice `Intern` :

```cpp
class AAction
{
    public:
        virtual ~AAction(void) {}
        virtual void run(void) const = 0;
};
class Jump : public AAction { public: void run(void) const { std::cout << "jump" << std::endl; } };
class Duck : public AAction { public: void run(void) const { std::cout << "duck" << std::endl; } };
```

Une fonction "usine" peut alors comparer une seule fois le nom à une liste de paires `{nom, type}` (ou utiliser une `std::map<std::string, ...>` à partir du Module 08/09) plutôt que d'enchaîner les `if`.

---

## 8. Module 06 — Casts C++

C++ remplace le cast C `(type)valeur` par quatre casts explicites, chacun avec un rôle précis :

```cpp
double d = 4.2;
int i        = static_cast<int>(d);          // conversion "normale" entre types compatibles, vérifiée à la compilation
Base* b      = dynamic_cast<Base*>(derived);  // conversion sûre dans une hiérarchie polymorphe, NULL si ça échoue
uintptr_t addr = reinterpret_cast<uintptr_t>(&d); // réinterprète les bits bruts, aucune vérification, dangereux
const int* cp = &i;
int* p       = const_cast<int*>(cp);          // ajoute/retire const, rien d'autre
```

- **`static_cast`** : le cas courant (numérique, pointeur de base vers dérivé si tu es sûr du type). Utilisé dans l'exercice `ScalarConverter`.
- **`dynamic_cast`** : le seul qui vérifie le type réel **à l'exécution** — nécessite une classe polymorphe (au moins une méthode `virtual`). Retourne `NULL` sur un pointeur si le cast est invalide (ou lève `std::bad_cast` sur une référence). C'est l'outil pour l'exercice `identify()` : tenter `dynamic_cast<A*>(p)`, puis `B*`, puis `C*`, et regarder lequel n'est pas `NULL` — sans jamais inclure `<typeinfo>`.
- **`reinterpret_cast`** : réinterprète une adresse comme un entier ou un autre pointeur sans aucune conversion de valeur — exactement ce que demande `Serializer::serialize`/`deserialize`.
- **`const_cast`** : seul cast capable de retirer un `const`, à n'utiliser qu'en dernier recours.

---

## 9. Module 07 — Templates

### Fonction template

```cpp
template <typename T>
T const & maxOf(T const & a, T const & b)
{
    return (a > b) ? a : b;
}
```

Le compilateur génère une version différente de la fonction pour chaque type utilisé (`maxOf(3, 5)`, `maxOf(std::string("a"), std::string("b"))`, ...) — c'est de la généricité résolue **à la compilation**, sans coût à l'exécution. Une fonction template doit être entièrement définie dans le header (pas de séparation .hpp/.cpp), sinon l'éditeur de liens ne trouve pas l'instanciation dont il a besoin.

### Classe template

```cpp
template <typename T>
class Box
{
    private:
        T _value;
    public:
        Box(T value) : _value(value) {}
        T get(void) const { return _value; }
};

Box<int> a(42);
Box<std::string> b("hello");
```

### `const` et non-`const` dans un template (le piège de `iter`)

Une fonction template appliquée à un tableau `const` doit pouvoir recevoir une fonction qui prend son paramètre par `const&`, et inversement pour un tableau non-`const`. Deux surcharges (une pour `T*`, une pour `T const*`) — ou un seul paramètre de template pour la fonction elle-même — permettent de couvrir les deux cas sans dupliquer toute la logique.

---

## 10. Module 08 — Containers, itérateurs, algorithmes

La STL est enfin autorisée : `<vector>`, `<list>`, `<map>`, `<stack>`, `<algorithm>`... Le but du module est de les utiliser **à la place** de tes propres boucles/tableaux dès que c'est pertinent.

### Un itérateur, c'est un pointeur généralisé

```cpp
std::vector<int> v;
v.push_back(1);
v.push_back(2);

for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << *it << std::endl;   // *it déréférence, comme un pointeur
```

`<algorithm>` fournit des fonctions qui travaillent sur des paires d'itérateurs, indépendamment du container : `std::find(v.begin(), v.end(), 42)` marche aussi bien sur un `vector` que sur un `list`.

### Étendre un container existant (le principe derrière `MutantStack`)

`std::stack` ne s'itère pas nativement, mais elle stocke ses éléments dans un attribut **protégé** nommé `c` (le container sous-jacent, par défaut un `std::deque`). En héritant, ce membre devient accessible :

```cpp
template <typename T>
class IterableStack : public std::stack<T>
{
    public:
        typedef typename std::stack<T>::container_type::iterator iterator;
        iterator begin(void) { return this->c.begin(); }
        iterator end(void)   { return this->c.end(); }
};
```

C'est le même principe pour rendre `std::stack` itérable dans l'exercice du module.

---

## 11. Module 09 — STL en pratique

Ce module impose une contrainte inhabituelle : **chaque container utilisé ne peut servir que pour un seul exercice** du module. Choisis-le donc dès le départ en fonction du besoin réel :

- **Recherche par date la plus proche (`BitcoinExchange`)** : un `std::map<std::string, double>` trié par clé. `map::lower_bound(date)` donne le premier élément **non inférieur** à la date cherchée ; si ce n'est pas une correspondance exacte, l'élément précédent (`--it`) donne la date la plus proche **inférieure**, exactement ce que demande le sujet.
- **Évaluation d'une expression postfixée (`RPN`)** : un `std::stack<int>` — on empile les nombres, et à chaque opérateur on dépile deux valeurs, on calcule, on repousse le résultat.
- **Tri fusion-insertion (`PmergeMe`)** : le sujet impose **deux containers différents** (ex. `std::vector` et `std::list`) pour comparer leurs performances sur le même algorithme (Ford-Johnson). Mesure le temps avec `std::clock()` de `<ctime>` (disponible en C++98, contrairement à `<chrono>`).

```cpp
#include <ctime>

std::clock_t start = std::clock();
// ... tri ...
double elapsed_us = 1000000.0 * (std::clock() - start) / CLOCKS_PER_SEC;
```

---

## 12. Méthode pour aller vite

1. **Lis tout le sujet du module avant de coder** — les exemples de sortie révèlent souvent des exigences absentes du texte.
2. **Écris le Makefile en premier**, même vide (`all`, `clean`, `fclean`, `re`) — tu ajoutes les fichiers au fur et à mesure sans y repenser.
3. **Compile après chaque fonction**, pas après toute la classe : un warning trouvé tout de suite coûte 10 secondes ; trouvé à la fin, il coûte une demi-heure de recherche.
4. **Un commit par exercice terminé et compilable** — jamais un commit qui casse la compilation.
5. **Teste avec `valgrind --leak-check=full --show-leak-kinds=all ./ton_programme`** dès qu'il y a un `new` dans l'exercice, pas seulement à la fin du module.
6. **Ne code pas Module N+1 avant que Module N compile sans warning** — les modules s'enchaînent, une base bancale se paie plus tard.
7. Bloque une session dédiée pour l'exercice le plus dur du module (voir la checklist [CPP Field Guide](https://claude.ai/code/artifact/e3bac983-7b02-4508-961d-3fec366043ad)) plutôt que de l'attaquer fatigué en fin de journée.

---

## 13. Ressources

- [cppreference.com](https://en.cppreference.com/w/) — référence complète et fiable, filtrer sur C++98 quand une page propose plusieurs versions
- [cplusplus.com/reference](https://cplusplus.com/reference/) — référence historique citée par les sujets 42 eux-mêmes (`string`, `iomanip`)
- `man valgrind` — détection de fuites mémoire
- La checklist interactive du repo : [CPP Field Guide](https://claude.ai/code/artifact/e3bac983-7b02-4508-961d-3fec366043ad) (stratégie et pistes par exercice)
