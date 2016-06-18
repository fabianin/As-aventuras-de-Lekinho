#include "Obstaculo.h"

Obstaculo::Obstaculo (Id id, Caracteristica caracteristica, float x, float y, float faixay, bool colide): 
						Elemento (id, caracteristica, x, y, faixay, colide) {
	this->projetil = NULL;
}

void Obstaculo::realizarAcao (bool pista1Ocupada, bool pista2Ocupada, bool pista3Ocupada) {
	switch (id) {
		case SAPO:
			if (ciclo == 45) {
				float pistaDestino = PISTA_ALEATORIA;
				if ((pistaDestino == PISTA1 && !pista1Ocupada) || (pistaDestino == PISTA2 && !pista2Ocupada) ||
					(pistaDestino == PISTA3 && !pista3Ocupada)) {
					setX(pistaDestino);
				}
			}
			break;
		case LAGARTO:
			if ((!pista1Ocupada && !pista2Ocupada) || (!pista1Ocupada && !pista3Ocupada) || (!pista2Ocupada && !pista3Ocupada)) {
				if (ciclo == 45 && ATIVAR_EFEITO) {
					float pistaAoLado;
					if (x == PISTA1)
						pistaAoLado = PISTA2;
					else
						pistaAoLado = x - TAM_PISTA;
					projetil = new Obstaculo (LINGUA, TERRESTRE, pistaAoLado, y, 0, true);
				}
			}
			break;
	}
}

Obstaculo* Obstaculo::getProjetil () {
	return projetil;
}

void Obstaculo::setProjetil (Obstaculo* projetil) {
	this->projetil = projetil;
}

void Obstaculo::atualizar (float fatorVelocidade, bool pista1Ocupada, bool pista2Ocupada, bool pista3Ocupada) {
	setY(getY()-(8*fatorVelocidade));
	realizarAcao(pista1Ocupada, pista2Ocupada, pista3Ocupada);
	setCiclo(getCiclo() + 1);
}

Obstaculo::~Obstaculo () {
	delete this;
}
        
