#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Obstaculo.h"

class Personagem: public Elemento {

	private:
		Obstaculo* projetil;
		
	public:
		Personagem (Id, float, float, float, bool);
		~Personagem ();
};

#endif
