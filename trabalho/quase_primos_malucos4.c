#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct parametro_thread
{
    int *n;
    int tid;
    int result;
    int qnt;
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
    for (int i = 0; i < param->qnt; i++)
    {

        // printf("\t%d \n", param->n[i]);
        if (param->n[i] <= 508079)
        {
            param->n[i] = 508079;
        }
        else
        {
            if (param->n[i] % 2 == 0)
            {
                param->n[i] += 1;
                // printf("\t\t%d \n", param->n[i]);
            }
            double raiz = sqrt((double)param->n[i]);
            param->n[i] = printa(param->n[i], raiz);
        }
    }

    pthread_exit(NULL);
}

void calcula_quase_primo_maluco2(void *parameter)
{
    parametro_thread *param = parameter;
    for (int i = 0; i < param->qnt; i++)
    {

        // printf("\t%d \n", param->n[i]);
        if (param->n[i] <= 508079)
        {
            param->n[i] = 508079;
        }
        else
        {
            if (param->n[i] % 2 == 0)
            {
                param->n[i] += 1;
                // printf("\t\t%d \n", param->n[i]);
            }
            double raiz = sqrt((double)param->n[i]);
            param->n[i] = printa(param->n[i], raiz);
        }
    }
}

int main(void)
{
    int qtd, i = 0;

    scanf("%d", &qtd);

    parametro_thread PARAMETRO_A;
    parametro_thread PARAMETRO_B;
    parametro_thread PARAMETRO_C;

    PARAMETRO_A.n = malloc(sizeof(int) * (qtd / 3) + 1);
    PARAMETRO_B.n = malloc(sizeof(int) * (qtd / 3) + 1);
    PARAMETRO_C.n = malloc(sizeof(int) * (qtd / 3) + 1);
    PARAMETRO_A.qnt = 0;
    PARAMETRO_B.qnt = 0;
    PARAMETRO_C.qnt = 0;
    while (i != qtd)
    {
        scanf(" %d", &PARAMETRO_A.n[PARAMETRO_A.qnt++]);
        i++;
        if (i != qtd)
        {
            scanf(" %d", &PARAMETRO_B.n[PARAMETRO_B.qnt++]);
            i++;
        }
        if (i != qtd)
        {
            scanf(" %d", &PARAMETRO_C.n[PARAMETRO_C.qnt++]);
            i++;
        }
    }
    pthread_t tid, tid2;

    pthread_create(&tid, NULL, calcula_quase_primo_maluco, &PARAMETRO_A);
    pthread_create(&tid2, NULL, calcula_quase_primo_maluco, &PARAMETRO_B);
    calcula_quase_primo_maluco2(&PARAMETRO_C);
    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);

    for (int i = 0; i < PARAMETRO_A.qnt; i++)
    {
        printf("%d\n", PARAMETRO_A.n[i]);
        if (i < PARAMETRO_B.qnt)
            printf("%d\n", PARAMETRO_B.n[i]);
        if (i < PARAMETRO_C.qnt)
            printf("%d\n", PARAMETRO_C.n[i]);
    }
    return 0;
}