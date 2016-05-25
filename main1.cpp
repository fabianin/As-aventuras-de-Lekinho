#include "glm/glm/vec3.hpp" // glm::vec3
#include "glm/glm/vec4.hpp" // glm::vec4
#include "glm/glm/mat4x4.hpp" // glm::mat4
#include "glm/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/glm/gtc/constants.hpp" // glm::pi
#include <GL/glut.h>
#include <bits/stdc++.h>
#define WIDTH 600
#define HEIGHT 400
using namespace std;

enum {ESQUERDA=-1, MEIO=0,DIREITA=1};
int posChar=MEIO;
int moves= 275.;
string str="000000010";
int posYObs=380;


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
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,WIDTH,0,HEIGHT,-100,100);
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
void criaPistas(){
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
}

void idle(){
	posYObs-=8;
	stringstream sstr;
	int a;
	sstr.clear();
	sstr << str;
	sstr >> a;
	a++;
	sstr << a;
	str.clear();
	str = sstr.str();
	if(posYObs<10){
		posYObs=380;
		pistaAleatoria=rand()%30;
		if(pistaAleatoria<10){
			pista=90;
		}
		else if(pistaAleatoria<20 ){
			pista=290;
		}
		else if(pistaAleatoria<30){
			pista=490;
		}
	}
	glutPostRedisplay();

}

void keyboard(unsigned char tecla, int x, int y){
		x=0;
		y=0;
		switch(tecla){
				case 'd': if(moves <400){
								  moves+=200;
						  }
						  break;
				case 'a': if(moves >80){
								  moves-=200;
						  }
						  break;
				default: break;
		}
	glutPostRedisplay();
}
void display(){
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
			criaPistas();
			print(490,380,str);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(moves,0,0);
			drawQuad();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(pista,posYObs,0);
			drawBlock();
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
