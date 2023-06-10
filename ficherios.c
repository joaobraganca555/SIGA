#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "string.h"
#include "Lib.h"

bool alocaValoresAtivos(ValorAtivo **valoresAtivos, int *maxValoresAtivos, int tam) {
    *valoresAtivos = (ValorAtivo *) malloc(tam * sizeof(ValorAtivo));
    if (*valoresAtivos == NULL) {
        printf("Erro ao alocar memoria para valores ativos\n");
        return false;
    } else {
        *maxValoresAtivos = tam;
        return true;
    }
}

bool realocaValoresAtivos(ValorAtivo **valoresAtivos, int *maxValoresAtivos) {
    ValorAtivo *temp;
    temp = (ValorAtivo *) realloc(*valoresAtivos, (*maxValoresAtivos * 2) * sizeof(ValorAtivo));

    if (temp == NULL) {
        printf("Erro ao realocar memoria para valores ativos\n");
        return false;
    } else {
        *valoresAtivos = temp;
        *maxValoresAtivos *= 2;
        return true;
    }
}

bool alocaAtivosFinanceiros(AtivoFinanceiro **ativosFinanceiros, int *maxAtivosFinanceiros, int tam) {

    *ativosFinanceiros = (AtivoFinanceiro *) malloc(tam * sizeof(AtivoFinanceiro));
    if (*ativosFinanceiros == NULL) {
        printf("Erro ao alocar memoria para Ativos Financeiros\n");
        return false;
    } else {
        *maxAtivosFinanceiros = tam;
        return true;
    }
}

bool realocaAtivosFinanceiros(AtivoFinanceiro **ativosFinanceiros, int *maxAtivosFinanceiros) {

    AtivoFinanceiro *temp;
    temp = (AtivoFinanceiro *) realloc(*ativosFinanceiros, (*maxAtivosFinanceiros * 2) * sizeof(AtivoFinanceiro));

    if (temp == NULL) {
        printf("Erro ao realocar memoria para ativos financeiros\n");
        return false;
    } else {
        *ativosFinanceiros = temp;
        *maxAtivosFinanceiros *= 2;
        return true;
    }
}

void lerDadosCarteiras(char *nomeArquivo, Carteira *carteiras, int *numCarteiras) {
    FILE *file;
    Carteira *tempCarteiras = carteiras;

    file = fopen(nomeArquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o file");
        return;
    }

    while (!feof(file)) {
        char linha[100];
        fgets(linha, sizeof(linha), file);

        if (*numCarteiras == MAX_CARTEIRAS) {
            printf("Limite de %d Carteiras atingido", MAX_CARTEIRAS);
            break;
        }

        // Nova carteira, reinicializar variáveis
        if (linha[0] == '-') {
            tempCarteiras++;
            continue;
        }

        // Carteira ID e Descrição
        if (linha[0] == 'C') {
            sscanf(linha, "CarteiraId %d", &tempCarteiras->id);
            fgets(linha, sizeof(linha), file);

            //para não apanhar os possiveis caraters de fim de linha
            sscanf(linha, "%[^\n\r]", tempCarteiras->descricao);

            tempCarteiras->numAtivosCarteira = 0;
            (*numCarteiras)++;
        }

        // Ler todas os AtivoCarteira desta carteira
        AtivoCarteira *tempAtivosCarteira = tempCarteiras->ativosCarteira;
        while (!feof(file)) {
            fgets(linha, sizeof(linha), file);

            // se encontrar --- recua no ponteiro do ficheiro para a linha anterior porque significa que é uma nova carteira
            if (linha[0] == '-') {
                fseek(file, (long long) -strlen(linha), SEEK_CUR);
                break;
            }

            if (tempCarteiras->numAtivosCarteira == MAX_ATIVOS_CARTEIRA) {
                printf("Limite de %d AtivosCarteira atingido para a carteira %d", MAX_ATIVOS_CARTEIRA, tempCarteiras->id);
                break;
            }

            sscanf(linha, "Id de AtivoFinanceiro %d", &tempAtivosCarteira->id);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "Quantidade de AtivoFinanceiro %d", &tempAtivosCarteira->quantidade);

            (tempCarteiras->numAtivosCarteira)++;
            tempAtivosCarteira++;
        }
    }
    fclose(file);
}

void lerAtivosFinanceiros(char *nomeArquivo, AtivoFinanceiro **ativosFinanceiros, int *tamanhoArray, int *numAtivosFinanceiros) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%d,%[^,],%49[^\n\r]",
                  &(*ativosFinanceiros)[i].id, (*ativosFinanceiros)[i].tipo, (*ativosFinanceiros)[i].nome) == 3) {
        i++;
        (*numAtivosFinanceiros)++;

        //remover o caracter de fim de linha
        (*ativosFinanceiros)[i].nome[strcspn((*ativosFinanceiros)[i].nome, "\r")] = '\0';

        //Se o tamanho maximo foi atingido é realocado mais memoria
        if (i >= *tamanhoArray) {
            if (!realocaAtivosFinanceiros(ativosFinanceiros, tamanhoArray)) {
                break;
            }
        }
    }
    fclose(file);
}

void atualizarValoresAtivos(char *nomeFicheiro, ValorAtivo **valoresAtivos, int *numValoresAtivos, int *maxValoresAtivos) {

    FILE *file = fopen(nomeFicheiro, "r");

    if (file == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    int i = 0;
    while (!feof(file)) {

        if (*numValoresAtivos == *maxValoresAtivos)
            if (!realocaValoresAtivos(valoresAtivos, maxValoresAtivos))
                break;

        char data[11];
        fscanf(file, "%s %d %f", data, &(*valoresAtivos)[i].ativoFinanceiroId, &(*valoresAtivos)[i].valor);

        strptime(data, "%Y-%m-%d", &(*valoresAtivos)[i].data);

        (*numValoresAtivos)++;
        i++;
    }
    fclose(file);
}



