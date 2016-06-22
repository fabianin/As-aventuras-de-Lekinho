#ifndef ELEMENTO_H
#define ELEMENTO_H

#include "Desenho.h"

using namespace std;

class Elemento {
	
	protected:
		Id id;
		float x, y, faixay;
		int tempoEstado;
		bool colide;
		Caracteristica caracteristica;
		Estado estado;
	
	public:
		Elemento (Id, Caracteristica, Estado, float, float, float, bool);
		void desenha ();
		Caracteristica getCaracteristica ();
		float getX ();
		float getY ();
		float getFaixaY ();
		bool podeColidir ();
		Estado getEstado ();
		int getTempoEstado ();
		void setX (float);
		void setY (float);
		void setFaixaY (float);
		void setPodeColidir (bool);
		bool colideCom (Elemento* elemento);
		void trocaEstado (Estado);
		void reiniciaTempoEstado ();
		float ySuperior ();
		float yInferior ();
		~Elemento ();
};

#endif
