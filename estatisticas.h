#ifndef SIGA_MAURICIO_ESTATISTICAS_H
#define SIGA_MAURICIO_ESTATISTICAS_H

/**
 * Imprime o valor medio dos ativos financeiro por tipo
 * @param ativosFinanceiros ponteiro os ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 */
void mediaValorAtivoFinanceiroPorTipo(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros, ValorAtivo *valoresAtivos, int numValoresAtivos);

/**
 * Imprime o top 5 ativos com maior valor
 * @param ativosFinanceiros ponteiro os ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 */
void top5AtivosFinanceiros(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros, ValorAtivo *valoresAtivos, int numValoresAtivos);

#endif //SIGA_MAURICIO_ESTATISTICAS_H
