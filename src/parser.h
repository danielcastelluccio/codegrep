#ifndef PARSER_H
#define PARSER_H

#include <tree_sitter/api.h>

typedef struct {
    TSTree *tree;
    char *source;
} ParseResult;

ParseResult parse_file(char *parser_name, char *file_path);

#endif
