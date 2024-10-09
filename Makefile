codegrep: bin/main.o bin/parser.o bin/c.o
	$(CC) -ltree-sitter -o codegrep bin/main.o bin/parser.o bin/c.o

bin/c.o: src/languages/c.c src/languages/c.h
	$(CC) -c -o bin/c.o src/languages/c.c

bin/parser.o: src/parser.c src/parser.h
	$(CC) -c -o bin/parser.o src/parser.c

bin/main.o: src/main.c src/parser.h src/languages/c.h
	$(CC) -c -o bin/main.o src/main.c

clean:
	rm bin/* codegrep
