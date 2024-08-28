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

    // Assign values to the struct members for demonstration
    example.a = 10;
    example.b = 'z';
    example.c = 20.5;

    // Print sizes of the struct members
    printf("Size of int a: %zu bytes\n", sizeof(((struct Example*)0)->a));
    printf("Size of char b: %zu bytes\n", sizeof(((struct Example*)0)->b));
    printf("Size of double c: %zu bytes\n", sizeof(((struct Example*)0)->c));
    printf("Total size of struct Example: %zu bytes\n", sizeof(struct Example));

    // Calculate and print offsets of the struct members
    size_t offset_a = offset_of(&example.a, &example);
    printf("Offset of 'a' is %zu bytes\n", offset_a);

    size_t offset_b = offset_of(&example.b, &example);
    printf("Offset of 'b' is %zu bytes\n", offset_b);

    size_t offset_c = offset_of(&example.c, &example);
    printf("Offset of 'c' is %zu bytes\n", offset_c);

    // Print the addresses and values of each struct member
    printf("Address of example.a: %p, Value of a: %d\n", (void*)&example.a, example.a);
    printf("Address of example.b: %p, Value of b: %c\n", (void*)&example.b, example.b);
    printf("Address of example.c: %p, Value of c: %f\n", (void*)&example.c, example.c);

    return 0;
}
