#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct list_node *list_pointer; 
struct list_node {
     char data; 
     list_pointer link; 
};

list_pointer Create(char* str){
     list_pointer first = (list_pointer) malloc(sizeof(list_node));
     int i = 0;
     list_pointer last;
     do{
          list_pointer newNode = (list_pointer) malloc(sizeof(list_node));
          newNode->data = str[i];
          newNode->link = NULL;
          if(i == 0){
               first = newNode;
               last = first;
          }else{
               last->link = newNode;
          }
          // move forward
          last = newNode;
          i++;
     }while(str[i] != '\0');

     return first;
}

list_pointer Insert(list_pointer list, int exeNum, char insertChar){
     int i = 1;
     bool stop = true;
     list_pointer preNode = list;
     // find the previous node of the insert position
     while(stop){
          if(i < exeNum - 1 && preNode->link != NULL)
               preNode = preNode->link;
          else
               stop = false;
          
          i++;
     }
     // build for the new node
     list_pointer temp; 
     temp = (list_pointer) malloc(sizeof(list_node)); 
     temp->data = insertChar;
     if(exeNum == 1){
          // first
          temp->link = list;
          list = temp;
     } else {
          // not the first
          temp->link = preNode->link;
          preNode->link = temp;
     }
     return list; 
}

list_pointer Delete(list_pointer list, int exeNum){
     int i = 1;
     bool stop = true;
     list_pointer trailNode = list;
     list_pointer deletedNode = trailNode->link;
     // find the nodes
     while(stop){
          if(i < exeNum - 1 && trailNode->link != NULL){
               trailNode = trailNode->link;
               deletedNode = trailNode->link;
          }
          else
               stop = false;
          
          i++;
     }

     if(exeNum == 1){
          // first
          list = list->link;
     }else if(trailNode->link != NULL){
          // delete for a node not in the last
          trailNode->link = deletedNode->link;
     }
     return list;
}

list_pointer Execute(list_pointer list, char command, int exeNum, char insertChar){
     if(command == 'A'){
          list = Insert(list, exeNum, insertChar);
     }else if(command == 'D'){
          list = Delete(list, exeNum);
     }
     return list;
}

void PrintList(list_pointer list){
     list_pointer temp;
     for (temp = list; temp->link; temp = temp->link)
     {
          printf("%c",temp->data);
     }
     printf("%c\n", temp->data);
}

// function to write linked list to a file
void WriteLinkedList(char filename[], list_pointer head){
    
     list_pointer temp = head;
    
    FILE* file;
    file = fopen (filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        exit (1);
    }
    
    // writing all the nodes of the linked list to the file
    while(temp!=NULL)
    {
        fwrite(temp, sizeof(char), 1, file);
        temp = temp->link;
    }
    
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

     database = fopen("test.txt", "r");

     if (NULL == database)
     {
          perror("opening database");
          return (-1);
     }

     char str[10000];
     fscanf(database, "%s", str);
     printf("> %s\n", str);
     list_pointer list = Create(str);
     PrintList(list);

     int commandNum;
     fscanf(database, "%d", &commandNum);
     printf("> %d\n", commandNum);

     for (int i = 0; i < commandNum; i++)
     {
          char command;
          int exeNum;
          char insertChar;
          fscanf(database, "\n%c %d", &command, &exeNum);
          // if command is A, need to scan more charactor for insert char
          if(command == 'A')
               fscanf(database, " %c", &insertChar);
          printf("> %c %d %c\n", command, exeNum, insertChar);
          list = Execute(list, command, exeNum, insertChar);
          PrintList(list);
     }

     fclose(database);
     PrintList(list);
     char fileName[30] = "output.txt";
     WriteLinkedList(fileName, list);
     return (0);
}