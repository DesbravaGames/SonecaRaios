#ifndef SONECA_SDL_DRAWER_H
#define SONECA_SDL_DRAWER_H

#include <SDL2/SDL.h>
#include "ppm.h"
#include "vetores.h"
#include "time.h"
#include "sdl_input.h"

SDL_Rect sdl_tamanho_janela;
SDL_Rect sdl_tamanho_textura;
SDL_Window * sdl_janela;
SDL_Renderer * sdl_renderizador;
SDL_Texture* sdl_textura;
Imagem * sdl_imagem;
SDL_Event sdl_evento;
int drawer_configurar(Imagem* img,int altura,int largura) {
     sdl_imagem=img;
     if(SDL_Init(SDL_INIT_EVERYTHING)) {   
          SDL_Log("Can't init %s", SDL_GetError());
          return 0;
     }
     sdl_janela=SDL_CreateWindow("DRAWER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largura,altura, 0);
     sdl_renderizador= SDL_CreateRenderer(sdl_janela, -1, SDL_RENDERER_ACCELERATED);
        sdl_textura = SDL_CreateTexture
               (
               sdl_renderizador,
                SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU8, SDL_ARRAYORDER_RGB,
                           SDL_PACKEDLAYOUT_NONE, 24, 3),
               SDL_TEXTUREACCESS_STREAMING,
               img->largura, img->altura
               );
               
      sdl_tamanho_textura=(SDL_Rect){0,0,img->largura,img->altura};
      sdl_tamanho_janela=(SDL_Rect){0,0,largura,altura};

     time_init();
   return 1;
}


u_int8_t *keystate;
Vetor3D eixo_movimento={0,0,0};


int drawer_atualizar() {
    // SDL_SetRenderDrawColor(sdl_renderizador, 0, 0, 0, SDL_ALPHA_OPAQUE );
     //SDL_RenderClear(sdl_renderizador); 
        SDL_UpdateTexture (
            sdl_textura,
            &sdl_tamanho_textura,
            sdl_imagem->pixels,
            sdl_imagem->largura*3
            );
     SDL_RenderCopy( sdl_renderizador, sdl_textura, NULL,NULL);
     static char titulo[100];
     sprintf(titulo,"FPS: %d",time_fps());
     SDL_SetWindowTitle(sdl_janela,titulo);
     SDL_RenderPresent(sdl_renderizador);
     time_update();
     sdl_processar_eventos();
     if(sdl_teclado(SDL_KEYDOWN,SDLK_ESCAPE) || sdl_checar_evento(SDL_QUIT)) {
          return 0;
     }
     return 1;
}


void drawer_destruir() {


/*save_texture(sdl_renderizador, sdl_textura,"image.bmp");*/
    SDL_DestroyRenderer( sdl_renderizador );
    SDL_DestroyWindow( sdl_janela );
    SDL_DestroyTexture(sdl_textura);
    SDL_Quit();
}
#endif
