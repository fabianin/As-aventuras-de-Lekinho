#ifndef FASE_H
#define FASE_H

#include "Texture.h"
#include "Personagem.h"

extern string imagem;
extern FILE *textura;
extern GLuint texID; 

class Fase {
	
	private:
		Cenario cenario;
		vector<Obstaculo*> obstaculos;
		Obstaculo *obstaculo1, *obstaculo2;
		Personagem* chefe;
		Bonus* bonus;

	public:
		Fase ();
		Obstaculo* getObstaculo1 ();
		Obstaculo* getObstaculo2 ();
		Personagem* getChefe ();
		Bonus* getBonus ();
		void iniciarChefe ();
		void terminarChefe ();
		void renovarObstaculos ();
		void renovarBonus ();
		void atualizarObstaculos (float);
		void atualizarBonus (float);
		bool pistaOcupada (float);
		~Fase ();
};

#endif
