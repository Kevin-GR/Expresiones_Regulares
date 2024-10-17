#include "main.h"
Node* createNode(const char *line, const char *production)
{
  char nom[50];
  char prod[50];
   Node *newNode = (Node*) malloc(sizeof(line));
  newNode->RuleIdentifier = malloc(strlen(nom) + 1);
  strcpy(newNode->RuleIdentifier, line);
  newNode->Production = malloc(strlen(prod) + 1);
  strcpy(newNode->Production, production);

  return newNode;
}

void appendNode(Node **head, const char *ruleIdentifier, const char *production)
{
  Node *newNode = createNode(ruleIdentifier, production);
  if(*head == NULL)
  *head = newNode;

  else
  {
    Node *temp = *head;
    while (temp->Next != NULL){
    temp = temp->Next;
    }
    temp->Next = newNode;
  }
}

void freeLinkedList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;       
        head = head->Next; 
        free(temp);        
    }
}

Node* createLinkedList(FILE *file)
{
  Node *head = NULL;
  char line[50];
  char ruleIdentifier[50];
  char production[50];

  while (fgets(line, sizeof(line), file))
  {
    line[strcspn(line, "\n")] = '\0';

   const char *delimiter= strstr(line, "->");

  if (delimiter != NULL)
  {
    strncpy(ruleIdentifier, line, delimiter - line);
    ruleIdentifier[delimiter - line ]  = '\0';
    strcpy(production, delimiter+2);
    appendNode(&head, ruleIdentifier,production);
  }

   
  }

  return head;
}


void printList(Node *head) {
    while (head != NULL) {
        printf("Identifier: %s, Production: %s\n", head->RuleIdentifier, head->Production);
        head = head->Next;  
    }
}

FILE *openFile()
{
 
  char archiv[25];
  printf("file name:");
  scanf("%s", archiv);
  FILE *grammar = fopen(archiv, "r");
 if(grammar == NULL)
{
  perror("Error opening the file");
  return EXIT_FAILURE;
}

  return grammar;
}

int main()
{
  FILE *grammar = openFile();
 


Node *Head = createLinkedList(grammar);
fclose(grammar);
printList(Head);
freeLinkedList(Head);

return EXIT_SUCCESS;
}
