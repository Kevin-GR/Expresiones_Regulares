#include "main.h"

int main() {
    FILE *grammar = openFile();
    Node *Head = createLinkedList(grammar);
    fclose(grammar);

    printf("Producciones originales:\n");
    printList(Head);

    printf("\nProducciones despues de eliminar recursividad:\n");

    removeRecursivity(&Head);
    removecharacters(&Head);
    printList(Head);

    printf("\nProducciones despues de reemplazar de manera ascendente:\n");
    replaceAscending(&Head);
    printList(Head);

    freeLinkedList(Head);
    return EXIT_SUCCESS;
}

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s -> %s\n", current->ruleIdentifier, current->productions);
        current = current->Next;
    }
}

void removeRecursivity(Node **head) {
    Node *current = *head;
    while (current != NULL) {
        const char *delimiter = strstr(current->productions, current->ruleIdentifier);
        if (delimiter != NULL && delimiter != current->productions) {
            char New[200];
            size_t textLength = delimiter - current->productions;

            strcpy(New, "{");
            New[1] = delimiter[-1];
            New[2] = '\0';

            strcat(New, "}");
            strcat(New, "(");
            strncat(New, current->productions, textLength - 1);
            strcat(New, delimiter + strlen(current->ruleIdentifier));
            strcat(New, ")");

            free(current->productions);
            current->productions = strdup(New);
        }
        current = current->Next;
    }
}

void removecharacters(Node **head) {
    Node *current = *head;
    while (current != NULL) {
        const char *delimiter = strstr(current->productions, "|");
        if (delimiter != NULL) {
            char nuevaCadena[200];

            size_t lengthBefore = delimiter - current->productions;
            strncpy(nuevaCadena, current->productions, lengthBefore);
            nuevaCadena[lengthBefore] = '\0';

            strcat(nuevaCadena, delimiter + 1);
            free(current->productions);
            current->productions = strdup(nuevaCadena);
        }
        current = current->Next;
    }
}


FILE *openFile() {
    char archiv[25];
    printf("file name: ");
    scanf("%s", archiv);
    FILE *grammar = fopen(archiv, "r");
    if (grammar == NULL) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }
    return grammar;
}

Node* createNode(const char *ruleIdentifier, const char *production) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->ruleIdentifier = strdup(ruleIdentifier);
    newNode->productions = strdup(production);
    newNode->Next = NULL;
    newNode->Prev = NULL;
    return newNode;
}

void freeLinkedList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *nextNode = current->Next;
        free(current->ruleIdentifier);
        free(current->productions);
        free(current);
        current = nextNode;
    }
}

void appendNode(Node **head, const char *ruleIdentifier, const char *production) {
    Node *newNode = createNode(ruleIdentifier, production);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->Next != NULL) {
            current = current->Next;
        }
        current->Next = newNode;
        newNode->Prev = current;
    }
}

Node* createLinkedList(FILE *file) {
    Node *head = NULL;
    char line[50];
    char ruleIdentifier[50];
    char production[50];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        splitLine(line, ruleIdentifier, production);
        appendOrUpdateNode(&head, ruleIdentifier, production);
    }
    return head;
}

void appendProduction(Node *node, const char *production) {
    size_t newSize = strlen(node->productions) + strlen(production) + 2;
    node->productions = (char *) realloc(node->productions, newSize);

    strcat(node->productions, "|");
    strcat(node->productions, production);
}
Node* findNode(Node *head, const char *ruleIdentifier) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->ruleIdentifier, ruleIdentifier) == 0) {
            return current;
        }
        current = current->Next;
    }
    return NULL;
}

void splitLine(const char *line, char *ruleIdentifier, char *production) {
    const char *delimiter = strstr(line, "->");
    if (delimiter != NULL) {
        strncpy(ruleIdentifier, line, delimiter - line);
        ruleIdentifier[delimiter - line] = '\0';
        strcpy(production, delimiter + 2);
    }
}

void appendOrUpdateNode(Node **head, const char *ruleIdentifier, const char *production) {
    Node *existingNode = findNode(*head, ruleIdentifier);
    if (existingNode != NULL) {
        appendProduction(existingNode, production);
    } else {
        appendNode(head, ruleIdentifier, production);
    }
}




void replaceAscending(Node **head) {
    Node *current = *head;
    while (current != NULL) {
        Node *temp = *head;
        while (temp != NULL) {
            if (temp != current) {
                const char *delimiter = strstr(current->productions, temp->ruleIdentifier);
                if (delimiter != NULL) {
                    char newC[15];
                    size_t lengthBefore = delimiter - current->productions;
                    strncpy(newC, current->productions, lengthBefore);
                    newC[lengthBefore] = '\0';

                    strcat(newC, temp->productions);
                    strcat(newC, delimiter + strlen(temp->ruleIdentifier));

                    free(current->productions);
                    current->productions = strdup(newC);
                }
            }
            temp = temp->Next;
        }
        current = current->Next;
    }
}
