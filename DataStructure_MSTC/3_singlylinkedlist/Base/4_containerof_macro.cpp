#include <stddef.h>
#include <stdio.h>

// Define the structure
struct my_struct {
    int a;
    double b;
    char c;
};

// Define container_of macro
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

int main() {
    struct my_struct example;
    example.a = 10;
    example.b = 20.5;
    example.c = 'z';

    // Print the address of the structure
    printf("Address of example (struct my_struct): %p\n", (void*)&example);

    // Print the address and offset of each member within the structure
    printf("Address of example.a: %p, Offset: %zu\n", (void*)&example.a, offsetof(struct my_struct, a));
    printf("Address of example.b: %p, Offset: %zu\n", (void*)&example.b, offsetof(struct my_struct, b));
    printf("Address of example.c: %p, Offset: %zu\n", (void*)&example.c, offsetof(struct my_struct, c));

    // Get a pointer to the member 'c'
    char* c_ptr = &example.c;
    printf("Address of example.c (using pointer c_ptr): %p\n", (void*)c_ptr);

    // Use container_of to get the pointer to the enclosing structure
    struct my_struct* example_ptr = container_of(c_ptr, struct my_struct, c);
    printf("Address calculated by container_of: %p\n", (void*)example_ptr);

    // Verify if we got the correct pointer
    if (example_ptr == &example) {
        printf("container_of works correctly!\n");
    }
    else {
        printf("container_of failed.\n");
    }

    return 0;
}
