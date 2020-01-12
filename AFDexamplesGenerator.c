#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int amount;
    int qantorsAmount;
    char **qantors;
    int counter1, counter2;
    int len;
    
    srand(time(0));
    if (argc > 1)
    {
        amount = atoi(argv[1]) + 1;
        if (argc > 2)
            qantorsAmount = atoi(argv[2]);
        else
            qantorsAmount = rand() % 5 + 3;
    }
    else
    {
        qantorsAmount = rand() % 5 + 3;
        amount = rand() % (qantorsAmount * 3) + 1;
    }
    
    qantors = (char**)malloc(qantorsAmount * sizeof(char*));
    for (counter1 = 0; counter1 < qantorsAmount; counter1++)
    {
        len = rand() % 5 + 1;
        len = 1;
        qantors[counter1] = (char*)malloc(len + 1);
        for (counter2 = 0; counter2 < len; counter2++)
        {
            qantors[counter1][counter2] = rand() % 26 + 'a';
        }
        qantors[counter1][counter2] = '\0';
    }
    
    printf("%s\n", qantors[rand() % qantorsAmount]);
    for (counter1 = 0; counter1 < amount; counter1++)
    {
        len = rand() % qantorsAmount;
        if (rand() % 2)
            printf("-");
        printf("%s", qantors[rand() % qantorsAmount]);
        for (counter2 = 0; counter2 < len; counter2++)
        {
            if (rand() % 2)
                printf("+");
            else
                printf("=>");
            if (rand() % 2)
                printf("-");
            printf("%s", qantors[rand() % qantorsAmount]);
        }
        if (counter1 + 2 < amount)
            printf("\n");
    }
    
    for (counter1 = 0; counter1 < qantorsAmount; counter1++)
        free(qantors[counter1]);
    free(qantors);
    return 0;
}
