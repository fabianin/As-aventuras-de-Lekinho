#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Elemento.h"

class Obstaculo: public Elemento {
	
	private:
		Obstaculo* projetil;
	
	public:
		Obstaculo (Id, Caracteristica, float, float, float, bool);
		void realizarAcao (bool, bool, bool);
		Obstaculo* getProjetil ();
		void setProjetil (Obstaculo*);
		void atualizar (float, bool, bool, bool);
		~Obstaculo ();
};

#endif
