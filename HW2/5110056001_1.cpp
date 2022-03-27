#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
    FILE * database;
    char buffer[30];

    database = fopen("/Users/alice/Desktop/NCHU/data_structure/5110056001_alice/HW2/test case 1/input_1.txt", "r");

    if (NULL == database)
    {
         perror("opening database");
         return (-1);
    }

    int line = 1;
    while (EOF != fscanf(database, "%[^\n]\n", buffer))
    {
        
         printf("> %s\n", buffer);
    }

    fclose(database);
    return (0);
}