#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Número máximo de carteiras
#define MAX_CARTEIRAS 100
// Número máximo de AtivosCarteira
#define MAX_ATIVOS 50

// Função para ler ficheiros
// Retorna o conteúdo do ficheiro como String
char* lerFicheiro(char* caminho) {
    // Abrir o ficheiro
    FILE* ficheiro = fopen(caminho, "r");

    // Verificar se houve algum erro a abrir o ficheiro
    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return NULL;
    }

    // Selecionar máximo do array arbitrário
    const long MAX_TAMANHO_CONTEUDO = 100000;

    char *conteudo_ficheiro = malloc(MAX_TAMANHO_CONTEUDO * sizeof(char));

    // Ler carater a carater até ao final do 
    // ficheiro "EOF" (End Of File)
    char ch;
    long k = 0; // inteiro índice
    int i = 1; // inteiro para expandir o tamanho do array

    while ((ch = fgetc(ficheiro)) != EOF) {
        if (k < MAX_TAMANHO_CONTEUDO) {
            conteudo_ficheiro[k] = ch;
            k++;
        } else {
            // Aumentar tamanho do array do conteúdo do ficheiro
            i++;
            char *temporario = realloc(conteudo_ficheiro, (MAX_TAMANHO_CONTEUDO*i) * sizeof(char));
            conteudo_ficheiro = temporario;
            // Adicionar o carater ao array já aumentado
            k++;
            conteudo_ficheiro[k] = ch;
        }
    }

    // Adicionar carater nulo ao fim da string
    // Posição k+1
    conteudo_ficheiro[k+1] = '\0';

    // Fechar ficheiro
    fclose(ficheiro);

    // Retornar string
    return conteudo_ficheiro;
}  


struct AtivoFinanceiro {
    int id;
    char tipo;
    char *nome;
};

struct ValorAtivo {
    int id;
    char *data;
    float valor;
};

struct Carteira {
    int id;
    char *descricao;
    int lista_AtivoCarteira[MAX_ATIVOS];
};

struct AtivoCarteira {
    int id;
    int quantidade;
};


int main() {

    char *caminho_ficheiro = "dados_tiao.txt";

    char *conteudo_ficheiro = lerFicheiro(caminho_ficheiro);

    printf("%s\n", conteudo_ficheiro);
}