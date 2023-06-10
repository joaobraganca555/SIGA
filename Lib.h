#ifndef SIGA_LIB_H
#define SIGA_LIB_H

#include <time.h>

#define MAX_CARTEIRAS 100       // numero maximo de carteiras
#define MAX_ATIVOS_CARTEIRA 50  // numero maximo de AtivosCarteira

typedef struct tm Data;

typedef struct {
    int id;
    int quantidade;
} AtivoCarteira;

typedef struct {
    int id;
    char tipo[20];
    char nome[50];
} AtivoFinanceiro;

typedef struct {
    int ativoFinanceiroId;
    Data data;
    float valor;
} ValorAtivo;

typedef struct {
    int id;
    char descricao[100];
    AtivoCarteira ativosCarteira[MAX_ATIVOS_CARTEIRA];
    int numAtivosCarteira;
} Carteira;

/**
 * Obter um ativo carteira por id
 * @param idAtivoFinanceiro id do ativo financeiro a encontrar o valor
 * @param carteira ponteiro para a carteira onde procurar o ativo carteira
 * @return ponteiro para o ativo carteira, caso não existe retorna NULL
 */
AtivoCarteira *getAtivoCarteiraPorId(int idAtivoFinanceiro, Carteira *carteira);

/**
 * Obter um ativo financeiro por id
 * @param idAtivo id do ativo financeiro a encontrar
 * @param ativosFinanceiros ponteiro os ativos financeiros
 * @param numAtivosFinanceiros quantidade de ativos financeiros que existe
 * @return ponteiro para o ativo financeiro, caso não existe retorna NULL
 */
AtivoFinanceiro *getAtivoFinanceiroPorId(int idAtivo, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros);

/**
 * * Obter um valor do ativo por id
 * @param idAtivoFinanceiro id do ativo financeiro a encontrar
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 * @return ponteiro para o valor da ativo, caso não existe retorna NULL
 */
ValorAtivo *getValorAtivoPorId(int idAtivoFinanceiro, ValorAtivo *valoresAtivos, int numValoresAtivos);

/**
 * Obter um valor do ativo por id
 * @param idAtivoFinanceiro id do ativo financeiro a encontrar o valor
 * @param valoresAtivos ponteiro para os valores dos ativos
 * @param numValoresAtivos quantidade que existe de valores de ativos
 * @return o valor do ativo financeiro, caso não exista retorna -1
 */
float getPrecoAtivoFinanceiro(int idAtivoFinanceiro, ValorAtivo *valoresAtivos, int numValoresAtivos);

#endif
