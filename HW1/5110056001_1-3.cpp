#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct User{
    int health;
    int level;
    int experience;
};

enum ObjType{
    H,
    M,
    B,
    K
};

struct ObjectItem{
    ObjType type;
    int point;
};

ObjType GetOpjectType(char *command){
    enum ObjType objType;
    switch (command[0])
    {
        case 'H':
            objType = H;
            break;

        case 'M':
            objType = M;
            break;

        case 'B':
            objType = B;
            break;

        case 'K':
            objType = K;
            break;

        default:
            break;
    }

    return objType;
}

User Execute(ObjectItem objectArr[], int sequence[], int objNum,int maxExp, int maxHealth)
{
    User user;
    user.health = maxHealth;
    user.level = 1;
    user.experience = 0;

    int i = 0;
    
    while (i < objNum)
    {
        int currentObjectId = sequence[i];
        int attack = 0;
        switch (objectArr[currentObjectId].type)
        {
            case H:
                user.health = user.health + user.level * objectArr[currentObjectId].point;

                if(user.health >= maxHealth)
                    user.health = maxHealth;

                break;

            case M:
                attack = objectArr[currentObjectId].point + user.level <= 0 
                            ? objectArr[currentObjectId].point + user.level 
                            : 1;
                user.health = user.health - attack;
                user.experience++;
                if (user.experience >= maxExp)
                {
                    user.experience = 0;
                    user.level++;
                }
                break;

            case B:
                attack = objectArr[currentObjectId].point + user.level <= 0 
                            ? objectArr[currentObjectId].point + user.level 
                            : 1;
                user.health = user.health - attack;
                user.experience = user.experience + 2;
                if (user.experience >= maxExp)
                {
                    user.experience = 0;
                    user.level++;
                }
                break;

            case K:
                user.health = user.health / 2;
                break;

            default:
                break;
        }

        if(user.health <= 0){
            break;
        }
        i++;
    }

    return user;
}

int Fitness(ObjectItem objectArr[], int sequence[],int objNum,int maxExp, int maxHealth)
{
    User user = Execute(objectArr, sequence, objNum, maxExp, maxHealth);
    return user.health <= 0 ? 0 : user.level * 3 + user.experience;
}
int main(){
    int maxExp;
    int maxHealth;

    printf("Please enter the life max value and the experience value required to level up(m n):");
    scanf("%d %d", &maxHealth, &maxExp);
    

    int objNum;
    printf("Please enter the total object number(I):");
    scanf("%d", &objNum);

    printf("Please enter each object number:\n", objNum);
    ObjectItem *objectArr[objNum];
    for (int i = 0; i < objNum; i++)
    {
        objectArr[i] = (ObjectItem *) malloc(sizeof(ObjectItem));
    }

    int currentCmdNum = 0;
    while(currentCmdNum < objNum){
        char command[2];
        int point;
        scanf("%s", command);
        (*objectArr)[currentCmdNum].type = GetOpjectType(command);

        if(command[0] != 'K'){
            scanf("%d", &point);
            (*objectArr)[currentCmdNum].point = point;
        } 
        else 
        {
            (*objectArr)[currentCmdNum].point = 0;
        }
        
        currentCmdNum++;
    }

    printf("Output:\n");

    int sequence[] = { 2, 3, 5, 9, 8, 6, 7, 10, 1, 4};
    
    User user = Execute(*objectArr, sequence, objNum, maxExp, maxHealth);
    int fitness = Fitness(*objectArr, sequence, objNum, maxExp, maxHealth);

    for (int i = 0; i < objNum; i++)
    {
        printf("%d ", sequence[i]);
    }
    
    printf("\n%d %d\n", user.level, user.experience);

    return 0;
}

