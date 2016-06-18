#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "Desenho.h"

using namespace std;

#define NUM_PISTAS 3
#define TAM_PISTA WIDTH/3.0
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
	LEKINHO, BONECO_NEVE, VERME,
	TERRA, PLANTA_CARNIVORA, SAPO, MINHOCA, TOCO,
	AGUA, GELO_TRINCADO, ICEBERGS, GELO_QUEBRADO, URSO, LEAO_MARINHO, 
	AREIA_MOVEDICA, CACTO, COBRA, LAGARTO, 
	LINGUA, BOLA_NEVE
} Id;

typedef enum {AEREO, TERRESTRE, SUBTERRANEO} Caracteristica;

class Elemento {
	
	protected:
		Id id;
		float x, y, faixay;
		int ciclo;
		bool colide, emColisao;
		Caracteristica caracteristica;
	
	public:
		Elemento (Id, Caracteristica, float, float, float, bool);
		void desenha ();
		Caracteristica getCaracteristica ();
		float getX ();
		float getY ();
		bool podeColidir ();
		bool IsEmColisao ();
		int getCiclo ();
		void setX (float);
		void setY (float);
		void setPodeColidir (bool);
		void setEmColisao (bool);
		void setCiclo (int);
		float ySuperior ();
		float yInferior ();
		~Elemento ();
};

#endif
