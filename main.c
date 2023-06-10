#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lib.h"


void cleanInputBuffer() {
    char ch;

    while ((ch = getchar()) != '\n' && ch != EOF);
}

int getIndexAtivoCarteiraById(int idAtivoFinanceiro, Carteira *carteira) {
    for (int i = 0; i < carteira->numAtivosCarteira; i++)
        if (carteira->ativosCarteira[i].id == idAtivoFinanceiro)
            return i;
    return -1;
}

int getIndexAtivoFinanceiroById(int idAtivo, AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {
    for (int i = 0; i < numAtivosFinanceiros; i++)
        if (ativosFinanceiros[i].id == idAtivo)
            return i;
    return -1;
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

void imprimirAtivosCarteira(Carteira *tempCarteiras) {
    AtivoCarteira *tempAtivosCarteira = tempCarteiras->ativosCarteira;
    printf("Ativos da carteira:\n");
    for (int j = 0; j < tempCarteiras->numAtivosCarteira; j++, *tempAtivosCarteira++) {
        printf("ID de AtivoFinanceiro: %d\n", tempAtivosCarteira->id);
        printf("Quantidade de AtivoFinanceiro: %d\n", tempAtivosCarteira->quantidade);
    }
    printf("\n");
}

void imprimirCarteiras(Carteira *carteiras, int numCarteiras) {
    Carteira *tempCarteiras = carteiras;

    for (int i = 0; i < numCarteiras; i++, tempCarteiras++) {
        printf("Carteira ID: %d\n", tempCarteiras->id);
        printf("Descrição: %s\n", tempCarteiras->descricao);

        imprimirAtivosCarteira(tempCarteiras);
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

float getPrecoAtivoFinanceiro(int idAtivoFinanceiro, ValorAtivo *valoresAtivos, int numValoresAtivos) {
    for (int i = 0; i < numValoresAtivos; ++i) {
        if (valoresAtivos[i].ativoFinanceiroId == idAtivoFinanceiro) {
            return valoresAtivos[i].valor;
        }
    }
    return -1;
}

void venderAtivo(Carteira *carteira, int idAtivoFinanceiro) {

    int quantidade;

    int indexAtivoCarteira = getIndexAtivoCarteiraById(idAtivoFinanceiro, carteira);

    if (indexAtivoCarteira < 0) {
        printf("Não possui ativos de %d", idAtivoFinanceiro);
        return;
    }

    AtivoCarteira *ativoCarteira = &carteira->ativosCarteira[indexAtivoCarteira];

    printf("Quantidade: ");
    scanf("%d", &quantidade);

    //Caso insira uma quantidade superior a que possui
    if (quantidade > ativoCarteira->quantidade) {
        printf("Apenas tem %d disponiveis", ativoCarteira->quantidade);
        return;
    }

    ativoCarteira->quantidade -= quantidade;

    printf("Vendeu %d do ativo %d ficou com %d unidades", quantidade, ativoCarteira->id, ativoCarteira->quantidade);
}

void comprarAtivo(Carteira *carteira, int idAtivoFinanceiro) {

    int quantidade;

    if (carteira->numAtivosCarteira == MAX_ATIVOS_CARTEIRA) {
        printf("Limite maximo de %d ativos por carteira atingido", MAX_ATIVOS_CARTEIRA);
        return;
    }

    int indexAtivoCarteira = getIndexAtivoCarteiraById(idAtivoFinanceiro, carteira);
    AtivoCarteira *ativoCarteira = &carteira->ativosCarteira[indexAtivoCarteira];

    printf("Quantidade: ");
    scanf("%d", &quantidade);

    //Verificar se ja tem este ativo comprado, se tiver so acrescenta
    if (ativoCarteira < 0) {
        carteira->ativosCarteira[carteira->numAtivosCarteira].quantidade = quantidade;
        carteira->ativosCarteira[carteira->numAtivosCarteira].id = idAtivoFinanceiro;
    } else {
        ativoCarteira->quantidade += quantidade;
    }

    carteira->numAtivosCarteira++;

    printf("Comprou %d unidades, agora possui %d to ativo %d", quantidade, ativoCarteira->quantidade, idAtivoFinanceiro);
}

void listarAtivosCarteira(Carteira *carteira,
                          AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros) {

    int opcaoAtivo, opcaoVenderComprar;

    if (carteira->numAtivosCarteira == 0) {
        printf("Não possui ativos nesta carteira\n");
        return;
    }

    do {
        printf("\n");
        for (int i = 0; i < carteira->numAtivosCarteira; ++i) {
            int indexAtivoFinanceiro = getIndexAtivoFinanceiroById(carteira->ativosCarteira[i].id, ativosFinanceiros, numAtivosFinanceiros);
            int i1 = i + 1;
//            printf("%d. %s, %d\n", i1, ativosFinanceiros[indexAtivoFinanceiro].nome, carteira->ativosCarteira[i].quantidade);
            printf("%d. %d, %d\n", i + 1, ativosFinanceiros[indexAtivoFinanceiro].id, carteira->ativosCarteira[i].quantidade);
        }
        printf("0. Cancelar\n");

        printf("Selecione o ativo: ");
        scanf("%d", &opcaoAtivo);

        if (opcaoAtivo == 0)
            break;

        do {
            printf("\n1. Vender\n");
            printf("2. Comprar\n");
            printf("0. Cancelar\n");
            printf("Opcao: ");
            scanf("%d", &opcaoVenderComprar);

            int idAtivoFinanceiro = carteira->ativosCarteira[opcaoAtivo - 1].id;
            if (opcaoVenderComprar == 1)
                venderAtivo(carteira, idAtivoFinanceiro);

            if (opcaoVenderComprar == 2)
                comprarAtivo(carteira, idAtivoFinanceiro);

        } while (opcaoVenderComprar != 0);
    } while (opcaoAtivo != 0);


}

void comprarAtivosListaTodos(Carteira *carteira,
                             AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros,
                             ValorAtivo *valoresAtivo, int numValoresAtivo) {

    int opcaoAtivo, quantidade;
    AtivoFinanceiro ativoFinanceiroAComprar;

    if (numAtivosFinanceiros == 0) {
        printf("Não existem ativos disponiveis para compra");
    }

    if (carteira->numAtivosCarteira == MAX_ATIVOS_CARTEIRA) {
        printf("Limite maximo de %d ativos por carteira atingido", MAX_ATIVOS_CARTEIRA);
        return;
    }

    do {
        printf("\nAtivos Financeiros disponiveis:\n");
        for (int i = 0; i < numAtivosFinanceiros; ++i) {
            float valor = getPrecoAtivoFinanceiro(ativosFinanceiros[i].id, valoresAtivo, numValoresAtivo);
            printf("%d. %.2f€\n", i + 1, valor);
//            printf("%d. %s %.2f €\n", i + 1, ativosFinanceiros[i].nome, valor);
        }

        printf("0. Cancelar\n");

        printf("Selecione o ativo: ");
        scanf("%d", &opcaoAtivo);

        comprarAtivo(carteira, ativosFinanceiros[opcaoAtivo - 1].id);
    } while (opcaoAtivo != 0);
}

void listarCarteiras(Carteira *carteiras, int numCarteiras,
                     AtivoFinanceiro *ativosFinanceiros, int numAtivosFinanceiros,
                     ValorAtivo *valoresAtivos, int numValoresAtivos) {

    int opcaoCarteira;
    int opcaoListar;

    if (numCarteiras == 0) {
        printf("Não possuir carteiras\n");
        return;
    }

    do {
        printf("\nOpcao -> idCarteira - nomeCarteira\n");
        for (int i = 0; i < numCarteiras; ++i)
            printf("%d. %d - %s", i + 1, carteiras[i].id, carteiras[i].descricao);
        printf("0. Cancelar\n");

        printf("Selecione a carteira: ");
        scanf("%d", &opcaoCarteira);

        if (opcaoCarteira <= 0 || opcaoCarteira > numCarteiras)
            break;

        do {
            printf("\nO que pretende faz com os ativos  desta carteira?\n");
            printf("1. Consultar Ativos\n");
            printf("2. Comprar Novos\n");
            printf("0. Cancelar\n");
            printf("Opcao: ");
            scanf("%d", &opcaoListar);

//            cleanInputBuffer();

            //Listar ativos que possui
            if (opcaoListar == 1)
                listarAtivosCarteira(&carteiras[opcaoCarteira - 1], ativosFinanceiros, numAtivosFinanceiros);

            //Comprar que não possui
            if (opcaoListar == 2)
                comprarAtivosListaTodos(&carteiras[opcaoCarteira - 1], ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numValoresAtivos);

        } while (opcaoListar != 0);
    } while (opcaoCarteira != 0);
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
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                printf("Você selecionou a opção 1 do Menu Principal.\n");
                lerDadosCarteiras("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/carteiras.txt", carteiras, &numCarteiras);
//                imprimirCarteiras(carteiras, numCarteiras);
                break;
            case 2:
                printf("Você selecionou a opção 2 do Menu Principal.\n");
                lerAtivosFinanceiros("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/ativos.txt", &ativosFinanceiros, &maxAtivosFinanceiros,
                                     &numAtivosFinanceiros);
//                imprimirAtivosFinanceiros(ativosFinanceiros, numAtivosFinanceiros);
                atualizarValoresAtivos("/Users/micaelmbp/Documents/Projects/C/SIGA_Mauricio/data/novosValoresAtivos.txt", &valoresAtivos,
                                       &numValoresAtivos, &maxValoresAtivos);
//                imprimirValoresAtivos(valoresAtivos, numValoresAtivos);
                break;
            case 3:
                atualizarValoresAtivos("data/valores.txt", valoresAtivos,
                                       &numAtivosFinanceiros);
                break;
            case 4:
                do {
                    printf("\nMenu Secundário:\n");
                    printf("1. Listar Carteiras\n");
                    printf("2. Opção B\n");
                    printf("0. Voltar\n");
                    printf("Opção: ");
                    scanf("%d", &opcaoSecundaria);

                    switch (opcaoSecundaria) {
                        case 1:
                            listarCarteiras(carteiras, numCarteiras, ativosFinanceiros, numAtivosFinanceiros, valoresAtivos, numAtivosFinanceiros);
                            break;
                        case 2:
                            printf("Você selecionou a Opção B do Menu Secundário.\n");
                            break;
                        case 3:
                            printf("Retornando ao Menu Principal...\n");
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opção inválida. Tente novamente.\n");
                            break;
                    }

                    printf("\n");
                } while (opcaoSecundaria != 0);

                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (opcaoPrincipal != 0);

    return 0;
}

