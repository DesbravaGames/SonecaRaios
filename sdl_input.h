#ifndef SONECA_SDL_INPUT_H
#define SONECA_SDL_INPUT_H

#include <SDL2/SDL.h>

#define MAXIMO_DE_EVENTOS 1000

SDL_Event eventos[MAXIMO_DE_EVENTOS];
int eventos_contagem=0;

void sdl_processar_eventos() {
    eventos_contagem=0;
    while (SDL_PollEvent(&eventos[eventos_contagem++]));
    //printf("%d eventos \n",eventos_contagem);
}

SDL_Event * sdl_checar_evento(int tipo) {
    for(int c=0;c<eventos_contagem;c++) {
        if(eventos[c].type==tipo) return &eventos[c];
    }
    return NULL;
}

int sdl_teclado(int tipo,int tecla) {
    for(int c=0;c<eventos_contagem;c++) {
        if((eventos[c].type == tipo && eventos[c].key.keysym.sym == tecla)) 
            return 1;
    }
    return 0;
}

#endif