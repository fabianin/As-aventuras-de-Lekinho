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
	
	renovarObstaculos();
}

Obstaculo* Fase::getObstaculo1 () {
	return obstaculo1;
}

Obstaculo* Fase::getObstaculo2 () {
	return obstaculo2;
}

void Fase::renovarObstaculos () {
	obstaculo1 = OBSTACULO_ALEATORIO;
	obstaculo1->setY(Y_INICIAL);
	obstaculo1->setCiclo(0);
	obstaculo1->setProjetil(NULL);
	if (GERAR_OBSTACULO2) {
		float pistaObstaculo2;
		obstaculo2 = OBSTACULO_ALEATORIO;
		do pistaObstaculo2 = PISTA_ALEATORIA; while (obstaculo1->getX() == pistaObstaculo2);
		obstaculo2->setX(pistaObstaculo2);
		obstaculo2->setY(HEIGHT + 100);
		obstaculo2->setCiclo(0);
	}
	else
		obstaculo2 = NULL;
}

void Fase::atualizarObstaculo (Obstaculo *obstaculo, float fatorVelocidade) {
	if (obstaculo) {
		obstaculo->setY(obstaculo->getY()-(8*fatorVelocidade));
		obstaculo->realizarAcao(pistaOcupada(PISTA1), pistaOcupada(PISTA2), pistaOcupada(PISTA3));
		obstaculo->setCiclo(obstaculo->getCiclo() + 1);
	}
}

void Fase::atualizarObstaculos (float fatorVelocidade) {
	atualizarObstaculo(obstaculo1->getProjetil(), fatorVelocidade);
	atualizarObstaculo(obstaculo1, fatorVelocidade);
	atualizarObstaculo(obstaculo2, fatorVelocidade);
}

bool Fase::pistaOcupada (float pista) {
	return 	(obstaculo1->getX() == pista) ||
			(obstaculo2 != NULL && obstaculo2->getX() == pista) ||
			(obstaculo1->getProjetil() != NULL && obstaculo1->getProjetil()->getX() == pista);
}

Fase::~Fase () {
	for (vector<Obstaculo*>::iterator it = (this->obstaculos).begin(); it != (this->obstaculos).end(); it++)
		delete *it;
	delete this;
}
