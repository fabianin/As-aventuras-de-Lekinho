#include "Obstaculo.h"

Obstaculo::Obstaculo (Id id, float x, float y, float faixay, bool colide): Elemento (id, x, y, faixay, colide) {}

void Obstaculo::realizaAcao (map<float, bool> pistasLivres) {
	switch (id) {
		case SAPO:
			if (ciclo == 45) {
				float pistaDestino; 
				do pistaDestino = PISTA_ALEATORIA; while (!pistasLivres[pistaDestino]);
				setX(pistaDestino);
			}
			break;
		case LAGARTO:
			break;
	}
}

Obstaculo::~Obstaculo () {
	delete this;
}
        
