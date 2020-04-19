Compiler le programme :

gcc -Wall src/EasyShare.c src/gestion_graphique.c src/user.c src/ressource.c src/calendar.c -ljson-c $(pkg-config --cflags --libs gtk+-2.0) -o EasyShare.exe


Exécuter le programme :

./EasyShare.exe
