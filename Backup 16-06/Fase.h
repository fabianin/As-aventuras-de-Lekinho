#ifndef FASE_H
#define FASE_H

#include "Obstaculo.h"

typedef enum {FLORESTA, GELO, DESERTO} Cenario;

class Fase {
	
	private:
		Cenario cenario;		
		vector<Obstaculo*> obstaculos;
		map<float, bool> pistasLivres;

	public:
		Fase (Cenario);
		Obstaculo* getObstaculo ();
		Obstaculo* obstaculoSegundoProbabilidade (float);
		map<float, bool> getPistasLivres ();
		void setPistasLivres (map <float, bool>);
		void ocupaPista (float, bool);
		bool pistaLivre (float);
		~Fase ();
};

#endif
