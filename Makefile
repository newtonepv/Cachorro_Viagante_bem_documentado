VERSION:= 1.0

all:
	gcc -o caixeiro main.c lista.c item.c cidade.c -Wall -std=c99

lista.c:
	gcc -c lista.c

item.c:
	gcc -c item.c

cidade.c:
	gcc -c cidade.c

clean:
	rm -rf *.o

run:
	./caixeiro $(ARGS)
