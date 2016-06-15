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
	desenhaElipse(x, y, radius, radius*WIDTH/400.0);
}

void desenhaCircunferencia (GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * M_PI;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
				(x + (radius * cos(i *  twicePi / lineAmount)))*WIDTH, 
				y*HEIGHT + (radius * sin(i * twicePi / lineAmount) * WIDTH)
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

/*void desenhaBonecoDeNeve () {
	glColor3f(0.95, 0.95, 1);
	desenhaCirculo(300.0/HEIGHT, 200.0/HEIGHT, 120.0/WIDTH); //bola inferior
	
	glColor3f(0.9, 0.9, 1);
	desenhaCirculo(300/WIDTH, 220/HEIGHT, 94/WIDTH); //bola central
	
	glColor3f(0.85, 0.85, 1);
	desenhaCirculo(300/WIDTH, 240/HEIGHT, 60/WIDTH); //bola superior
	
	glColor3f(0, 0, 0);
	desenhaElipse(300/WIDTH, 260/HEIGHT, 60/WIDTH, 40/WIDTH); //cartola
	desenhaElipse(300/WIDTH, 300/HEIGHT, 40/WIDTH, 28/WIDTH);
	
	desenhaTriangulo(265/WIDTH, 200/HEIGHT, 283/WIDTH, 200, 265/WIDTH, 212/HEIGHT); //olhos
	desenhaTriangulo(335/WIDTH, 200/HEIGHT, 317/WIDTH, 200, 335/WIDTH, 212/HEIGHT);
	
	desenhaLinha(394/WIDTH, 220/HEIGHT, 394/WIDTH, 120/HEIGHT, 5); //braços
	desenhaLinha(394/WIDTH, 120/HEIGHT, 300/WIDTH, 80/HEIGHT, 5);
	desenhaLinha(206/WIDTH, 220/HEIGHT, 206/WIDTH, 120/HEIGHT, 5);
	desenhaLinha(206/WIDTH, 120/HEIGHT, 300/WIDTH, 40/HEIGHT, 5);
	
	glColor3f(0.44, 0.126, 0.919); //arma
	desenhaQuadrilatero(265/WIDTH, 20/HEIGHT, 335/WIDTH, 20/HEIGHT, 335/WIDTH, 80/HEIGHT, 265/WIDTH, 80/HEIGHT);
	desenhaQuadrilatero(265/WIDTH, 80/HEIGHT, 285/WIDTH, 120/HEIGHT, 315/WIDTH, 120/HEIGHT, 335/WIDTH, 80/HEIGHT);
	glColor3f(1, 0.5, 0);
	desenhaQuadrilatero(291/WIDTH, 40/HEIGHT, 291/WIDTH, 100/HEIGHT, 309/WIDTH, 100/HEIGHT, 309/WIDTH, 40/HEIGHT);
	desenhaElipse(300/WIDTH, 16/HEIGHT, 48/WIDTH, 16/WIDTH);
	glColor3f(0, 0, 0);
	desenhaElipse(300/WIDTH, 12, 40/WIDTH, 8/WIDTH);
		
	glColor3f(1, 0.5, 0);
	desenhaTriangulo(288/WIDTH, 188/HEIGHT, 312/WIDTH, 188/HEIGHT, 300/WIDTH, 120/HEIGHT); //nariz
}*/

void desenhaGeloTrincado () {
	glColor3f(0, 0, 1);
	desenhaLinha(0.00,  0.00, 0.05, -0.05, 1);
	desenhaLinha(0.05, -0.05, 0.05, -0.10, 1);
	
	desenhaLinha(0.00,   0.00, -0.03, -0.05, 1);
	desenhaLinha(-0.03, -0.05, -0.07, -0.06, 1);
	
	desenhaLinha(0.00,  0.00, -0.05, 0.00, 1);
	desenhaLinha(-0.05, 0.00, -0.10, 0.05, 1);
	
	desenhaLinha(0.00, 0.00,  0.00, 0.05, 1);
	desenhaLinha(0.00, 0.05, -0.03, 0.10, 1);
	
	desenhaLinha(0.00, 0.00, 0.05, 0.03, 1);
	desenhaLinha(0.05, 0.03, 0.09, 0.03, 1);
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

void desenhaGeloQuebrado (int ciclo) {
	if (ciclo < 45)	
		desenhaGeloTrincado();
	else
		desenhaAgua();
}

void desenhaIceberg (float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	glColor3f(0.94, 0.94, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x1, y1, x4, y4);
	glColor3f(0.86, 0.86, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x3, y3, x4, y4);
	glColor3f(0.78, 0.78, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x1, y1, x2, y2);
	glColor3f(0.7, 0.7, 1);
	desenhaTriangulo(0.5*(x1+x3), 0.5*(y2+y4), x2, y2, x3, y3);
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

void desenhaPlantaCarnivora (int ciclo) {
	glColor3f(0, 0.3, 0);
	desenhaElipse(-0.07, 0, 0.07, 0.075);
	desenhaElipse( 0.07, 0, 0.07, 0.075); 
	
	glColor3f(0, 0.6, 0);
	desenhaCirculo(0, 0, 0.07);
	
	bool aplicarEfeito = (ciclo/5)%2 != 0;
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
		desenhaTriangulo(-0.024, -0.035, -0.024, -0.09, -0.012, -0.035);
		desenhaTriangulo( 0.012, -0.035,  0.024, -0.09,  0.036, -0.035); 
	}
}

void desenhaMinhoca (int ciclo) {
	desenhaTerra();

	if (ciclo > 45) {
		desenhaCirculo(0, 0, 0.06);
		glColor3f(1, 0.8, 0.8);
		desenhaCirculo(0, 0, 0.04);
		
		if (ciclo < 50) 
			for (float i = -0.15; i <= 0.15; i += 0.3)
				for (float j = -0.15; j <= 0.15; j += 0.3) {
					glColor3f(0.5, 0.2, 0.1);
					desenhaCirculo(j, i, 0.01);
					glColor3f(0, 0, 0);
					desenhaCircunferencia(j, i, 0.01);
				}
		else {
			glPushMatrix();
				int numero0a3 = (ciclo/10)%4;
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

void desenhaAreiaMovedica (int ciclo) {
	glColor3f(0.7, 0.6, 0);
	desenhaCirculo(0, 0, 0.1);
	
	float aux = 0.09;
	bool aplicarEfeito = (ciclo/5)%2 != 0;
	if (aplicarEfeito)
		aux = 0.08;
	
	glColor3f(0.5, 0.2, 0);
	for (float i = aux; i > 0; i -= 0.02) 
		desenhaCircunferencia(0, 0, i);
}

void desenhaCacto () {
	glColor3f(0, 0.4, 0);
	desenhaQuadrilatero(-0.1, 0.03, 0.1, 0.03, 0.1, -0.03, -0.1, -0.03);
	
	glColor3f(0, 0.6, 0);
	desenhaCirculo(0, 0, 0.05);
	desenhaCirculo(-0.1, 0, 0.03);
	desenhaCirculo(0.1, 0, 0.03);
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

void desenhaLagarto () {
	/*if (efeito) {
		glColor3f(1, 0, 0);
		desenhaLinha(0, 0, -0.4, 0, 7);
	}*/
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

void desenhaLekinho (/*int anguloMovimento*/) {
	glPushMatrix();
		//glRotatef(anguloMovimento, 1, 0, 0);
	
		glColor3f(1, 0.8, 0.6);
		desenhaQuadrilatero(0.05, 0, 0.07, 0, 0.07, 0.08, 0.05, 0.08); //braço direito
		desenhaCirculo(0.06, 0.08, 0.015);
		
		glColor3f(0, 0, 0.7);
		desenhaQuadrilatero(-0.01, 0, -0.04, 0, -0.04, 0.1, -0.01, 0.1); //perna esquerda
		glColor3f(0.55, 0.27, 0.07);
		desenhaElipse(-0.025, 0.1, 0.02, 0.02);
	glPopMatrix();
	
	glPushMatrix();
		//glRotatef(-anguloMovimento, 1, 0, 0); 
	
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
