#ifndef SONECA_GRAFICOS_H
#define SONECA_GRAFICOS_H
#include "vetores.h"

///////////////////////////
typedef struct {
    float vermelho,verde,azul;
} Cor;

const Cor cor_branco={1,1,1};
const Cor cor_preto={0,0,0};
const Cor cor_vermelo={1,0,0};
const Cor cor_verde={1,0,0};
const Cor cor_azul={1,0,0};

Cor cor(float vermelho,float verde,float azul) {
    return (Cor) {vermelho,verde,azul};
}

Cor cor_soma(Cor a,Cor b) {
    Cor result;
    result.vermelho = clamp(a.vermelho + b.vermelho);
    result.verde = clamp(a.verde + b.verde);
    result.azul = clamp(a.azul + b.azul);
    return result;
}
Cor dimensionar_cor(Cor c,float itensidade) {
    return (Cor){c.vermelho*itensidade,c.verde*itensidade,c.azul*itensidade};
}

Cor misturar_cores(Cor a,Cor b) {
    return (Cor){ (a.vermelho+b.vermelho)/2,(a.verde+b.verde)/2,(a.azul+b.azul)/2};
}

#endif