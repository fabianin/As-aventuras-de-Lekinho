#include "Desenho.h"

void desenhaElipse (GLfloat x, GLfloat y, float radiusX, float radiusY){
   int i;
 
   glBegin(GL_POLYGON);
 
   for(i=0;i<360;i++)
   {
      float rad = i*M_PI/180.0;
      glVertex2f(
      	(x + cos(rad)*radiusX)*WIDTH,
        y*HEIGHT + sin(rad)*radiusY*HEIGHT
      );
   }
 
   glEnd();
}

void desenhaCirculo (GLfloat x, GLfloat y, GLfloat radius){
	desenhaElipse(x, y, radius, radius*WIDTH/FATOR_PROPORCAO);
}

void desenhaCircunferencia (GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * M_PI;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
				(x + (radius * cos(i *  twicePi / lineAmount)))*WIDTH, 
				y*HEIGHT + (radius * sin(i * twicePi / lineAmount) * WIDTH * HEIGHT/FATOR_PROPORCAO)
			);
		}
	glEnd();
}

void desenhaPonto (float x, float y) {
	glBegin(GL_POINTS);
		glVertex2f(x*WIDTH, y*HEIGHT);
	glEnd();
}

void desenhaTriangulo (float x1, float y1, float x2, float y2, float x3, float y3) {
	glBegin(GL_TRIANGLES);
		glVertex2f(x1*WIDTH, y1*HEIGHT);
		glVertex2f(x2*WIDTH, y2*HEIGHT);
		glVertex2f(x3*WIDTH, y3*HEIGHT);
	glEnd();
}

void desenhaLinha (float x1, float y1, float x2, float y2, float largura) {
	glLineWidth(largura);
	glBegin(GL_LINES);
		glVertex2f(x1*WIDTH, y1*HEIGHT);
		glVertex2f(x2*WIDTH, y2*HEIGHT);
	glEnd();
	glLineWidth(1);
}

void desenhaQuadrilatero (float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	glBegin(GL_POLYGON);
		glVertex2f(x1*WIDTH, y1*HEIGHT);
		glVertex2f(x2*WIDTH, y2*HEIGHT);
		glVertex2f(x3*WIDTH, y3*HEIGHT);
		glVertex2f(x4*WIDTH, y4*HEIGHT);
	glEnd();
} 

void desenhaGeloTrincado () {
	glColor3f(0, 0, 1);
	desenhaLinha(0.00,  0.00, 0.05, -0.05, 3);
	desenhaLinha(0.05, -0.05, 0.05, -0.10, 3);
	
	desenhaLinha(0.00,   0.00, -0.03, -0.05, 3);
	desenhaLinha(-0.03, -0.05, -0.07, -0.06, 3);
	
	desenhaLinha(0.00,  0.00, -0.05, 0.00, 3);
	desenhaLinha(-0.05, 0.00, -0.10, 0.05, 3);
	
	desenhaLinha(0.00, 0.00,  0.00, 0.05, 3);
	desenhaLinha(0.00, 0.05, -0.03, 0.10, 3);
	
	desenhaLinha(0.00, 0.00, 0.05, 0.03, 3);
	desenhaLinha(0.05, 0.03, 0.09, 0.03, 3);
}

void desenhaUrso () {
	glColor3f(0.9, 0.9, 0.9);
	desenhaQuadrilatero(-0.1, -0.125, 0.1, -0.125, 0.1, 0.125, -0.1, 0.125);
	desenhaCirculo(0, 0.125, 0.1);
	desenhaCirculo(0, 0.275, 0.02);
	desenhaElipse(-1/15.0, -0.125, 1/30.0, 0.125);
	desenhaElipse( 1/15.0, -0.125, 1/30.0, 0.125);
	
	glColor3f(1, 1, 1);
	desenhaCirculo(0, -0.1, 0.06);
	desenhaCirculo( 0.05, -0.05, 0.02);
	desenhaCirculo(-0.05, -0.05, 0.02);
	desenhaElipse(0, -0.17, 0.03, 0.0675);
	
	glColor3f(0, 0, 0);
	desenhaTriangulo(-0.015, -0.21, 0.015, -0.21, 0, -0.23);
	desenhaLinha(-0.03, -0.15, -0.01, -0.15, 1);
	desenhaLinha(0.03, -0.15, 0.01, -0.15, 1);
}

