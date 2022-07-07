#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void trataSinal(int sig)
{

    char cam[11];

    int ret;

    ret = scanf(" %s", cam);

    if (ret == EOF)
    {
        exit(0);
    }

    if (sig == SIGTERM)
    {
        if (cam[3] == '2')
        {
            printf("Certo\n");
        }
        else
        {
            printf("Erro\n");
            kill(getppid(), SIGALRM);
        }
    }
    if (sig == SIGUSR1)
    {
        if (cam[0] == 'I')
        {
            printf("Certo\n");
        }
        else
        {
            printf("Erro\n");
            kill(getppid(), SIGALRM);
        }
    }
    if (sig == SIGUSR2)
    {
        if (cam[0] == 'M')
        {
            printf("Certo\n");
        }
        else
        {
            printf("Erro\n");
            kill(getppid(), SIGALRM);
        }
    }
    if (sig == SIGINT)
    {
        if (cam[3] == '1')
        {
            printf("Certo\n");
        }
        else
        {
            printf("Erro\n");
            kill(getppid(), SIGALRM);
        }
    }
    if (sig == SIGALRM)
    {
        if (cam[0] == 'S')
        {
            printf("Certo\n");
        }
        else
        {
            printf("Erro\n");
            kill(getppid(), SIGALRM);
        }
    }
}

int main()
{
    signal(SIGTERM, trataSinal);
    signal(SIGUSR1, trataSinal);
    signal(SIGUSR2, trataSinal);
    signal(SIGINT, trataSinal);
    signal(SIGALRM, trataSinal);

    while (1)
    {
    }

    return 0;
}