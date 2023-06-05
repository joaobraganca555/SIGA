#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Número máximo de carteiras
#define MAX_CARTEIRAS 100
// Número máximo de AtivosCarteira
#define MAX_ATIVOS 50

struct Data
{
    int dia;
    int mes;
    int ano;
};

typedef struct
{
    int id;
    char tipo[20];
    char nome[50];
} AtivoFinanceiro;

typedef struct
{
    int ativo_financeiro_id;
    struct Data data;
    double valor;
} ValorAtivo;

typedef struct
{
    int id;
    char descricao[100];
    int *ativo_carteira_ids;
    int num_ativo_carteira;
} Carteira;

typedef struct
{
    int id;
    int ativo_financeiro_id;
    int quantidade;
} AtivoCarteira;


void lerDadosCarteiras(const char *nomeArquivo, Carteira *carteiras, int numCarteiras)
{
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int idCarteiraAtual = 0;
    int numAtivosCarteiraAtual = 0;

    while (!feof(arquivo))
    {
        char linha[100];
        fgets(linha, sizeof(linha), arquivo);

        if (linha[0] == '-')
        {
            // Nova carteira, reinicializar variáveis
            idCarteiraAtual++;
            numAtivosCarteiraAtual = 0;
            continue;
        }

        // if (idCarteiraAtual < 0 || idCarteiraAtual >= numCarteiras)
        // {
        //     printf("Erro: número de carteiras inválido.\n");
        //     break;
        // }

        if (linha[0] == 'C')
        {
            // Carteira ID e Descrição
            sscanf(linha, "CarteiraId %d", &carteiras[idCarteiraAtual].id);
            fgets(carteiras[idCarteiraAtual].descricao, sizeof(carteiras[idCarteiraAtual].descricao), arquivo);
        }
        // else if (linha[0] == 'I')
        // {
        //     // ID de AtivoFinanceiro e Quantidade de AtivoFinanceiro
        //     sscanf(linha, "Id de AtivoFinanceiro %d", &carteiras[idCarteiraAtual].ativo_carteira_ids[numAtivosCarteiraAtual]);
        //     sscanf(linha + strlen("Id de AtivoFinanceiro %d\n"), "Quantidade de AtivoFinanceiro %d", &carteiras[idCarteiraAtual].ativo_carteira_ids[numAtivosCarteiraAtual]);
        //     numAtivosCarteiraAtual++;
        // }
    }

    fclose(arquivo);
}

void imprimirCarteiras(Carteira *carteiras, int numCarteiras)
{
    for (int i = 0; i < numCarteiras; i++)
    {
        printf("Carteira ID: %d\n", carteiras[i].id);
        printf("Descrição: %s\n", carteiras[i].descricao);

        printf("Ativos da carteira:\n");
        for (int j = 0; j < carteiras[i].num_ativo_carteira; j++)
        {
            printf("ID de AtivoFinanceiro: %d\n", carteiras[i].ativo_carteira_ids[j]);
            printf("Quantidade de AtivoFinanceiro: %d\n", carteiras[i].ativo_carteira_ids[j + 1]);
            j++;
        }

        printf("\n");
    }
}

int main()
{
    int opcao_principal, opcao_secundaria;
    const int numCarteiras = 2;
    Carteira carteiras[numCarteiras];

    do
    {
        printf("Menu Principal:\n");
        printf("1. Ler Carteiras\n");
        printf("2. Atualizar valores AtivoFinanceiro\n");
        printf("3. Menu Secundário\n");
        printf("4. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal)
        {
        case 1:
            printf("Você selecionou a opção 1 do Menu Principal.\n");
            lerDadosCarteiras("data/carteiras.txt", carteiras, 2);
            imprimirCarteiras(carteiras, 2);
            break;
        case 2:
            printf("Você selecionou a opção 2 do Menu Principal.\n");
            break;
        case 3:
            do
            {
                printf("\nMenu Secundário:\n");
                printf("1. Opção A\n");
                printf("2. Opção B\n");
                printf("3. Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcao_secundaria);

                switch (opcao_secundaria)
                {
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
