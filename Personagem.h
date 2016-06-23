#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Bonus.h"
#include "Obstaculo.h"

class Personagem: public Elemento {

	private:
		int vida;
		Obstaculo* projetil;
		
	public:
		Personagem (Id, Caracteristica, Estado, float, float, float, bool, int);
		int getVida ();
		Obstaculo* getProjetil ();
		void setVida (int);
		void setProjetil (Obstaculo*);
		bool coletaBonus (Bonus*);
		void incrementaVida ();
		void decrementaVida ();
		void atualizar (float, float, Personagem*, Obstaculo*, Obstaculo*, Bonus*);
		~Personagem ();
};

#endif
