#include "action.h"

#include <string.h>

#include "languages/c.h"

ParseResult parse(char *language, char *file_path) {
    return parse_file(language, file_path);
}

bool print_functions(char* language, ParseResult parse_result) {
    if (strcmp(language, "c") == 0) {
        print_functions_c(parse_result);
    } else {
        return false;
    }

    return true;
}
