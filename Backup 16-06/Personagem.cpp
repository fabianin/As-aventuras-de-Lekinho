#include "Personagem.h"

Personagem::Personagem (Id id, float x, float y, float faixay, bool colide): Elemento (id, x, y, faixay, colide) {
	this->projetil = NULL;
}

Personagem::~Personagem () {
	delete this;
}
