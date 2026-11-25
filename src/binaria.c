#include "binaria.h"
#include "medicao.h"

/* ===================== TAREFA 2: BUSCA BINÁRIA ===================== */

int busca_binaria(const Aluno *v, int n, int mat) {
    int ini = 0;
    int fim = n - 1;

    while (ini <= fim) {
        int meio = ini + (fim - ini) / 2;
        comparacoes++;  /* uma vez por elemento do meio examinado */

        if (v[meio].matricula == mat) {
            return meio;
        } else if (v[meio].matricula < mat) {
            ini = meio + 1;   /* procura à direita */
        } else {
            fim = meio - 1;   /* procura à esquerda */
        }
    }

    return -1;
}
