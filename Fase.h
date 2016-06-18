#ifndef FASE_H
#define FASE_H

#include "Obstaculo.h"
#include "Personagem.h"

typedef enum {FLORESTA, GELO, DESERTO} Cenario;

class Fase {
	
	private:
		Cenario cenario;
		bool emChefe;	
		vector<Obstaculo*> obstaculos;
		Obstaculo *obstaculo1, *obstaculo2;
		Personagem* chefe;

	public:
		Fase (Cenario);
		Obstaculo* getObstaculo1 ();
		Obstaculo* getObstaculo2 ();
		Personagem* getChefe ();
		bool IsEmChefe ();
		void setEmChefe (bool);
		void renovarObstaculos ();
		void atualizarObstaculos (float);
		bool pistaOcupada (float);
		~Fase ();
};

#endif
