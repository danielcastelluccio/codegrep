codegrep: bin/main.o bin/parser.o bin/action.o bin/tree_util.o bin/c.o
	$(CC) -ltree-sitter -o codegrep bin/main.o bin/parser.o bin/action.o bin/tree_util.o bin/c.o

bin/c.o: src/languages/c.c src/languages/c.h
	$(CC) -c -o bin/c.o src/languages/c.c

bin/tree_util.o: src/tree_util.c src/tree_util.h src/parser.h
	$(CC) -c -o bin/tree_util.o src/tree_util.c

bin/action.o: src/action.c src/action.h src/languages/c.h
	$(CC) -c -o bin/action.o src/action.c

bin/parser.o: src/parser.c src/parser.h
	$(CC) -c -o bin/parser.o src/parser.c

bin/main.o: src/main.c src/parser.h src/action.h
	$(CC) -c -o bin/main.o src/main.c

clean:
	rm bin/* codegrep
