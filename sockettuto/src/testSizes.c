#include<limits.h>
#include<stdint.h>
#include<stdio.h>

// ---
int main(int argc, char **argv){
    printf("CHAR_BIT is %d\n\n", CHAR_BIT);

    printf("sizeof(char) is %zu\n", sizeof(char));
    printf("sizeof(short) is %zu\n", sizeof(short));
    printf("sizeof(int) is %zu\n", sizeof(int));
    printf("sizeof(long) is %zu\n", sizeof(long));
    printf("sizeof(long long) is %zu\n\n", sizeof(long long));

    printf("sizeof(int8_t) is %zu\n", sizeof(int8_t));
    printf("sizeof(int16_t) is %zu\n", sizeof(int16_t));
    printf("sizeof(int32_t) is %zu\n", sizeof(int32_t));
    printf("sizeof(int64_t) is %zu\n\n", sizeof(int64_t));

    printf("sizeof(uint8_t) is %zu\n", sizeof(uint8_t));
    printf("sizeof(uint16_t) is %zu\n", sizeof(uint16_t));
    printf("sizeof(uint32_t) is %zu\n", sizeof(uint32_t));
    printf("sizeof(uint64_t) is %zu\n\n", sizeof(uint64_t));
    
    return 0;
}
