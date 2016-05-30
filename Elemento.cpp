#include "Elemento.h"

Elemento::Elemento (fdesenho funcaoDesenho, float faixay) {
	this->funcaoDesenho = funcaoDesenho;
	this->faixay = faixay;
}

fdesenho Elemento::desenha () {
	return funcaoDesenho;
}

float Elemento::getX () {
	return x;
}

float Elemento::getY () {
	return y;
}

void Elemento::setX (float x) {
	this->x = x;
}

void Elemento::setY (float y) {
	this->y = y;
}

float Elemento::ySuperior () {
	return y + faixay/2.0; 
}

float Elemento::yInferior () {
	return y - faixay/2.0;
}

Elemento::~Elemento () {
	delete this;
}
