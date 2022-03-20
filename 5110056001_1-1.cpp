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

void EnqueueCommand(Port p){
    printf("開始作業:\n");
    queue<int> portQs[p.portNum];

    int currentCmdNum = 0;
    while(currentCmdNum < p.commandNum)
    {
        char command[10];
        int userId;
        int portId;
        scanf("%s", command);
        if (strcmp(command, "enqueue") == 0){
            scanf("%d %d", &userId, &portId);
            portQs[portId-1].push(userId);
            currentCmdNum++;
        }else if (strcmp(command, "dequeue") == 0){
            Execute(p, portQs);
            // printf("============> Dequeue output: %d \n", resultQ.front());
            // resultQ.pop();
            currentCmdNum++;
        }
        bzero(command, 10);
    }
    while(HasAnyInQueue(portQs, p.portNum))
    {
        Execute(p, portQs);
    };
    printf("\n所有指令已結束\n");
}



Port Initialize(){
    Port port;
    printf("海關口數量:");
    scanf("%d", &port.portNum);

    char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);

    printf("請輸入個海關口查驗時間,中間以空白區隔:");
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

    printf("接下來有幾道指令?");
    scanf("%d", &port.commandNum);
    
    // print inputs
    printf("\n海關口數量為:%d\n", port.portNum);
    printf("個別查驗時間為:");
    for (int i = 0; i < port.portNum; i++)
    {
        printf("%d ", port.processTime[i]);
    }
    printf("\n指令數為:%d\n", port.commandNum);

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

