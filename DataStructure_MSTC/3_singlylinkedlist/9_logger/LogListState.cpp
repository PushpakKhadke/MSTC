#include <stdio.h>
#include <stddef.h> // For size_t
#include <stdlib.h> // For malloc and free

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

// Function to log the current state of the linked list
void log_list_state(struct list_node* head) {
    printf("\n[LOG LIST STATE] Current list state:\n");
    struct list_node* current = head;
    while (current != NULL) {
        struct data_node* data = (struct data_node*)get_container(current, get_offset(&(((struct data_node*)0)->node), (void*)0));
        printf("[LOG LIST STATE] Node address: %p, Data: %d, Next: %p\n", (void*)current, data->data, (void*)current->next);
        current = current->next;
    }
    printf("[LOG LIST STATE] End of list state.\n");
}

// Function to add a node to the linked list with debugging logs
void add_node(struct list_node** head, struct list_node* new_node) {
    printf("\n[ADD NODE] Adding node with address: %p\n", (void*)new_node);
    printf("[ADD NODE] Current head address: %p\n", (void*)*head);

    new_node->next = *head; // Set the new node's next pointer to the current head
    *head = new_node; // Update the head to the new node

    printf("[ADD NODE] New head address after adding: %p\n", (void*)*head);
    printf("[ADD NODE] Next node address in the new head: %p\n", (void*)(*head)->next);

    log_list_state(*head); // Log the state of the list after adding a node
}

// Function to remove a node from the linked list using manual container_of functionality
void remove_node(struct list_node** head, struct list_node* node_to_remove) {
    printf("\n[REMOVE NODE] Attempting to remove node with address: %p\n", (void*)node_to_remove);

    if (*head == NULL) {
        printf("[REMOVE NODE] List is empty; cannot remove node.\n");
        return;
    }

    size_t offset = get_offset(&(((struct data_node*)0)->node), (void*)0);

    // If the node to remove is the head
    if (*head == node_to_remove) {
        *head = (*head)->next;
        free(get_container(node_to_remove, offset)); // Free the memory of the removed node
        printf("[REMOVE NODE] Removed head node. New head address: %p\n", (void*)*head);
        log_list_state(*head); // Log the state of the list after removing a node
        return;
    }

    struct list_node* current = *head;

    while (current->next != NULL && current->next != node_to_remove) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("[REMOVE NODE] Node to remove not found in the list.\n");
    }
    else {
        // Bypass the node to remove
        current->next = node_to_remove->next;
        free(get_container(node_to_remove, offset)); // Free the memory of the removed node
        printf("[REMOVE NODE] Node removed. Current node now points to: %p\n", (void*)current->next);
        log_list_state(*head); // Log the state of the list after removing a node
    }
}

// Function to find a node by data value in the linked list using manual container_of functionality
struct data_node* find_node(struct list_node* head, int data_value) {
    struct list_node* current = head;
    size_t offset = get_offset(&(((struct data_node*)0)->node), (void*)0);

    printf("\n[FIND NODE] Searching for node with data value: %d\n", data_value);

    while (current != NULL) {
        struct data_node* data = (struct data_node*)get_container(current, offset);
        if (data->data == data_value) {
            printf("[FIND NODE] Node with data %d found at address: %p\n", data_value, (void*)data);
            return data;
        }
        current = current->next;
    }

    printf("[FIND NODE] Node with data %d not found in the list.\n", data_value);
    return NULL;
}

// Function to clear the entire linked list and free all allocated memory
void clear_list(struct list_node** head) {
    struct list_node* current = *head;
    struct list_node* next;
    size_t offset = get_offset(&(((struct data_node*)0)->node), (void*)0);

    printf("\n[CLEAR LIST] Clearing all nodes in the linked list...\n");

    while (current != NULL) {
        next = current->next; // Store the next node
        printf("[CLEAR LIST] Freeing node with address: %p\n", (void*)current);
        free(get_container(current, offset)); // Free the memory of the current node
        current = next; // Move to the next node
    }

    *head = NULL;
    printf("[CLEAR LIST] All nodes cleared. List is now empty.\n");
    log_list_state(*head); // Log the state of the list after clearing it
}

