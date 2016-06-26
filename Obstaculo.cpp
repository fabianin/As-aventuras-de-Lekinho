#include "Obstaculo.h"

Obstaculo::Obstaculo (Id id, Caracteristica caracteristica, Estado estado, float x, float y, float faixay, bool colide, bool podeAtivarEfeito): 
						Elemento (id, caracteristica, estado, x, y, faixay, colide) {
	this->podeAtivarEfeito = podeAtivarEfeito;
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
					if (tempoEstado == 0) {
						colide = false;
						podeAtivarEfeito = true;
					}
					if (y <= 0.65*HEIGHT) {
						if (podeAtivarEfeito && ATIVAR_EFEITO) {
							trocaEstado(INICIANDO_ATAQUE);
							trocouEstado = true;
						}
						podeAtivarEfeito = false;
					}
					break;
				case INICIANDO_ATAQUE:
					if (tempoEstado == 5) {
						trocaEstado(ATACANDO);
						trocouEstado = true;
					}
					break;
				case ATACANDO:
					if (tempoEstado == 0)
						colide = true;
					break;
			}
			break;			
		case SAPO:
			if (tempoEstado == 0)
				podeAtivarEfeito = true;
			if (y <= 0.8*HEIGHT) {
				if (podeAtivarEfeito) {
					float pistaDestino = PISTA_ALEATORIA;
					if ((pistaDestino == PISTA1 && !pista1Ocupada) || (pistaDestino == PISTA2 && !pista2Ocupada) ||
						(pistaDestino == PISTA3 && !pista3Ocupada)) {
						setX(pistaDestino);
					}
				}
				podeAtivarEfeito = false;
			}
			break;
		case GELO_QUEBRADO:
			switch (estado) {
				case TRANSLADANDO:
					if (tempoEstado == 0) {
						colide = false;
						podeAtivarEfeito = true;
					}
					if (y <= 0.8*HEIGHT) {
						if (podeAtivarEfeito && ATIVAR_EFEITO) {
							colide = true;
							trocaEstado(ATACANDO);
							trocouEstado = true;
						}
						podeAtivarEfeito = false;
					}
					break;
			}
			break;
		case LAGARTO:
			if (tempoEstado == 0)
				podeAtivarEfeito = true;
			if (y <= 0.8*HEIGHT) {
				if (podeAtivarEfeito && ATIVAR_EFEITO) {
					if ((!pista1Ocupada && !pista2Ocupada) || (!pista1Ocupada && !pista3Ocupada) || (!pista2Ocupada && !pista3Ocupada)) {
						float pistaAoLado;
						if (x == PISTA1)
							pistaAoLado = PISTA2;
						else
							pistaAoLado = x - TAM_PISTA;
						projetil = new Obstaculo (LINGUA, TERRESTRE, TRANSLADANDO, pistaAoLado, y, 0, true, false);
					}
				}
				podeAtivarEfeito = false;
			}
			break;
	}
	
	if (!trocouEstado)
		tempoEstado++;
}

Obstaculo::~Obstaculo () {
	delete this;
}
        
