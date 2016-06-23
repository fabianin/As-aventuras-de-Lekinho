#include "Bonus.h"

Bonus::Bonus (Id id, Caracteristica caracteristica, Estado estado, float x, float y, float faixay, bool colide): 
						Elemento (id, caracteristica, estado, x, y, faixay, colide) {
	coletado = false;
}

bool Bonus::foiColetado () {
	return coletado;
}

void Bonus::setColetado (bool coletado) {
	this->coletado = coletado;
}

void Bonus::atualizar (float fatorVelocidade) {
	y -= 8*fatorVelocidade;
	tempoEstado++;
}

Bonus::~Bonus () {
	delete this;
}
        
