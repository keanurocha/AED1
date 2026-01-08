#include <stdio.h>

void selectionSort(short *, unsigned short);
int alunosSemTroca;

int main(void) {

    unsigned short numCasos;
    unsigned short numAlunos;
    int i;

    scanf("%hu", &numCasos);

    while (numCasos--) {

        scanf("%hu", &numAlunos);

        short filaOriginal[numAlunos];
        short filaOrdenada[numAlunos];

        for (i = 0; i < numAlunos; i++) {
            scanf("%hd", &filaOriginal[i]);
            filaOrdenada[i] = filaOriginal[i];
        }

        alunosSemTroca = 0;
        selectionSort(filaOrdenada, numAlunos);

        for (i = 0; i < numAlunos; i++) {
            if (filaOriginal[i] == filaOrdenada[i])
                alunosSemTroca++;
        }

        printf("%d\n", alunosSemTroca);
    }

    return 0;
}

void selectionSort(short *vetor, unsigned short tamanho) {

    unsigned short i, j, indiceMaior;
    short temp;

    for (i = 0; i < tamanho - 1; i++) {

        indiceMaior = i;
        for (j = i + 1; j < tamanho; j++) {
            if (vetor[j] > vetor[indiceMaior])
                indiceMaior = j;
        }

        if (i != indiceMaior) {
            temp = vetor[i];
            vetor[i] = vetor[indiceMaior];
            vetor[indiceMaior] = temp;
        }
    }
}
