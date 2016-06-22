#include "Fase.h"

Fase::Fase (Cenario cenario) {
	this->chefe = NULL;
	this->cenario = cenario;
	
	switch (cenario) {
		case FLORESTA:
			glClearColor(0, 0.5, 0, 0);
			
			this->obstaculos.push_back(new Obstaculo (MINHOCA, 			SUBTERRANEO,	TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.08*WIDTH, 	false));
			this->obstaculos.push_back(new Obstaculo (PLANTA_CARNIVORA, TERRESTRE, 		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.14*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (SAPO, 			TERRESTRE, 		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT,	true));
			this->obstaculos.push_back(new Obstaculo (TOCO, 			TERRESTRE, 		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.16*WIDTH, 	true));
			
			break;
		case GELO:
			glClearColor(0.8, 0.8, 1, 0);
			this->obstaculos.push_back(new Obstaculo (GELO_QUEBRADO,	SUBTERRANEO,	TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT, 	false));
			this->obstaculos.push_back(new Obstaculo (ICEBERGS, 		TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT,	true));
			this->obstaculos.push_back(new Obstaculo (URSO, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (LEAO_MARINHO, 	TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.16*WIDTH, 	true));
			
			break;
		case DESERTO:
			glClearColor(0.6, 0.5, 0, 0);
			
			this->obstaculos.push_back(new Obstaculo (CACTO, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.10*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (AREIA_MOVEDICA, 	SUBTERRANEO,	TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.20*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (COBRA, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.20*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (LAGARTO, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.10*HEIGHT, 	true));
			
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

Personagem* Fase::getChefe () {
	return chefe;
}

void Fase::iniciarChefe () {
	switch(cenario) {
		case FLORESTA:
			this->chefe = new Personagem (ARANHA, TERRESTRE, SURGINDO, PISTA2, Y_INICIAL, 0.2*HEIGHT, true, 3);
			break;
		case GELO:
			this->chefe = new Personagem (BONECO_NEVE, TERRESTRE, SURGINDO, PISTA_ALEATORIA, Y_INICIAL, 0.24*WIDTH, false, 3);
			break;
		case DESERTO:
			this->chefe = new Personagem (VERME, SUBTERRANEO, SURGINDO, PISTA_ALEATORIA, Y_FINAL, 0.12*WIDTH, false, 3);
			break;
	}
}

void Fase::terminarChefe () {
	chefe = NULL;
}

void Fase::renovarObstaculos () {
	if (!chefe) {
		obstaculo1 = OBSTACULO_ALEATORIO;
		obstaculo1->setX(PISTA_ALEATORIA);
		if (GERAR_OBSTACULO2) {
			float pistaObstaculo2;
			obstaculo2 = OBSTACULO_ALEATORIO;
			do pistaObstaculo2 = PISTA_ALEATORIA; while (obstaculo1->getX() == pistaObstaculo2);
			obstaculo2->setX(pistaObstaculo2);
			obstaculo2->setY(Y_INICIAL);
			obstaculo2->reiniciaTempoEstado();
			obstaculo2->trocaEstado(TRANSLADANDO);
		}
		else
			obstaculo2 = NULL;
	}
	else {
		obstaculo1 = OBSTACULO_CHEFE;
		obstaculo1->setX(PISTA_ALEATORIA);
		obstaculo2 = NULL;
	}
	obstaculo1->setY(Y_INICIAL);
	obstaculo1->reiniciaTempoEstado();
	obstaculo1->trocaEstado(TRANSLADANDO);
	obstaculo1->setProjetil(NULL);
}

void Fase::atualizarObstaculos (float fatorVelocidade) {
	if (obstaculo1->getProjetil())
		obstaculo1->getProjetil()->atualizar(fatorVelocidade, pistaOcupada(PISTA1), pistaOcupada(PISTA2), pistaOcupada(PISTA3));
	obstaculo1->atualizar(fatorVelocidade, pistaOcupada(PISTA1), pistaOcupada(PISTA2), pistaOcupada(PISTA3));
	if (obstaculo2)
		obstaculo2->atualizar(fatorVelocidade, pistaOcupada(PISTA1), pistaOcupada(PISTA2), pistaOcupada(PISTA3));
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
