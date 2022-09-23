#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct parametro_thread
{
    int n;
    int result;
} parametro_thread;

int printa(int num, double raiz)
{
    while (1)
    {

        int count = 0;
        if ((num % 3 != 0) && (num % 5 != 0) && (num % 7 != 0))
        {
            for (int i = 11; i < raiz; i++)
            {
                if (num % i == 0)
                    count++;
            }
            if (count > 10)
            {
                return num;
            }
        }
        num += 2;
    }
}

void *calcula_quase_primo_maluco(void *parameter)
{
    parametro_thread *param = parameter;

    if (param->n <= 508079)
    {
        param->n = 508079;
    }
    else
    {
        if (param->n % 2 == 0)
        {
            param->n += 1;
        }
        double raiz = sqrt((double)param->n);
        param->result = printa(param->n, raiz);
    }
}

int main(void)
{
    int qtd;

    scanf("%d", &qtd);

    parametro_thread PARAMETRO[3];

    pthread_t tid[2];
    while (1)
    {
        if (scanf(" %d", &PARAMETRO[0].n) == EOF)
        {
            break;
        }
        pthread_create(&tid[0], NULL, calcula_quase_primo_maluco, &PARAMETRO[0]);
        pthread_join(tid[0], NULL);
        printf("%d\n", PARAMETRO[0].result);

        if (scanf(" %d", &PARAMETRO[1].n) == EOF)
        {
            break;
        }

        pthread_create(&tid[1], NULL, calcula_quase_primo_maluco, &PARAMETRO[1]);
        pthread_join(tid[1], NULL);
        printf("%d\n", PARAMETRO[1].result);

        if (scanf(" %d", &PARAMETRO[2].n) == EOF)
        {
            break;
        }

        calcula_quase_primo_maluco(&PARAMETRO[2]);
        printf("%d\n", PARAMETRO[2].result);
    }

    return 0;
}
