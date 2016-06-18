#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Obstaculo.h"

class Personagem: public Elemento {

	private:
		int vida, vidaInicial;
		Obstaculo* projetil;
		
	public:
		Personagem (Id, Caracteristica, float, float, float, bool, int);
		int getVida ();
		int getVidaInicial ();
		Obstaculo* getProjetil ();
		void setVida (int);
		void setVidaInicial (int);
		void setProjetil (Obstaculo*);
		void incrementaVida ();
		void decrementaVida ();
		void atualizar (float, float);
		~Personagem ();
};

#endif
