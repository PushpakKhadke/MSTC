#include <stdio.h>
#include <stddef.h> // For size_t

// Define a structure for the linked list node
struct list_node {
    struct list_node* next;
};

// Define a structure that contains the actual data and the list node
struct data_node {
    int data;
    struct list_node node; // Embedded linked list node
};

// Function to calculate the offset of a member within a structure
size_t get_offset(void* member_ptr, void* base_ptr) {
    return (char*)member_ptr - (char*)base_ptr;
}

// Function to calculate the containing structure pointer from the member pointer
void* get_container(void* member_ptr, size_t offset) {
    return (char*)member_ptr - offset;
}

// Function to add a node to the linked list with debugging logs
void add_node(struct list_node** head, struct list_node* new_node) {
    printf("Adding node with address: %p\n", (void*)new_node);
    printf("Current head address: %p\n", (void*)*head);

    new_node->next = *head; // Set the new node's next pointer to the current head
    *head = new_node; // Update the head to the new node

    printf("New head address after adding: %p\n", (void*)*head);
    printf("Next node address in the new head: %p\n", (void*)(*head)->next);
}

int main() {
    // Initialize the head of the linked list
    struct list_node* head = NULL;
    printf("Initial head address: %p\n", (void*)head);

    // Create data nodes
    struct data_node node1 = { 1, {NULL} };
    struct data_node node2 = { 2, {NULL} };
    struct data_node node3 = { 3, {NULL} };

    // Add nodes to the linked list
    add_node(&head, &node1.node);
    add_node(&head, &node2.node);
    add_node(&head, &node3.node);

    return 0;
}
