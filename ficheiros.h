#ifndef SIGA_MAURICIO_FICHEIROS_H
#define SIGA_MAURICIO_FICHEIROS_H


#include <stdbool.h>
#include "Lib.h"

/**
 * Aloca uma determinada quantidade de memoria disponivel para os valores de ativos
 * @param valoresAtivos duplo ponteiro para a lista de ativos
 * @param maxValoresAtivos tamanho maximo de valores de ativos
 * @return true em caso de sucesso, false caso contrario
 */
bool alocaValoresAtivos(ValorAtivo **valoresAtivos, int *maxValoresAtivos);

/**
 * Realoca para o dobro quantidade de memoria disponivel para os valores de ativos
 * @param valoresAtivos duplo ponteiro para a lista de ativos
 * @param maxValoresAtivos tamanho maximo de valores de ativos
 * @return true em caso de sucesso, false caso contrario
 */
bool realocaValoresAtivos(ValorAtivo **valoresAtivos, int *maxValoresAtivos);

/**
 * Aloca uma determinada quantidade de memoria disponivel para os ativos financeiros
 * @param ativosFinanceiros duplo ponteiro para a lista de ativos
 * @param maxAtivosFinanceiros tamanho maximo de valores de ativos
 * @return true em caso de sucesso, false caso contrario
 */
bool alocaAtivosFinanceiros(AtivoFinanceiro **ativosFinanceiros, int *maxAtivosFinanceiros);

/**
 * Realoca para o dobro quantidade de memoria disponivel para os ativos financeiros
 * @param ativosFinanceiros duplo ponteiro para a lista de ativos financeiros
 * @param maxAtivosFinanceiros tamanho maximo de ativos financeiros
 * @return true em caso de sucesso, false caso contrario
 */
bool realocaAtivosFinanceiros(AtivoFinanceiro **ativosFinanceiros, int *maxAtivosFinanceiros);

/**
 * Le de um ficherio toda a informação das carteiras
 * @param nomeArquivo nome do ficherio a ler
 * @param carteiras ponteiro as carteiras
 * @param numCarteiras quantidade de carteiras que existe
 */
void lerDadosCarteiras(char *nomeArquivo, Carteira *carteiras, int *numCarteiras);

/**
 * Le de um ficherio toda a informação dos ativos financeiros
 * @param nomeArquivo nome do ficherio a ler
 * @param ativosFinanceiros duplo ponteiro para a lista de ativos financeiros
 * @param tamanhoArray tamanho maximo de ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 */
void lerAtivosFinanceiros(char *nomeArquivo, AtivoFinanceiro **ativosFinanceiros, int *tamanhoArray, int *numAtivosFinanceiros);

/**
 * Le de um ficherio toda a informação dos valores de ativos
 * @param nomeArquivo nome do ficherio a ler
 * @param valoresAtivos duplo ponteiro para a lista de valores de ativos
 * @param numValoresAtivos quantidade de valores de ativos que existe
 * @param maxValoresAtivos quantidade maxima memoria disponivel para os valores de ativos
 */
void atualizarValoresAtivos(char *nomeFicheiro, ValorAtivo **valoresAtivos, int *numValoresAtivos, int *maxValoresAtivos);

/**
 * Importar de ficheiro binario os valores dos ativos
 * @param valoresAtivos duplo ponteiro para a lista de valores de ativos
 * @param numValoresAtivos quantidade de valores de ativos que existe
 * @param maxValoresAtivos quantidade maxima memoria disponivel para os valores de ativos
 */
void importarValoresAtivos(ValorAtivo **valoresAtivos, int *numValoresAtivos, int *maxValoresAtivos);

/**
 * Exporta para ficherio binario os valores dos ativos
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 */
void exportarValoresAtivos(ValorAtivo *valoresAtivos, int numValoresAtivos);

/**
 * Exporta para ficherio binario os carteiras
 * @param carteiras ponteiro as carteiras
 * @param numCarteiras quantidade de carteiras que existe
 */
void exportarCarteiras(Carteira *carteiras, int numCarteiras);

/**
 * Importar de ficheiro binario os carteiras
 * @param carteiras ponteiro as carteiras
 * @param numCarteiras quantidade de carteiras que existe
 */
void importarCarteiras(Carteira *carteiras, int *numCarteiras);

#endif //SIGA_MAURICIO_FICHEIROS_H
