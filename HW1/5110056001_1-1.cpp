#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

queue<int> resultQ;
int timeCount[100];

struct Port
{
    int portNum;
    int processTime[100];
    int commandNum;
};

void Execute(Port p, queue<int> portQs[]){
    bool continueProcess = true;

    while(continueProcess){
        continueProcess = true;
        for (int i = 0; i < p.portNum; i++)
        {
            if(timeCount[i] == 0)
                timeCount[i] = p.processTime[i];
            
            if(!portQs[i].empty())
                timeCount[i]--;
        }
        for (int i = 0; i < p.portNum; i++)
        {
            if(timeCount[i] == 0)
                continueProcess = false;
        }
    }

    for (int i = 0; i < p.portNum; i++)
    {
        if(timeCount[i] == 0)
        {
            resultQ.push(portQs[i].front());
            portQs[i].pop();
        }
    }
}

bool HasAnyInQueue(queue<int> portQs[], int portNum){
    bool result = false;
    for (int i = 0; i < portNum; i++)
    {
        if(!portQs[i].empty()){
            result = true;
            break;
        }
    }
    return result;
}

bool stringCmp(string inputCommand, string command){
    bool result = true;
    for(int i = 0; inputCommand[i] != '\0'; i++){
        if(inputCommand[i] != command[i]) result = false;
    }
    return result;
}

void EnqueueCommand(Port p){
    printf("Start process:\n");
    queue<int> portQs[p.portNum];

    int currentCmdNum = 0;
    while(currentCmdNum < p.commandNum)
    {
        char command[10];
        int userId;
        int portId;
        scanf("%s", command);
        if (stringCmp(command, "enqueue")){
            scanf("%d %d", &userId, &portId);
            portQs[portId-1].push(userId);
            currentCmdNum++;
        }else if (stringCmp(command, "dequeue")){
            Execute(p, portQs);
            // printf("============> Dequeue output: %d \n", resultQ.front());
            // resultQ.pop();
            currentCmdNum++;
        }
        for(int i = 0; i < 10; i++){
            command[i] = '\0';
        }
    }
    while(HasAnyInQueue(portQs, p.portNum))
    {
        Execute(p, portQs);
    };
    printf("\nAll commands are completed.\n");
}



Port Initialize(){
    Port port;
    printf("The port number:");
    scanf("%d", &port.portNum);

    char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);

    printf("Please enter the processing time of each port, split by space:");
    int i = 0;
    while(i < port.portNum)
    {
        int input;
        scanf("%d", &input);
        if(input != '\0'){
            port.processTime[i] = input;
            i++;
        }
    }

    for (int i = 0; i < port.portNum; i++)
    {
        timeCount[i] = port.processTime[i];
    }

    printf("How many command is there?");
    scanf("%d", &port.commandNum);
    
    // print inputs
    printf("\nThe port number is:%d\n", port.portNum);
    printf("The each processing time is:");
    for (int i = 0; i < port.portNum; i++)
    {
        printf("%d ", port.processTime[i]);
    }
    printf("\nThe command number:%d\n", port.commandNum);

    printf("\n");
    return port;
}

int main(){
    Port port = Initialize();
    
    EnqueueCommand(port);
    // print all
    printf("============> Total output:\n");
    while(!resultQ.empty()){
        printf("%d ", resultQ.front());
        resultQ.pop();
    }
    printf("\n\n");
    return 0;
}

