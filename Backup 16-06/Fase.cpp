#include "Fase.h"

Fase::Fase (Cenario cenario) {
	this->cenario = cenario;
	
	switch (cenario) {
		case FLORESTA:
			glClearColor(0, 0.5, 0, 0);
			this->obstaculos.push_back(new Obstaculo (TERRA, 			PISTA_ALEATORIA, HEIGHT + 100, 0, 			false));
			this->obstaculos.push_back(new Obstaculo (PLANTA_CARNIVORA, PISTA_ALEATORIA, HEIGHT + 100, 0.14*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (SAPO, 			PISTA_ALEATORIA, HEIGHT + 100, 0.30*HEIGHT, true));
			this->obstaculos.push_back(new Obstaculo (MINHOCA, 			PISTA_ALEATORIA, HEIGHT + 100, 0.08*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (TOCO, 			PISTA_ALEATORIA, HEIGHT + 100, 0.16*WIDTH, 	true));
			break;
		case GELO:
			glClearColor(0.8, 0.8, 1, 0);
			this->obstaculos.push_back(new Obstaculo (GELO_TRINCADO,	PISTA_ALEATORIA, HEIGHT + 100, 0, 			false));
			this->obstaculos.push_back(new Obstaculo (ICEBERGS, 		PISTA_ALEATORIA, HEIGHT + 100, 0.30*HEIGHT, true));
			this->obstaculos.push_back(new Obstaculo (GELO_QUEBRADO,	PISTA_ALEATORIA, HEIGHT + 100, 0.30*HEIGHT, true));
			this->obstaculos.push_back(new Obstaculo (URSO, 			PISTA_ALEATORIA, HEIGHT + 100, 0.30*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (LEAO_MARINHO, 	PISTA_ALEATORIA, HEIGHT + 100, 0.32*WIDTH, 	true));
			break;
		case DESERTO:
			glClearColor(0.6, 0.5, 0, 0);
			this->obstaculos.push_back(new Obstaculo (AREIA_MOVEDICA, 	PISTA_ALEATORIA, HEIGHT + 100, 0.20*WIDTH, 		true));
			this->obstaculos.push_back(new Obstaculo (CACTO, 			PISTA_ALEATORIA, HEIGHT + 100, 0.10*WIDTH, 		true));
			this->obstaculos.push_back(new Obstaculo (COBRA, 			PISTA_ALEATORIA, HEIGHT + 100, 0.20*WIDTH, 		true));
			this->obstaculos.push_back(new Obstaculo (LAGARTO, 			PISTA_ALEATORIA, HEIGHT + 100, 0.10*HEIGHT, 	true));
			break;
	}
	
	pistasLivres[PISTA1] = true;
	pistasLivres[PISTA2] = true;
	pistasLivres[PISTA3] = true;
}

Obstaculo* Fase::getObstaculo () {
	Obstaculo* obstaculo = OBSTACULO_ALEATORIO;
	float pista;
	do pista = PISTA_ALEATORIA; while (!pistaLivre(pista));
	obstaculo->setX(pista);
	obstaculo->setY(HEIGHT + 100);
	obstaculo->setCiclo(0);
	obstaculo->setProjetil(NULL);
	ocupaPista(obstaculo->getX(), true);
	return obstaculo;
}

Obstaculo* Fase::obstaculoSegundoProbabilidade (float probabilidade) {
	if (0.1*(rand()%11) <= probabilidade)
		return getObstaculo();
	else
		return NULL;
}

map<float, bool> Fase::getPistasLivres () {
	return pistasLivres;
}

void Fase::setPistasLivres (map<float, bool> pistasLivres) {
	this->pistasLivres = pistasLivres;
}

void Fase::ocupaPista (float pista, bool ocupa) {
	pistasLivres[pista] = !ocupa;
}

bool Fase::pistaLivre (float pista) {
	return pistasLivres[pista];
}

Fase::~Fase () {
	for (vector<Obstaculo*>::iterator it = (this->obstaculos).begin(); it != (this->obstaculos).end(); it++)
		delete *it;
	delete this;
}
