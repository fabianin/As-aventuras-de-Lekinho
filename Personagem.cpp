#include "Personagem.h"

Personagem::Personagem (Id id, Caracteristica caracteristica, float x, float y, float faixay, bool colide, int vidaInicial): 
						Elemento (id, caracteristica, x, y, faixay, colide) {
	this->vidaInicial = this->vida = vidaInicial;
	this->projetil = NULL;
}

int Personagem::getVida () {
	return vida;
}

int Personagem::getVidaInicial () {
	return vidaInicial;
}

Obstaculo* Personagem::getProjetil () {
	return projetil;
}

void Personagem::setVida (int vida) {
	this->vida = vida;
}

void Personagem::setVidaInicial (int vidaInicial) {
	this->vidaInicial = vidaInicial;
}

void Personagem::setProjetil (Obstaculo* projetil) {
	this->projetil = projetil;
}

void Personagem::incrementaVida () {
	vida++;
}

void Personagem::decrementaVida () {
	vida--;
}

void Personagem::atualizar (float xLekinho, float fatorVelocidade) {
	switch (id) {
		case VERME:
			if (ciclo <= 180)
				setX(xLekinho);
			if (ciclo == 250)
				setPodeColidir(true);
			if (ciclo >= 430 && !emColisao) {
				ciclo = 0;
				setPodeColidir(false);
			}
			else
				ciclo++;
			break;
		case BONECO_NEVE:
			if (ciclo == 0)
				projetil = NULL;
			if (ciclo <= 100)
				setX(xLekinho);
			if (ciclo == 170)
				projetil = new Obstaculo (BOLA_NEVE, AEREO, x, y - 0.33*HEIGHT, 0.07*WIDTH, true);
			if (ciclo >= 170)
				projetil->atualizar(fatorVelocidade, false, false, false);
			if (projetil && projetil->getY() < Y_FINAL)
				ciclo = 0;
			else
				ciclo++;
			break;
	}
}			

Personagem::~Personagem () {
	delete this;
}
