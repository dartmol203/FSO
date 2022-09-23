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

    // printf("\t%d \n", param->n[i]);
    if (param->n <= 508079)
    {
        param->n = 508079;
    }
    else
    {
        if (param->n % 2 == 0)
        {
            param->n += 1;
            // printf("\t\t%d \n", param->n[i]);
        }
        double raiz = sqrt((double)param->n);
        param->result = printa(param->n, raiz);
    }
}

int main(void)
{
    int qtd, i = 0;

    scanf("%d", &qtd);

    parametro_thread PARAMETRO[3];

    pthread_t tid[2];
    while (qtd % 3 != 0)
    {
        scanf(" %d", &PARAMETRO[qtd % 3].n);
        pthread_create(&tid[qtd % 3], NULL, calcula_quase_primo_maluco, &PARAMETRO[qtd % 3]);
        pthread_join(tid[qtd % 3], NULL);
        printf("%d\n", PARAMETRO[qtd % 3].result);
        qtd--;
    }
    while (qtd > 0)
    {
        scanf(" %d", &PARAMETRO[0].n);

        scanf(" %d", &PARAMETRO[1].n);

        scanf(" %d", &PARAMETRO[2].n);

        pthread_create(&tid[0], NULL, calcula_quase_primo_maluco, &PARAMETRO[0]);
        pthread_create(&tid[1], NULL, calcula_quase_primo_maluco, &PARAMETRO[1]);
        calcula_quase_primo_maluco(&PARAMETRO[2]);
        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);

        printf("%d\n", PARAMETRO[0].result);
        printf("%d\n", PARAMETRO[1].result);
        printf("%d\n", PARAMETRO[2].result);

        qtd -= 3;
    }

    return 0;
}
