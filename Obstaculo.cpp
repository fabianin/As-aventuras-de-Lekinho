#include "Obstaculo.h"

Obstaculo::Obstaculo (Id id, Caracteristica caracteristica, Estado estado, float x, float y, float faixay, bool colide): 
						Elemento (id, caracteristica, estado, x, y, faixay, colide) {
	this->projetil = NULL;
}

Obstaculo* Obstaculo::getProjetil () {
	return projetil;
}

void Obstaculo::setProjetil (Obstaculo* projetil) {
	this->projetil = projetil;
}

void Obstaculo::atualizar (float fatorVelocidade, bool pista1Ocupada, bool pista2Ocupada, bool pista3Ocupada) {
	bool trocouEstado = false;
	
	y -= 8*fatorVelocidade;
	switch (id) {
		case MINHOCA:
			switch (estado) {
				case TRANSLADANDO:
					if (tempoEstado == 0)
						colide = false;
					if (tempoEstado == 55 && ATIVAR_EFEITO) { //mudar para altura
						colide = true;
						trocaEstado(INICIANDO_ATAQUE);
						trocouEstado = true;
					}
					break;
				case INICIANDO_ATAQUE:
					if (tempoEstado == 5) {//mudar para altura
						trocaEstado(ATACANDO);
						trocouEstado = true;
					}
					break;
			}
			break;			
		case SAPO:
			if (tempoEstado == 45) { //mudar para altura
				float pistaDestino = PISTA_ALEATORIA;
				if ((pistaDestino == PISTA1 && !pista1Ocupada) || (pistaDestino == PISTA2 && !pista2Ocupada) ||
					(pistaDestino == PISTA3 && !pista3Ocupada)) {
					setX(pistaDestino);
				}
			}
			break;
		case GELO_QUEBRADO:
			switch (estado) {
				case TRANSLADANDO:
					if (tempoEstado == 0)
						colide = false;
					if (tempoEstado == 45 && ATIVAR_EFEITO) { //mudar para altura
						colide = true;
						trocaEstado(ATACANDO);
						trocouEstado = true;
					}
					break;
			}
			break;
		case LAGARTO:
			if ((!pista1Ocupada && !pista2Ocupada) || (!pista1Ocupada && !pista3Ocupada) || (!pista2Ocupada && !pista3Ocupada)) {
				if (tempoEstado == 45 && ATIVAR_EFEITO) { //mudar para altura
					float pistaAoLado;
					if (x == PISTA1)
						pistaAoLado = PISTA2;
					else
						pistaAoLado = x - TAM_PISTA;
					projetil = new Obstaculo (LINGUA, TERRESTRE, TRANSLADANDO, pistaAoLado, y, 0, true);
				}
			}
			break;
	}
	
	if (!trocouEstado)
		tempoEstado++;
}

Obstaculo::~Obstaculo () {
	delete this;
}
        