void desenhaAgua () {
	glColor3f(0, 0, 1);
		glBegin(GL_POLYGON);
			glVertex2f(-0.10*WIDTH,  0.10*HEIGHT);
			glVertex2f(-0.05*WIDTH,  0.16*HEIGHT);
			glVertex2f(-0.03*WIDTH,  0.20*HEIGHT);
			glVertex2f( 0,			 0.13*HEIGHT);
			glVertex2f( 0.06*WIDTH,  0.13*HEIGHT);
			glVertex2f( 0.07*WIDTH,  0.15*HEIGHT);
			glVertex2f( 0.09*WIDTH,  0.12*HEIGHT);
			glVertex2f( 0.07*WIDTH,  0.09*HEIGHT);
			glVertex2f( 0.11*WIDTH,  0.05*HEIGHT);
			glVertex2f( 0.10*WIDTH,  0.02*HEIGHT);
			glVertex2f( 0.15*WIDTH,  0);
			glVertex2f( 0.09*WIDTH, -0.11*HEIGHT);
			glVertex2f( 0.09*WIDTH, -0.12*HEIGHT);
			glVertex2f( 0.07*WIDTH, -0.13*HEIGHT);
			glVertex2f( 0.05*WIDTH, -0.20*HEIGHT);
			glVertex2f( 0.05*WIDTH, -0.16*HEIGHT);
			glVertex2f( 0, 			-0.18*HEIGHT);
			glVertex2f(-0.05*WIDTH, -0.13*HEIGHT);
			glVertex2f(-0.05*WIDTH, -0.07*HEIGHT);
			glVertex2f(-0.10*WIDTH, -0.04*HEIGHT);
		glEnd();
}

void desenhaGeloQuebrado (Estado estado) {
	if (estado == TRANSLADANDO)	
		desenhaGeloTrincado();
	else
		desenhaAgua();
}

void desenhaIceberg (float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	glColor3f(1, 1, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x2, y2, x3, y3);
	glColor3f(0.9, 0.9, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x1, y1, x4, y4);
	glColor3f(0.6, 0.6, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x3, y3, x4, y4);
	glColor3f(0.5, 0.5, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x1, y1, x2, y2);
}

void desenhaIcebergs () {
	desenhaIceberg(-0.15, 0.00,  0.0, 0.15,  0.15, 0.00,  0.0, -0.15);
	desenhaIceberg( 0.05, 0.15,  0.1, 0.20,  0.15, 0.15,  0.1,  0.10);
	desenhaIceberg(-0.15, 0.15, -0.1, 0.20, -0.05, 0.15, -0.1,  0.10);
}

void desenhaLeaoMarinho () {
	desenhaAgua();
	
	glColor3f(0.55, 0.27, 0.07);
	desenhaElipse(0, 0, 0.15, 0.075);
	desenhaCirculo(0, 0, 0.08);
	
	glColor3f(1, 1, 1);
	desenhaLinha(-0.05, -0.07, 0.05, -0.07, 1);
	desenhaLinha(-0.05, -0.08, 0.05, -0.08, 1);
	desenhaLinha(-0.05, -0.09, 0.05, -0.09, 1);
	
	glColor3f(0.65, 0.37, 0.17);
	desenhaCirculo(-0.01, -0.06, 0.03);
	desenhaCirculo( 0.01, -0.06, 0.03);
	desenhaCirculo( 0.00,  0.00, 0.05);
	
	glColor3f(0, 0, 0);
	desenhaElipse( 0.00, -0.105, 0.005, 0.0045);
	desenhaElipse( 0.04, -0.050, 0.003, 0.0075);
	desenhaElipse(-0.04, -0.050, 0.003, 0.0075);
}

