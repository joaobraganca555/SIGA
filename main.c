#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lib.h"

int pesquisa_ativo_carteira(AtivoCarteira *ativosCarteira,
                            int numAtivosCarteira, int idAtivo) {
    int i = 0;
    while (i < numAtivosCarteira && ativosCarteira[i].id != idAtivo) ++i;

    if (i < numAtivosCarteira)
        return i;
    else {
        return -1;
    }
}

void lerDadosCarteiras(const char *nomeArquivo, Carteira *carteiras,
                       AtivoCarteira *ativosCarteira, int *numCarteiras,
                       int *numAtivosCarteiras) {
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
            printf("Limite de &d Carteiras atingido");
            break;
        }

        // Nova carteira, reinicializar variáveis
        if (linha[0] == '-') {
            *tempCarteiras++;
            continue;
        }

        // Carteira ID e Descrição
        if (linha[0] == 'C') {
            sscanf(linha, "CarteiraId %d", &tempCarteiras->id);
            fgets(tempCarteiras->descricao, sizeof(tempCarteiras->descricao),
                  file);

            tempCarteiras->num_ativo_carteira = 0;
            (*numCarteiras)++;
        }

        // Ler todas os AtivoCarteira desta carteira
        AtivoCarteira *tempAtivosCarteira = tempCarteiras->ativosCarteira;
        while (!feof(file)) {
            fgets(linha, sizeof(linha), file);

            // se encontrar --- recua no ponteiro do ficheiro para a linha
            // anterior
            if (linha[0] == '-') {
                fseek(file, (long long)-strlen(linha), SEEK_CUR);
                break;
            }

            if (tempCarteiras->num_ativo_carteira == MAX_ATIVOS_CARTEIRA) {
                printf(
                    "Limite de %d AtivosCarteira atingido para a carteira %d",
                    MAX_ATIVOS_CARTEIRA, tempCarteiras->id);
                break;
            }

            sscanf(linha, "Id de AtivoFinanceiro %d", &tempAtivosCarteira->id);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "Quantidade de AtivoFinanceiro %d",
                   &tempAtivosCarteira->quantidade);

            (tempCarteiras->num_ativo_carteira)++;
            *tempAtivosCarteira++;
        }
    }
    fclose(file);
}

void imprimirCarteiras(Carteira *carteiras, int numCarteiras) {
    Carteira *tempCarteiras = carteiras;

    for (int i = 0; i < numCarteiras; i++, tempCarteiras++) {
        printf("Carteira ID: %d\n", tempCarteiras->id);
        printf("Descrição: %s\n", tempCarteiras->descricao);

        AtivoCarteira *tempAtivosCarteira = tempCarteiras->ativosCarteira;
        printf("Ativos da carteira:\n");
        for (int j = 0; j < tempCarteiras->num_ativo_carteira;
             j++, *tempAtivosCarteira++) {
            printf("ID de AtivoFinanceiro: %d\n", tempAtivosCarteira->id);
            printf("Quantidade de AtivoFinanceiro: %d\n",
                   tempAtivosCarteira->quantidade);
        }
        printf("\n");
    }
}

void lerAtivosFinanceiros(const char *nomeArquivo,
                          AtivoFinanceiro *ativosFinanceiros,
                          int *tamanhoArray) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%d,%c,%49[^\n]", &ativosFinanceiros[i].id,
                  &ativosFinanceiros[i].tipo, ativosFinanceiros[i].nome) == 3) {
        i++;
        if (i >= *tamanhoArray) {
            printf("Tamanho máximo do array de ativos financeiros atingido.\n");
            break;  // Interrompe a leitura se o array estiver cheio
        }
        // if (i >= *tamanhoArray) {
        //     *tamanhoArray += 10;  // Aumenta o tamanho do array em 10
        //     *ativosFinanceiros = realloc(
        //         *ativosFinanceiros, (*tamanhoArray) *
        //         sizeof(AtivoFinanceiro));
        //     printf('----------------------------------------');
        //     printf("Tamanho máximo atingido, a realocar memória...\n");
        //     printf('----------------------------------------');
        //     if (*ativosFinanceiros == NULL) {
        //         printf("Erro ao realocar memória.\n");
        //         break;
        //     }
        // }
    }

    fclose(file);

    // Imprime os ativos financeiros lidos do arquivo
    printf("Ativos Financeiros:\n");
    for (int j = 0; j < i; j++) {
        printf("ID: %d, Tipo: %c, Nome: %s\n", ativosFinanceiros[j].id,
               ativosFinanceiros[j].tipo, ativosFinanceiros[j].nome);
        //     printf("ID: %d, Tipo: %c, Nome: %s\n",
        //     (*ativosFinanceiros)[j].id,
        //    (*ativosFinanceiros)[j].tipo, (*ativosFinanceiros)[j].nome);
    }
}

