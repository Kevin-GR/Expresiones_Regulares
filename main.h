#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Nod {
    char *ruleIdentifier;
    char *productions;
    struct Nod *Next;
    struct Nod *Prev;
} Node;

Node *createNode(const char *ruleIdentifier, const char *production);
void appendNode(Node **head, const char *ruleIdentifier, const char *production);
void freeLinkedList(Node *head);
Node *createLinkedList(FILE *file);
void printList(Node *head);
Node* findNode(Node *head, const char *ruleIdentifier);
void splitLine(const char *line, char *ruleIdentifier, char *production);
void appendProduction(Node *node, const char *production);
void appendOrUpdateNode(Node **head, const char *ruleIdentifier, const char *production);
FILE *openFile();
void removeRecursivity(Node **head);
void removecharacters(Node **head);
void replaceAscending(Node **head);