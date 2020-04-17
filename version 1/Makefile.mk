MAKE = make
GCC = gcc
CFLAGS+= -Wall $(shell pkg-config --cflags json-c) $(shell pkg-config --cflags --libs gtk+-2.0)
LDFLAGS+=$(shell pkg-config --libs json-c)
INCLUDE=./lib
SRC = ./src/EasyShare.c ./src/gestion_graphique.c ./src/ressource.c ./src/user.c
OBJ = $(SRC:.c=.o)
EXEC = EasyShare.exe

all: $(EXEC)

$(EXEC): $(OBJ) $(INCLUDE)/*.h
	$(GCC) $(CFLAGS) $(LDFLAGS) -o $(EXEC) $(OBJ) -I$(INCLUDE)

src/main.o : src/EasyShare.c
	$(GCC) $(CFLAGS) -o ./src/main.o -c ./src/EasyShare.c

src/main.o : src/gestion_graphique.c
	$(GCC) $(CFLAGS) -o ./src/gestion_graphique.o -c ./src/gestion_graphique.c

src/main.o : src/ressource.c
	$(GCC) $(CFLAGS) -o ./src/ressource.o -c ./src/ressource.c

src/main.o : src/user.c
	$(GCC) $(CFLAGS) -o ./src/user.o -c ./src/user.c

clean:
	rm -rf $(OBJ) $(EXEC)
