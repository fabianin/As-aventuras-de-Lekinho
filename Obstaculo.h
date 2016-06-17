#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Elemento.h"

class Obstaculo: public Elemento {
	
	private:
		Obstaculo* projetil;
	
	public:
		Obstaculo (Id, float, float, float, bool);
		Obstaculo* getProjetil ();
		void setProjetil (Obstaculo*);
		void realizarAcao (bool, bool, bool);
		~Obstaculo ();
};

#endif
