#ifndef BONUS_H
#define BONUS_H

#include "Elemento.h"

class Bonus: public Elemento {
	
	private:
		bool coletado;
	
	public:
		Bonus (Id, Caracteristica, Estado, float, float, float, bool);
		bool foiColetado ();
		void setColetado (bool);
		void atualizar (float);
		~Bonus ();
};

#endif
