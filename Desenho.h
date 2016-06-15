#ifndef DESENHO_H
#define DESENHO_H

#include <bits/stdc++.h>
#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 400
#define RESPOSTA_ALEATORIA rand()%2?true:false

//GEOMETRIA
void desenhaElipse();
void desenhaCirculo();
void desenhaCircunferencia();
void desenhaPonto();
void desenhaLinha();
void desenhaQuadrilatero();

//PERSONAGENS
void desenhaLekinho();

//AUXILIARES
void desenhaIceberg(float, float, float, float, float, float, float, float);
void desenhaAgua();

//OBSTÁCULOS
void desenhaTerra();
void desenhaPlantaCarnivora(int);
void desenhaSapo();
void desenhaMinhoca(int);
void desenhaToco();
void desenhaGeloTrincado();
void desenhaIcebergs();
void desenhaGeloQuebrado(int);
void desenhaUrso();
void desenhaLeaoMarinho();
void desenhaAreiaMovedica(int);
void desenhaCacto();
void desenhaCobra();
void desenhaLagarto();
//void desenhaLingua();

# endif
