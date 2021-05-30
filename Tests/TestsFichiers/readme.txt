Programme de tests automatiques - mode d'emploi


-------------------------------------------------------------------------------
test.sh [ repertoire [ fichier.csv ] ]

- repertoire indique le repertoire dans lequel se trouvent les fichiers de
configuration du test
- fichier.csv indique un fichier dans lequel les resultats du tests seront
ajoutes

En l'absence d'arguments, le script traitera le repertoire courant

Fichiers de configuration :
- run : fichier texte indiquant la ligne de commande a executer (obligatoire)
- std.in : fichier texte indiquant une entree clavier a simuler (facultatif)
- std.out : fichier texte indiquant la sortie devant etre produite
(facultatif/validation*)
- stderr.out : fichier texte indiquant la sortie d'erreur devant etre produite
(facultatif/validation*)
- description : fichier texte donnant la description du test (facultatif)
- returncode : fichier texte contenant l'entier code retour attendu 
(facultatif/validation*)
- *.outfile : un ou plusieurs fichiers devant etre produits par le programme
(facultatif/validation*)
  si le fichier s'appelle exemple.txt.outfile, il sera compare a exemple.txt

*validation indique que le script va tester la conformite, si cette conformite
n'est pas 
satisfaite, il l'indiquera

-------------------------------------------------------------------------------
mktest.sh

