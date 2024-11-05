VERSION:= 1.0

all: all_dp
	gcc -o caixeiro main.c lista.o item.o cidade.o caminho.o -Wall -std=c99

all_dp: lista item cidade caminho
	gcc -o caixeiro_dp main_heldkarp.c lista.o item.o cidade.o caminho.o -Wall -std=c99

lista:
	gcc -c lista.c

item:
	gcc -c item.c

cidade:
	gcc -c cidade.c

caminho:
	gcc -c caminho.c

clean:
	rm caixeiro_dp caixeiro -rf *.o

run:
	./caixeiro
run_dp:
	./caixeiro_dp