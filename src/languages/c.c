#include "c.h"

#include <stdio.h>
#include <string.h>

#include "../tree_util.h"

void print_functions_c(ParseResult parse_result) {
    TSNode root = ts_tree_root_node(parse_result.tree);
    size_t root_child_count = ts_node_child_count(root);
    for (size_t j = 0; j < root_child_count; j++) {
        TSNode declaration = ts_node_child(root, j);
        if (strcmp(ts_node_type(declaration), "function_definition") == 0) {
            TSNode declarator = ts_node_child_by_field_name(declaration, "declarator", 10);
            TSNode name_node = ts_node_child_by_field_name(declarator, "declarator", 10);

            char *name = ts_node_extract_string(parse_result, name_node);
            printf("%s\n", name);
        }
    }
}
