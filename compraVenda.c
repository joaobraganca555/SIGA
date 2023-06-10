#include <stdio.h>
#include "compraVenda.h"
#include "Lib.h"

void venderAtivo(Carteira *carteira, int indiceAtivoNaCarteira) {

    int quantidade;
    AtivoCarteira *ativoCarteira = &carteira->ativosCarteira[indiceAtivoNaCarteira];

    printf("Quantidade: ");
    scanf("%d", &quantidade);

    //Caso insira uma quantidade superior a que possui
    if (quantidade > ativoCarteira->quantidade) {
        printf("Apenas tem %d disponiveis", ativoCarteira->quantidade);
        return;
    }

    ativoCarteira->quantidade -= quantidade;

    printf("Vendeu %d do ativo %d ficou com %d unidades\n", quantidade, ativoCarteira->id, ativoCarteira->quantidade);
}

void comprarAtivo(Carteira *carteira, int indiceAtivoNaCarteira) {

    int quantidade;
    AtivoCarteira *ativoCarteira = &carteira->ativosCarteira[indiceAtivoNaCarteira];

    if (carteira->numAtivosCarteira == MAX_ATIVOS_CARTEIRA) {
        printf("Limite maximo de %d ativos por carteira atingido", MAX_ATIVOS_CARTEIRA);
        return;
    }

    printf("Quantidade: ");
    scanf("%d", &quantidade);

    //Verificar se ja tem este ativo comprado, se tiver so acrescenta
    if (ativoCarteira < 0) {
        carteira->ativosCarteira[carteira->numAtivosCarteira].quantidade = quantidade;
        carteira->ativosCarteira[carteira->numAtivosCarteira].id = indiceAtivoNaCarteira;
        carteira->numAtivosCarteira++;
    } else {
        ativoCarteira->quantidade += quantidade;
    }

    printf("Comprou %d unidades, agora possui %d to ativo %d\n", quantidade, ativoCarteira->quantidade, indiceAtivoNaCarteira);
}



