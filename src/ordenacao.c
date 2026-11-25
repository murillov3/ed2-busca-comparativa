#include "ordenacao.h"
#include "medicao.h"

/* ===================== TAREFA 1: ORDENAÇÃO ===================== */

void ordena_insercao(Aluno *v, int n) {
    for (int i = 1; i < n; i++) {
        Aluno x = v[i];
        int j = i - 1;

        /* Desloca para a direita os alunos com matrícula maior que x */
        while (j >= 0) {
            comparacoes++;
            if (v[j].matricula > x.matricula) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }

        v[j + 1] = x;
    }
}

/* Função auxiliar recursiva do Quicksort (Hoare, pivô = elemento do meio) */
static void quick(Aluno *v, int ini, int fim) {
    int i = ini;
    int j = fim;
    int pivo = v[ini + (fim - ini) / 2].matricula;

    while (i <= j) {
        /* Avança i enquanto matrícula < pivô */
        while (1) {
            comparacoes++;
            if (v[i].matricula < pivo) i++;
            else break;
        }

        /* Recua j enquanto matrícula > pivô */
        while (1) {
            comparacoes++;
            if (v[j].matricula > pivo) j--;
            else break;
        }

        if (i <= j) {
            Aluno tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            i++;
            j--;
        }
    }

    if (ini < j) quick(v, ini, j);
    if (i < fim) quick(v, i, fim);
}

void ordena_quick(Aluno *v, int n) {
    if (n > 1) {
        quick(v, 0, n - 1);
    }
}
