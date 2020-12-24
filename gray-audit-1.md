---
author: Guillaume Lozengez ; Alexis Lebis
version: 1.0
---
# Audit - TEAM-PROJECT-XXX

@auditor: Guillaume L.

## Process 

1. Connect to the git webpage of the project and get a first view of the project.
2. Follow the install instruction 
3. Execute the software.
4. Enter in the source code and the documentation.

## Presentation:

**Does the index page (the README file) provides a clear overview of the project and an overmealing desire to try it ?**

README au minimum.

**Is The installation instruction clear and complete ?**

Minimal

**Is the compilation of the software easy ?**

Compilation OK, mais message inquiétant de warning ( free(&p) )


**Is the project correctly organized ?**

Ok. mention spéciale pour la création du répertoire `dist/` (par contre c'est bien dist/ ou `./dist` et non pas `/dist` qui supposerait une installation à la racine de votre système. )

**Further comments ?**


## Quality of the solution:

**Does the provided software run well ?**

Le soft: Un rectangle que l'on déplace avec une grille en fond.

Minimal, mais fonctionnel.

**Does the software have a clear and ergonomic interface ?**

pas applicable en l'état (ou je n'ai pas découvert le but du soft) 

**Is there any tutorial of some sort to highlight specific software functionalities ?**

Instruction minimale dans le README.

**Further comments ?**


## The project in depth:

### Project managment

**Does projet-outline.md clearly state what has been done, and by who ?**

Le projet-outline.md n'ait pas cohérent avec ce qui a été effectivement réalisé. 
La version semble identique à l'original, mais les réalisations du programme ont divergé.
Sur la base de ce constat, il est impossible de se faire une idée de ce que les développeurs on voulu réaliser.

**Does projet-outline.md defines the next steps to achieve ?**

Il est tout aussi impossible de voir où il souhaite aller.

**Did the group distribute the tasks between them correctly ?**

Ben du cou les membres sont affectés à des fonctionnalités fantômes.


### Source code


**Is the entrance point of the application easy to find ?**


Les sources sont instanciées dans un unique fichier source. (des éléments dans des header qui, du fait, ne sont plus vraiment des headers...)

Mention spéciale sur la fonction logger pour faciliter les messages de débug.

**PLATFORM_WEB** ??? (personnellement jamais tester).

Main concis. 


**Is source code of quality (names, comments, small atomic functions...) ?**


Je ne suis personnellement pas un grand fan des variables global. Cela rend les fonctions créées difficiles à réutiliser dans la mesure où les paramètres des fonctions ne sont pas clairement identifiés.

Dans l'état actuel, seul le Player semble être utilisé des structures créé.

En revanche, le découpage en fonction atomic est propre.


**Is source code architecture coherent (decomposition in structure and their interaction, well desgined OOP, programming patterns...) ?**

Oui, sauf qu'il n'y a pas de types spécifiques ni de répartition sur des fichiers multiples.

**Is the solution's algorithmic efficient (minimizing the computation time while K.I.S.S) ?**

Pas de gros algos, mais ok.


**Does the solution has a good memory management (no memory leaks, heavy element is manipulated with pointers, the memory is allocated and free appropriately) ?**

Nop.

Pourquoi mettre en place des fonctions de création et de destruction des éléments du programme pour ne pas les utiliser ? Et surtout le Warning pointe en effet une erreur de programmation.

**Is there a documentation and what is its quality ?**

Non il n'ait pas évident de rentrer dans le code du fait de ces variables globales d'on on a du mal à suivre l'évolution et le manque de commentaire n'aide pas. Heureusement les variables et les fonctions sont astucieusement nommées.

**Further comments ?**


## Recomentations:


- Détacher l'implémentation des fonctions sur les structures dans des fichiers dédier.
- S'interdire, au maximum l'usage de variable globale.
- Reprendre le `projet-outline.md` pour qu'il devienne un réel outil présentant se qui à été fait.


## Conclusion


**Is the development of the project far advanced ?**

Pas vraiment, soit il manque de la mise en commun de travaux, soit il y a un gros déséquilibre de travail dans le groupe.

**Would-it be easy for a new developer to participate in the project ?**

non.

**Is it interresting to further develop this project ?**

Oui, à condition de bien définir où le groupe souhaite aller...

**Final comments...**

