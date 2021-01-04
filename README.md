# 50 Nuances De Codes

Petit jeu 2D qui vous procura une grande dose de bonheur (metacritic 98/100).
Réalisé par Samad, Jules, Dylan, Ismaël, Nabil, Carl, Alexandre.

## Histoire

Vous êtes un membre d'équipage enfermé dans une cellule à la suite d'une rixe avec un supérieur hiérarchique (Mr. Guillaume Alexis) qui vous a valu un blâme et un isolement de 90 jours (bon je vous l'accorde, c'est pire que le COVID).
Après une nuit de sommeil plutôt agité vous vous réveillez et vous constatez que tout l'équipage a disparu et que le vaisseau a été envahi par une horde d'aliens flottants au milieu des différentes salles composant cet immense bâtiment.
Dans le même temps l'ordinateur principal a totalement été corrompu par un virus extraterrestre et cela a déclenché la procédure d'autodestruction. 
Votre but sera de trouver les différentes cartes magnétiques et clés afin d'ouvrir les portes qui vous mèneront vers votre objectif : une clé USB contenant un programme de secours vous permettant de reprendre le contrôle du vaisseau dans le but de revenir sur Terre et retrouver la civilisation.

## Installation

Projet conçu pour une compilation avec GCC et la librairie Raylib. De par la nature de la procédure d'installation et de linkage, Linux est le système d'exploitation à préférer.

## dans un terminal linux installation de gcc, CMake et git: 

```bash 
sudo apt update
sudo apt install 
sudo apt install build-essential git cmake
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev 
```
## Compiler et installer Raylib 3.0.0 
```bash
## on choisi le répertoire de son choix 
cd ~/Documents 
## puis clonage et compilation

git clone https://github.com/raysan5/raylib.git raylib
cd raylib
git checkout '3.0.0'
mkdir build && cd build
cmake -DSHARED=ON -DSTATIC=ON ..
make 


## puis installation 
sudo make install
cd ..
 
## optionnel supprimer le dossier initiale 
rm -fr raylib
```

## Utilisation du jeu

```bash
## terminal
git clone https://gvipers.imt-lille-douai.fr/fatus/50NuancesDeCode/game

## dans le répertoire game

make

cd /dist

./app-50NuancesDeCodes 
```

### Contrôles
| <div style="display: flex; flex-flow: row nowrap"> 	<div style="display: flex; flex-flow: column nowrap; justify-content: center; align-items: center;"> 		<div style="display: block"> 			<kbd>Z</kbd> 		</div> 		<div style="display: block"> 			<kbd>Q</kbd> 			<kbd>S</kbd> 			<kbd>D</kbd> 		</div> 	</div>  	<h5> OU </h5>  	<div style="display: flex; flex-flow: column nowrap; justify-content: center; align-items: center;"> 		<div style="display: block"> 			<kbd>↑</kbd> 		</div> 		<div style="display: block"> 			<kbd>←</kbd> 			<kbd>↓</kbd> 			<kbd>→</kbd> 		</div> 	</div> </div> 	|        Pour se déplacer       	|
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:	|:-----------------------------:	|
|                                                                                                                                                                                                                                                                      <kbd>Shift</kbd>                                                                                                                                                                                                                                                                     	|         Pour sprinter         	|
|                                                                                                                                                                                                                                      <img src="https://static.thenounproject.com/png/486803-200.png" height="60px"/>                                                                                                                                                                                                                                      	|      Pour changer d'item      	|
|                                                                                                                                                      <div style="display: flex; flex-flow: row nowrap; justify-content: center; align-items: center;"> 		<kbd>Shift</kbd> <h4 style="padding-left: 10px">+</h4> <img src="https://static.thenounproject.com/png/486803-200.png" height="60px"/> 	</div>                                                                                                                                                      	| Pour zoomer sur la mini-carte 	|
|                                                                                                                                                                                                                                                                        <kbd>E</kbd>                                                                                                                                                                                                                                                                       	|         Pour utiliser         	|
|                                                                                                                                                                                                                                                                        <kbd>F</kbd>                                                                                                                                                                                                                                                                       	|         Pour ramasser         	|