void desenhaToco () {
	glColor3f(0.4, 0.27, 0.07);
	desenhaQuadrilatero(-0.03,  0.03, 0.13,  0.16, 0.03, -0.03, -0.13, -0.16);
	desenhaQuadrilatero(-0.03, -0.03, 0.13, -0.16, 0.03,  0.03, -0.13,  0.16);
	glColor3f(0.55, 0.27, 0.07);
	desenhaCirculo(0, 0, 0.08);
	glColor3f(0.65, 0.65, 0.15);
	desenhaCirculo(0, 0, 0.07);
	glColor3f(0.55, 0.27, 0.07);
	desenhaCircunferencia(0, 0, 0.06);
	desenhaCircunferencia(0, 0, 0.04);
	desenhaCircunferencia(0, 0, 0.02);
}

void desenhaSapo () {
	glColor3f(0, 0.2, 0);
	desenhaElipse( 0.04, 0.07, 0.02, 0.06);
	desenhaElipse(-0.04, 0.07, 0.02, 0.06);
	
	glColor3f(0, 0.4, 0);
	desenhaElipse( 0.04, -0.02, 0.02, 0.06);
	desenhaElipse(-0.04, -0.02, 0.02, 0.06);
	desenhaCirculo(-0.065, -0.12, 0.005);
	desenhaCirculo(-0.040, -0.12, 0.005);
	desenhaCirculo(-0.015, -0.12, 0.005);
	desenhaCirculo( 0.005, -0.12, 0.005);
	desenhaCirculo( 0.040, -0.12, 0.005);
	desenhaCirculo( 0.065, -0.12, 0.005);
	desenhaTriangulo(-0.04, -0.02, -0.07, -0.12, -0.01, -0.12);
	desenhaTriangulo( 0.04, -0.02,  0.01, -0.12,  0.07, -0.12);
	
	glColor3f(0, 0.6, 0);
	desenhaElipse(0, 0, 0.05, 0.15);
	
	glColor3f(0, 0.4, 0);
	desenhaElipse(-0.02, -0.064, 0.015, 0.015);
	desenhaElipse( 0.02, -0.064, 0.015, 0.015);
	glColor3f(0, 0, 0);
	desenhaElipse(-0.02, -0.07, 0.01, 0.0075);
	desenhaElipse( 0.02, -0.07, 0.01, 0.0075);
	
	desenhaPonto(-0.005, -0.14);
	desenhaPonto( 0.005, -0.14);
	desenhaPonto(-0.010,  0.02);
	desenhaPonto( 0.010,  0.02);
	desenhaPonto(-0.010,  0.04);
	desenhaPonto( 0.010,  0.04);
	desenhaPonto(-0.010,  0.06);
	desenhaPonto( 0.010,  0.06);
}

void desenhaTerra () {
	glColor3f(0, 0, 0);
	desenhaQuadrilatero(-0.1, -0.1, -0.1, 0.1, 0.1, 0.1, 0.1, -0.1);
	for (float i = -0.1; i < 0.12; i += 0.025)
		for (float j = -0.1; j < 0.12; j += 0.02) {
			glColor3f(0.5, 0.2, 0.1);
			desenhaCirculo(j, i, 0.01);
			glColor3f(0, 0, 0);
			desenhaCircunferencia(j, i, 0.01);
		}
}

void desenhaPlantaCarnivora (int tempoEstado) {
	glColor3f(0, 0.3, 0);
	desenhaElipse(-0.07, 0, 0.07, 0.075);
	desenhaElipse( 0.07, 0, 0.07, 0.075); 
	
	glColor3f(0, 0.6, 0);
	desenhaCirculo(0, 0, 0.07);
	
	bool aplicarEfeito = (tempoEstado/5)%2 != 0;
	if (aplicarEfeito) {
		glColor3f(0.5, 0.7, 0.5);
		desenhaElipse(0, -0.08, 0.06, 0.025);
	}
	else {
		glColor3f(0.5, 0.7, 0.5);
		desenhaElipse(0, -0.07, 0.06, 0.045);
		glColor3f(0, 0, 0);
		desenhaElipse(0, -0.08, 0.045, 0.035);
		glColor3f(0.5, 0.7, 0.5);
		desenhaTriangulo(-0.012, -0.035,  0.000, -0.09,  0.012, -0.035);
		desenhaTriangulo(-0.036, -0.035, -0.024, -0.09, -0.012, -0.035);
		desenhaTriangulo( 0.012, -0.035,  0.024, -0.09,  0.036, -0.035); 
	}
}

