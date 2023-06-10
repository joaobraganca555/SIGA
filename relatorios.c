#include <stdio.h>

#include "relatorios.h"
#include "Lib.h"


void imprimirAtivosCarteira(Carteira *carteira, ValorAtivo *valoresAtivos, int numValoresAtivos) {
    printf("\tAtivos da carteira:\n");
    float valorTotal = 0;
    for (int j = 0; j < carteira->numAtivosCarteira; j++) {
        printf("\t%d quantidade: %d\n", carteira->ativosCarteira[j].id, carteira->ativosCarteira[j].quantidade);
        valorTotal += getPrecoAtivoFinanceiro(carteira->ativosCarteira[j].id, valoresAtivos, numValoresAtivos);
    }
    printf("Valor total da carteira %.2f€\n", valorTotal);
}

void imprimirCarteira(Carteira *carteira, ValorAtivo *valoresAtivos, int numValoresAtivos) {
    printf("\n%d - %s\n", carteira->id, carteira->descricao);
    imprimirAtivosCarteira(carteira, valoresAtivos, numValoresAtivos);
}

void imprimirCarteiras(Carteira *carteiras, int numCarteiras, ValorAtivo *valoresAtivos, int numValoresAtivos) {
    for (int i = 0; i < numCarteiras; i++) {
        imprimirCarteira(carteiras, valoresAtivos, numValoresAtivos);
    }
}

void imprimirAtivosFinanceiros(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {
    printf("Ativos Financeiros:\n");
    for (int j = 0; j < numAtivosFinanceiros; j++) {
        printf("ID: %d, Tipo: %s, Nome: %s\n", ativosFinanceiros[j].id, ativosFinanceiros[j].tipo, ativosFinanceiros[j].nome);
    }
}

void imprimirValoresAtivos(ValorAtivo *valoresAtivos, int numValoresAtivos) {
    printf("Valores Ativos:\n");
    for (int j = 0; j < numValoresAtivos; j++) {
        printf("data: %d,%d,%d, id: %d, valor: %f\n",
               valoresAtivos[j].data.tm_year + 1900, valoresAtivos[j].data.tm_mon + 1,
               valoresAtivos[j].data.tm_mday, valoresAtivos[j].ativoFinanceiroId, valoresAtivos[j].valor);
    }
}

