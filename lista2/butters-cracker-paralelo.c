#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int QNTThread = 8;

typedef struct item
{

    int *vet;
    int inicio, fim, cont;

} item;

void *encontraSeed(void *args)
{

    item recebi = *((item *)args);
    for (unsigned int i = recebi.inicio; i <= recebi.fim; i++)
    {
        // printf("-- %u -- %d -- %d \n", i, inicio, fim);
        int contaux = 0;
        unsigned int seed = i;
        for (int j = 0; j < recebi.cont; j++)
        {
            for (int k = 1; k < 10000; k++)
            {
                rand_r(&seed);
            }
            int x = rand_r(&seed) % 256;
            // printf("%d ", x);
            if (x == recebi.vet[j])
            {
                contaux++;
            }
            else
            {
                break;
            }
        }

        if (recebi.cont == contaux)
        {
            printf("%u\n", i);
            break;
        }
    }
    return;
}

int main()
{

    int inicio, fim, vet[100000], cont = 0;

    pthread_t t[QNTThread];

    item entrada[QNTThread];

    scanf(" %d %d", &inicio, &fim);

    while (scanf(" %d", &vet[cont]) != EOF)
    {
        cont++;
    }

    if (fim - inicio != 0)
    {
        int varia = ((fim - inicio) / QNTThread) + 1;

        // printf("%d - %d / %d = %d \n", fim, inicio, QNTThread, varia);

        for (int i = 0; i < QNTThread; i++)
        {
            entrada[i].cont = cont;
            entrada[i].vet = vet;
            entrada[i].inicio = inicio + (varia * i);
            entrada[i].fim = inicio + (varia * i) + varia;
            // printf("%d -- %d\t", entrada[i].inicio, entrada[i].fim);
            pthread_create(&t[i], NULL, encontraSeed, (void *)&entrada[i]);
        }

        for (int i = 0; i < QNTThread; i++)
        {
            // printf(".");
            pthread_join(t[i], NULL);
        }
        // encontraSeed((void *)&entrada);
    }
    else
    {
        printf("%d\n", inicio);
    }

    // printf("to aqui\n");

    return 0;
}