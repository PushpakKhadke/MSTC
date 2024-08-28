#include <stddef.h>
#include <stdio.h>

// Define a structure
struct example_struct {
    int a;
    double b;
    char c;
};

// Use container_of to get the parent structure from a member pointer
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

int main() {
    struct example_struct ex = {108,23.34,'A'};
	
    char* c_ptr = &ex.c;  // Pointer to the member 'c'

    // Get the pointer to the containing structure
    struct example_struct* ex_ptr = container_of(c_ptr, struct example_struct, c);

    // Check if the computed address is correct
	printf("Address of structure %p\n", (void*)&ex);
	printf("Address of structure using offsetof %p\n", (void*)ex_ptr);
	
    if (ex_ptr == &ex) {
        printf("container_of works correctly !\n");
    }
    else {
        printf("container_of failed.\n");
    }

    return 0;
}