void desenhaMinhoca (Estado estado, int tempoEstado) {
	desenhaTerra();

	if (estado != TRANSLADANDO) {
		desenhaCirculo(0, 0, 0.06);
		glColor3f(1, 0.8, 0.8);
		desenhaCirculo(0, 0, 0.04);
		
		if (estado == INICIANDO_ATAQUE) 
			for (float i = -0.15; i <= 0.15; i += 0.3)
				for (float j = -0.15; j <= 0.15; j += 0.3) {
					glColor3f(0.5, 0.2, 0.1);
					desenhaCirculo(j, i, 0.01);
					glColor3f(0, 0, 0);
					desenhaCircunferencia(j, i, 0.01);
				}
		else {
			glPushMatrix();
				int numero0a3;
				if (estado != PRESO)
					numero0a3 = (tempoEstado/10)%4;
				else
					numero0a3 = 3;
				glRotatef(numero0a3 * 90, 0, 0, 1);
				glColor3f(1, 0.8, 0.8);
				desenhaQuadrilatero(-0.04, 0, 0.04, 0, 0.04, -0.11, -0.04, -0.11);
				desenhaCirculo(0, -0.11, 0.04);
				glColor3f(1, 0, 0);
				desenhaLinha(-0.04,  0.00, 0.04,  0.00, 2);
				desenhaLinha(-0.04, -0.05, 0.04, -0.05, 2);
				desenhaLinha(-0.04, -0.10, 0.04, -0.10, 2);
			glPopMatrix();
		}
	}
}

void desenhaAreiaMovedica (int tempoEstado) {
	glColor3f(0.95, 0.7, 0.4);
	desenhaCirculo(0, 0, 0.1);
	
	float aux = 0.09;
	bool aplicarEfeito = (tempoEstado/5)%2 != 0;
	if (aplicarEfeito)
		aux = 0.08;
	
	glColor3f(0.5, 0.2, 0);
	for (float i = aux; i >= 0; i -= 0.02) 
		desenhaCircunferencia(0, 0, i);
}

void desenhaCacto (Estado estado) { 
	glColor3f(0, 0.4, 0);
	if (estado != COLIDINDO) {
		desenhaQuadrilatero(-0.1, 0.03, 0.1, 0.03, 0.1, -0.03, -0.1, -0.03);
		
		glColor3f(0, 0.6, 0);
		desenhaCirculo(0, 0, 0.05);
		desenhaCirculo(-0.1, 0, 0.03);
		desenhaCirculo(0.1, 0, 0.03);
	}
	else {
		desenhaCirculo(0, 0, 0.02);
		desenhaCirculo(-0.1,  0.1, 0.02);
		desenhaCirculo(-0.1, -0.1, 0.02);
		desenhaCirculo( 0.1,  0.1, 0.02);
		desenhaCirculo( 0.1, -0.1, 0.02);
	}
		
}

