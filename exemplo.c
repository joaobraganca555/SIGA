#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char tipo[20];
    char nome[50];
} AtivoFinanceiro;

typedef struct {
    int id;
    int ativo_financeiro_id;
    char data[20];
    double valor;
} ValorAtivo;

typedef struct {
    int id;
    char descricao[100];
    int* ativo_carteira_ids;
    int num_ativo_carteira;
} Carteira;

typedef struct {
    int id;
    int ativo_financeiro_id;
    int quantidade;
} AtivoCarteira;

int main() {
    // Exemplo de utilização das estruturas

    // Criando alguns Ativos Financeiros
    AtivoFinanceiro ativo1 = {1, "Ação", "Empresa X"};
    AtivoFinanceiro ativo2 = {2, "Bond", "Título de Dívida Y"};

    // Criando alguns Valores Ativos
    ValorAtivo valor1 = {1, 1, "2023-06-01", 10.50};
    ValorAtivo valor2 = {2, 2, "2023-06-01", 1000.00};

    // Criando uma Carteira com Ativos Carteira
    Carteira carteira1 = {1, "Minha Carteira", NULL, 0};

    // Criando alguns Ativos Carteira
    AtivoCarteira ativoCarteira1 = {1, 1, 5};
    AtivoCarteira ativoCarteira2 = {2, 2, 2};

    // Adicionando os Ativos Carteira à Carteira
    carteira1.ativo_carteira_ids = (int*)malloc(2 * sizeof(int));
    carteira1.ativo_carteira_ids[0] = ativoCarteira1.id;
    carteira1.ativo_carteira_ids[1] = ativoCarteira2.id;
    carteira1.num_ativo_carteira = 2;

    // Exibindo os dados da Carteira
    printf("Carteira ID: %d\n", carteira1.id);
    printf("Descrição: %s\n", carteira1.descricao);
    printf("Ativos Carteira:\n");
    for (int i = 0; i < carteira1.num_ativo_carteira; i++) {
        printf("Ativo Carteira ID: %d\n", carteira1.ativo_carteira_ids[i]);
    }

    // Liberando a memória alocada para os Ativos Carteira
    free(carteira1.ativo_carteira_ids);

    return 0;
}
