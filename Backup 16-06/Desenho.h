#ifndef DESENHO_H
#define DESENHO_H

#include <bits/stdc++.h>
#include <GL/glut.h>

#define WIDTH 600
#define HEIGHT 400
#define ATIVAR_EFEITO rand()%2?true:false
#define PISTA1 WIDTH/6.0
#define PISTA2 WIDTH/2.0
#define PISTA3 5*WIDTH/6.0

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
void desenhaLagarto(float, int);
void desenhaLingua(float);

# endif
