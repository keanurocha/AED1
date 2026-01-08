#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    char conteudo;
    struct No *seg;
} No;

No* empilhar(No *topo);
No* desempilhar(No *topo);

int main()
{
    char N[1000];

    while (fgets(N, sizeof(N), stdin) != NULL)
    {
        No *pilha = NULL;

        int erro = 0;

        for (int i = 0; N[i] != '\0'; i++)
        {
            if (N[i] == '(')
            {
                pilha = empilhar(pilha);
            } 
            else if (N[i] == ')')
            {
                if (pilha == NULL)
                {
                    erro = 1; 
                    break;
                }
                else
                {
                    pilha = desempilhar(pilha);
                }
            }
        }

        if (erro == 1 || pilha != NULL)
        {
            printf("incorrect\n");
        }
        else
        {
            printf("correct\n");
        }

        free(pilha);
    }
}

No* empilhar(No *topo)
{
    No *nova = malloc(sizeof(No));

    nova->conteudo = '(';
    nova->seg = topo;
    return nova;

    return topo;
}

No* desempilhar(No *topo)
{
    if (topo != NULL)
    {
        No *aux = topo;
        topo = topo->seg;
        free(aux);
        return topo;
    }
    return NULL;
}
