#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    unsigned short numero;  
    unsigned short posicao;  
} Pessoa;

int main(void) {

    unsigned short qtsPessoas, qtsPessoasSairam;
    unsigned short i, idPessoa;
    Pessoa fila[51000];

    scanf("%hu", &qtsPessoas);

    memset(fila, 0, sizeof(fila));

    for (i = 0; i < qtsPessoas; i++) {
        scanf("%hu", &idPessoa);
        fila[i].numero = idPessoa;
        fila[idPessoa].posicao = i;
    }

    scanf("%hu", &qtsPessoasSairam);
    for (i = 0; i < qtsPessoasSairam; i++) {
        scanf("%hu", &idPessoa);
        fila[fila[idPessoa].posicao].numero = 0;
    }

    bool primeiro = true;
    for (i = 0; i < qtsPessoas; i++) {
        if (fila[i].numero != 0) {
            if (!primeiro)
                printf(" ");
            printf("%hu", fila[i].numero);
            primeiro = false;
        }
    }

    printf("\n");
    return 0;
}
