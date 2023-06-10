#ifndef SIGA_MAURICIO_RELATORIOS_H
#define SIGA_MAURICIO_RELATORIOS_H

#include "Lib.h"

/**
 *
 * Imprime os ativos que estao associados a uma determinada carteira
 * @param carteira ponteiro para a carteira a imprimir
 * @param ativosFinanceiros ponteiro os ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 */
void imprimirAtivosCarteira(Carteira *carteira, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros,
                            ValorAtivo *valoresAtivos, int numValoresAtivos);

/**
 * Imprimir toda informação de uma carteira
 * @param carteira ponteiro para a carteira a imprimir
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 * @param ativosFinanceiros ponteiro os ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 */
void
imprimirCarteira(Carteira *carteira, ValorAtivo *valoresAtivos, int numValoresAtivos, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros);

/**
 * Imprime toda a informação de todas as carteiras
 * @param carteiras ponteiro as carteiras
 * @param numCarteiras quantidade de carteira que existe
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 * @param ativosFinanceiros ponteiro os ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 */
void imprimirCarteiras(Carteira *carteiras, int numCarteiras, ValorAtivo *valoresAtivos, int numValoresAtivos,
                       AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros);

/**
 * Imprimir toda informação dos ativos financeiros
 * @param ativosFinanceiros ponteiro os ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 */
void imprimirAtivosFinanceiros(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros);

/**
 * Imprimir informação de todos os valores de ativos
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 */
void imprimirValoresAtivos(ValorAtivo *valoresAtivos, int numValoresAtivos);

#endif //SIGA_MAURICIO_RELATORIOS_H
