#include "Fase.h"

Fase::Fase (Cenario cenario) {
	this->emChefe = false;
	this->cenario = cenario;
	
	switch (cenario) {
		case FLORESTA:
			glClearColor(0, 0.5, 0, 0);
			
			this->obstaculos.push_back(new Obstaculo (TERRA, 			TERRESTRE, 		PISTA_ALEATORIA, Y_INICIAL, 0, 				false));
			this->obstaculos.push_back(new Obstaculo (PLANTA_CARNIVORA, TERRESTRE, 		PISTA_ALEATORIA, Y_INICIAL, 0.14*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (SAPO, 			TERRESTRE, 		PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT,	true));
			this->obstaculos.push_back(new Obstaculo (MINHOCA, 			SUBTERRANEO,	PISTA_ALEATORIA, Y_INICIAL, 0.08*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (TOCO, 			TERRESTRE, 		PISTA_ALEATORIA, Y_INICIAL, 0.16*WIDTH, 	true));
			
			break;
		case GELO:
			glClearColor(0.8, 0.8, 1, 0);
			
			this->obstaculos.push_back(new Obstaculo (AGUA,				SUBTERRANEO,	PISTA_ALEATORIA, Y_INICIAL, 0.35*HEIGHT, 	true));
			this->obstaculos.push_back(new Obstaculo (GELO_TRINCADO,	TERRESTRE,		PISTA_ALEATORIA, Y_INICIAL, 0, 				false));
			this->obstaculos.push_back(new Obstaculo (ICEBERGS, 		TERRESTRE,		PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT,	true));
			this->obstaculos.push_back(new Obstaculo (GELO_QUEBRADO,	SUBTERRANEO,	PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT, 	true));
			this->obstaculos.push_back(new Obstaculo (URSO, 			TERRESTRE,		PISTA_ALEATORIA, Y_INICIAL, 0.30*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (LEAO_MARINHO, 	TERRESTRE,		PISTA_ALEATORIA, Y_INICIAL, 0.32*WIDTH, 	true));
			
			this->chefe = new Personagem (BONECO_NEVE, TERRESTRE, PISTA_ALEATORIA, 0.7*HEIGHT, 0.24*WIDTH, true, 7);
			break;
		case DESERTO:
			glClearColor(0.6, 0.5, 0, 0);
			
			this->obstaculos.push_back(new Obstaculo (CACTO, 			TERRESTRE,		PISTA_ALEATORIA, Y_INICIAL, 0.10*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (AREIA_MOVEDICA, 	SUBTERRANEO,	PISTA_ALEATORIA, Y_INICIAL, 0.20*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (COBRA, 			TERRESTRE,		PISTA_ALEATORIA, Y_INICIAL, 0.20*WIDTH, 	true));
			this->obstaculos.push_back(new Obstaculo (LAGARTO, 			TERRESTRE,		PISTA_ALEATORIA, Y_INICIAL, 0.10*HEIGHT, 	true));
			
			this->chefe = new Personagem (VERME, SUBTERRANEO, PISTA_ALEATORIA, Y_LEKINHO, 0.12*WIDTH, false, 3);
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

bool Fase::IsEmChefe () {
	return emChefe;
}

void Fase::setEmChefe (bool emChefe) {
	if (emChefe)
		chefe->setVida(chefe->getVidaInicial());
	this->emChefe = emChefe;
}

void Fase::renovarObstaculos () {
	if (!emChefe) {
		obstaculo1 = OBSTACULO_ALEATORIO;
		obstaculo1->setX(PISTA_ALEATORIA);
		if (GERAR_OBSTACULO2) {
			float pistaObstaculo2;
			obstaculo2 = OBSTACULO_ALEATORIO;
			do pistaObstaculo2 = PISTA_ALEATORIA; while (obstaculo1->getX() == pistaObstaculo2);
			obstaculo2->setX(pistaObstaculo2);
			obstaculo2->setY(Y_INICIAL);
			obstaculo2->setCiclo(0);
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
	obstaculo1->setCiclo(0);
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
