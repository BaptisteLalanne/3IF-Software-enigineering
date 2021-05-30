CPP=g++
CPPFLAGS= -O3 -Wall -ansi -pedantic -std=c++11 -g
EXEC= airwatcher
TEST= test
REPO= dataset

all: $(EXEC) $(TEST)

airwatcher: main.o Capteur.o Mesure.o Service.o Utilisateur.o
#.o vers executable airwatcher, operation d'edition de liens, etape relieur
	$(CPP) -o $@ $+
test: Test.o Capteur.o Mesure.o Service.o Utilisateur.o
	$(CPP) -o $@ $+

%.o: %.cpp %.h
#traduction en langage machine (preprocesseur + compilateur + assembleur)
	$(CPP) -c $< $(CPPFLAGS)


debug:
	valgrind ./airwatcher

.PHONY: clean mproper
#permet d'assurer la commande make mproper ou make clean meme si un fichier a un tel nom dans le dossier courant

clean:
#suppression de tous les fichiers objets (.o)
	clear
	rm -rf *.o

mproper: clean
#permet une reconstruction totale du projet, s'assure que tous les fichiers .o ont ete supprimes avant
	rm -rf $(EXEC)
	rm -rf $(TEST)
	clear

run: $(EXEC)
	./$(EXEC) $(REPO)

runTest: $(TEST)
	./$(TEST)
