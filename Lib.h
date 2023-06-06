//
// Created by Micael Sampaio on 06/06/2023.
//

#ifndef SIGA_MAURICIO_LIB_H
#define SIGA_MAURICIO_LIB_H

// Número máximo de carteiras
#define MAX_CARTEIRAS 100
// Número máximo de AtivosCarteira
#define MAX_ATIVOS_CARTEIRA 50

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int id;
    char descricao[100];
    int ativo_carteira_ids[MAX_ATIVOS_CARTEIRA];
    int num_ativo_carteira;
} Carteira;

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
    int ativo_financeiro_id;
    Data data;
    double valor;
} ValorAtivo;

#endif //SIGA_MAURICIO_LIB_H
