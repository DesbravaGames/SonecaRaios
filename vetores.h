#ifndef SONECA_VETORES_H
#define SONECA_VETORES_H

#include <math.h>

float clamp(float x){ return x<0 ? 0 : x>1 ? 1 : x; } 

typedef struct {float x, y, z;} Vetor3D;


Vetor3D vetor3d(float x,float y,float z) {
    return (Vetor3D){x,y,z};
}

Vetor3D vetor3d_soma(Vetor3D a,Vetor3D b) {
    return (Vetor3D) { a.x + b.x,a.y + b.y,a.z + b.z};
}

Vetor3D vetor3d_subtracao(Vetor3D a, Vetor3D b) {
    return (Vetor3D) { a.x - b.x,a.y - b.y,a.z - b.z};
}

Vetor3D vetor3d_escalar(Vetor3D v, float escalar) {
    return (Vetor3D) {v.x * escalar,v.y*escalar,v.z*escalar};
}

float vetor3d_modulo(Vetor3D vetor) {
    return (double) sqrt( 
                (vetor.x*vetor.x) + 
                (vetor.y*vetor.y) +
                (vetor.z*vetor.z)
    );
}
float vetor3d_distancia(Vetor3D a,Vetor3D b) {
    return vetor3d_modulo(vetor3d_subtracao(b,a));
}
void vetor3d_normalizar(Vetor3D* vetor) {
    float itensidade_do_vetor = vetor3d_modulo(*vetor);
    vetor->x/=itensidade_do_vetor;
    vetor->y/=itensidade_do_vetor;
    vetor->z/=itensidade_do_vetor;
}

void vetor3d_somar(Vetor3D* a,Vetor3D b) {
    a->x+=b.x;  a->y+=b.y;  a->z+=b.z;    
}
void vetor3d_subtrair(Vetor3D* a,Vetor3D b) {
    a->x-=b.x;  a->y-=b.y;  a->z-=b.z;    
}

float vetor3d_produto(Vetor3D a, Vetor3D b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

#endif