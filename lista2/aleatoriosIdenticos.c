#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int QNTThread = 4;

int S;

typedef struct item
{
    int inicio, fim;
    int vet[100000];
    int qnt;
} item;

typedef struct retorno
{
    int vet[100000];
    int qnt;
} retorno;

void *encontraSeed(void *args)
{

    item recebi = *((item *)args);
    retorno *ret = malloc(sizeof(retorno));
    int qnt = 0;
    for (unsigned int i = recebi.inicio; i <= recebi.fim; i++)
    {
        // printf("-- %u -- %d -- %d \n", i, inicio, fim);
        unsigned int seed = i;

        for (int k = 1; k < 100000; k++)
        {
            rand_r(&seed);
        }
        int x = rand_r(&seed) % 8;
        // printf("%d ", x);
        if (x == S)
        {
            ((item *)args)->vet[qnt] = i;
            qnt++;
            // printf("%u\n", i);
        }
    }
    ((item *)args)->qnt = qnt;
    return (void *)ret;
}

int main()
{

    int inicio, fim;

    pthread_t t[QNTThread];

    item entrada[QNTThread];
    retorno saida[QNTThread];

    scanf(" %d %d %d", &inicio, &fim, &S);

    int varia = ((fim - inicio) / QNTThread) + 1;

    // printf("%d - %d / %d = %d \n", fim, inicio, QNTThread, varia);

    for (int i = 0; i < QNTThread; i++)
    {
        entrada[i].inicio = inicio + (varia * i);
        entrada[i].fim = inicio + (varia * i) + varia - 1;
        // printf("%d -- %d\t", entrada[i].inicio, entrada[i].fim);
        pthread_create(&t[i], NULL, encontraSeed, (void *)&entrada[i]);
    }

    for (int i = 0; i < QNTThread; i++)
    {
        // printf(".");
        pthread_join(t[i], (void *)&saida[i]);
    }

    for (int i = 0; i < QNTThread; i++)
    {
        for (int j = 0; j < entrada[i].qnt; j++)
        {
            printf("%d\n", entrada[i].vet[j]);
        }
    }

    // encontraSeed((void *)&entrada);

    // printf("to aqui\n");

    return 0;
}