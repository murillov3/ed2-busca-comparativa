#include <stdlib.h>
#include "hash.h"
#include "medicao.h"

Hash *hash_cria(int m) {
    Hash *h = malloc(sizeof(Hash));
    if (h == NULL) return NULL;

    h->m = m;
    h->n = 0;
    h->lista = calloc(m, sizeof(NoHash *));
    if (h->lista == NULL) {
        free(h);
        return NULL;
    }

    return h;
}

int hash_funcao(const Hash *h, int chave) {
    int r = chave % h->m;
    return (r < 0) ? r + h->m : r;
}

void hash_insere(Hash *h, int chave, int pos) {
    int i = hash_funcao(h, chave);

    NoHash *novo = malloc(sizeof(NoHash));
    if (novo == NULL) return;

    novo->chave = chave;
    novo->pos = pos;
    novo->prox = h->lista[i];
    h->lista[i] = novo;

    h->n++;
}

int hash_busca(const Hash *h, int chave) {
    int i = hash_funcao(h, chave);
    NoHash *p = h->lista[i];

    while (p != NULL) {
        comparacoes++;
        if (p->chave == chave) {
            return p->pos;
        }
        p = p->prox;
    }

    return -1;
}

int hash_maior_lista(const Hash *h) {
    int maior = 0;

    for (int i = 0; i < h->m; i++) {
        int tam = 0;
        NoHash *p = h->lista[i];
        while (p != NULL) {
            tam++;
            p = p->prox;
        }
        if (tam > maior) {
            maior = tam;
        }
    }

    return maior;
}

void hash_libera(Hash *h) {
    if (h == NULL) return;

    for (int i = 0; i < h->m; i++) {
        NoHash *p = h->lista[i];
        while (p != NULL) {
            NoHash *prox = p->prox;
            free(p);
            p = prox;
        }
    }

    free(h->lista);
    free(h);
}
