#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "Desenho.h"

using namespace std;

#define NUM_PISTAS 3
#define TAM_PISTA WIDTH/3.0
#define NUM_FASES 3
#define PISTA_ALEATORIA (1+ 2*(rand()%3))*WIDTH/6.0
#define OBSTACULO_ALEATORIO (this->obstaculos).at(rand()%(this->obstaculos).size())
#define CENARIO_ALEATORIO rand()%NUM_FASES

typedef enum {
	LEKINHO,
	TERRA, PLANTA_CARNIVORA, SAPO, MINHOCA, TOCO,
	GELO_TRINCADO, ICEBERGS, GELO_QUEBRADO, URSO, LEAO_MARINHO, 
	AREIA_MOVEDICA, CACTO, COBRA, LAGARTO, 
	LINGUA
} Id;

class Elemento {
	
	protected:
		Id id;
		float x, y, faixay;
		int ciclo;
		bool colide;
	
	public:
		Elemento (Id, float, float, float, bool);
		void desenha ();
		float getX ();
		float getY ();
		bool podeColidir ();
		int getCiclo ();
		void setX (float);
		void setY (float);
		void setPodeColidir (bool);
		void setCiclo (int);
		float ySuperior ();
		float yInferior ();
		~Elemento ();
};

#endif
