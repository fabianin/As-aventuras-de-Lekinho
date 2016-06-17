#include "Elemento.h"

Elemento::Elemento (Id id, float x, float y, float faixay, bool colide) {
	this->id = id;
	this->x = x;
	this->y = y;	
	this->faixay = faixay;
	this->colide = colide;
	this->ciclo = 0;
}

void Elemento::desenha () {
	glPushMatrix();
		glTranslatef(x, y, 0);
		switch (id) {
			case LEKINHO: 			desenhaLekinho();				break;
			case TERRA:				desenhaTerra();					break;
			case PLANTA_CARNIVORA: 	desenhaPlantaCarnivora(ciclo); 	break;
			case SAPO: 				desenhaSapo(); 					break;
			case MINHOCA:			desenhaMinhoca(ciclo); 			break;
			case TOCO:				desenhaToco(); 					break;
			case GELO_TRINCADO:		desenhaGeloTrincado();			break;
			case ICEBERGS:			desenhaIcebergs(); 				break;
			case GELO_QUEBRADO:		desenhaGeloQuebrado(ciclo); 	break;
			case URSO:				desenhaUrso(); 					break;
			case LEAO_MARINHO:		desenhaLeaoMarinho(); 			break;
			case AREIA_MOVEDICA:	desenhaAreiaMovedica(ciclo); 	break;
			case CACTO:				desenhaCacto();					break;
			case COBRA:				desenhaCobra();					break;
			case LAGARTO:			desenhaLagarto(x, ciclo);		break;
			case LINGUA:			desenhaLingua(x);				break;
		}
	glPopMatrix();
}

float Elemento::getX () {
	return x;
}

float Elemento::getY () {
	return y;
}

bool Elemento::podeColidir () {
	return colide;
}

int Elemento::getCiclo () {
	return ciclo;
}

void Elemento::setX (float x) {
	this->x = x;
}

void Elemento::setY (float y) {
	this->y = y;
}

void Elemento::setPodeColidir (bool colide) {
	this->colide = colide;
}

void Elemento::setCiclo (int ciclo) {
	this->ciclo = ciclo;
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
