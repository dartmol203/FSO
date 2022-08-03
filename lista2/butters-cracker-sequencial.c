#include <stdio.h>
#include <stdlib.h>

int main()
{

    int inicio, fim, vet[100000], cont = 0, contaux;

    scanf(" %d %d", &inicio, &fim);

    while (scanf(" %d", &vet[cont]) != EOF)
    {
        cont++;
    }

    if (fim - inicio != 0)
    {
        for (unsigned int i = inicio; i <= fim; i++)
        {
            // printf("-- %u -- %d -- %d \n", i, inicio, fim);
            contaux = 0;
            unsigned int seed = i;
            for (int j = 0; j < cont; j++)
            {
                for (int k = 1; k < 10000; k++)
                {
                    rand_r(&seed);
                }
                int x = rand_r(&seed) % 256;
                // printf("%d ", x);
                if (x == vet[j])
                {
                    contaux++;
                }
                else
                {
                    break;
                }
            }
            // printf("\n%d %d\n", cont, contaux);
            if (cont == contaux)
            {
                printf("%u\n", i);
                break;
            }
        }
    }
    else
    {
        printf("%d\n", inicio);
    }

    // printf("to aqui\n");

    return 0;
}