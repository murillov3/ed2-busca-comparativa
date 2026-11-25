#include <stddef.h>
#include "arvoreb.h"
#include "medicao.h"

/* ===================== TAREFA 4: ÁRVORE-B ===================== */

int arvb_busca(const ArvoreB *a, int chave) {
    NoB *x = a->raiz;

    while (x != NULL) {
        comparacoes++;

        int i = 0;

        while (i < x->n && chave > x->chave[i])
            i++;

        if (i < x->n && chave == x->chave[i])
            return x->pos[i];

        if (x->folha)
            return -1;

        x = x->filho[i];
    }

    return -1;
}

static void divide_filho(ArvoreB *a, NoB *x, int i) {
    int t = a->t;

    NoB *y = x->filho[i];
    NoB *z = arvb_novo_no(a, y->folha);

    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->chave[j] = y->chave[j + t];
        z->pos[j] = y->pos[j + t];
    }

    if (!y->folha) {
        for (int j = 0; j < t; j++)
            z->filho[j] = y->filho[j + t];
    }

    y->n = t - 1;

    for (int j = x->n; j >= i + 1; j--)
        x->filho[j + 1] = x->filho[j];

    x->filho[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) {
        x->chave[j + 1] = x->chave[j];
        x->pos[j + 1] = x->pos[j];
    }

    x->chave[i] = y->chave[t - 1];
    x->pos[i] = y->pos[t - 1];

    x->n++;
}

static void insere_nao_cheio(ArvoreB *a, NoB *x, int k, int v) {
    int i = x->n - 1;

    if (x->folha) {
        while (i >= 0 && k < x->chave[i]) {
            x->chave[i + 1] = x->chave[i];
            x->pos[i + 1] = x->pos[i];
            i--;
        }

        x->chave[i + 1] = k;
        x->pos[i + 1] = v;
        x->n++;
    } else {
        while (i >= 0 && k < x->chave[i])
            i--;

        i++;

        if (x->filho[i]->n == 2 * a->t - 1) {
            divide_filho(a, x, i);

            if (k > x->chave[i])
                i++;
        }

        insere_nao_cheio(a, x->filho[i], k, v);
    }
}

void arvb_insere(ArvoreB *a, int chave, int pos) {
    if (arvb_busca(a, chave) != -1)
        return;

    if (a->raiz == NULL) {
        a->raiz = arvb_novo_no(a, 1);

        a->raiz->chave[0] = chave;
        a->raiz->pos[0] = pos;
        a->raiz->n = 1;

        return;
    }

    NoB *r = a->raiz;

    if (r->n == 2 * a->t - 1) {
        NoB *s = arvb_novo_no(a, 0);

        a->raiz = s;
        s->filho[0] = r;

        divide_filho(a, s, 0);

        insere_nao_cheio(a, s, chave, pos);
    } else {
        insere_nao_cheio(a, r, chave, pos);
    }
}

int arvb_altura(const ArvoreB *a) {
    int altura = 0;
    NoB *x = a->raiz;

    while (x != NULL) {
        altura++;

        if (x->folha)
            break;

        x = x->filho[0];
    }

    return altura;
}

/* ===================== DESAFIO (BÔNUS) ===================== */

static int conta_faixa(NoB *x, int ini, int fim) {
    if (x == NULL)
        return 0;

    int total = 0;
    int i;

    for (i = 0; i < x->n; i++) {
        if (!x->folha && fim >= x->chave[i])
            total += conta_faixa(x->filho[i], ini, fim);

        if (x->chave[i] >= ini && x->chave[i] <= fim)
            total++;
        
        if (x->chave[i] > fim)
            break;
    }

    if (!x->folha && (i == x->n || x->chave[i] <= fim))
        total += conta_faixa(x->filho[i], ini, fim);

    return total;
}

int arvb_conta_faixa(const ArvoreB *a, int ini, int fim) {
    if (ini > fim || a->raiz == NULL)
        return 0;

    return conta_faixa(a->raiz, ini, fim);
}