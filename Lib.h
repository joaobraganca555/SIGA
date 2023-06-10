#ifndef SIGA_LIB_H
#define SIGA_LIB_H

#define MAX_CARTEIRAS 100       // numero maximo de carteiras
#define MAX_ATIVOS_CARTEIRA 50  // numero maximo de AtivosCarteira

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int id;
    int quantidade;
} AtivoCarteira;

typedef struct {
    int id;
    char tipo;
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

#endif