// Function to count the number of nodes in the linked list using manual container_of functionality
int count_nodes(struct list_node* head) {
    struct list_node* current = head;
    int count = 0;

    printf("\n[COUNT NODES] Counting nodes in the linked list...\n");

    while (current != NULL) {
        count++;
        printf("[COUNT NODES] Visiting node with address: %p, current count: %d\n", (void*)current, count);
        current = current->next;
    }

    printf("[COUNT NODES] Total number of nodes: %d\n", count);
    return count;
}

// Function to reverse the linked list using manual container_of functionality
void reverse_list(struct list_node** head) {
    struct list_node* prev = NULL;
    struct list_node* current = *head;
    struct list_node* next = NULL;

    printf("\n[REVERSE LIST] Reversing the linked list...\n");

    while (current != NULL) {
        next = current->next;  // Store next
        current->next = prev;  // Reverse current node's pointer
        prev = current;        // Move pointers one position ahead
        current = next;
        printf("[REVERSE LIST] Current node address: %p, Next node address: %p\n", (void*)prev, (void*)current);
    }

    *head = prev;
    printf("[REVERSE LIST] Linked list reversed. New head address: %p\n", (void*)*head);
    log_list_state(*head); // Log the state of the list after reversing
}

// Function to print the linked list using the manual container_of functionality with enhanced debugging logs
void print_linked_list(struct list_node* head) {
    struct list_node* current = head;
    printf("\n[PRINT LIST] Starting to print linked list...\n");

    while (current != NULL) {
        // Calculate the offset of 'node' in 'data_node'
        size_t offset = get_offset(&(((struct data_node*)0)->node), (void*)0);
        printf("[PRINT LIST] Offset of 'node' in 'data_node': %zu bytes\n", offset);

        // Get the pointer to the containing structure 'data_node' from the 'node' pointer
        struct data_node* data = (struct data_node*)get_container(current, offset);
        printf("[PRINT LIST] Current list node address: %p\n", (void*)current);
        printf("[PRINT LIST] Data node address derived from current list node: %p\n", (void*)data);
        printf("[PRINT LIST] Data value in data node: %d\n", data->data);

        // Print the data
        printf("[PRINT LIST] Data: %d\n", data->data);

        // Log the next node pointer
        printf("[PRINT LIST] Next node pointer in current list node: %p\n", (void*)current->next);

        // Move to the next node
        current = current->next;
        printf("[PRINT LIST] Moved to the next node: %p\n", (void*)current);
    }

    printf("[PRINT LIST] Finished printing linked list.\n");
}

int main() {
    // Initialize the head of the linked list
    struct list_node* head = NULL;
    printf("[MAIN] Initial head address: %p\n", (void*)head);

    // Create data nodes dynamically using malloc
    struct data_node* node1 = (struct data_node*)malloc(sizeof(struct data_node));
    node1->data = 1;
    node1->node.next = NULL;

    struct data_node* node2 = (struct data_node*)malloc(sizeof(struct data_node));
    node2->data = 2;
    node2->node.next = NULL;

    struct data_node* node3 = (struct data_node*)malloc(sizeof(struct data_node));
    node3->data = 3;
    node3->node.next = NULL;

    // Add nodes to the linked list
    add_node(&head, &node1->node);
    add_node(&head, &node2->node);
    add_node(&head, &node3->node);

    // Print the linked list
    print_linked_list(head);

    // Count the nodes in the linked list
    count_nodes(head);

    // Reverse the linked list
    reverse_list(&head);

    // Print the linked list after reversing
    print_linked_list(head);

    // Find a node in the linked list
    find_node(head, 2);

    // Remove a node from the linked list
    remove_node(&head, &node2->node);

    // Print the linked list after removal
    print_linked_list(head);

    // Count the nodes in the linked list after removal
    count_nodes(head);

    // Find a node that no longer exists
    find_node(head, 2);

    // Clear the entire list
    clear_list(&head);

    // Print the linked list after clearing
    print_linked_list(head);

    return 0;
}
