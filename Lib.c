#include "Lib.h"


AtivoCarteira *getAtivoCarteiraPorId(int idAtivoFinanceiro, Carteira *carteira) {
    for (int i = 0; i < carteira->numAtivosCarteira; i++)
        if (carteira->ativosCarteira[i].id == idAtivoFinanceiro)
            return &carteira->ativosCarteira[i];
    return NULL;
}

AtivoFinanceiro *getAtivoFinanceiroPorId(int idAtivo, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {
    for (int i = 0; i < numAtivosFinanceiros; i++)
        if (ativosFinanceiros[i].id == idAtivo)
            return &ativosFinanceiros[i];
    return NULL;
}

ValorAtivo *getValorAtivoPorId(int idAtivoFinanceiro, ValorAtivo *valoresAtivos, int numValoresAtivos) {
    time_t maisRecente = 0;
    ValorAtivo *valorAtivo = NULL;

    for (int i = 0; i < numValoresAtivos; ++i) {
        if (valoresAtivos[i].ativoFinanceiroId == idAtivoFinanceiro) {
            time_t currentDate = mktime(&(valoresAtivos[i].data));
            if (currentDate > maisRecente) {
                maisRecente = currentDate;
                valorAtivo = &valoresAtivos[i];
            }
        }
    }
    return valorAtivo;
}

float getPrecoAtivoFinanceiro(int idAtivoFinanceiro, ValorAtivo *valoresAtivos, int numValoresAtivos) {
    ValorAtivo *valorAtivo = getValorAtivoPorId(idAtivoFinanceiro, valoresAtivos, numValoresAtivos);

    if (valorAtivo == NULL)
        return -1;
    else
        return valorAtivo->valor;
}

