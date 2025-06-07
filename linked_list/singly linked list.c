#include <stdio.h>
#include <stdlib.h>

// Define the node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Add at the beginning
struct Node* addFirst(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    newNode->next = head;
    return newNode;
}

// Add at the end
struct Node* addLast(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    if (head == NULL) {
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Delete first node
struct Node* delFirst(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

// Delete last node
struct Node* delLast(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    struct Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    return head;
}

// Insert at position (1-based index)
struct Node* insertAtPos(struct Node* head, int value, int pos) {
    if (pos < 1) {
        printf("Invalid position.\n");
        return head;
    }
    if (pos == 1) {
        return addFirst(head, value);
    }

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds.\n");
        return head;
    }

    struct Node* newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

// Delete at position (1-based index)
struct Node* delAtPos(struct Node* head, int pos) {
    if (head == NULL || pos < 1) {
        printf("Invalid position or empty list.\n");
        return head;
    }
    if (pos == 1) {
        return delFirst(head);
    }

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        printf("Position out of bounds.\n");
        return head;
    }

    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
    return head;
}

// Display the linked list
void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Free the entire list (cleanup)
struct Node* freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    return NULL;
}

int main() {
    struct Node* head = NULL;
    int choice, value, pos;

    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. Add First\n");
        printf("2. Add Last\n");
        printf("3. Delete First\n");
        printf("4. Delete Last\n");
        printf("5. Insert at Position\n");
        printf("6. Delete at Position\n");
        printf("7. Display List\n");
        printf("8. Exit\n");
        printf("==========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to add first: ");
                scanf("%d", &value);
                head = addFirst(head, value);
                break;

            case 2:
                printf("Enter value to add last: ");
                scanf("%d", &value);
                head = addLast(head, value);
                break;

            case 3:
                head = delFirst(head);
                break;

            case 4:
                head = delLast(head);
                break;

            case 5:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                printf("Enter position to insert at (1-based index): ");
                scanf("%d", &pos);
                head = insertAtPos(head, value, pos);
                break;

            case 6:
                printf("Enter position to delete (1-based index): ");
                scanf("%d", &pos);
                head = delAtPos(head, pos);
                break;

            case 7:
                display(head);
                break;

            case 8:
                printf("Exiting program. Goodbye!\n");
                head = freeList(head);
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
