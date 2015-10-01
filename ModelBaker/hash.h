#ifndef HASH_H
#define HASH_H
#include <string>
unsigned int HashString(const char* str){
    const int A = 54059;
    const int B = 76963;
    const int C = 86969;

    unsigned int h = 32;
    while(*str){
        h = (h * A) ^(str[0] * B);
        str++;
    }
    return h % C;
}

#endif // HASH_H

