#include "Fase.h"

Fase::Fase () {
	
	this->chefe = NULL;
	
	switch (SELECAO_CENARIO) {
		case 0:
			this->cenario = FLORESTA;
			break;
		case 1:
			this->cenario = GELO;
			break;
		case 2:
			this->cenario = DESERTO;
			break;
	}
	
	switch (cenario) {
		case FLORESTA:
			imagem = "grama.bmp";
			
			this->obstaculos.push_back(new Obstaculo (MINHOCA, 			SUBTERRANEO,	TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.08*WIDTH, 	false, true));
			this->obstaculos.push_back(new Obstaculo (PLANTA_CARNIVORA, TERRESTRE, 		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.14*WIDTH, 	true, false));
			this->obstaculos.push_back(new Obstaculo (SAPO, 			TERRESTRE, 		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT,	true, true));
			this->obstaculos.push_back(new Obstaculo (TOCO, 			TERRESTRE, 		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.16*WIDTH, 	true, false));
			
			break;
		case GELO:
			imagem = "gelo.bmp";
			
			this->obstaculos.push_back(new Obstaculo (GELO_QUEBRADO,	SUBTERRANEO,	TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT, 	false, true));
			this->obstaculos.push_back(new Obstaculo (ICEBERGS, 		TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*HEIGHT,	true, false));
			this->obstaculos.push_back(new Obstaculo (URSO, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.30*WIDTH, 	true, false));
			this->obstaculos.push_back(new Obstaculo (LEAO_MARINHO, 	TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.16*WIDTH, 	true, false));
			
			break;
		case DESERTO:
			imagem = "deserto.bmp";
			
			this->obstaculos.push_back(new Obstaculo (CACTO, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.10*WIDTH, 	true, false));
			this->obstaculos.push_back(new Obstaculo (AREIA_MOVEDICA, 	SUBTERRANEO,	TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.20*WIDTH, 	true, false));
			this->obstaculos.push_back(new Obstaculo (COBRA, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.20*WIDTH, 	true, false));
			this->obstaculos.push_back(new Obstaculo (LAGARTO, 			TERRESTRE,		TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.10*HEIGHT, 	true, true));
			
			break;
	}
	
	textura = fopen(imagem.c_str(), "rb");
	Texture tex(textura);
    texID = tex.getTexID();
	
	renovarObstaculos();
	renovarBonus();
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

Bonus* Fase::getBonus () {
	return bonus;
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

void Fase::renovarBonus () {
	bonus = NULL;
	if (GERAR_BONUS) {
		float pistaBonus;
		do pistaBonus = PISTA_ALEATORIA; while (pistaOcupada(pistaBonus));
		switch (SELECAO_BONUS) {
			case 0:
				this->bonus = new Bonus (ESCUDO, TERRESTRE, TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.22*HEIGHT, true);
				break;
			case 1:
				this->bonus = new Bonus (INVENCIBILIDADE, TERRESTRE, TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.24*HEIGHT, true);
				break;
			case 2:
				this->bonus = new Bonus (PONTOS, TERRESTRE, TRANSLADANDO, PISTA_ALEATORIA, Y_INICIAL, 0.15*HEIGHT, true);
				break;
		}
		bonus->setX(pistaBonus);
	}
}

void Fase::atualizarObstaculos (float fatorVelocidade) {
	if (obstaculo1->getProjetil())
		obstaculo1->getProjetil()->atualizar(fatorVelocidade, pistaOcupada(PISTA1), pistaOcupada(PISTA2), pistaOcupada(PISTA3));
	obstaculo1->atualizar(fatorVelocidade, pistaOcupada(PISTA1), pistaOcupada(PISTA2), pistaOcupada(PISTA3));
	if (obstaculo2)
		obstaculo2->atualizar(fatorVelocidade, pistaOcupada(PISTA1), pistaOcupada(PISTA2), pistaOcupada(PISTA3));
}

void Fase::atualizarBonus (float fatorVelocidade) {
	if (bonus)
		if (bonus->foiColetado())
			bonus = NULL;
		else
			bonus->atualizar(fatorVelocidade);
}

bool Fase::pistaOcupada (float pista) {
	return 	(obstaculo1->getX() == pista) ||
			(obstaculo2 != NULL && obstaculo2->getX() == pista) ||
			(obstaculo1->getProjetil() != NULL && obstaculo1->getProjetil()->getX() == pista) ||
			(bonus != NULL && bonus->getX() == pista);
}

Fase::~Fase () {
	for (vector<Obstaculo*>::iterator it = (this->obstaculos).begin(); it != (this->obstaculos).end(); it++)
		delete *it;
	delete this;
}
