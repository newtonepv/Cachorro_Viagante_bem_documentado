VERSION:= 1.0

all: lista item cidade
	gcc -o caixeiro main.c lista.o pilha.o item.o cidade.o -Wall -std=c99

lista:
	gcc -c lista.c

item:
	gcc -c item.c

cidade:
	gcc -c cidade.c

clean:
	rm -rf *.o

run:
	./caixeiro