#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Elemento.h"

class Personagem: public Elemento {

	public:
		Personagem (Id, float, float, float, bool);
		~Personagem ();
};

#endif
