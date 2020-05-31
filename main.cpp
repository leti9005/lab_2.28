#include <iostream>

int strlen(char *str) {
    const int max_str_len = 80;
    int i = 0;
    while(i<max_str_len) {
        if(str[i] == 0) {
            return i;
        }
        i++;
    }
    return max_str_len;
}

int strcmp(const char *s0, const char *s1) {
    int i = 0;
    while(s0[i] == s1[i] && s0[i] != 0 && s1[i] != 0) {
        i++;
    }
    return i;
}

int strpos(char *where, char *what) {
    int search_len = strlen(where) - strlen(what);
    int what_len = strlen(what);
    for(int i = 0;i<=search_len;i++) {
        if(strcmp(&where[i], &what[0]) == what_len) {
            return i;
        }
    }
    return -1;
}

char *replace(char *source_string, char *old_string, char *new_string) {
    int old_string_pos = strpos(source_string, old_string);
    if(old_string_pos == -1) {
        return nullptr;
    }

    int new_string_len = strlen(new_string);
    int source_string_len = strlen(source_string);
    int old_string_len = strlen(old_string);
    int old_tail_pos = old_string_pos + old_string_len;
    int new_tail_pos = old_string_pos + new_string_len;
    int tail_len = source_string_len - old_tail_pos;
    int result_size = source_string_len - old_string_len + new_string_len;

    char *result = new char[result_size];
    for(int i = 0; i < old_string_pos; i++) {
        result[i] = source_string[i];
    }

    for(int i = 0;i<new_string_len;i++) {
        result[old_string_pos + i] = new_string[i];
    }

    for(int i = 0;i<tail_len;i++) {
        result[new_tail_pos+i] = source_string[old_tail_pos+i];
    }
    return  result;
}

int main() {
    char *hello = (char *) "Hello, World!";
    char *new_hello = replace(hello, (char *) "World", (char *) "pretty World");
    std::cout << new_hello  << std::endl;
    char *next_hello = replace(new_hello, (char *) "pretty", (char *) "ugly");
    std::cout << next_hello  << std::endl;
    return 0;
}
