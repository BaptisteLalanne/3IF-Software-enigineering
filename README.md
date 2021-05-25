# Génie Logiciel - 3IF
### _Fait par Arthur ROSSELLO-POULET, Rami EL RIFAI, Capucine BOIS, Baptiste LALANNE_




Dans le cadre du projet en Génie Logiciel, nous développons deux fonctionalités d'un programme d'analyse de la polution de l'air.

Fonctionalités retunues pour ce code:
- Vérification des capteurs
- Calculer indice ATMO dans une région et une période donnée


## Utilisation du programme

```sh
make
```

Par défaut le makefile prend un fichier avec les différents csv requis dans le dossier actuel "$(PWD)/dataset" 
Pour donner une différente adresse/nom de fichier pour les data, utiliser:
```sh
make repo_test="./monDossier"
```

## Utilisation des tests
*Pour utiliser les tests, il faut au préalable créer l'executable*
```
make
```

```sh
cd Tests
sh maketest.sh
```
> Note: Il est possible de compiler "manuellement" et de tester les méthodes test avec l'option à l'éxecution `-test` 

```bash
./main -test "./dataset"
```
Pour observer la validation des tests unitaires et de bout en bout, il est possible d'ouvrir le .csv crée ou tout simplement observé le passage des tests sur le terminal.

## *Versions*
Il y a peu de version car nous utilisons un IDE (CLion de JetBrains) pour coder en direct sur une même session. Nous faisons donc un commit par séance plutôt que un commit par features ou debug.
