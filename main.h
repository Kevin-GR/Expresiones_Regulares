#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct  Nod
{
  char *RuleIdentifier;
  char *productions;
  struct Nod *Next;
}Node;

Node *createNode(const char *line, const char *production);
void appendNode(Node **head, const char *Identifier, const char *line);
void freeLinkedList(Node *head);
Node *createLinkedList(FILE *file);
void printList(Node *head);

Node* findNode(Node *head, const char ruleIdentifier);
void splitLine(Node *head, const char *ruleIdentifier, char *Production);
void appendProduction(Node *node, const char *Production);
void appendOrUpdateNode(Node **head,  const char *ruleIdentifier, const char *production);
FILE *openFile();
