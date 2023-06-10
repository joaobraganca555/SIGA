#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Lib.h"
#include "ficheiros.h"
#include "compraVenda.h"
#include "estatisticas.h"
#include "relatorios.h"


void menuVenderComprar(Carteira *carteira, int indexAtivoNaCarteira) {
    int opcaoVenderComprar;
    do {
        printf("\n1. Vender\n");
        printf("2. Comprar\n");
        printf("0. Cancelar\n");
        printf("Opcao: ");
        scanf("%d", &opcaoVenderComprar);

        switch (opcaoVenderComprar) {
            case 1:
                venderAtivo(carteira, indexAtivoNaCarteira);
                break;
            case 2:
                comprarAtivo(carteira, indexAtivoNaCarteira);
                break;
            case 0:
                break;
            default:
                printf("Opção invalida\n");
                break;
        }
    } while (opcaoVenderComprar != 0);
}

void menuAtivosNaCarteira(Carteira *carteira, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {

    int opcaoAtivo;

    if (carteira->numAtivosCarteira == 0) {
        printf("Não possui ativos nesta carteira\n");
        return;
    }

    do {
        printf("\nOpcao. nomeAtivo quantidadeEmCarteira\n");
        for (int i = 0; i < carteira->numAtivosCarteira; ++i) {
            AtivoFinanceiro *ativoFinanceiro = getAtivoFinanceiroPorId(carteira->ativosCarteira[i].id, ativosFinanceiros, numAtivosFinanceiros);
            printf("%d. %s, %d\n", i + 1, ativoFinanceiro->nome, carteira->ativosCarteira[i].quantidade);
        }
        printf("0. Cancelar\n");

        printf("Selecione o ativo: ");
        scanf("%d", &opcaoAtivo);

        if (opcaoAtivo == 0)
            break;

        int indexAtivoNaCarteira = opcaoAtivo - 1;

        menuVenderComprar(carteira, indexAtivoNaCarteira);
    } while (opcaoAtivo != 0);
}

void menuAtivos(Carteira *carteira, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros, ValorAtivo *valoresAtivo,
                int numValoresAtivo) {

    int opcaoAtivo;

    if (numAtivosFinanceiros == 0) {
        printf("Não existem ativos disponiveis para compra");
        return;
    }

    if (carteira->numAtivosCarteira == MAX_ATIVOS_CARTEIRA) {
        printf("Limite maximo de %d ativos por carteira atingido", MAX_ATIVOS_CARTEIRA);
        return;
    }

    do {
        printf("\nAtivos Financeiros disponiveis:\n");
        for (int i = 0; i < numAtivosFinanceiros; ++i) {
            float valor = getPrecoAtivoFinanceiro(ativosFinanceiros[i].id, valoresAtivo, numValoresAtivo);
            printf("%d. %s %.2f€\n", i + 1, ativosFinanceiros[i].nome, valor);
        }
        printf("0. Cancelar\n");

        printf("Selecione o ativo: ");
        scanf("%d", &opcaoAtivo);

        if (opcaoAtivo == 0)
            break;

        int indexAtivoNaCarteira = opcaoAtivo - 1;
        comprarAtivo(carteira, indexAtivoNaCarteira);
    } while (opcaoAtivo != 0);
}

void menuAcoesCarteira(Carteira *carteira, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros,
                       ValorAtivo *valoresAtivos, int numValoresAtivos) {
    int opcao;
    do {
        printf("\nO que pretende faz com os ativos  desta carteira?\n");
        printf("1. Consultar Ativos\n");
        printf("2. Comprar Novos\n");
        printf("0. Cancelar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuAtivosNaCarteira(carteira, ativosFinanceiros, numAtivosFinanceiros);
                break;
            case 2:
                menuAtivos(carteira, ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numValoresAtivos);
                break;
            case 0:
                break;
            default:
                printf("Opção invalida");
                break;
        }
    } while (opcao != 0);
}

void menuCarteiras(Carteira *carteiras, int numCarteiras, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros,
                   ValorAtivo *valoresAtivos, int numValoresAtivos) {

    int opcao;

    if (numCarteiras == 0) {
        printf("Não possui carteiras\n");
        return;
    }

    do {
        printf("\nOpcao -> idCarteira - nomeCarteira\n");
        for (int i = 0; i < numCarteiras; ++i)
            printf("%d. %d - %s\n", i + 1, carteiras[i].id, carteiras[i].descricao);
        printf("0. Cancelar\n");

        printf("Selecione a carteira: ");
        scanf("%d", &opcao);

        if (opcao <= 0 || opcao > numCarteiras)
            break;

        int indiceCarteira = opcao - 1;
        menuAcoesCarteira(&carteiras[indiceCarteira], ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numValoresAtivos);
    } while (opcao != 0);
}

void menuEstatisticas(AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros, ValorAtivo *valoresAtivos, int numValoresAtivo) {

    int opcao;

    do {
        printf("\n1. Top 5 Ativos Financeiros com maior valor\n");
        printf("2. Média do valor de Ativo Financeiro por tipo\n");
        printf("0. Cancelar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                top5AtivosFinanceiros(ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numValoresAtivo);
                break;
            case 2:
                mediaValorAtivoFinanceiroPorTipo(ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numValoresAtivo);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);
}

void menuRelatorios(Carteira *carteiras, int numCarteiras, ValorAtivo *valoresAtivos, int numValoresAtivos) {

    int opcaoCarteira;
    if (numCarteiras == 0) {
        printf("Não possuir carteiras\n");
        return;
    }

    do {
        printf("\nOpcao -> idCarteira - nomeCarteira\n");
        for (int i = 0; i < numCarteiras; ++i)
            printf("%d. %d - %s\n", i + 1, carteiras[i].id, carteiras[i].descricao);
        printf("0. Cancelar\n");

        printf("Selecione a carteira: ");
        scanf("%d", &opcaoCarteira);

        imprimirCarteira(carteiras, valoresAtivos, numValoresAtivos);

    } while (opcaoCarteira != 0);
}

void menuSecondario(int numCarteiras, int numAtivosFinanceiros, Carteira *carteiras, AtivoFinanceiro *ativosFinanceiros,
                    ValorAtivo *valoresAtivos) {

    int opcao;

    do {
        printf("\nMenu Secundário:\n");
        printf("1. Listar Carteiras\n");
        printf("2. Estatisticas\n");
        printf("3. Relatorios\n");
        printf("0. Voltar\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuCarteiras(carteiras, numCarteiras, ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numAtivosFinanceiros);
                break;
            case 2:
                menuEstatisticas(ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numAtivosFinanceiros);
                break;
            case 3:
                menuRelatorios(carteiras, numCarteiras, valoresAtivos, numAtivosFinanceiros);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);
}

void menuPrincipal(Carteira *carteiras, int *numCarteiras, AtivoFinanceiro **ativosFinanceiros, int *numAtivosFinanceiros, int *maxAtivosFinanceiros,
                   ValorAtivo **valoresAtivos, int *numValoresAtivos, int *maxValoresAtivos) {

    int opcao;
    do {
        printf("Menu Principal:\n");
        printf("1. Ler Carteiras\n");
        printf("2. Ler Ativos Financeiro\n");
        printf("3. Menu Secundário\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                lerDadosCarteiras("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/carteiras.txt", carteiras, numCarteiras);
//                imprimirCarteiras(carteiras, numCarteiras);
                break;
            case 2:
                lerAtivosFinanceiros("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/ativos.txt", ativosFinanceiros, maxAtivosFinanceiros,
                                     numAtivosFinanceiros);
//                imprimirAtivosFinanceiros(ativosFinanceiros, numAtivosFinanceiros);
                atualizarValoresAtivos("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/novosValoresAtivos.txt", valoresAtivos,
                                       numValoresAtivos, maxValoresAtivos);
//                imprimirValoresAtivos(valoresAtivos, numValoresAtivos);
                break;
            case 3:
                menuSecondario((*numCarteiras), (*numAtivosFinanceiros), carteiras, (*ativosFinanceiros), (*valoresAtivos));
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcao != 0);
}

int main() {
    int numCarteiras = 0;
    int numAtivosFinanceiros = 0, maxAtivosFinanceiros = 0;
    int numValoresAtivos = 0, maxValoresAtivos = 0;

    Carteira carteiras[MAX_CARTEIRAS];
    AtivoFinanceiro *ativosFinanceiros;
    ValorAtivo *valoresAtivos;

    alocaAtivosFinanceiros(&ativosFinanceiros, &maxAtivosFinanceiros, 10);
    alocaValoresAtivos(&valoresAtivos, &maxValoresAtivos, 10);

    menuPrincipal(carteiras, &numCarteiras, &ativosFinanceiros, &numAtivosFinanceiros, &maxAtivosFinanceiros,
                  &valoresAtivos, &numValoresAtivos, &maxValoresAtivos);

    return 0;
}

