/*#include "glm/glm/vec3.hpp" // glm::vec3
#include "glm/glm/vec4.hpp" // glm::vec4
#include "glm/glm/mat4x4.hpp" // glm::mat4
#include "glm/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/glm/gtc/constants.hpp" // glm::pi*/

#include "Elemento.h"
#include <GL/glut.h>
using namespace std;

enum {ESQUERDA=-1, MEIO=0,DIREITA=1};
int posChar=MEIO;
int moves= WIDTH/2.0;
string str="000000010";
int posYObs=380;

//****MODELAGEM - INÍCIO****
#define ESC 27
#define DEG2RAD 3.14159/180.0
#define X_LEKINHO 50

float escala = 0;

bool efeito = false;
int efeitoMinhoca = 0;

int theta = 0, incremento = -10; 

void desenhaElipse (GLfloat x, GLfloat y, float radiusX, float radiusY)
{
   int i;
 
   glBegin(GL_POLYGON);
 
   for(i=0;i<360;i++)
   {
      float rad = i*DEG2RAD;
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

void desenhaBonecoDeNeve () {
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
}

void desenhaUrso () {
	glColor3f(0.9, 0.9, 0.9);
	desenhaQuadrilatero(0.4, 0.375, 0.6, 0.375, 0.6, 0.625, 0.4, 0.625);
	desenhaCirculo(0.5, 0.625, 0.1);
	desenhaCirculo(0.5, 0.775, 0.02);
	desenhaElipse((13/30.0), 0.375, (1/30.0), 0.125);
	desenhaElipse((17/30.0), 0.375, (1/30.0), 0.125);
	
	glColor3f(1, 1, 1);
	desenhaCirculo(0.5, 0.4, 0.06);
	desenhaCirculo(0.55, 0.45, 0.02);
	desenhaCirculo(0.45, 0.45, 0.02);
	desenhaElipse(0.5, 0.33, 0.03, 0.0675);
	
	glColor3f(0, 0, 0);
	desenhaTriangulo(0.485, 0.29, 0.515, 0.29, 0.5, 0.27);
	desenhaLinha(0.47, 0.35, 0.49, 0.35, 1);
	desenhaLinha(0.53, 0.35, 0.51, 0.35, 1);
}

void desenhaGeloTrincado () {
	glColor3f(0, 0, 1);
	desenhaLinha(0.50, 0.50, 0.55, 0.45, 1);
	desenhaLinha(0.55, 0.45, 0.55, 0.40, 1);
	
	desenhaLinha(0.50, 0.50, 0.47, 0.45, 1);
	desenhaLinha(0.47, 0.45, 0.43, 0.44, 1);
	
	desenhaLinha(0.50, 0.50, 0.45, 0.50, 1);
	desenhaLinha(0.45, 0.50, 0.40, 0.55, 1);
	
	desenhaLinha(0.50, 0.50, 0.50, 0.55, 1);
	desenhaLinha(0.50, 0.55, 0.47, 0.60, 1);
	
	desenhaLinha(0.50, 0.50, 0.55, 0.53, 1);
	desenhaLinha(0.55, 0.53, 0.59, 0.53, 1);
}

void desenhaGeloQuebrado () {
	//desenhaGeloTrincado();
	
	int escala = 1; //apenas teste
	glColor3f(0, 0, 1); //apenas teste
	
	glBegin(GL_POLYGON);
		glVertex2f((0.5-0.1*escala)*WIDTH, (0.5+0.1*escala)*HEIGHT);
		glVertex2f((0.5-0.05*escala)*WIDTH, (0.5+0.16*escala)*HEIGHT);
		glVertex2f((0.5-0.03*escala)*WIDTH, (0.5+0.2*escala)*HEIGHT);
		glVertex2f(0.5*WIDTH, (0.5+0.13*escala)*HEIGHT);
		glVertex2f((0.5+0.06*escala)*WIDTH, (0.5+0.13*escala)*HEIGHT);
		glVertex2f((0.5+0.07*escala)*WIDTH, (0.5+0.15*escala)*HEIGHT);
		glVertex2f((0.5+0.09*escala)*WIDTH, (0.5+0.12*escala)*HEIGHT);
		glVertex2f((0.5+0.07*escala)*WIDTH, (0.5+0.09*escala)*HEIGHT);
		glVertex2f((0.5+0.11*escala)*WIDTH, (0.5+0.05*escala)*HEIGHT);
		glVertex2f((0.5+0.1*escala)*WIDTH, (0.5+0.02*escala)*HEIGHT);
		glVertex2f((0.5+0.15*escala)*WIDTH, 0.5*HEIGHT);
		glVertex2f((0.5+0.09*escala)*WIDTH, (0.5-0.11*escala)*HEIGHT);
		glVertex2f((0.5+0.09*escala)*WIDTH, (0.5-0.12*escala)*HEIGHT);
		glVertex2f((0.5+0.07*escala)*WIDTH, (0.5-0.13*escala)*HEIGHT);
		glVertex2f((0.5+0.05*escala)*WIDTH, (0.5-0.2*escala)*HEIGHT);
		glVertex2f((0.5+0.05*escala)*WIDTH, (0.5-0.16*escala)*HEIGHT);
		glVertex2f(0.5*WIDTH, (0.5-0.18*escala)*HEIGHT);
		glVertex2f((0.5-0.05*escala)*WIDTH, (0.5-0.13*escala)*HEIGHT);
		glVertex2f((0.5-0.05*escala)*WIDTH, (0.5-0.07*escala)*HEIGHT);
		glVertex2f((0.5-0.1*escala)*WIDTH, (0.5-0.04*escala)*HEIGHT);
	glEnd();
	
	if (escala < 1)
		escala += 0.1;
	cout << escala << endl;
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
	desenhaIceberg(0.35, 0.5, 0.5, 0.65, 0.65, 0.5, 0.5, 0.35);
	desenhaIceberg(0.55, 0.65, 0.6, 0.7, 0.65, 0.65, 0.6, 0.6);
	desenhaIceberg(0.35, 0.65, 0.4, 0.7, 0.45, 0.65, 0.4, 0.6);
}

void desenhaLeaoMarinho () {
	desenhaGeloQuebrado();
	
	glColor3f(0.55, 0.27, 0.07);
	desenhaElipse(0.5, 0.5, 0.15, 0.075);
	desenhaCirculo(0.5, 0.5, 0.08);
	
	glColor3f(1, 1, 1);
	desenhaLinha(0.45, 0.43, 0.55, 0.43, 1);
	desenhaLinha(0.45, 0.42, 0.55, 0.42, 1);
	desenhaLinha(0.45, 0.41, 0.55, 0.41, 1);
	
	glColor3f(0.65, 0.37, 0.17);
	desenhaCirculo(0.49, 0.44, 0.03);
	desenhaCirculo(0.51, 0.44, 0.03);
	desenhaCirculo(0.5, 0.5, 0.05);
	
	glColor3f(0, 0, 0);
	desenhaElipse(0.50, 0.395, 0.005, 0.0045);
	desenhaElipse(0.54, 0.45, 0.003, 0.0075);
	desenhaElipse(0.46, 0.45, 0.003, 0.0075);
}

void desenhaToco () {
	glColor3f(0.4, 0.27, 0.07);
	desenhaQuadrilatero(0.47, 0.53, 0.63, 0.66, 0.53, 0.47, 0.37, 0.34);
	desenhaQuadrilatero(0.47, 0.47, 0.63, 0.34, 0.53, 0.53, 0.37, 0.66);
	glColor3f(0.55, 0.27, 0.07);
	desenhaCirculo(0.5, 0.5, 0.08);
	glColor3f(0.65, 0.65, 0.15);
	desenhaCirculo(0.5, 0.5, 0.07);
	glColor3f(0.55, 0.27, 0.07);
	desenhaCircunferencia(0.5, 0.5, 0.06);
	desenhaCircunferencia(0.5, 0.5, 0.04);
	desenhaCircunferencia(0.5, 0.5, 0.02);
}

void desenhaSapo () {
	glColor3f(0, 0.2, 0);
	desenhaElipse(0.54, 0.57, 0.02, 0.06);
	desenhaElipse(0.46, 0.57, 0.02, 0.06);
	
	glColor3f(0, 0.4, 0);
	desenhaElipse(0.54, 0.48, 0.02, 0.06);
	desenhaElipse(0.46, 0.48, 0.02, 0.06);
	desenhaCirculo(0.435, 0.38, 0.005);
	desenhaCirculo(0.460, 0.38, 0.005);
	desenhaCirculo(0.485, 0.38, 0.005);
	desenhaCirculo(0.505, 0.38, 0.005);
	desenhaCirculo(0.540, 0.38, 0.005);
	desenhaCirculo(0.565, 0.38, 0.005);
	desenhaTriangulo(0.46, 0.48, 0.43, 0.38, 0.49, 0.38);
	desenhaTriangulo(0.54, 0.48, 0.51, 0.38, 0.57, 0.38);
	
	glColor3f(0, 0.6, 0);
	desenhaElipse(0.5, 0.5, 0.05, 0.15);
	
	glColor3f(0, 0.4, 0);
	desenhaElipse(0.48, 0.436, 0.015, 0.015);
	desenhaElipse(0.52, 0.436, 0.015, 0.015);
	glColor3f(0, 0, 0);
	desenhaElipse(0.48, 0.43, 0.01, 0.0075);
	desenhaElipse(0.52, 0.43, 0.01, 0.0075);
	
	desenhaPonto(0.495, 0.36);
	desenhaPonto(0.505, 0.36);
	desenhaPonto(0.49, 0.52);
	desenhaPonto(0.51, 0.52);
	desenhaPonto(0.49, 0.54);
	desenhaPonto(0.51, 0.54);
	desenhaPonto(0.49, 0.56);
	desenhaPonto(0.51, 0.56);
}

void desenhaPlantaCarnivora () {
	glColor3f(0, 0.3, 0);
	desenhaElipse(0.43, 0.5, 0.07, 0.075);
	desenhaElipse(0.57, 0.5, 0.07, 0.075); 
	
	glColor3f(0, 0.6, 0);
	desenhaCirculo(0.5, 0.5, 0.07);
	
	if (!efeito) {
		glColor3f(0.5, 0.7, 0.5);
		desenhaElipse(0.5, 0.42, 0.06, 0.025);
	}
	else {
		glColor3f(0.5, 0.7, 0.5);
		desenhaElipse(0.5, 0.43, 0.06, 0.045);
		glColor3f(0, 0, 0);
		desenhaElipse(0.5, 0.42, 0.045, 0.035);
		glColor3f(0.5, 0.7, 0.5);
		desenhaTriangulo(0.488, 0.465, 0.500, 0.41, 0.512, 0.465);
		desenhaTriangulo(0.464, 0.465, 0.476, 0.41, 0.488, 0.465);
		desenhaTriangulo(0.512, 0.465, 0.524, 0.41, 0.536, 0.465); 
	}
}

void desenhaMinhoca () {
	glColor3f(0, 0, 0);
	desenhaQuadrilatero(0.4, 0.4, 0.4, 0.61, 0.6, 0.61, 0.6, 0.4);
	for (float i = 0.4; i <= 0.61; i += 0.03)
		for (float j = 0.4; j <= 0.6; j += 0.02) {
			glColor3f(0.5, 0.2, 0.1);
			desenhaCirculo(j, i, 0.01);
			glColor3f(0, 0, 0);
			desenhaCircunferencia(j, i, 0.01);
		}
	if (efeitoMinhoca % 3) {
		desenhaCirculo(0.5, 0.5, 0.06);
		glColor3f(1, 0.8, 0.8);
		desenhaCirculo(0.5, 0.5, 0.04);
		if (efeitoMinhoca % 3 == 1) {
			for (float i = 0.35; i <= 0.65; i += 0.3)
				for (float j = 0.35; j <= 0.65; j += 0.3) {
					glColor3f(0.5, 0.2, 0.1);
					desenhaCirculo(j, i, 0.01);
					glColor3f(0, 0, 0);
					desenhaCircunferencia(j, i, 0.01);
				}
		}
		else {
			desenhaQuadrilatero(0.46, 0.5, 0.54, 0.5, 0.54, 0.39, 0.46, 0.39);
			desenhaCirculo(0.5, 0.39, 0.04);
			glColor3f(1, 0, 0);
			desenhaLinha(0.46, 0.50, 0.54, 0.50, 2);
			desenhaLinha(0.46, 0.45, 0.54, 0.45, 2);
			desenhaLinha(0.46, 0.40, 0.54, 0.40, 2);
		}
	}
}

void desenhaAreiaMovedica () {
	glColor3f(0.7, 0.6, 0);
	desenhaCirculo(0, 0, 0.1);
	
	float aux = 0.09;
	if ((theta / incremento) % 2) aux = 0.08;
	
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

void desenhaLekinho () {
	glPushMatrix();
		glRotatef(theta, 1, 0, 0);
	
		glColor3f(1, 0.8, 0.6);
		desenhaQuadrilatero(0.05, 0, 0.07, 0, 0.07, 0.08, 0.05, 0.08); //braço direito
		desenhaCirculo(0.06, 0.08, 0.015);
		
		glColor3f(0, 0, 0.7);
		desenhaQuadrilatero(-0.01, 0, -0.04, 0, -0.04, 0.1, -0.01, 0.1); //perna esquerda
		glColor3f(0.55, 0.27, 0.07);
		desenhaElipse(-0.025, 0.1, 0.02, 0.02);
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(-theta, 1, 0, 0); 
	
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
//****MODELAGEM - FIM****

Elemento lekinho (desenhaLekinho, 0.06*HEIGHT);

Elemento areiaMovedica (desenhaAreiaMovedica, 0.2*WIDTH);
Elemento cobra (desenhaCobra, 0.2*WIDTH);
Elemento cacto (desenhaCacto, 0.1*WIDTH);
Elemento lagarto (desenhaLagarto, 0.05*HEIGHT); 
Elemento deserto[4] = {areiaMovedica, cobra, cacto, lagarto};

Elemento obs = deserto[rand() % 4];

int pistaAleatoria;
int pista=290;
void drawBlock(){
		glPushMatrix();
			glColor3f(1,0,1);
			glBegin(GL_POLYGON);
				glVertex2f(0,0);
				glVertex2f(20,0);
				glVertex2f(20,20);
				glVertex2f(0,20);
			glEnd();
		glPopMatrix();
		glutSwapBuffers();
}


void init(){
    
    srand(time(NULL));
    glClearColor(0.75, 0.65, 0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,WIDTH,0,HEIGHT,-100,100);
    
    lekinho.setX(WIDTH / 2.0);
    lekinho.setY(X_LEKINHO);
    
    obs.setX((1 + 2*(rand()%3)) * WIDTH/6.0);
	obs.setY(HEIGHT + 100);
}

void drawQuad(){
		glPushMatrix();
			glColor3f(1,0,0);
			glBegin(GL_POLYGON);
				glVertex2f(0,0);
				glVertex2f(50,0);
				glVertex2f(50,50);
				glVertex2f(0,50);
			glEnd();
		glPopMatrix();
//		glutSwapBuffers();
}


void print(int x, int y, string& string){
	glPushMatrix();
		glColor3f(1,1,0);
		glRasterPos2f(x,y);
		int len = (int) string.size();
		for (int i = 0; i < len; i++){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
		}
	glPopMatrix();
//	glutSwapBuffers();
}
/*void criaPistas(){
    glPushMatrix();
        glColor3f(0.0,1.0,0.0);
        glBegin(GL_LINES);
            glVertex2f(200.,0);
            glVertex2f(200.,HEIGHT);
        glEnd();
        glBegin(GL_LINES);
            glVertex2f(400.,0.);
            glVertex2f(400.,HEIGHT);
        glEnd();
    glPopMatrix();
//    glutSwapBuffers();
}*/

void idle(){
	obs.setY(obs.getY()-8);
	stringstream sstr;
	int a;
	sstr.clear();
	sstr << str;
	sstr >> a;
	a++;
	sstr << a;
	str.clear();
	str = sstr.str();
	if (obs.yInferior() < lekinho.ySuperior() && obs.ySuperior() > lekinho.ySuperior())
		if (obs.getX() == lekinho.getX())
			exit(0);
	if (obs.getY() < -100){
		obs = deserto[rand() % 4];
		obs.setX((1 + 2*(rand()%3)) * WIDTH/6.0);
		obs.setY(HEIGHT + 100);
	}
	theta += incremento;
	if (theta == 0)
		incremento = -10;
	if (theta == 180)
		incremento = 10;
	glutPostRedisplay();

}

void keyboard(unsigned char tecla, int x, int y){
	switch(tecla){
		case 'd':
			if(lekinho.getX() < 2*WIDTH/3.0)
				lekinho.setX(lekinho.getX() + WIDTH/3.0);
			break;
		case 'a':
			if(lekinho.getX() > WIDTH/3.0)
				lekinho.setX(lekinho.getX() - WIDTH/3.0);
			break;
	}
	glutPostRedisplay();
}

void display(){
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
			//criaPistas();
			print(490,380,str);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(obs.getX(), obs.getY(), 0);
			//drawBlock();
			obs.desenha()();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(lekinho.getX(), lekinho.getY(), 0);
			//drawQuad();
			lekinho.desenha()();
		glPopMatrix();
		glutSwapBuffers();

}
int main(int argc,char** argv){
		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(250,200);
		glutInitWindowSize(WIDTH,HEIGHT);
		glutCreateWindow("As aventuras de Lekinho");
		init();
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		glutIdleFunc(idle);
		glutMainLoop();

}
