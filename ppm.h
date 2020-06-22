#ifndef SONECA_PPM_H
#define SONECA_PPM_H
    
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    u_int16_t altura,largura;
    u_int8_t* pixels;
} Imagem;

Imagem imagem_alocar(u_int16_t altura,u_int16_t largura) {
    Imagem img;
    img.altura=altura;
    img.largura=largura;
    img.pixels=calloc(altura*largura*3,1);
    return img;
}

u_int8_t* imagem_obter_pixel(Imagem* img,int x, int y) {
    return img->pixels+(((y*img->largura)+x)*3);
}
void imagem_pintar_pixel(Imagem* img,int x, int y,u_int8_t vermelho,u_int8_t verde,u_int8_t azul) {
    u_int8_t* pixel=imagem_obter_pixel(img,x,y);
    pixel[0]=vermelho;
    pixel[1]=verde;
    pixel[2]=azul;
}

void imagem_salvar_ppm(Imagem* img,FILE* f) {
    fprintf(f, "P6\n%d %d\n255\n", img->altura, img->largura); 
    for(int y=0;y<img->altura;y++) {
            for(int x=0;x<img->largura;x++) {
            u_int8_t* pixel=imagem_obter_pixel(img,x,y);
            fwrite(pixel,1,3,f);
        }
    }
}


#endif