#include "Personagem.h"

Personagem::Personagem (Id id, Caracteristica caracteristica, Estado estado, float x, float y, float faixay, bool colide, int vida): 
						Elemento (id, caracteristica, estado, x, y, faixay, colide) {
	this->vida = vida;
	this->projetil = NULL;
}

int Personagem::getVida () {
	return vida;
}

Obstaculo* Personagem::getProjetil () {
	return projetil;
}

void Personagem::setVida (int vida) {
	this->vida = vida;
}

void Personagem::setProjetil (Obstaculo* projetil) {
	this->projetil = projetil;
}

bool Personagem::coletaBonus (Bonus* bonus) {
	return	bonus != NULL &&
			bonus->yInferior() < this->ySuperior() &&
			bonus->ySuperior() > this->yInferior() &&
			this->getX() == bonus->getX();
}

void Personagem::incrementaVida () {
	vida++;
}

void Personagem::decrementaVida () {
	vida--;
}

void Personagem::atualizar (float xLekinho, float fatorVelocidade, Personagem* chefe, Obstaculo* obstaculo1, Obstaculo* obstaculo2, 
							Bonus* bonus) {
	switch (id) {
		case LEKINHO:
			if (coletaBonus(bonus)) {
				bonus->setColetado(true);
				switch (bonus->getId()) {
					case ESCUDO:
						if (estado != INVENCIVEL && estado != PROTEGIDO_E_INVENCIVEL)
							trocaEstado(PROTEGIDO);
						else {
							int tempoInvencivel = tempoEstado;
							trocaEstado(PROTEGIDO_E_INVENCIVEL);
							tempoEstado = tempoInvencivel;
						}
						break;
					case INVENCIBILIDADE:
						if (estado != PROTEGIDO && estado != PROTEGIDO_E_INVENCIVEL )
							trocaEstado(INVENCIVEL);
						else
							trocaEstado(PROTEGIDO_E_INVENCIVEL);
						break;
				}
			}
			switch (estado) {
				case TRANSLADANDO:
					if (tempoEstado == 0)
						colide = true;
					if (colideCom(obstaculo1) || colideCom(obstaculo1->getProjetil()) || colideCom(obstaculo2) || colideCom(chefe) ||
						(chefe && colideCom(chefe->getProjetil())))
						exit(0);
					tempoEstado++;
					break;
				case PROTEGIDO:
					if (tempoEstado == 0)
						colide = true;
					if (colideCom(obstaculo1) || colideCom(obstaculo1->getProjetil()) || colideCom(obstaculo2) || colideCom(chefe) ||
						(chefe && colideCom(chefe->getProjetil())))
						trocaEstado(RECUPERANDO);
					else
						tempoEstado++;
					break;
				case RECUPERANDO:
					if (tempoEstado == 0)
						colide = false;
					if (tempoEstado == 100)
						trocaEstado(TRANSLADANDO);
					else
						tempoEstado++;
					break;
				case INVENCIVEL:
					if (tempoEstado == 0)
						colide = false;
					if (tempoEstado == 500)
						trocaEstado(TRANSLADANDO);
					else
						tempoEstado++;
					break;
				case PROTEGIDO_E_INVENCIVEL:
					colide = false;
					if (tempoEstado == 500)
						trocaEstado(PROTEGIDO);
					else
						tempoEstado++;
					break;
			}
			break;
		case VERME:
			switch (estado) {
				case SURGINDO:
					y += 8*fatorVelocidade;
					if (y >= Y_LEKINHO)
						trocaEstado(TRANSLADANDO);
					else {
						x = xLekinho;
						tempoEstado++;
					}
					break;
				case TRANSLADANDO:
					if (tempoEstado == 0)
						colide = false;
					if (tempoEstado < 180) {
						x = xLekinho;
						tempoEstado++;
					}
					else
						trocaEstado(INICIANDO_ATAQUE);
					break;
				case INICIANDO_ATAQUE:
					if (tempoEstado == 50)
						trocaEstado(ATACANDO);
					else
						tempoEstado++;
					break;
				case ATACANDO:
					if (tempoEstado == 0)
						colide = true;
					if (colideCom(obstaculo1)) {
						trocaEstado(COLIDINDO);
						obstaculo1->trocaEstado(COLIDINDO);
					}
					if (tempoEstado == 180)
						trocaEstado(TRANSLADANDO);
					else
						tempoEstado++;
					break;
				case COLIDINDO:
					if (tempoEstado == 70) {
						vida--;
						if (vida)
							trocaEstado(TRANSLADANDO);
						else
							trocaEstado(MORRENDO);
					}
					else
						tempoEstado++;
					break;
				case MORRENDO:
					y -= 8*fatorVelocidade;
					tempoEstado++;
					break;
			}
			break;
		case BONECO_NEVE:
			if (projetil)
				projetil->atualizar(fatorVelocidade, false, false, false);
			switch (estado) {
				case SURGINDO:
					y -= 8*fatorVelocidade;
					if (y <= 0.7*HEIGHT)
						trocaEstado(TRANSLADANDO);
					else {
						x = xLekinho;
						tempoEstado++;
					}
				break;
				case TRANSLADANDO:
					if (tempoEstado == 0) {
						projetil = NULL;
						colide = true;
					}
					if (colideCom(obstaculo1))
						trocaEstado(COLIDINDO);
					if (tempoEstado <= 50) {
						x = xLekinho;
						tempoEstado++;
					}
					else
						trocaEstado(INICIANDO_ATAQUE);
					break;
				case INICIANDO_ATAQUE:
					if (colideCom(obstaculo1))
						trocaEstado(COLIDINDO);
					if (tempoEstado == 50)
						trocaEstado(ATACANDO);
					else
						tempoEstado++;
					break;
				case ATACANDO:
					if (tempoEstado == 0)
						projetil = new Obstaculo (BOLA_NEVE, AEREO, TRANSLADANDO, x, y - 0.33*HEIGHT, 0.07*WIDTH, true);
					if (colideCom(obstaculo1))
						trocaEstado(COLIDINDO);
					if (projetil->getY() < Y_FINAL)
						trocaEstado(TRANSLADANDO);
					else
						tempoEstado++;
					break;
				case COLIDINDO:
					if (tempoEstado == 0)
						colide = false;
					if (tempoEstado == 50) {
						vida--;
						if (vida)
							trocaEstado(TRANSLADANDO);
						else
							trocaEstado(MORRENDO);
					}
					else
						tempoEstado++;
					break;
				case MORRENDO:
					y -= 8*fatorVelocidade;
					tempoEstado++;
				break;
			}
			break;
		case ARANHA:
			switch (estado) {
				case SURGINDO:
					y -= 8*fatorVelocidade;
					if (y <= 0.9*HEIGHT)
						trocaEstado(TRANSLADANDO);
					else {
						tempoEstado++;
						x = xLekinho;
					}
					break;
				case TRANSLADANDO:
					if (tempoEstado == 0)
						projetil = NULL;
					if (tempoEstado == 180)
						trocaEstado(INICIANDO_ATAQUE);
					else {
						tempoEstado++;
						x = xLekinho;
					}
					break;
				case INICIANDO_ATAQUE:
					if (tempoEstado == 50)
						trocaEstado(ATACANDO);
					else
						tempoEstado++;
					break;
				case ATACANDO:
					if (tempoEstado == 0)
						projetil = new Obstaculo (TEIA, TERRESTRE, PARADO, x, 0.5*HEIGHT, HEIGHT, true);
					if (projetil->colideCom(obstaculo1)) {
						trocaEstado(PRESO);
						obstaculo1->trocaEstado(PRESO);
					}
					if (tempoEstado == 100)
						trocaEstado(TRANSLADANDO);
					else
						tempoEstado++;
					break;
				case PRESO:
					if (y < 0.4*HEIGHT)
						trocaEstado(SOFRENDO_DANO);
					else {
						float inferiorTeia = obstaculo1->ySuperior();
						if (yInferior() < inferiorTeia)
							inferiorTeia = 0;
						y -= 8*fatorVelocidade;
						projetil->setFaixaY(yInferior() - inferiorTeia);
						projetil->setY(0.5*(yInferior() + inferiorTeia));
						tempoEstado++;
					}
				break;
				case SOFRENDO_DANO:
					if (tempoEstado == 0)
						projetil = NULL;
					if (y < 0.9*HEIGHT) {
						y += 8*fatorVelocidade;
						tempoEstado++;
					}
					else {
						y = 0.9*HEIGHT;
						vida--;
						if (vida)
							trocaEstado(TRANSLADANDO);
						else
							trocaEstado(MORRENDO);
					}
				break;
				case MORRENDO:
					y -= 8*fatorVelocidade;
					tempoEstado++;
				break;
			}
			break;
	}
}			

Personagem::~Personagem () {
	delete this;
}
