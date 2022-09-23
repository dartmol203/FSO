#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>

typedef struct parametro_thread
{
    int n;
    int tid;
    int result;
} parametro_thread;

typedef struct thread
{
    pthread_t tid;
    int i;
} Thread;

parametro_thread *Parametro_golbal;

Thread threads[2];

int calcula(int number)
{
    if (number == 1 || number % 2 == 0)
    {
        return 0;
    }

    int aux = 0;
    for (int i = 3, f = floor(sqrt(number)); i < f; i += 2)
    {
        if (number % i == 0 && i < 11)
        {
            return 0;
        }
        else if (number % i == 0 && i > 10)
        {
            aux++;
        }
    }

    if (aux >= 10)
    {
        return 1;
    }
    return 0;
}

void *calcule_sequaseprimo_maluco(void *arg)
{

    int i = *((int *)arg);

    while (calcula(Parametro_golbal[i].n) == 0)
    {
        Parametro_golbal[i].n++;
    }
    Parametro_golbal[i].result = Parametro_golbal[i].n;
}

int main()
{

    int qtd;
    int num;
    int aux = 0;

    scanf("%d", &qtd);
    Parametro_golbal = (parametro_thread *)malloc(qtd * sizeof(parametro_thread));

    for (int i = 0; i < qtd; i++)
    {
        scanf("%d", &num);

        if (num < 508079)
        {
            Parametro_golbal[i].result = 508079;
        }
        else
        {
            Parametro_golbal[i].n = num;
            Parametro_golbal[i].tid = aux;

            threads[aux].i = i;
            pthread_create(&threads[aux].tid, NULL, &calcule_sequaseprimo_maluco, (void *)&threads[aux].i);
            if (aux == 1)
            {
                aux = 0;
            }
            else
            {
                aux++;
            }
            for (int j = 0; j < 2; j++)
            {
                pthread_join(threads[j].tid, NULL);
            }
        }
    }

    for (int i = 0; i < qtd; i++)
    {
        printf("%d\n", Parametro_golbal[i].result);
    }

    return 0;
}