#include "Elemento.h"

Elemento::Elemento (Id id, Caracteristica caracteristica, Estado estado, float x, float y, float faixay, bool colide) {
	this->id = id;
	this->caracteristica = caracteristica;
	this->estado = estado;
	this->x = x;
	this->y = y;	
	this->faixay = faixay;
	this->colide = colide;
	this->tempoEstado = 0;
}

void Elemento::desenha () {
	glPushMatrix();
		glTranslatef(x, y, 0);
		switch (id) {
			case LEKINHO: 			desenhaLekinho();							break;
			case PLANTA_CARNIVORA: 	desenhaPlantaCarnivora(tempoEstado); 		break;
			case SAPO: 				desenhaSapo(); 								break;
			case MINHOCA:			desenhaMinhoca(estado, tempoEstado);		break;
			case TOCO:				desenhaToco(); 								break;
			case ICEBERGS:			desenhaIcebergs(); 							break;
			case GELO_QUEBRADO:		desenhaGeloQuebrado(estado); 				break;
			case URSO:				desenhaUrso(); 								break;
			case LEAO_MARINHO:		desenhaLeaoMarinho(); 						break;
			case AREIA_MOVEDICA:	desenhaAreiaMovedica(tempoEstado); 			break;
			case CACTO:				desenhaCacto(estado);						break;
			case COBRA:				desenhaCobra();								break;
			case LAGARTO:			desenhaLagarto(x);							break;
			case LINGUA:			desenhaLingua();							break;
			case BOLA_NEVE:			desenhaBolaDeNeve();						break;
			case TEIA:				desenhaTeia(faixay);						break;
			case VERME:				desenhaVerme(tempoEstado, estado);			break;
			case BONECO_NEVE:		desenhaBonecoDeNeve(tempoEstado, estado);	break;
			case ARANHA:			desenhaAranha(tempoEstado, estado);
		}
	glPopMatrix();
}

Caracteristica Elemento::getCaracteristica () {
	return caracteristica;
}

float Elemento::getX () {
	return x;
}

float Elemento::getY () {
	return y;
}

float Elemento::getFaixaY () {
	return faixay;
}

bool Elemento::podeColidir () {
	return colide;
}

Estado Elemento::getEstado () {
	return estado;
}

int Elemento::getTempoEstado () {
	return tempoEstado;
}

void Elemento::setX (float x) {
	this->x = x;
}

void Elemento::setY (float y) {
	this->y = y;
}

void Elemento::setFaixaY (float faixay) {
	this->faixay = faixay;
}

void Elemento::setPodeColidir (bool colide) {
	this->colide = colide;
}

bool Elemento::colideCom (Elemento* elemento) {
	return	elemento != NULL &&
			this->podeColidir() &&
			elemento->podeColidir() &&
			elemento->yInferior() < this->ySuperior() &&
			elemento->ySuperior() > this->yInferior() &&
			this->getX() == elemento->getX();
}	

void Elemento::trocaEstado (Estado estado) {
	this->tempoEstado = 0;
	this->estado = estado;
}

void Elemento::reiniciaTempoEstado () {
	tempoEstado = 0;
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
