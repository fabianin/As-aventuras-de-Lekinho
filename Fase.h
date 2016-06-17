#ifndef FASE_H
#define FASE_H

#include "Obstaculo.h"

typedef enum {FLORESTA, GELO, DESERTO} Cenario;

class Fase {
	
	private:
		Cenario cenario;		
		vector<Obstaculo*> obstaculos;
		Obstaculo *obstaculo1, *obstaculo2;

	public:
		Fase (Cenario);
		Obstaculo* getObstaculo1 ();
		Obstaculo* getObstaculo2 ();
		void renovarObstaculos ();
		void atualizarObstaculo (Obstaculo*, float);
		void atualizarObstaculos (float);
		bool pistaOcupada (float);
		~Fase ();
};

#endif
