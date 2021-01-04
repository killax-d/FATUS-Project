# NetWord - Outline of the project

This document lists the project components as in a backlog-product from the [*SCRUM*](https://fr.wikipedia.org/wiki/Scrum_(d%C3%A9veloppement)#Glossaire) terminology.

NetWorld aims to become a KISS (keep it stupid simple) Game-engine in which the game entities interact on a world seen as a network of key positions (nodes).

The development is organized over several functionalities listed here from the most mandatory to the less important:
Each Functionnality groups several components to develop as UserStories under the responsibility of one or two main developers.

## Fct.1 - Project Framing.
---
- @MainDevelopers: Dylan Donne | @Killax-D - @dylan.donne
---

This functionality cover a framework for the team of developers.

- [x] Developers can communicate with others (discord, ...) @dylan.donne
- [x] A developer can share a working directory (git, gitlab, ...) @dylan.donne
- [x] Hello World’s programmes can be completed and executed. @dylan.donne
- [x] Everyone can refer to documentation. @dylan.donne
- [x] A realize by merging contribution could be generated. @dylan.donne
- [ ] A solution for Unit Test is operational.

## Fct.2 - NetWorld
---
- @MainDevelopers: Alexandre Leva | @Rokem-prog - @alexandre.leva
- @SecondaryDevelopers: Carl Dhennin | @carl.dhennin

- @SupportDevelopers: Dylan Donne | @Killax-D - @dylan.donne
---

NetWorld represent the center piece of the game engine. It is the programme component that glue all the others. 
It is an environment for the game entities, viewed as a planar graph modelling all the possible movements. 

- [x] A NetWorld is composed of nodes at specific position (x,y). @dylan.donne & @jules.decottignies
- [x] Nodes are connected to other with edges. @dylan.donne & @jules.decottignies
- [x] Nodes can contain entities. @dylan.donne
- [x] It is possible to generate NetWorld randomly (example: random nodes and Gabriel graph). @dylan.donne
- [x] An algorithm provides paths in the NetWorld between two positions (A*). @alexandre.leva & @carl.dhennin
- [x] Long edges are subdivided with intermediate nodes in order to generate an almost regular game tabletop. @dylan.donne & @carl.dhennin

## Fct.3 - Entities

---
- @MainDevelopers: Jules Decottignies | @juliodctg - @jules.decottignies
- @SecondaryDevelopers: Nabil Bentayaa | @bilnamd - @nabil.bentayaa
- @TertiaryDevelopers: Samad Rokia | @Samad-Rokia - @samad.rokia

- @SupportDevelopers: Dylan Donne | @Killax-D - @dylan.donne
---

Entities are the game element capable of actions. This functionality mainly regroups the basic interactions of those entities between them and with the NetWorld.


- [x] An entity is at a specific node. @dylan.donne
- [x] Entities see the different possible movements (edges from the nodes) and can try one. The movement succeed only if the node is not over populated. @dylan.donne
- [x] Entities can act on the NetWorld (change the colour of a node for instance). @nabil.bentayaa & @samad.rokia
- [x] Entities can act over other entities (damaging them for instance). @nabil.bentayaa & @samad.rokia

## Fct.4 - User Interface
---
- @MainDevelopers: Dylan Donne | @Killax-D - @dylan.donne
- @SecondaryDevelopers: Jules Decottignies | @juliodctg - @jules.decottignies
---

This functionality focus on a graphical rendering of the NetWold and to provide a control through the mouse and keyboard.

- [x] The program starts on welcome menu @dylan.donne
- [x] It is possible to launch and visualize a NetWorld and its Entities @dylan.donne
- [ ] Players can save and load a game 
- [ ] Players can select its own entities and provide them for an expected location.
- [x] Animations are triggered when an entity move from a node to another. @jules.decottignies


## Fct.5 - Robust Development environment
---
- @MainDevelopers: Dylan Donne | @Killax-D - @dylan.donne
- @SecondaryDevelopers: Jules Decottignies | @juliodctg - @jules.decottignies
---

- [x] All developers can refer to a good-practice doc for code. @dylan.donne
- [ ] Developers would use a proper C unit-test framework.


## Fct.5 - Game-play
---
- @MainDevelopers: Samad Rokia | @Samad-Rokia - @samad.rokia
- @SecondaryDevelopers: Nabil Bentayaa | @bilnamd - @nabil.bentayaa

- @SupportDevelopers: Dylan Donne | @Killax-D - @dylan.donne
---

- [x] It is time to define a game objectives and maybe change the name of the project. @samad.rokia, @nabil.bentayaa & @dylan.donne

## Fct.6 - Programme distributed programme
---
- @MainDevelopers: Samad Rokia | @Samad-Rokia - @samad.rokia
- @SecondaryDevelopers: Nabil Bentayaa | @bilnamd - @nabil.bentayaa
- @TertiaryDevelopers: Ismaël Rousseau | @ismael.rousseau

- @SupportDevelopers: Dylan Donne | @Killax-D - @dylan.donne
---

The goal here is to distribute the game process.

- [ ] A player owns entities.
- [ ] The player process can be executed on an independent computer process (network)
- [ ] The NetWorld simulation can be distributed over processes.
- [ ] The game is reachable from a web interface.

## Fct.7 - Tanks

- [ ] Nodes are defined with a collection of tanks  where resources can be placed. (water for instance)
