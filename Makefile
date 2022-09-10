CFLAGS=-Wall -Wextra -std=c99

build:
	gcc $(CFLAGS) -o tema1 tema1.c lists.c card_decks.c 

pack:
	zip -FSr 311CA_DinutaEduardStefan_Tema3.zip README Makefile *.c *.h

clean:
	rm -f tema1 *.o

.PHONY: pack clean
