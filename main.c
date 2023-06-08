#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lib.h"


int pesquisaAtivoCarteira(AtivoCarteira *ativosCarteira, int numAtivosCarteira, int idAtivo) {
    int i = 0;
    while (i < numAtivosCarteira && ativosCarteira[i].id != idAtivo)
        ++i;

    if (i < numAtivosCarteira)
        return i;
    else {
        return -1;
    }
}

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

bool realocaAtivosFinanceiros(AtivoFinanceiro **ativosFinanceiro, int *maxAtivosFinanceiros) {

    AtivoFinanceiro *temp;
    temp = (AtivoFinanceiro *) realloc(*ativosFinanceiro, (*maxAtivosFinanceiros * 2) * sizeof(AtivoFinanceiro));

    if (temp == NULL) {
        printf("Erro ao realocar memoria para ativos financeiros\n");
        return false;
    } else {
        *ativosFinanceiro = temp;
        *maxAtivosFinanceiros *= 2;
        return true;
    }
}


void lerDadosCarteiras(const char *nomeArquivo, Carteira *carteiras, int *numCarteiras) {
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
            *tempCarteiras++;
            continue;
        }

        // Carteira ID e Descrição
        if (linha[0] == 'C') {
            sscanf(linha, "CarteiraId %d", &tempCarteiras->id);
            fgets(tempCarteiras->descricao, sizeof(tempCarteiras->descricao),
                  file);

            tempCarteiras->numAtivosCarteira = 0;
            (*numCarteiras)++;
        }

        // Ler todas os AtivoCarteira desta carteira
        AtivoCarteira *tempAtivosCarteira = tempCarteiras->ativosCarteira;
        while (!feof(file)) {
            fgets(linha, sizeof(linha), file);

            // se encontrar --- recua no ponteiro do ficheiro para a linha
            // anterior
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
            sscanf(linha, "Quantidade de AtivoFinanceiro %d",
                   &tempAtivosCarteira->quantidade);

            (tempCarteiras->numAtivosCarteira)++;
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
        for (int j = 0; j < tempCarteiras->numAtivosCarteira;
             j++, *tempAtivosCarteira++) {
            printf("ID de AtivoFinanceiro: %d\n", tempAtivosCarteira->id);
            printf("Quantidade de AtivoFinanceiro: %d\n", tempAtivosCarteira->quantidade);
        }
        printf("\n");
    }
}

void lerAtivosFinanceiros(const char *nomeArquivo,
                          AtivoFinanceiro **ativosFinanceiros,
                          int *tamanhoArray,
                          int *numAtivosFinanceiros) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%d,%c,%49[^\n]", &(*ativosFinanceiros)[i].id,
                  &(*ativosFinanceiros)[i].tipo, (*ativosFinanceiros)[i].nome) == 3) {
        i++;
        (*numAtivosFinanceiros)++;

        //Se o tamanho maximo foi atingido é realocado mais memoria
        if (i >= *tamanhoArray) {
            printf("----------------------------------------\n");
            printf("Tamanho máximo atingido, a realocar memória...\n");
            printf("----------------------------------------\n");

            if (!realocaAtivosFinanceiros(ativosFinanceiros, tamanhoArray)) {
                break;
            }
        }
    }
    fclose(file);
}

void imprimirAtivosFinanceiros(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {
    printf("Ativos Financeiros:\n");
    for (int j = 0; j < numAtivosFinanceiros; j++) {
        printf("ID: %d, Tipo: %c, Nome: %s\n", ativosFinanceiros[j].id, ativosFinanceiros[j].tipo, ativosFinanceiros[j].nome);
    }
}


void atualizarValoresAtivos(const char *nomeFicheiro, ValorAtivo **valoresAtivos, int *numValoresAtivos, int *maxValoresAtivos) {

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

        fscanf(file, "%d-%d-%d %d %f", &(*valoresAtivos)[i].data.ano, &(*valoresAtivos)[i].data.mes, &(*valoresAtivos)[i].data.dia,
               &(*valoresAtivos)[i].ativoFinanceiroId, &(*valoresAtivos)[i].valor);

        (*numValoresAtivos)++;
        i++;
    }
    fclose(file);
}

void imprimirValoresAtivos(ValorAtivo *valoresAtivos, int numValoresAtivos) {
    printf("Valores Ativos:\n");
    for (int j = 0; j < numValoresAtivos; j++) {
        printf("data: %d,%d,%d, id: %d, valor: %f\n", valoresAtivos[j].data.ano, valoresAtivos[j].data.mes, valoresAtivos[j].data.dia,
               valoresAtivos[j].ativoFinanceiroId, valoresAtivos[j].valor);
    }
}


int main() {
    int opcaoPrincipal, opcaoSecundaria;
    int numCarteiras = 0;
    int numAtivosFinanceiros = 0, maxAtivosFinanceiros = 10;
    int numValoresAtivos = 0, maxValoresAtivos = 10;

    Carteira carteiras[MAX_CARTEIRAS];
    AtivoFinanceiro *ativosFinanceiros;
    ValorAtivo *valoresAtivos;

    alocaAtivosFinanceiros(&ativosFinanceiros, &maxAtivosFinanceiros, maxAtivosFinanceiros);
    alocaValoresAtivos(&valoresAtivos, &maxValoresAtivos, maxValoresAtivos);

    do {
        printf("Menu Principal:\n");
        printf("1. Ler Carteiras\n");
        printf("2. Ler Ativos Financeiro\n");
        printf("3. Menu Secundário\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                printf("Você selecionou a opção 1 do Menu Principal.\n");
                lerDadosCarteiras("data/carteiras.txt", carteiras, &numCarteiras);
                imprimirCarteiras(carteiras, numCarteiras);
                break;
            case 2:
                printf("Você selecionou a opção 2 do Menu Principal.\n");
                lerAtivosFinanceiros("data/ativos.txt", &ativosFinanceiros, &maxAtivosFinanceiros, &numAtivosFinanceiros);
                imprimirAtivosFinanceiros(ativosFinanceiros, numAtivosFinanceiros);
                atualizarValoresAtivos("data/novosValoresAtivos.txt", &valoresAtivos, &numValoresAtivos, &maxValoresAtivos);
                imprimirValoresAtivos(valoresAtivos, numValoresAtivos);
                break;
            case 3:
                do {
                    printf("\nMenu Secundário:\n");
                    printf("1. Opção A\n");
                    printf("2. Opção B\n");
                    printf("3. Voltar\n");
                    printf("Opção: ");
                    scanf("%d", &opcaoSecundaria);

                    switch (opcaoSecundaria) {
                        case 1:
                            printf("Você selecionou a Opção A do Menu Secundário.\n");
                            break;
                        case 2:
                            printf("Você selecionou a Opção B do Menu Secundário.\n");
                            break;
                        case 3:
                            printf("Retornando ao Menu Principal...\n");
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            break;
                    }

                    printf("\n");
                } while (opcaoSecundaria != 3);

                break;
            case 4:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcaoPrincipal != 4);

    return 0;
}