void desenhaCobra () {
	glColor3f(0.1, 0, 0.3);
	desenhaQuadrilatero(0.08, 0, 0.1, 0, 0.1, 0.2, 0.08, 0.2);
	desenhaTriangulo(0.08, 0.2, 0.1, 0.2, 0.09, 0.25);

	for (float i = 0.02; i < 0.12; i += 0.02) { 
		glColor3f(5*i, 0, 0.3);
		desenhaCirculo(0, 0, 0.12-i);
		glColor3f(0, 0, 0);
		desenhaCircunferencia(0, 0, 0.12-i);
	}
	
	glColor3f(1, 0, 0);
	desenhaLinha(0, -0.1, 0, -0.2, 2);
	desenhaLinha(0, -0.2, -0.01, -0.21, 2);
	desenhaLinha(0, -0.2, 0.01, -0.21, 2);
	
	glColor3f(0.5, 0, 0.3);
	desenhaElipse(0, -0.05, 0.07, 0.05);
	desenhaElipse(0, -0.1, 0.03, 0.06);
	
	glColor3f(0.2, 0, 0.3);
	desenhaElipse(-0.015, -0.115, 0.01, 0.005);
	desenhaElipse(0.015, -0.115, 0.01, 0.005);
}

void desenhaLingua () {	
	glColor3f(1, 0, 0);
	desenhaLinha(-0.25, 0, 0.25, 0, 7);
}

void desenhaLagarto (float x) {
	if (x == PISTA1)
		glRotatef(180, 0, 0, 1);
	glColor3f(0.5, 0.8, 0.3);
	desenhaElipse(0, 0, 0.07, 0.05);
	desenhaElipse(-0.06, 0, 0.05, 0.05);
	desenhaTriangulo(0, 0.04, 0, -0.04, 0.16, 0);
	desenhaLinha(-0.04, -0.1, -0.04, 0.1, 5);
	desenhaLinha(0.04, -0.1, 0.04, 0.1, 5);
	desenhaLinha(-0.04, 0.08, -0.05, 0.09, 5);
	desenhaLinha(-0.04, 0.08, -0.03, 0.09, 5);
	desenhaLinha(0.04, 0.08, 0.03, 0.09, 5);
	desenhaLinha(0.04, 0.08, 0.05, 0.09, 5);
	desenhaLinha(-0.04, -0.08, -0.05, -0.09, 5);
	desenhaLinha(-0.04, -0.08, -0.03, -0.09, 5);
	desenhaLinha(0.04, -0.08, 0.03, -0.09, 5);
	desenhaLinha(0.04, -0.08, 0.05, -0.09, 5);
}

void desenhaTeia (float faixay) {
	glColor3f(1, 1, 1);
	desenhaLinha(0, 0.5*faixay/HEIGHT, 0, -0.5*faixay/HEIGHT, 2);
}

void desenhaAranha (int tempoEstado, Estado estado) {
	bool virada = false;
	if (estado == MORRENDO)
		virada = true;
	int fatorVelocMovPatas = (int) (5/fatorVelocidade);
	if (estado == PRESO || fatorVelocMovPatas < 1)
		fatorVelocMovPatas = 1;
	int anguloAberturaQueliceras = 0;
	float pataMovimento1 = -0.06 + 0.04*((tempoEstado/fatorVelocMovPatas)%2);
	float pataMovimento2 =  0.02 + 0.04*((tempoEstado/fatorVelocMovPatas)%2);
	int ladoPataMovimento = (tempoEstado/5)%2? 1 : -1;
	if (estado == SURGINDO || estado == TRANSLADANDO ||
		estado == INICIANDO_ATAQUE && (tempoEstado/10)%2)
		anguloAberturaQueliceras = 5;
	else if (estado == ATACANDO || estado == PRESO || estado == SOFRENDO_DANO)
		anguloAberturaQueliceras = 12;

	if (estado == SOFRENDO_DANO && (tempoEstado/10)%2)
		virada = true;
	else if (estado != MORRENDO)
		virada = false;
	if (virada)
		glRotatef(180, 1, 0, 0);
	glColor3f(1, 0, 0);
	for (int lado = 1; lado >= -1; lado -= 2) {
		for (float i = -0.06; i < 0.10; i += 0.04) { //patas
			glPushMatrix();
				glTranslatef(0, i, 0);
				if ((i == pataMovimento1 || i == pataMovimento2) && lado == ladoPataMovimento)
					glRotatef(30*lado, 0, 0, 1);
				desenhaLinha(0.00, 		i, 0.08*lado, i, 		3);
				desenhaLinha(0.08*lado, i, 0.09*lado, i - 0.05, 3);
			glPopMatrix();
		}
		
		glPushMatrix(); //queliceras
			glTranslatef(0, -0.08, 0);
			glRotatef(anguloAberturaQueliceras*lado, 0, 0, 1);
			desenhaTriangulo(0, 0, 0, -0.2,  0.03*lado, 0);
		glPopMatrix();
	}
	
	glColor3f(0, 0, 0); //corpo
	desenhaElipse(0, 0, 0.04, 0.1);
	desenhaCirculo(0, -0.08, 0.04);
	
	if (!virada) {
		glColor3f(1, 0, 0); //olhos
		for (float i = -0.085; i > -0.105; i -= 0.015)
			for (float j = -0.015; j <= 0.015; j += 0.01)
				desenhaCirculo(j, i, 0.005);
	}
}

