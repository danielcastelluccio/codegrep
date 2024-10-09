codegrep: bin/main.o bin/parser.o
	$(CC) -ltree-sitter -o codegrep bin/main.o bin/parser.o

bin/parser.o: src/parser.c src/parser.h
	$(CC) -c -o bin/parser.o src/parser.c

bin/main.o: src/main.c src/parser.h
	$(CC) -c -o bin/main.o src/main.c

clean:
	rm bin/* codegrep
