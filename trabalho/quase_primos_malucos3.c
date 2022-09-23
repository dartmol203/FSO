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
    if (num <= 508079)
    {
        return 508079;
    }
    else
    {
        int count = 0;
        if ((num & 1 != 0) && (num % 3 != 0) && (num % 5 != 0) && (num % 7 != 0))
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
        return printa(num + 1, raiz);
    }
}

void *calcula_quase_primo_maluco(void *parameter)
{
    parametro_thread *param = parameter;
    for (int i = 0; i < param->qnt; i++)
    {

        double raiz = sqrt((double)param->n[i]);
        param->n[i] = printa(param->n[i], raiz);
    }

    pthread_exit(NULL);
}

void calcula_quase_primo_maluco2(void *parameter)
{
    parametro_thread *param = parameter;
    for (int i = 0; i < param->qnt; i++)
    {

        double raiz = sqrt((double)param->n[i]);
        param->n[i] = printa(param->n[i], raiz);
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
        /*
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
        */
        int ret = scanf("%d %d %d", &PARAMETRO_A.n[PARAMETRO_A.qnt], &PARAMETRO_B.n[PARAMETRO_B.qnt], &PARAMETRO_C.n[PARAMETRO_C.qnt]);
        i += ret;
        switch (ret)
        {
        case 1:
            PARAMETRO_A.qnt++;
            break;
        case 2:
            PARAMETRO_A.qnt++;
            PARAMETRO_B.qnt++;
            break;
        default:
            PARAMETRO_A.qnt++;
            PARAMETRO_B.qnt++;
            PARAMETRO_C.qnt++;
            break;
        }
    }
    pthread_t tid, tid2;

    // printf("%d %d %d\n", PARAMETRO_A.qnt, PARAMETRO_B.qnt, PARAMETRO_B.qnt);

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