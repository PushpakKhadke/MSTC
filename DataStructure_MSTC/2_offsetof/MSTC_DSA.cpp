#include <stddef.h>
#include <stdio.h>

// Define a structure
struct example_struct {
    int a;
    double b;
    char c;
};

int main() {
	printf("sizeof(int) : %lld\n", sizeof(int));
	printf("sizeof(double) : %lld\n", sizeof(double));
	printf("sizeof(char) : %lld\n", sizeof(char));
	
	printf("Offset of 'a': %lld\n", offsetof(struct example_struct, a));
	printf("Offset of 'b': %lld\n", offsetof(struct example_struct, b));
	printf("Offset of 'c': %lld\n", offsetof(struct example_struct, c));

    return 0;
}
