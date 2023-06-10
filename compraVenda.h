#ifndef SIGA_MAURICIO_COMPRAVENDA_H
#define SIGA_MAURICIO_COMPRAVENDA_H

#include "Lib.h"

/**
 * Realiza a compra de um ativo numa carteira
 * @param carteira ponteiro para a carteira onde comprar o ativo
 * @param indiceAtivoNaCarteira indice do ativo carteira no array da carteira
 */
void comprarAtivo(Carteira *carteira, int indiceAtivoNaCarteira);

/**
 * Realiza a venda de um ativo numa carteira
 * @param carteira ponteiro para a carteira a vender o ativo
 * @param indiceAtivoNaCarteira indice do ativo carteira no array da carteira
 */
void venderAtivo(Carteira *carteira, int indiceAtivoNaCarteira);

#endif //SIGA_MAURICIO_COMPRAVENDA_H
