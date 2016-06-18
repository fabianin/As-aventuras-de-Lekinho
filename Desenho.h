#ifndef DESENHO_H
#define DESENHO_H

#include <bits/stdc++.h>
#include <GL/glut.h>

#define WIDTH 600.0
#define HEIGHT 400.0
#define FATOR_PROPORCAO 400.0
#define PISTA1 WIDTH/6
#define PISTA2 WIDTH/2
#define PISTA3 5*WIDTH/6

//GEOMETRIA
void desenhaElipse();
void desenhaCirculo();
void desenhaCircunferencia();
void desenhaPonto();
void desenhaLinha();
void desenhaQuadrilatero();

//PERSONAGENS
void desenhaLekinho();
void desenhaBonecoDeNeve(int, bool);
void desenhaVerme(int, bool);

//AUXILIARES
void desenhaIceberg(float, float, float, float, float, float, float, float);

//OBSTÁCULOS
void desenhaTerra();
void desenhaPlantaCarnivora(int);
void desenhaSapo();
void desenhaMinhoca(int);
void desenhaToco();
void desenhaAgua();
void desenhaGeloTrincado();
void desenhaIcebergs();
void desenhaGeloQuebrado(int);
void desenhaUrso();
void desenhaLeaoMarinho();
void desenhaAreiaMovedica(int);
void desenhaCacto(bool);
void desenhaCobra();
void desenhaLagarto(float, int);

//PROJÉTEIS
void desenhaLingua();
void desenhaBolaDeNeve();

# endif