## Réflexion philosophique très profonde
|                                                                                                                                                        Contributeur                                                                                                                                                        	|       Fonction(s)       	|                                                          Avis                                                         	|
|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:	|:-----------------------:	|:---------------------------------------------------------------------------------------------------------------------:	|
|            <a style="flex-flow: column nowrap" href="https://github.com/killax-d"><h6 style="margin: 0">@Killax-D</h6><img src="https://avatars3.githubusercontent.com/u/42719459?s=460&u=b0dcdb0a96f1ebc0825a4a690474a73cca883c83&v=4" alt="Killax-D" height="120" style="vertical-align:top; margin:4px"></a>            	|      Lead Developer     	|                      <img height="150" src="https://i.giphy.com/media/oZEBLugoTthxS/giphy.webp"/>                     	|
| <a style="flex-flow: column nowrap" href="https://github.com/Rokem-prog"><h6 style="margin: 0">@Rokem</h6><img src="https://cdn.discordapp.com/attachments/765202757878939648/795316855027138590/136048486_178091217339501_6094403774743025825_n.png" alt="Rokem" height="120" style="vertical-align:top; margin:4px"></a> 	|            IA           	|          <img height="150" src="https://media1.tenor.com/images/7b450db04f95674f3af1f8d378f13650/tenor.gif"/>         	|
|                                                              <h6 style="margin: 0">@Carl</h6><img src="https://www.wired.com/wp-content/uploads/2015/05/Pinhead-Hellraiser1.jpg" alt="Carlo el'calamaro" height="120" style="vertical-align:top; margin:4px">                                                              	|   Evaluator Support IA  	|                                   RRReeeechercher... RRReeeechercher... TROUVER !!!                                   	|
|                                                                     <h6 style="margin: 0">@Viag</h6><img src="https://pbs.twimg.com/profile_images/1087432799764660224/H37WN53L.jpg" alt="Ismaël" height="120" style="vertical-align:top; margin:4px">                                                                     	| Evaluator Support Tools 	|                                                   Je préfère python                                                   	|
|                    <h6 style="margin: 0">@Samad</h6><img src="https://s.yimg.com/uu/api/res/1.2/vAvUdqUBeuEJLtCWXSUhyQ--~B/aD03MTQ7dz0xMDIwO2FwcGlkPXl0YWNoeW9u/https://media.zenfs.com/fr/elle-fr.fr/43699fae8cded45ece4412b2baa8e6be" alt="Samad" height="120" style="vertical-align:top; margin:4px">                   	|   Gameplay / Entities   	|  <img height="150" src="https://media1.tenor.com/images/b09d745c0c09cb5c7d9c4dd1fc96cc50/tenor.gif?itemid=9563129" /> 	|
|                                <a style="flex-flow: column nowrap" href="https://github.com/bilnamd"><h6 style="margin: 0">@Bilnamd</h6><img src="https://www.fbi.gov/image-repository/gotti.jpeg/@@images/image/high" alt="Nabil" height="120" style="vertical-align:top; margin:4px"></a>                                	|   Gameplay / Entities   	|        <img height="150" src="https://i.pinimg.com/originals/b8/ee/8b/b8ee8bf6f1f677f54fe3744a7e62b2d8.jpg" />        	|
|                          <h6 style="margin: 0">@Julio</h6><img src="https://cdn.discordapp.com/attachments/787703407325609984/795368766778245160/deguise-en-jeff-tuche-un-gilet-jaune-fait-le-buzz-sur-les-reseaux-sociaux.jpeg" alt="Julio" height="120" style="vertical-align:top; margin:4px">                          	|        Developer        	|         <img height="150" src="https://media1.tenor.com/images/c7504b9fb03c95b3b5687d744687e11c/tenor.gif" />         	|

## Version
Dernière version stable : Release-1.0

[Linkwhichoverkillyourcomputeur](https://tu_es_mort)