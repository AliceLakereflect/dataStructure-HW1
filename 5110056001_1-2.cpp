#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

const int TABLE_SIZE = 36;
struct PasswordTable{
    int row;
    int col;
    char value;
};

struct Msg{
    char msg[100];
};

PasswordTable * Initialize()
{
    PasswordTable *result[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        result[i] = (PasswordTable *) malloc(sizeof(PasswordTable));
    }
    
    int p = 0;
    int asciiNum = 65;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            (*result)[p].row = i;
            (*result)[p].col = j;
            (*result)[p].value = asciiNum;
            p++;
            if(asciiNum == 90){
                asciiNum = 49;
            }else if(asciiNum == 57){
                asciiNum = 32;
            }else{
                asciiNum++;
            }
        }
    }
    return *result;
}

PasswordTable * Encrypt(PasswordTable * table, int x, int y)
{
    PasswordTable *passwordTable = table;
    for (int p = 0; p < TABLE_SIZE; p++)
    {
        passwordTable[p].row = (table[p].row + x) % 6;
        passwordTable[p].col = (table[p].col + y) % 6;
    }
    return passwordTable;
}

char Find(PasswordTable * displayTable, PasswordTable * passwordTable, char target)
{
    char result = '\0';
    PasswordTable key;
    for (int p = 0; p < TABLE_SIZE; p++)
    {
        if(displayTable[p].value == target)
        {
            key = displayTable[p];
            break;
        }
    }

    for (int p = 0; p < TABLE_SIZE; p++)
    {
        if(passwordTable[p].row == key.row && passwordTable[p].col == key.col)
        {
            result = passwordTable[p].value;
            break;
        }
    }
    
    return result;
}

void Execute(PasswordTable * displayTable, PasswordTable * passwordTable, Msg message, int reverseNum)
{
    queue<char> result;
    stack<char> tempStack;

    int i = 0;
    while(message.msg[i] != '\0'){
        char password = Find(displayTable, passwordTable, message.msg[i]);
        
        tempStack.push(password);
        if(tempStack.size() == reverseNum){
            while (!tempStack.empty())  
            {
                result.push(tempStack.top());
                tempStack.pop();
            }
        }          
        i++;
    }
    while (!tempStack.empty())  
    {
        result.push(tempStack.top());
        tempStack.pop();
    }

    while (!result.empty()) {
        printf("%c", result.front());
        result.pop();
    }
    printf("\n");
}

void showq(queue<Msg> gq)
{
    queue<Msg> g = gq;
    while (!g.empty()) {
        printf("%s\n",g.front().msg);
        g.pop();
    }
    cout << '\n';
}

int main(){
    PasswordTable *displayTable;
    PasswordTable *passwordTable;
    displayTable = Initialize();
    passwordTable = Initialize();

    int x = 0,y = 0;
    printf("Please enter the enctrytion method(x y):");
    scanf("%d %d", &x, &y);

    Encrypt(passwordTable, x, y);

    int reverseNum = 0;
    printf("Please enter how many char you would like to reverse(n)):");
    scanf("%d", &reverseNum);

    int commandNum = 0;
    printf("Please enter the command number(m)):");
    scanf("%d", &commandNum);

    printf("Please start to enter the command:");
    queue<Msg> stringQueue;
    int commandCount = 0;
    char input[100];
    while(commandCount < commandNum){
        scanf("\n%[^\n]", input); 
        Msg message;
        for(int i = 0; input[i] != '\0'; i++){
            message.msg[i] = input[i];
        }
        stringQueue.push(message);
        commandCount++;
    }
    
    printf("Start the process:\n");
    printf("Original list:\n");
    showq(stringQueue);
    printf("Encrypted text:\n");

    while(!stringQueue.empty())
    {
        Execute(displayTable, passwordTable, stringQueue.front(), reverseNum);
        stringQueue.pop();
    }

    printf("\nAll commands are completed.\n");
    printf("\n\n");
    return 0;
}

