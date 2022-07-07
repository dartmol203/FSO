#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

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