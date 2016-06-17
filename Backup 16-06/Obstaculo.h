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
		map<float, bool> realizaAcao (map<float, bool>);
		~Obstaculo ();
};

#endif
