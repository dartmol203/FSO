#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

int entrada1, entrada2, entrada3;
int ret1, ret2, ret3;

void *eh_quase_primo1()
{
    int n = entrada1++;
    int count = 0;
    if (n & 1 == 0)
        n++;

    while (count <= 10)
    {
        int count = 0;
        for (int i = 3, f = floor(sqrt(n)); i < f; i += 2)
            if (n % i == 0 && i < 11)
                break;
            else if (n % i == 0 && i > 10)
                count++;

        if (count >= 10)
        {
            ret1 = n;
            return;
        }

        n += 2;
        count = 0;
    }
}

void *eh_quase_primo2()
{
    int n = entrada2++;
    int count = 0;
    if (n & 1 == 0)
        n++;

    while (count <= 10)
    {
        int count = 0;
        for (int i = 3, f = floor(sqrt(n)); i < f; i += 2)
            if (n % i == 0 && i < 11)
                break;
            else if (n % i == 0 && i > 10)
                count++;

        if (count >= 10)
        {
            ret2 = n;
            return;
        }

        n += 2;
        count = 0;
    }
}

void eh_quase_primo3()
{
    int n = entrada3++;
    int count = 0;

    if (n & 1 == 0)
        n++;

    while (count <= 10)
    {
        int count = 0;
        for (int i = 3, f = floor(sqrt(n)); i < f; i += 2)
            if (n % i == 0 && i < 11)
                break;
            else if (n % i == 0 && i > 10)
                count++;

        if (count >= 10)
        {
            ret3 = n;
            return;
        }

        n += 2;
        count = 0;
    }
}

int main()
{

    int casos_teste;
    scanf("%d", &casos_teste);

    pthread_t t1, t2;

    while (casos_teste % 3 != 0)
    {
        casos_teste--;
        scanf("%d", &entrada1);
        pthread_create(&t1, NULL, eh_quase_primo1, NULL);
        pthread_join(t1, NULL);
        printf("%d\n", (int)ret1);
    }
    while (casos_teste > 0)
    {
        scanf("%d", &entrada1);
        scanf("%d", &entrada2);
        scanf("%d", &entrada3);
        casos_teste = casos_teste - 3;

        pthread_create(&t1, NULL, eh_quase_primo1, NULL);
        pthread_create(&t2, NULL, eh_quase_primo2, NULL);
        eh_quase_primo3();
        pthread_join(t1, NULL);
        printf("%d\n", ret1);
        pthread_join(t2, NULL);
        printf("%d\n", ret2);
        printf("%d\n", ret3);
    }

    return 0;
}