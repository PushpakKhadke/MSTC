#include <stdio.h>

// Correct structure definition
struct inner {
    int a;
    int b;
};

struct outer {
    char c;
    struct inner in;
};

// Function to calculate the offset of a member within a structure
size_t get_offset(void* member_ptr, void* base_ptr) {
    return (char*)member_ptr - (char*)base_ptr;
}

int main() {
    struct outer out = { 'A', {12,45} };  // Define an instance of the outer structure
    struct inner* p_in = &out.in;  // Pointer to the member 'in'

    // Calculate the offset of 'in' within 'outer'
    size_t offset = get_offset(&(out.in), &out);

    // Print the offset
    printf("Offset of 'in' in 'outer': %zu bytes\n", offset);

    // Print the address of 'out' and 'in'
    printf("Address of 'out': %p\n", (void*)&out);
    printf("Address of 'in' (p_in): %p\n", (void*)p_in);

    // Compute the address of the containing structure 'outer'
    struct outer* p_out = (struct outer*)((char*)p_in - offset);

    // Print the calculated address of 'outer'
    printf("Calculated outer address from p_in: %p\n", (void*)p_out);

    // Print to verify if the calculated address matches the original address of 'out'
    printf("Original outer address: %p\n", (void*)&out);
    printf("Does calculated address match original? %s\n", (p_out == &out) ? "Yes" : "No");

    return 0;
}
