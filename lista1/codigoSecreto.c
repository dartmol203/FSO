#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int senha;

void trataSinal(int sig)
{

    printf("recebi %d\n", sig);
    if (senha == 3)
    {
        if (sig == SIGUSR1)
        {
            printf("Tchau\n");
            exit(0);
        }
        else
        {
            senha = 0;
        }
    }
    if (senha == 2)
    {
        if (sig == SIGTERM)
        {
            senha = 3;
            printf("Senha acionada\n");
        }
        else
        {
            senha = 0;
        }
    }
    if (senha == 1)
    {
        if (sig == SIGUSR2)
        {
            senha = 2;
        }
        else
        {
            senha = 0;
        }
    }
    if (sig == SIGINT)
    {
        senha = 1;
    }
}

int main()
{
    senha = 0;
    signal(SIGTERM, trataSinal);
    signal(SIGUSR1, trataSinal);
    signal(SIGUSR2, trataSinal);
    signal(SIGINT, trataSinal);

    while (1)
    {
    }

    return 0;
}