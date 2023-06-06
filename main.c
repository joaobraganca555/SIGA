#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lib.h"

void lerDadosCarteiras(const char *nomeArquivo, Carteira *carteiras,
                       AtivoCarteira *ativosCarteira, int *numCarteiras,
                       int *numAtivosCarteiras) {
    FILE *file;
    AtivoCarteira *tempAtivosCarteira = ativosCarteira;
    Carteira *tempCarteiras = carteiras;

    file = fopen(nomeArquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o file");
        return;
    }

    while (!feof(file)) {
        char linha[100];
        fgets(linha, sizeof(linha), file);

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
        int *tempListaIdsCarteira = tempCarteiras->ativo_carteira_ids;
        while (!feof(file)) {
            fgets(linha, sizeof(linha), file);

            // se encontrar --- recua no ponteiro do ficheiro para a linha
            // anterior
            if (linha[0] == '-') {
                fseek(file, (long long)-strlen(linha), SEEK_CUR);
                break;
            }

            sscanf(linha, "Id de AtivoFinanceiro %d", &tempAtivosCarteira->id);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "Quantidade de AtivoFinanceiro %d",
                   &tempAtivosCarteira->quantidade);

            (*numAtivosCarteiras)++;
            (tempCarteiras->num_ativo_carteira)++;

            *tempListaIdsCarteira = tempAtivosCarteira->id;

            *tempAtivosCarteira++;
            *tempListaIdsCarteira++;
        }
    }
    fclose(file);
}

void imprimirCarteiras(Carteira *carteiras, int numCarteiras) {
    Carteira *tempCarteiras = carteiras;
    for (int i = 0; i < numCarteiras; i++, tempCarteiras++) {
        printf("Carteira ID: %d\n", tempCarteiras->id);
        printf("Descrição: %s\n", tempCarteiras->descricao);

        printf("Ativos da carteira:\n");
        for (int j = 0; j < tempCarteiras->num_ativo_carteira; j++) {
            // Esta a aceder á zero para não dar erro, falta acabar leitura
            printf("ID de AtivoFinanceiro: %d\n",
                   carteiras->ativo_carteira_ids[0]);

            // Como estamos a usar id's não sabemos a quandidade diretamente,
            // temos de procurar na struct AtivoCarteira atravez do id para ir
            // buscar a quantidade
            //            printf("Quantidade de AtivoFinanceiro: %d\n",
            //            carteiras[i].ativo_carteira_ids[j + 1]);
        }
        printf("\n");
    }
}

void lerAtivosFinanceiros(const char *nomeArquivo,
                          AtivoFinanceiro **ativosFinanceiros,
                          int *tamanhoArray) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    int i = 0;
    while (fscanf(file, "%d,%c,%49[^\n]", &((*ativosFinanceiros)[i].id),
                  &((*ativosFinanceiros)[i].tipo),
                  (*ativosFinanceiros)[i].nome) == 3) {
        i++;
        if (i >= *tamanhoArray) {
            *tamanhoArray += 10;  // Aumenta o tamanho do array em 10
            *ativosFinanceiros = realloc(
                *ativosFinanceiros, (*tamanhoArray) * sizeof(AtivoFinanceiro));
            if (*ativosFinanceiros == NULL) {
                printf("Erro ao realocar memória.\n");
                break;
            }
        }
    }

    fclose(file);

    // Imprime os ativos financeiros lidos do arquivo
    printf("Ativos Financeiros:\n");
    for (int j = 0; j < i; j++) {
        printf("ID: %d, Tipo: %c, Nome: %s\n", (*ativosFinanceiros)[j].id,
               (*ativosFinanceiros)[j].tipo, (*ativosFinanceiros)[j].nome);
    }
}

void atualizarValoresAtivos() {}

int main() {
    int opcao_principal, opcao_secundaria;
    int numCarteiras, numAtivosCarteira = 0;
    int tamanhoAtivosFinanceiros = 10;
    Carteira carteiras[MAX_CARTEIRAS];
    AtivoCarteira ativosCarteiras[MAX_ATIVOS_CARTEIRA];
    AtivoFinanceiro *ativosFinanceiros = malloc(10 * sizeof(AtivoFinanceiro));

    do {
        printf("Menu Principal:\n");
        printf("1. Ler Carteiras\n");
        printf("2. Ler Ativos Financeiro\n");
        printf("3. Menu Secundário\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1:
                printf("Você selecionou a opção 1 do Menu Principal.\n");
                lerDadosCarteiras(
                    "data/"
                    "carteiras.txt",
                    carteiras, ativosCarteiras, &numCarteiras,
                    &numAtivosCarteira);
                imprimirCarteiras(carteiras, numCarteiras);
                break;
            case 2:
                printf("Você selecionou a opção 2 do Menu Principal.\n");
                lerAtivosFinanceiros("data/ativos.txt", &ativosFinanceiros,
                                     &tamanhoAtivosFinanceiros);
                break;
            case 3:
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
            case 4:
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
