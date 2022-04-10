#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum Direction {
     left,
     right,
};

typedef struct list_node *list_pointer; 
struct list_node {
     int data; 
     list_pointer prev; 
     list_pointer next; 
};

list_pointer Create(int hatNum){
     list_pointer first = (list_pointer) malloc(sizeof(list_node));
     int i = 1;
     list_pointer last;
     last = NULL;
     do {
          list_pointer newNode = (list_pointer) malloc(sizeof(list_node));
          newNode->data = i;
          newNode->next = NULL;
          newNode->prev = last;
          if(i == 1){
               first = newNode;
               last = first;
          }else{
               last->next = newNode;
          }
          last = newNode;
          i++;
     }while(i <= hatNum);
     
     return first;
}

list_pointer Insert(list_pointer list, int id, int insertNodeData, list_pointer nodeB, Direction d){
     list_pointer newNode = (list_pointer) malloc(sizeof(list_node)); 
     newNode->data = insertNodeData;
     if(d == left){
          newNode->prev = nodeB->prev;
          newNode->next = nodeB;
          if(nodeB->prev != NULL){
               nodeB->prev->next = newNode;
               nodeB->prev = newNode;
          } else {
               nodeB->prev = newNode;
               list = newNode;
          }
     }else{
          newNode->next = nodeB->next;
          newNode->prev = nodeB;
          if(nodeB->next != NULL)
               nodeB->next->prev = newNode;
          nodeB->next = newNode;
     }

     newNode = NULL;
     return list; 
}

list_pointer Delete(list_pointer list, int id, list_pointer deleteNode, list_pointer nodeBeforeDelete){
     list_pointer temp = (list_pointer) malloc(sizeof(list_node));
     if (nodeBeforeDelete == NULL){
          // first
          temp = list;
          list = list->next;
          list->prev = NULL;
          temp = NULL;
     } else {
          nodeBeforeDelete->next = deleteNode->next;
          if(deleteNode->next != NULL)
               nodeBeforeDelete->next->prev = nodeBeforeDelete;
     }
     return list;
}

list_pointer Swap(list_pointer list, int idA, int idB){
     list_pointer nodeA = (list_pointer) malloc(sizeof(list_node));
     list_pointer nodeB = (list_pointer) malloc(sizeof(list_node));
     list_pointer temp = (list_pointer) malloc(sizeof(list_node));
     temp = list;
     int i = 1;
     bool stop = true;
     
     while (stop){
          if(nodeA->data != '\0' && nodeB->data != '\0') stop = false;
          
          if(idA == list->data) nodeA = list;

          if(idB == list->data) nodeB = list;
          
          if(list->next == NULL) stop = false;
          else {
               list = list->next;
          }
          
          i++;
     }

     list = temp;
     temp = NULL;

     int tmp = nodeA->data;
     nodeA->data = nodeB->data;
     nodeB->data = tmp;

     // nodeA->data = '\0';
     // nodeA->prev = NULL;
     // nodeA->next = NULL;
     // nodeB->data = '\0';
     // nodeB->prev = NULL;
     // nodeB->next = NULL;
     nodeA = NULL;
     nodeB = NULL;

     return list;
}

list_pointer Inverse(list_pointer list, int size){
     int s = size / 2;
     list_pointer min = (list_pointer) malloc(sizeof(list_node));
     list_pointer max = (list_pointer) malloc(sizeof(list_node));
     min = list;
     max = list;
     while (max->next){
          max = max->next;
     }

     for(int i = 0; i < s; i++){
          int tmp = min->data;
          min->data = max->data;
          max->data = tmp;

          min = min->next;
          max = max->prev;
     }

     return list;
}

list_pointer InsertById(list_pointer list, int idA, int idB, Direction d){
     list_pointer nodeA = (list_pointer) malloc(sizeof(list_node));
     list_pointer nodeB = (list_pointer) malloc(sizeof(list_node));
     list_pointer temp = (list_pointer) malloc(sizeof(list_node));
     temp = list;
     int i = 1;
     bool stop = true;
     while (stop){
          if(nodeA->data != '\0' && nodeB->data != '\0') stop = false;
          
          if(idA == list->data) {
               nodeA = list;
          }

          if(idB == list->data) 
               nodeB = list;
          
          if(list->next == NULL) stop = false;
          else list = list->next;
          
          i++;
     }

     list = temp;
     temp = NULL;

     if((d == left && nodeA->next == nodeB) || (d == right && nodeA->prev == nodeB)){
          return list;
     }

     list = Insert(list, idB, nodeA->data, nodeB, d);
     list = Delete(list, idA, nodeA, nodeA->prev);

     nodeA = NULL;
     nodeB = NULL;
     
     return list; 
}

list_pointer Execute(list_pointer list, int command, int idA, int idB, int hatNum){
     list_node nodeA, nodeB;
     switch (command)
     {
          case 1:
               list = InsertById(list, idA, idB, left);
               break;
          case 2:
               list = InsertById(list, idA, idB, right);
               break;
          case 3:
               list = Swap(list, idA, idB);
               break;
          case 4:
               list = Inverse(list, hatNum);
               break;
          
          default:
               break;
     }

     return list;
}

// function to write linked list to a file
void WriteLinkedList(char filename[], list_pointer head){
     list_pointer temp = head;
    
     FILE *file = fopen (filename, "w+");
     if (file == NULL)
     {
          fprintf(stderr, "\nCouldn't Open File'\n");
          exit (1);
     }
     int sum = 0;
     int i = 1;
     while(temp!=NULL)
     {
          if(i % 2 == 1) sum += temp->data;
          temp = temp->next;
          i++;
     }
     fprintf(file, "%d\n", sum); 
     
     if(&fwrite != 0)
     {
          printf("Linked List stored in the file successfully\n");
     }
          else
     {
          printf("Error While Writing\n");
     }
     
     fclose(file);
    
}

int main(int argc, char * argv[])
{
     FILE * database;

     database = fopen("test_case_2/test3.txt", "r");

     if (NULL == database)
     {
          perror("opening database");
          return (-1);
     }

     int hatNum, commandNum;
     fscanf(database, "%d %d", &hatNum, &commandNum);
     printf("> %d %d\n", hatNum, commandNum);
     list_pointer list = Create(hatNum);

     for (int i = 0; i < commandNum; i++)
     {
          int command;
          int idA;
          int idB;
          fscanf(database, " %d", &command);
          if(command != 4)
               fscanf(database, "\n%d %d", &idA, &idB);
          // printf("> %d %d %d\n", command, idA, idB);
          list = Execute(list, command, idA, idB, hatNum);
          if(i % 1000 == 0) 
               printf("i = %d\n", i);
     }

     fclose(database);
     char fileName[30] = "output.txt";
     WriteLinkedList(fileName, list);
     return (0);
}