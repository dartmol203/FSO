#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int qnt;

void trataSinal(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    }
    if (sig == SIGALRM)
    {
        if (qnt < 2)
        {
            printf("Ai que sono, quero dormir mais um pouco\n");
            qnt++;
        }
        else
        {
            printf("Os incomodados que se mudem, tchau\n");
            exit(0);
        }
    }
}

int main()
{

    qnt = 0;

    signal(SIGALRM, trataSinal);
    signal(SIGUSR1, trataSinal);

    while (1)
    {
    }

    return 0;
}