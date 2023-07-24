#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "string.h"
#include "Lib.h"

bool alocaValoresAtivos(ValorAtivo **valoresAtivos, int *maxValoresAtivos) {
    *valoresAtivos = (ValorAtivo *) malloc(*maxValoresAtivos * sizeof(ValorAtivo));
    if (*valoresAtivos == NULL) {
        printf("Erro ao alocar memoria para valores ativos\n");
        return false;
    } else {
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

bool alocaAtivosFinanceiros(AtivoFinanceiro **ativosFinanceiros, int *maxAtivosFinanceiros) {

    *ativosFinanceiros = (AtivoFinanceiro *) malloc(*maxAtivosFinanceiros * sizeof(AtivoFinanceiro));
    if (*ativosFinanceiros == NULL) {
        printf("Erro ao alocar memoria para Ativos Financeiros\n");
        return false;
    } else {
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

void importarValoresAtivos(ValorAtivo **valoresAtivos, int *numValoresAtivos, int *maxValoresAtivos) {

    int aux;
    FILE *file = fopen("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/valoresAtivos.bin", "r");

    if (file == NULL) {
        printf("Erro na leitura do ficheiro valoresAtivos!\n");
    } else {
        fread(numValoresAtivos, sizeof(int), 1, file);
        maxValoresAtivos = numValoresAtivos;

        if (alocaValoresAtivos(valoresAtivos, maxValoresAtivos)) {
            aux = (int) fread(*valoresAtivos, sizeof(ValorAtivo), *numValoresAtivos, file);
            if (aux != *numValoresAtivos) {
                *numValoresAtivos = 0;
                *maxValoresAtivos = 0;
                free(valoresAtivos);
                valoresAtivos = NULL;
            } else {
                printf("Ficheiro clientes lido com sucesso!\n");
            }
        }
    }
    fclose(file);
}

void exportarValoresAtivos(ValorAtivo *valoresAtivos, int numValoresAtivos) {
    FILE *file = fopen("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/valoresAtivos.bin", "w");
    if (file == NULL)
        printf("Erro ao abrir ficheiro valoresAtivos!\n");
    else {
        fwrite(&numValoresAtivos, sizeof(int), 1, file);
        fwrite(valoresAtivos, sizeof(ValorAtivo), numValoresAtivos, file);
        fclose(file);
        printf("Carteiras gravadas com sucesso!\n");
    }
}

void importarCarteiras(Carteira *carteiras, int *numCarteiras) {

    FILE *file = fopen("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/carteiras.bin", "r");

    if (file == NULL) {
        printf("Erro na leitura do ficheiro carteiras!\n");
    } else {
        fread(numCarteiras, sizeof(int), 1, file);

        for (int i = 0; i < *numCarteiras; ++i) {
            fread(&(carteiras[i]), sizeof(Carteira), 1, file);
            fread(&(carteiras[i].numAtivosCarteira), sizeof(int), 1, file);
            fread(&(carteiras[i].ativosCarteira), sizeof(AtivoCarteira), carteiras[i].numAtivosCarteira, file);
        }
        printf("Ficheiro carteiras lido com sucesso!\n");
    }
    fclose(file);
}

void exportarCarteiras(Carteira *carteiras, int numCarteiras) {
    FILE *file = fopen("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/carteiras.bin", "w");
    if (file == NULL)
        printf("Erro ao abrir ficheiro carteiras!\n");
    else {
        fwrite(&numCarteiras, sizeof(int), 1, file);
        for (int i = 0; i < numCarteiras; ++i) {
            fwrite(&carteiras[i], sizeof(Carteira), 1, file);
            fwrite(&carteiras[i].numAtivosCarteira, sizeof(int), 1, file);
            fwrite(&carteiras[i].ativosCarteira, sizeof(AtivoCarteira), carteiras->numAtivosCarteira, file);
        }
        fclose(file);
        printf("Valores de ativos gravados com sucesso!\n");
    }
}







