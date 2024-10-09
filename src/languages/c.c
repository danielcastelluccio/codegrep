#include "c.h"

#include <stdio.h>
#include <string.h>

bool print_functions_c(ParseResult parse_result) {
    TSNode root = ts_tree_root_node(parse_result.tree);
    size_t root_child_count = ts_node_child_count(root);
    for (size_t j = 0; j < root_child_count; j++) {
        TSNode declaration = ts_node_child(root, j);
        if (strcmp(ts_node_type(declaration), "function_definition") == 0) {
            TSNode declarator = ts_node_child_by_field_name(declaration, "declarator", 10);
            TSNode name = ts_node_child_by_field_name(declarator, "declarator", 10);

            size_t name_start = ts_node_start_byte(name);
            size_t name_end = ts_node_end_byte(name);
            size_t name_size = name_end - name_start;

            char *name_reallocated = malloc(name_size + 1);
            if (name_reallocated == NULL) {
                return false;
            }

            name_reallocated[name_size] = '\0';
            memcpy(name_reallocated, parse_result.source + name_start, name_size);

            printf("%s\n", name_reallocated);
        }
    }

    return true;
}
