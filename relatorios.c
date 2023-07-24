#include <stdio.h>

#include "relatorios.h"
#include "Lib.h"


void imprimirAtivosCarteira(Carteira *carteira, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros,
                            ValorAtivo *valoresAtivos, int numValoresAtivos) {
    printf("Ativos da carteira:\n");
    float valorTotal = 0;
    for (int j = 0; j < carteira->numAtivosCarteira; j++) {
        AtivoFinanceiro *ativoFinanceiro = getAtivoFinanceiroPorId(carteira->ativosCarteira[j].id, ativosFinanceiros, numAtivosFinanceiros);
        valorTotal += (getPrecoAtivoFinanceiro(carteira->ativosCarteira[j].id, valoresAtivos, numValoresAtivos) *
                       (float) carteira->ativosCarteira[j].quantidade);
        printf("\tid: %d, quantidade: %d, nome: %s\n", carteira->ativosCarteira[j].id, carteira->ativosCarteira[j].quantidade, ativoFinanceiro->nome);
    }
    printf("Valor total da carteira %.2f€\n", valorTotal);
}

void imprimirCarteira(Carteira *carteira, ValorAtivo *valoresAtivos, int numValoresAtivos,
                      AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {
    printf("\n%d - %s\n", carteira->id, carteira->descricao);
    imprimirAtivosCarteira(carteira, ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numValoresAtivos);
}

void imprimirCarteiras(Carteira *carteiras, int numCarteiras, ValorAtivo *valoresAtivos, int numValoresAtivos,
                       AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {
    for (int i = 0; i < numCarteiras; i++) {
        imprimirCarteira(&carteiras[i], valoresAtivos, numValoresAtivos, ativosFinanceiros, numAtivosFinanceiros);
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
        printf("data: %d-%d-%d, id: %d, valor: %f\n",
               valoresAtivos[j].data.tm_year + 1900, valoresAtivos[j].data.tm_mon + 1,
               valoresAtivos[j].data.tm_mday, valoresAtivos[j].ativoFinanceiroId, valoresAtivos[j].valor);
    }
}

