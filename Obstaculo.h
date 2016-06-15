#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "Elemento.h"

class Obstaculo: public Elemento {
	
	public:
		Obstaculo (Id, float, float, float, bool);
		void realizaAcao (map<float, bool>);
		~Obstaculo ();
};

#endif
