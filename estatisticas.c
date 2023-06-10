#include <string.h>
#include <stdio.h>

#include "Lib.h"


void mediaValorAtivoFinanceiroPorTipo(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros, ValorAtivo *valoresAtivos, int numValoresAtivos) {

    typedef struct {
        char tipo[20];
        float sum;
        int count;
    } MediaContagem;

    MediaContagem tipos[numAtivosFinanceiros];
    int numMediaContagem = 0;

    for (int i = 0; i < numAtivosFinanceiros; i++) {
        char *tipo = ativosFinanceiros[i].tipo;
        float valor = getPrecoAtivoFinanceiro(ativosFinanceiros[i].id, valoresAtivos, numValoresAtivos);

        int existe = 0;
        for (int j = 0; j < numMediaContagem; j++) {
            if (strcmp(tipos[j].tipo, tipo) == 0) {
                tipos[j].sum += valor;
                tipos[j].count++;
                existe = 1;
                break;
            }
        }

        if (!existe) {
            strcpy(tipos[numMediaContagem].tipo, tipo);
            tipos[numMediaContagem].sum = valor;
            tipos[numMediaContagem].count = 1;
            numMediaContagem++;
        }
    }

    printf("\nMedia valor Ativo Financeiro por tipo:\n");
    for (int i = 0; i < numMediaContagem; i++) {
        float media = tipos[i].sum / (float) tipos[i].count;
        printf("Tipo: %s, valor médio: %.2f€\n", tipos[i].tipo, media);
    }
}


void top5AtivosFinanceiros(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros, ValorAtivo *valoresAtivos, int numValoresAtivos) {

    //Criar array com os indices do ativos financeiros para não trocar a ordem original
    int indices[numAtivosFinanceiros];
    for (int i = 0; i < numAtivosFinanceiros; i++)
        indices[i] = i;

    for (int i = 0; i < numAtivosFinanceiros - 1; i++) {
        for (int j = 0; j < numAtivosFinanceiros - i - 1; j++) {
            float valor1 = getPrecoAtivoFinanceiro(ativosFinanceiros[indices[j]].id, valoresAtivos, numValoresAtivos);
            float valor2 = getPrecoAtivoFinanceiro(ativosFinanceiros[indices[j + 1]].id, valoresAtivos, numValoresAtivos);

            if (valor1 < valor2) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }

    printf("\nTop 5 Ativos Financeiros com maior valor:\n");
    for (int i = 0; i < 5 && i < numAtivosFinanceiros; i++) {
        int indiceAtivo = indices[i];
        AtivoFinanceiro *ativo = &ativosFinanceiros[indiceAtivo];
        ValorAtivo *valorAtivo = getValorAtivoPorId(ativo->id, valoresAtivos, numValoresAtivos);
        int ano = valorAtivo->data.tm_year + 1900;
        int mes = valorAtivo->data.tm_mon + 1;
        int dia = valorAtivo->data.tm_mday;
        printf("%d. %.2f€ %d-%d-%d %d %s\n", i + 1, valorAtivo->valor, ano, mes, dia, ativo->id, ativo->nome);
    }
}
