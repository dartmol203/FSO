#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tam_vetor;
    int valor;
    int *vetor;
    int tam_quadro, *quadro;
    int j = 0, pf = 0, antigo = 0, i = 0;
    int vetor_quadro[10000], vetor_pf[10000];
    int count = 0;
    int flag = 0;

    scanf("%d", &tam_vetor);

    vetor = malloc(tam_vetor * sizeof(int));

    // aloco cada numero em cada posicao do vetor
    for (i = 0; i < tam_vetor; i++)
    {
        scanf("%d", &valor);
        vetor[i] = valor;
    }

    // le o tamanho dos quadros
    while (scanf("%d", &tam_quadro) != EOF)
    {
        // cria e inicializa meu vetor quadro com a quantidade do input
        quadro = (int *)malloc(tam_quadro * sizeof(int));
        for (i = 0; i < tam_quadro; i++)
        {
            quadro[i] = 0;
        }

        j = 0;
        pf = 0;
        antigo = 0;

        for (int i = 0; i < tam_vetor; i++)
        {
            // verifica se o num do vetor esta dentro do quadro se sim ele nao da page fault
            for (j = 0; j < tam_quadro; j++)
            {
                if (vetor[i] == quadro[j])
                {
                    break;
                }

                // verifica as posicoes
                if (j == tam_quadro - 1 && vetor[i] != quadro[j])
                {
                    pf++;
                    quadro[antigo] = vetor[i];
                    if (antigo == (tam_quadro - 1))
                    {
                        antigo = 0;
                    }
                    else
                    {
                        antigo++;
                    }
                }
            }
        }

        vetor_quadro[count] = tam_quadro;
        vetor_pf[count] = pf;
        count++;
    }

    // detecta Anomalia
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (vetor_quadro[i] > vetor_quadro[j] && vetor_pf[i] > vetor_pf[j])
            {
                flag = 1;
            }
        }
        printf("%d %d\n", vetor_quadro[i], vetor_pf[i]);
    }

    if (flag == 1)
    {
        printf("Belady detectado\n");
    }
    else
    {
        printf("Sem anomalia\n");
    }

    return 0;
}