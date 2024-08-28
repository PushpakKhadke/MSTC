#include <stdio.h>
#include <stddef.h> // For size_t

struct Example {
    double c;
    int a;
    char b;
};

// Generalized function to calculate offset of any member
size_t offset_of(void* member, void* base) {
    return (size_t)((char*)member - (char*)base);
}

int main()
{
    struct Example example;

    printf("Size of int a: %zu bytes\n", sizeof(((struct Example*)0)->a));
    printf("Size of char b: %zu bytes\n", sizeof(((struct Example*)0)->b));
    printf("Size of double c: %zu bytes\n", sizeof(((struct Example*)0)->c));
    printf("Total size of struct Example: %zu bytes\n", sizeof(struct Example));

    size_t offset_a = offset_of(&example.a, &example);
    printf("Offset of 'a' is %zu bytes\n", offset_a);

    size_t offset_b = offset_of(&example.b, &example);
    printf("Offset of 'b' is %zu bytes\n", offset_b);

    size_t offset_c = offset_of(&example.c, &example);
    printf("Offset of 'c' is %zu bytes\n", offset_c);
}
