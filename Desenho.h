#ifndef DESENHO_H
#define DESENHO_H

#include <bits/stdc++.h>
#include <GL/glut.h>

#define WIDTH 600.0
#define HEIGHT 400.0
#define FATOR_PROPORCAO 400.0
#define TAM_PISTA WIDTH/3.0
#define PISTA1 WIDTH/6
#define PISTA2 WIDTH/2
#define PISTA3 5*WIDTH/6
#define NUM_PISTAS 3
#define NUM_FASES 3
#define Y_LEKINHO 50.0
#define PISTA_ALEATORIA (1 + 2*(rand()%3))*WIDTH/6.0
#define OBSTACULO_ALEATORIO (this->obstaculos).at(rand()%(this->obstaculos).size())
#define OBSTACULO_CHEFE (this->obstaculos).at(0)
#define CENARIO_ALEATORIO rand()%NUM_FASES
#define ATIVAR_EFEITO rand()%2?true:false
#define Y_INICIAL HEIGHT+100
#define Y_FINAL -100
#define GERAR_OBSTACULO2 0.1*(rand()%11) <= 0.3

typedef enum {
	LEKINHO, ARANHA, BONECO_NEVE, VERME,
	PLANTA_CARNIVORA, SAPO, MINHOCA, TOCO,
	ICEBERGS, GELO_QUEBRADO, URSO, LEAO_MARINHO, 
	AREIA_MOVEDICA, CACTO, COBRA, LAGARTO, 
	LINGUA, BOLA_NEVE, TEIA
} Id;

typedef enum {AEREO, TERRESTRE, SUBTERRANEO} Caracteristica;

typedef enum {SURGINDO, TRANSLADANDO, PARADO, PRESO, SOFRENDO_DANO, INICIANDO_ATAQUE, ATACANDO, COLIDINDO, MORRENDO} Estado;

//GEOMETRIA
void desenhaElipse();
void desenhaCirculo();
void desenhaCircunferencia();
void desenhaPonto();
void desenhaLinha();
void desenhaQuadrilatero();

//PERSONAGENS
void desenhaLekinho();
void desenhaBonecoDeNeve(int, Estado);
void desenhaVerme(int, Estado);
void desenhaAranha(int, Estado);

//AUXILIARES
void desenhaIceberg(float, float, float, float, float, float, float, float);
void desenhaAgua();
void desenhaGeloTrincado();
void desenhaTerra();

//OBSTÁCULOS
void desenhaPlantaCarnivora(int);
void desenhaSapo();
void desenhaMinhoca(Estado, int);
void desenhaToco();
void desenhaIcebergs();
void desenhaGeloQuebrado(Estado);
void desenhaUrso();
void desenhaLeaoMarinho();
void desenhaAreiaMovedica(int);
void desenhaCacto(Estado);
void desenhaCobra();
void desenhaLagarto(float);

//PROJÉTEIS
void desenhaLingua();
void desenhaBolaDeNeve();
void desenhaTeia(float);

# endif