void atualizarValoresAtivos(const char *nomeArquivo, ValorAtivo *valoresAtivos,
                            int *tamanhoArray) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int novoTamanhoArray = *tamanhoArray;
    while (fscanf(file, "%10s %d %lf\n", valoresAtivos[novoTamanhoArray].data,
                  &valoresAtivos[novoTamanhoArray].ativo_financeiro_id,
                  &valoresAtivos[novoTamanhoArray].valor) == 3) {
        novoTamanhoArray++;
    }

    fclose(file);

    // Verifica e atualiza os valores dos ativos com datas maiores do que as
    // existentes
    for (int j = *tamanhoArray; j < novoTamanhoArray; j++) {
        int k;
        int dataExistente = 0;
        for (k = 0; k < *tamanhoArray; k++) {
            if (strcmp(valoresAtivos[j].data, valoresAtivos[k].data) == 0 &&
                valoresAtivos[j].ativo_financeiro_id ==
                    valoresAtivos[k].ativo_financeiro_id) {
                dataExistente = 1;
                break;
            }
        }

        if (!dataExistente) {
            // Atualiza o valor do ativo
            int id = valoresAtivos[j].ativo_financeiro_id;
            double novoValor = valoresAtivos[j].valor;

            for (k = 0; k < *tamanhoArray; k++) {
                if (valoresAtivos[k].ativo_financeiro_id == id &&
                    strcmp(valoresAtivos[k].data, valoresAtivos[j].data) < 0) {
                    valoresAtivos[k].valor = novoValor;
                }
            }
        }
    }

    // Imprime os valores atualizados dos ativos
    printf("Valores Atualizados dos Ativos:\n");
    for (int i = 0; i < tamanhoArray; i++) {
        printf("Ativo: %d, Data: %s, Valor: %.2lf\n",
               valoresAtivos[i].ativo_financeiro_id, valoresAtivos[i].data,
               valoresAtivos[i].valor);
    }
}

int main() {
    int opcao_principal, opcao_secundaria;
    int numCarteiras, numAtivosCarteira = 0;
    int numAtivosFinanceiros = 10;
    Carteira carteiras[MAX_CARTEIRAS];
    AtivoCarteira ativosCarteiras[MAX_ATIVOS_CARTEIRA];
    AtivoFinanceiro ativosFinanceiros[numAtivosFinanceiros];
    ValorAtivo valoresAtivos[numAtivosFinanceiros];
    // AtivoFinanceiro *     = malloc(10 *
    // sizeof(AtivoFinanceiro));

    do {
        printf("Menu Principal:\n");
        printf("1. Ler Carteiras\n");
        printf("2. Ler Ativos Financeiro\n");
        printf("3. Atualizar Valores Ativos\n");
        printf("4. Menu Secundário\n");
        printf("5. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1:
                lerDadosCarteiras(
                    "data/"
                    "carteiras.txt",
                    carteiras, ativosCarteiras, &numCarteiras,
                    &numAtivosCarteira);
                imprimirCarteiras(carteiras, numCarteiras);
                break;
            case 2:
                lerAtivosFinanceiros("data/ativos.txt", ativosFinanceiros,
                                     &numAtivosFinanceiros);
                break;
            case 3:
                atualizarValoresAtivos("data/valores.txt", valoresAtivos,
                                       &numAtivosFinanceiros);
                break;
            case 4:
                do {
                    printf("\nMenu Secundário:\n");
                    printf("1. Opção A\n");
                    printf("2. Opção B\n");
                    printf("3. Voltar\n");
                    printf("Opção: ");
                    scanf("%d", &opcao_secundaria);

                    switch (opcao_secundaria) {
                        case 1:
                            printf(
                                "Você selecionou a Opção A do Menu "
                                "Secundário.\n");
                            break;
                        case 2:
                            printf(
                                "Você selecionou a Opção B do Menu "
                                "Secundário.\n");
                            break;
                        case 3:
                            printf("Retornando ao Menu Principal...\n");
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            break;
                    }

                    printf("\n");
                } while (opcao_secundaria != 3);

                break;
            case 5:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao_principal != 4);

    return 0;
}
