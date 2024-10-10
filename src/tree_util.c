#include "tree_util.h"

#include <string.h>

char *ts_node_extract_string(ParseResult parse_result, TSNode node) {
    size_t name_start = ts_node_start_byte(node);
    size_t name_end = ts_node_end_byte(node);
    size_t name_size = name_end - name_start;

    char *result = malloc(name_size + 1);
    result[name_size] = '\0';
    memcpy(result, parse_result.source + name_start, name_size);

    return result;
}