void desenhaBolaDeNeve () {
	glColor3f(1, 1, 1);
	desenhaCirculo(0, 0, 0.035);
}

void desenhaBonecoDeNeve (int tempoEstado, Estado estado) {
	float alteraCor = (estado == COLIDINDO)? 0.25 : 0;
	
	if (estado != MORRENDO) {
		glColor3f(0.95, 0.95 - alteraCor, 1  - alteraCor);
		desenhaCirculo(0, 0, 0.12); //bola inferior
		
		glColor3f(0.9, 0.9 - alteraCor, 1 - alteraCor);
		desenhaCirculo(0, 0.03, 0.094); //bola central
		
		glColor3f(0.85, 0.85 - alteraCor, 1 - alteraCor);
		desenhaCirculo(0, 0.06, 0.06); //bola superior
		
		glColor3f(0, 0, 0);
		desenhaTriangulo(-0.035, 0, -0.017, 0, -0.035, 0.018); //olhos
		desenhaTriangulo( 0.035, 0,  0.017, 0,  0.035, 0.018);
	}
	else {
		glColor3f(0.95, 0.95, 1);
		desenhaCirculo(-0.05, -0.05, 0.08);
		desenhaCirculo( 0.05, -0.05, 0.08);
		desenhaCirculo( 0.00,  0.05, 0.08);
	}  

	
	glColor3f(0, 0, 0);
	desenhaElipse(0, 0.09, 0.06, 0.060); //cartola
	desenhaElipse(0, 0.15, 0.04, 0.042);
	
	desenhaLinha( 0.094,  0.03,  0.094, -0.12, 5); //braços
	desenhaLinha( 0.094, -0.12,  0.000, -0.18, 5);
	desenhaLinha(-0.094,  0.03, -0.094, -0.12, 5);
	desenhaLinha(-0.094, -0.12,  0.000, -0.24, 5);
	
	bool piscaArma = estado == INICIANDO_ATAQUE && (tempoEstado/5)%2;
	glColor3f(0.44, 0.126, 0.919); //arma
	desenhaQuadrilatero(-0.035, -0.27,  0.035, -0.27, 0.035, -0.18, -0.035, -0.18);
	desenhaQuadrilatero(-0.035, -0.18, -0.015, -0.12, 0.015, -0.12,  0.035, -0.18);
	glColor3f(1, 0.5, 0);
	desenhaQuadrilatero(-0.009, -0.24, -0.009, -0.15, 0.009, -0.15, 0.009, -0.24);
	desenhaElipse(0, -0.276, 0.048, 0.024);
	
	if (!piscaArma)
		glColor3f(0, 0, 0);
	else
		glColor3f(0.9, 0.9, 1);
	desenhaElipse(0, -0.282, 0.04, 0.012);
		
	glColor3f(1, 0.5, 0);
	desenhaTriangulo(-0.012, -0.018, 0.012, -0.018, 0, -0.12); //nariz
}

