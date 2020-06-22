#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "vetores.h"
#include "sdl_drawer.h"
#include "time.h"
#include "graficos.h"


typedef struct {
    Vetor3D posicao;
    Cor cor;
    float intensidade;
} Luz;

typedef struct {
    Cor cor_ambiente;
    float cor_ambiente_intensidade;
    Luz lampada;
} Cena;

typedef struct {
    Vetor3D posicao;
} Camera;

/* raio */
typedef struct {
    Vetor3D origem,direcao;
} Raio;


/*  esfera */
typedef struct {
    Vetor3D posicao;
    float raio;
} Esfera;

Esfera esfera_criar(float raio,Vetor3D posicao) {
    Esfera bola;
    bola.raio=raio;
    bola.posicao=posicao;
    return bola;
}

float raio_intersepta_esfera(Raio *raio,Esfera *esfera) {
    Vetor3D op = vetor3d_subtracao(esfera->posicao,raio->origem); // resolve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    float t, eps=1e-4, 
        b=vetor3d_produto(op,raio->direcao),
     det=b*b-vetor3d_produto(op,op)+(esfera->raio*esfera->raio);

    if (det<0) return 0; else det=sqrt(det);
    
    return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0);
}


Raio camera_tracar_raio(Camera* camera,int x,int y,int w,int h) {
    float posicaox=(float)(x-(w/2))/(float)w;
    float posicaoy=(float)(y-(h/2))/(float)h;
    if(1) {
        //posicaox*=-1.0;
        posicaoy*=-1.0;
    }
   // printf(" %d x %d - %f %f\n",x,y,posicaox,posicaoy);
    Vetor3D raio_destino=vetor3d_soma(camera->posicao,vetor3d(posicaox,posicaoy,1));
      //printf(" %d x %d - %f %f\n",x,y,camera->posicao.x,camera->posicao.y);
  
    Raio novo_raio;
    novo_raio.origem=camera->posicao;
    novo_raio.direcao=vetor3d_subtracao(raio_destino,novo_raio.origem);
    vetor3d_normalizar(&novo_raio.direcao);

    return novo_raio;
}

Esfera bola1;
Esfera bola2;
Esfera bola3;
int main() {
    Camera camera;
    camera.posicao=(Vetor3D){0,0,-1000};
    Cena cena={
        {1,1,1}, // cor ambiente
        0.06,// intensidade cor ambiente
        {// lampada
            {0,0,0}, // posicao
            {1,1,1}, //cor
            1 // itensidade
        }
    };
    Imagem img=imagem_alocar(400,400);
    bola1=esfera_criar(200,vetor3d(0,-100,300));
    bola2=esfera_criar(200,vetor3d(0,200,200));
    bola3.posicao=vetor3d(-20,0,200);
    bola3.raio=20;

    drawer_configurar(&img,800,800);
    while(drawer_atualizar()) {
        if(sdl_teclado(SDL_KEYDOWN,SDLK_w)) {
            camera.posicao.z+=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_s)) {
            camera.posicao.z-=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_a)) {
            camera.posicao.x-=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_d)) {
            camera.posicao.x+=100*time_delta();
        }

        if(sdl_teclado(SDL_KEYDOWN,SDLK_e)) {
            camera.posicao.y+=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_q)) {
            camera.posicao.y-=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_UP)) {
            cena.lampada.posicao.y+=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_DOWN)) {
            cena.lampada.posicao.y-=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_LEFT)) {
            cena.lampada.posicao.x-=100*time_delta();
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_RIGHT)) {
            cena.lampada.posicao.x+=100*time_delta();
        }

        bola3.posicao=cena.lampada.posicao;
        int pixels_pintados=0;
        int pixels_colididos=0;
        for(int x=0;x<img.largura;x++) {
            for(int y=0;y<img.altura;y++) {
                // PARA CADA PIXEL
               
                Raio r=camera_tracar_raio(&camera,x,y,img.largura,img.altura);
                float z_anterior=9999999999.0;
                int pintou_pixel=0;
                Cor px;
                //printf("RAIO %d x %d - %f %f %f\n",x,y,r.direcao.x,r.direcao.y,r.direcao.z);
                //if(0)
                for(int c=0;c<3;c++) {
                    Esfera bola;
                    if(c==0) bola=bola1;
                    if(c==1) bola=bola2;
                    if(c==2) bola=bola3;
                    
                    float t=raio_intersepta_esfera(&r,&bola);
                    
                    if(t) {
                        pixels_colididos++;
                        if(z_anterior>t) {
                           // printf("%f \n",t);
                            pintou_pixel=1;
                            Vetor3D ponto_colisao=vetor3d_soma(camera.posicao,vetor3d_escalar(r.direcao,t));
                            Vetor3D normal=vetor3d_subtracao(ponto_colisao,bola.posicao);
                            vetor3d_normalizar(&normal);
                            Vetor3D to_light=vetor3d_subtracao(cena.lampada.posicao,ponto_colisao);
                            vetor3d_normalizar(&to_light);
                            float cos_angle = vetor3d_produto(normal,to_light);
                           // if(cos_angle<0) cos_angle=0;
                            cos_angle = clamp(cos_angle);

                            // Scale the color of this fragment based on its angle to the light.
                            Cor cor_difusa=dimensionar_cor(cena.lampada.cor,cos_angle);
                            px=cor_soma(cor_difusa,dimensionar_cor(cena.cor_ambiente,cena.cor_ambiente_intensidade));

                            z_anterior=t;
                        }
                    }
                }

                if(pintou_pixel) {
                    pixels_pintados++;
                    imagem_pintar_pixelf(&img,x,y,px.vermelho,px.verde,px.azul);
                } else {
                    imagem_pintar_pixel(&img,x,y,0,0,0);
                }
            
            }
            
                imagem_pintar_pixel(&img,25,25,255,0,255);
        }

        if(sdl_teclado(SDL_KEYDOWN,SDLK_F5)) {
            printf("%d pixels colididos\n",pixels_colididos);
            printf("%d pixels pintados\n",pixels_pintados);
        }
        if(sdl_teclado(SDL_KEYDOWN,SDLK_F3)) {
            FILE *f = fopen("draw.ppm", "wb");
            imagem_salvar_ppm(&img,f);
            fclose(f);
            system("nohup xli draw.ppm > /dev/null &");
        }
    }
    
    drawer_destruir();
    free(img.pixels);
    
   return 1;
}