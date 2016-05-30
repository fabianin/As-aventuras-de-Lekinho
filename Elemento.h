#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <bits/stdc++.h>

#define WIDTH 600
#define HEIGHT 400

typedef void (*fdesenho) ();

class Elemento {
	
	private:
		fdesenho funcaoDesenho;
		float x, y, faixay;
	
	public:
		Elemento (fdesenho, float);
		fdesenho desenha ();
		float getX ();
		float getY ();
		void setX (float);
		void setY (float);
		float ySuperior ();
		float yInferior ();
		~Elemento ();
};

#endif
