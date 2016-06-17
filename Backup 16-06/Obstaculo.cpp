#include "Obstaculo.h"

Obstaculo::Obstaculo (Id id, float x, float y, float faixay, bool colide): Elemento (id, x, y, faixay, colide) {
	this->projetil = NULL;
}

map<float, bool> Obstaculo::realizaAcao (map<float, bool> pistasLivres) {
	switch (id) {
		case SAPO:
			if (ciclo == 45) {
				float pistaDestino = PISTA_ALEATORIA;
				pistasLivres[x] = true;
				if (pistasLivres[pistaDestino]) {
					setX(pistaDestino);
					pistasLivres[x] = false;
				}
			}
			break;
		case LAGARTO:
			if ((pistasLivres[PISTA1] && pistasLivres[PISTA2]) ||
				(pistasLivres[PISTA1] && pistasLivres[PISTA3]) ||
				(pistasLivres[PISTA2] && pistasLivres[PISTA3]  )) {
				if (ciclo == 45 && ATIVAR_EFEITO) {
					float pistaAoLado;
					if (x == PISTA1)
						pistaAoLado = PISTA2;
					else
						pistaAoLado = x - TAM_PISTA;
					projetil = new Obstaculo (LINGUA, pistaAoLado, y, 0, true);
					pistasLivres[pistaAoLado] = false;
				}
			}
			if (projetil)
				projetil->setY(y);
			break;
	}
	return pistasLivres;
}

Obstaculo* Obstaculo::getProjetil () {
	return projetil;
}

void Obstaculo::setProjetil (Obstaculo* projetil) {
	this->projetil = projetil;
}

Obstaculo::~Obstaculo () {
	delete this;
}
        
