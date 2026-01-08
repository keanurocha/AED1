#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define MAXSIZE 1000

typedef unsigned short us;


typedef struct tipoNoQueue {
    int dado;
    struct tipoNoQueue *proximo;
} tipoNoQueue;

typedef struct tipoFila {
    tipoNoQueue *primeiro;
    tipoNoQueue *ultimo;
} tipoFila;


typedef struct tipoNoPilha {
    int dado;
    struct tipoNoPilha *proximo;
} tipoNoPilha;

typedef struct tipoPilha {
    tipoNoPilha *topo;
} tipoPilha;


typedef struct pqueue {
    int dado;
    int prioridade;
} pqueue;

typedef struct _pqueue {
    int qtd;
    struct pqueue dados[MAXSIZE];
} _pqueue;

void queue(tipoFila *);
void push(tipoFila *, int);
int front(tipoFila *);
void pop(tipoFila *);


void stack(tipoPilha *);
void pushPilha(tipoPilha *, int);
void popPilha(tipoPilha *);
int top(tipoPilha *);


_pqueue* priority();
void pushPqueue(_pqueue *, int, int);
void popPqueue(_pqueue *);
int topPqueue(_pqueue *);
void balanceiaRemocao(_pqueue *, int);
void balanceiaInsercao(_pqueue *, int);

int main(void) {
    int n;
    while (scanf("%d", &n) != EOF) {

        int x, comando, i;
        _Bool queueN, stackN, pqueueN;

        _pqueue *priority_queue = priority();
        tipoFila fila;
        tipoPilha stackk;

        queue(&fila);
        stack(&stackk);

        queueN = stackN = pqueueN = true;

        for (i = 0; i < n; ++i) {
            scanf("%d %d", &comando, &x);

            if (comando == 1) {
                // inserção
                pushPqueue(priority_queue, x, x);
                pushPilha(&stackk, x);
                push(&fila, x);
            } else {
                // remoção
                if (!stackk.topo || top(&stackk) != x)
                    stackN = false;
                else
                    popPilha(&stackk);

                if (!fila.primeiro || front(&fila) != x)
                    queueN = false;
                else
                    pop(&fila);

                if (topPqueue(priority_queue) != x)
                    pqueueN = false;
                else
                    popPqueue(priority_queue);
            }
        }

        if (!stackN && !queueN && !pqueueN)
            printf("impossible\n");
        else if ((stackN && queueN) || (stackN && pqueueN) || (queueN && pqueueN))
            printf("not sure\n");
        else if (stackN)
            printf("stack\n");
        else if (queueN)
            printf("queue\n");
        else if (pqueueN)
            printf("priority queue\n");

        free(priority_queue);
    }

    return 0;
}


void queue(tipoFila *fila) {
    fila->primeiro = fila->ultimo = NULL;
}

void push(tipoFila *fila, int x) {
    tipoNoQueue *aux = (tipoNoQueue *) malloc(sizeof(tipoNoQueue));
    if (!aux) exit(1);
    aux->dado = x;
    aux->proximo = NULL;

    if (fila->primeiro)
        fila->ultimo->proximo = aux;
    else
        fila->primeiro = aux;

    fila->ultimo = aux;
}

void pop(tipoFila *fila) {
    if (!fila->primeiro) return;

    tipoNoQueue *aux = fila->primeiro;
    fila->primeiro = fila->primeiro->proximo;

    if (!fila->primeiro)
        fila->ultimo = NULL;

    free(aux);
}

int front(tipoFila *fila) {
    if (!fila->primeiro) return -1;
    return fila->primeiro->dado;
}


void stack(tipoPilha *pilha) {
    pilha->topo = NULL;
}

void pushPilha(tipoPilha *pilha, int x) {
    tipoNoPilha *aux = (tipoNoPilha *) malloc(sizeof(tipoNoPilha));
    if (!aux) exit(1);
    aux->dado = x;
    aux->proximo = pilha->topo;
    pilha->topo = aux;
}

void popPilha(tipoPilha *pilha) {
    if (!pilha->topo) return;
    tipoNoPilha *aux = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(aux);
}

int top(tipoPilha *pilha) {
    if (!pilha->topo) return -1;
    return pilha->topo->dado;
}

_pqueue* priority() {
    _pqueue *filaP = (_pqueue *) malloc(sizeof(_pqueue));
    if (filaP)
        filaP->qtd = 0;
    return filaP;
}

void pushPqueue(_pqueue *filaP, int prioridade, int id) {
    if (!filaP || filaP->qtd == MAXSIZE) exit(1);

    filaP->dados[filaP->qtd].dado = id;
    filaP->dados[filaP->qtd].prioridade = prioridade;
    balanceiaInsercao(filaP, filaP->qtd);
    ++filaP->qtd;
}

void balanceiaInsercao(_pqueue *filaP, int filho) {
    int pai = (filho - 1) / 2;
    pqueue tmp;

    while (filho > 0 && filaP->dados[pai].prioridade < filaP->dados[filho].prioridade) {
        tmp = filaP->dados[filho];
        filaP->dados[filho] = filaP->dados[pai];
        filaP->dados[pai] = tmp;

        filho = pai;
        pai = (filho - 1) / 2;
    }
}

int topPqueue(_pqueue *filaP) {
    if (!filaP || filaP->qtd == 0) return -1;
    return filaP->dados[0].dado;
}

void popPqueue(_pqueue *filaP) {
    if (!filaP || filaP->qtd == 0) return;

    --filaP->qtd;
    filaP->dados[0] = filaP->dados[filaP->qtd];
    balanceiaRemocao(filaP, 0);
}

void balanceiaRemocao(_pqueue *filaP, int pai) {
    int filho;
    pqueue tmp;

    filho = 2 * pai + 1;

    while (filho < filaP->qtd) {
        if (filho < filaP->qtd - 1 &&
            filaP->dados[filho].prioridade < filaP->dados[filho + 1].prioridade)
            ++filho;

        if (filaP->dados[pai].prioridade >= filaP->dados[filho].prioridade)
            break;

        tmp = filaP->dados[pai];
        filaP->dados[pai] = filaP->dados[filho];
        filaP->dados[filho] = tmp;

        pai = filho;
        filho = 2 * pai + 1;
    }
}