void desenhaVerme (int tempoEstado, Estado estado) {
	glColor3f(0.9, 0.65, 0.35); //areia
	desenhaCirculo(0, 0, 0.08);
	desenhaQuadrilatero(-0.08, 0, 0.08, 0, 0.08, -50/HEIGHT, -0.08, -50/HEIGHT);
	glColor3f(0.5, 0.2, 0);
	for (int i = 0; i >= -50; i -= 15)
		desenhaLinha(-0.08, (i - 2*fatorVelocidade*(tempoEstado%10))/HEIGHT, 0.08, (i - 2*fatorVelocidade*(tempoEstado%10))/HEIGHT, 1);
	glColor3f(1, 0.9, 0.8);
	if (estado == INICIANDO_ATAQUE) {
		desenhaCirculo(0, 0, 0.01*((tempoEstado/2)%8));
		desenhaCirculo(0, 0, 0.01*((tempoEstado/2)%4));
	}
	
	//cabeça
	if (estado == ATACANDO || estado == COLIDINDO || estado == MORRENDO) {
		glColor3f(0.7, 0.3, 0);
		desenhaCirculo(0, 0, 0.08);
		if (estado == ATACANDO) {
			glColor3f(1, 1, 1);
			desenhaCirculo(0, 0, 0.05);
			glColor3f(0, 0, 0);
			for (int angulo = 0; angulo < 360; angulo += 45) {
				glPushMatrix();
					glRotatef(angulo, 0, 0, 1);
					desenhaTriangulo(-0.05, 0, 0, 0.01*(1+(tempoEstado/10)%3), 0, -0.01*(1+(tempoEstado/10)%3));
				glPopMatrix();
			}
		}
		else {
			if (estado == COLIDINDO) {
				int numero0a3 = (tempoEstado/5)%4;
				glRotatef(numero0a3 * 90, 0, 0, 1);
			}
			desenhaQuadrilatero(-0.08, 0, 0.08, 0, 0.08, 0.1, -0.08, 0.1);
			desenhaCirculo(0, 0.1, 0.08);
		}
	}
}

void desenhaLekinho (int tempoEstado, Estado estado) {
	if ((estado != INVENCIVEL && estado != RECUPERANDO && estado != PROTEGIDO_E_INVENCIVEL) || (tempoEstado/5)%2) {
		glPushMatrix();
			glRotatef(15*tempoEstado*fatorVelocidade, 1, 0, 0);
		
			glColor3f(1, 0.8, 0.6);
			desenhaQuadrilatero(0.05, 0, 0.07, 0, 0.07, 0.08, 0.05, 0.08); //braço direito
			desenhaCirculo(0.06, 0.08, 0.015);
			
			glColor3f(0, 0, 0.7);
			desenhaQuadrilatero(-0.01, 0, -0.04, 0, -0.04, 0.1, -0.01, 0.1); //perna esquerda
			glColor3f(0.55, 0.27, 0.07);
			desenhaElipse(-0.025, 0.1, 0.02, 0.02);
		glPopMatrix();
		
		glPushMatrix();
			glRotatef(-15*tempoEstado*fatorVelocidade, 1, 0, 0); 
		
			glColor3f(1, 0.8, 0.6);
			desenhaQuadrilatero(-0.05, 0, -0.07, 0, -0.07, -0.08, -0.05, -0.08); //braço esquerdo
			desenhaCirculo(-0.06, -0.08, 0.015);
		
			glColor3f(0, 0, 0.7);
			desenhaQuadrilatero(0.01, 0, 0.04, 0, 0.04, -0.1, 0.01, -0.1); //perna direita
			glColor3f(0.55, 0.27, 0.07);
			desenhaElipse(0.025, -0.1, 0.02, 0.02);
		glPopMatrix();
		
		glColor3f(1, 0, 0);
		desenhaElipse(0, 0, 0.07, 0.03);
		glColor3f(0, 0, 0);
		desenhaCirculo(0, 0, 0.03);
		desenhaTriangulo(-0.015, 0.04, -0.01, 0.07, -0.005, 0.04);
		desenhaTriangulo(-0.005, 0.04, +0.00, 0.07, +0.005, 0.04); 
		desenhaTriangulo(+0.005, 0.04, +0.01, 0.07, +0.015, 0.04);
		glColor3f(1, 1, 1);
		desenhaLinha(-0.01, -0.02, -0.01, 0.02, 1);
		desenhaLinha(0, -0.02, 0, 0.02, 1);
		desenhaLinha(0.01, -0.02, 0.01, 0.02, 1);
	
	}	
	if (estado == PROTEGIDO || estado == PROTEGIDO_E_INVENCIVEL) {
		glLineWidth(5);
		glColor3f(0, 1, 0);
		desenhaCircunferencia(0, 0, 0.1);
		glLineWidth(1);
	}
}

