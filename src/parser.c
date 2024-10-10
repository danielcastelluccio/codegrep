#include "parser.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TSLanguage *(*open_parser(char *name))(void) {
    char buffer[32] = {};
    strcpy(buffer, "libtree-sitter-");
    strcpy(buffer + 15, name);
    strcpy(buffer + 15 + strlen(name), ".so");
    void *library = dlopen(buffer, RTLD_LAZY);
    memset(buffer, 0, 32);
    strcpy(buffer, "tree_sitter_");
    strcpy(buffer + 12, name);
    return dlsym(library, buffer);
}

ParseResult parse_file(char *parser_name, char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        return (ParseResult) { NULL, NULL };
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *contents = malloc(size + 1);
    contents[size] = '\0';
    fread(contents, 1, size, file);

    TSLanguage *(*language_parser)() = open_parser(parser_name);
    TSParser *parser = ts_parser_new();
    ts_parser_set_language(parser, language_parser());

    TSTree *tree = ts_parser_parse_string(parser, NULL, contents, size);

    free(contents);
    return (ParseResult) { tree, contents };
}
