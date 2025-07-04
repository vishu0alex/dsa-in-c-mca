#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = newNode; // Important: Initially circular
    return newNode;
}

struct Node* addFirst(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    if (head == NULL) {
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    newNode->next = head;
    temp->next = newNode;
    return newNode; // new head
}

struct Node* addLast(struct Node* head, int value) {
    struct Node* newNode = createNode(value);
    if (head == NULL) {
        return newNode;
    }
    struct Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

struct Node* delFirst(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    if (head->next == head) {
        free(head);
        return NULL;
    }
    struct Node* temp = head;
    struct Node* last = head;
    while (last->next != head) {
        last = last->next;
    }
    head = head->next;
    last->next = head;
    free(temp);
    return head;
}

struct Node* delLast(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    if (head->next == head) {
        free(head);
        return NULL;
    }
    struct Node* temp = head;
    while (temp->next->next != head) {
        temp = temp->next;
    }
    struct Node* lastNode = temp->next;
    temp->next = head;
    free(lastNode);
    return head;
}

struct Node* insertAtPos(struct Node* head, int value, int pos) {
    if (pos < 1) {
        printf("Invalid position.\n");
        return head;
    }
    if (pos == 1) {
        return addFirst(head, value);
    }

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp->next != head; i++) {
        temp = temp->next;
    }
    if (temp->next == head && pos != 2) {
        printf("Position out of bounds.\n");
        return head;
    }

    struct Node* newNode = createNode(value);
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

struct Node* delAtPos(struct Node* head, int pos) {
    if (head == NULL || pos < 1) {
        printf("Invalid position or empty list.\n");
        return head;
    }
    if (pos == 1) {
        return delFirst(head);
    }

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp->next != head; i++) {
        temp = temp->next;
    }
    if (temp->next == head) {
        printf("Position out of bounds.\n");
        return head;
    }

    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    free(nodeToDelete);
    return head;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}

struct Node* freeList(struct Node* head) {
    if (head == NULL)
        return NULL;

    struct Node* temp = head;
    struct Node* nextNode;

    do {
        nextNode = temp->next;
        free(temp);
        temp = nextNode;
    } while (temp != head);

    return NULL;
}

int main() {
    struct Node* head = NULL;
    int choice, value, pos;

    while (1) {
        printf("\n========== CIRCULAR SINGLY LINKED LIST MENU ==========\n");
        printf("1. Add First\n2. Add Last\n3. Delete First\n4. Delete Last\n5. Insert at Position\n6. Delete at Position\n7. Display List\n8. Exit\n");
        printf("======================================================\n");
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