void desenhaEscudo (int tempoEstado) {
	if ((tempoEstado/5)%2) {
		glColor3f(0, 1, 0);
		desenhaQuadrilatero(-0.04, 0.07, 0.04, 0.07, 0.04, 0.11, -0.04, 0.11);
		desenhaQuadrilatero(-0.07, -0.07, 0.07, -0.07, 0.07, 0.07, -0.07, 0.07);
		desenhaTriangulo(-0.07, -0.07, 0, -0.14, 0.07, -0.07);
	}
}

void desenhaInvencibilidade (int tempoEstado) {
	if ((tempoEstado/5)%2) {
		glColor3f(1, 1, 0);
		desenhaQuadrilatero(-0.06, 0.04, 0, 0.04, 0, 0.12, -0.06, 0.12);
		desenhaQuadrilatero(-0.03, -0.04, 0.03, -0.04, 0.03, 0.04, -0.03, 0.04);
		desenhaTriangulo(0, -0.04, 0, -0.15, 0.06, -0.04);
	}
}

void desenhaPontos (int tempoEstado) {
	if ((tempoEstado/5)%2) {
		glColor3f(1, 0, 0);
		desenhaQuadrilatero(-0.15, -0.015, -0.09, -0.015, -0.09, 0.015, -0.15, 0.015);
		desenhaQuadrilatero(-0.13, -0.045, -0.11, -0.045, -0.11, 0.045, -0.13, 0.045);
		
		desenhaQuadrilatero(-0.07,  0.045, -0.01,  0.045, -0.01,  0.075, -0.07,  0.075);
		desenhaQuadrilatero(-0.07, -0.015, -0.05, -0.015, -0.05,  0.075, -0.07,  0.075);
		desenhaQuadrilatero(-0.07, -0.015, -0.01, -0.015, -0.01,  0.015, -0.07,  0.015);
		desenhaQuadrilatero(-0.03, -0.075, -0.01, -0.075, -0.01,  0.015, -0.03,  0.015);
		desenhaQuadrilatero(-0.07, -0.045, -0.01, -0.045, -0.01, -0.075, -0.07, -0.075);
		
		desenhaQuadrilatero(0.01,  0.045, 0.07,  0.045, 0.07,  0.075, 0.01,  0.075);
		desenhaQuadrilatero(0.01, -0.075, 0.03, -0.075, 0.03,  0.075, 0.01,  0.075);
		desenhaQuadrilatero(0.05, -0.075, 0.07, -0.075, 0.07,  0.075, 0.05,  0.075);
		desenhaQuadrilatero(0.01, -0.045, 0.07, -0.045, 0.07, -0.075, 0.01, -0.075);
		
		desenhaQuadrilatero(0.09, 0.045,  0.15, 0.045,  0.15,  0.075, 0.09,  0.075);
		desenhaQuadrilatero(0.09, -0.075, 0.11, -0.075, 0.11,  0.075, 0.09,  0.075);
		desenhaQuadrilatero(0.13, -0.075, 0.15, -0.075, 0.15,  0.075, 0.13,  0.075);
		desenhaQuadrilatero(0.09, -0.045, 0.15, -0.045, 0.15, -0.075, 0.09, -0.075);
	}
}

void desenhaQuadro () {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0, 0, 0, 0.4);
	desenhaQuadrilatero(1/12.0, 1/8.0, 11/12.0, 1/8.0, 11/12.0, 7/8.0, 1/12.0, 7/8.0);
	glDisable(GL_BLEND);
}
