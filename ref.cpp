#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define w 400
#define h 400

int rot=0;
int frente;
int back;
int rodPa;

void ground(){
		glColor3f(0,1,0);
		glPushMatrix();
			glTranslatef(-250,-250,0);
			glBegin(GL_POLYGON);
				glVertex2f(0,0);
				glVertex2f(0,250);
				glVertex2f(500,250);
				glVertex2f(500,0);
			glEnd();
		glPopMatrix();
		glutSwapBuffers();

}

void drawWheels(int posX, int posY, float radius, int num_seg){
		glColor3f(0.439215686,0.501960784,0.564705882);
		glBegin(GL_POLYGON);
			for(int ii=0;ii<num_seg;ii++){
					float angle = 2.0f*M_PI*float(ii)/float(num_seg);
					float xx=radius*cosf(angle);
					float yy=radius*sinf(angle);
					glVertex2f(posX+xx,posY+yy);
			}
		glEnd();
		glutSwapBuffers();
}

void keyboard(unsigned char tecla, int x, int y){
		switch(tecla){
				case 'd': rot-=2;
						  frente+=3;
						  break;
				case 'a': rot+=2;
						  frente-=3;
						  break;
				case 'i': rodPa+=1;
						  break;
				case 'j': rodPa-=1;
					  		break;
				default: exit(0);
		}
		glutPostRedisplay();
}

void pa(){
		glBegin(GL_POLYGON);
			glVertex2f(0,0);
			glVertex2f(50,-30);
			glVertex2f(50,-50);
		glEnd();
		glutSwapBuffers();
}

void tractor(void){
		glColor3f(1,1,0);
		glPushMatrix();
			glTranslatef(-250,15,0);	
			glBegin(GL_POLYGON);
				glVertex2f(0,40);
				glVertex2f(20,40);
				glVertex2f(30,60);
				glVertex2f(40,40);
				glVertex2f(60,20);
				glVertex2f(60,40);
				glVertex2f(120,40);
				glVertex2f(120,0);
				glVertex2f(50,0);
				glVertex2f(50,20);
				glVertex2f(40,30);
				glVertex2f(0,30);
			glEnd();
		glPopMatrix();
		glutSwapBuffers();
}

void display(){
		glClear(GL_COLOR_BUFFER_BIT);
		ground();
		glPushMatrix();
			glTranslatef(frente,0,0);
			tractor();
			glPushMatrix();
				glTranslatef(-130,50,0);
				glRotatef(rodPa,0,0,1);
				pa();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-225,20,0);
				glRotatef(rot,0,0,1);
				drawWheels(0,0,30,10);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-165,15,0);
				glRotatef(2*rot,0,0,1);
				drawWheels(0,0,15,7);
			glPopMatrix();
		glPopMatrix();
}
void init(){
		glClearColor(0.0,0.0,0.0,0.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-250,250,
				-250,250,
				100,-100);
}
int main(int argc, char** argv){
		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(250,50);
		glutInitWindowSize(w,h);
		glutCreateWindow("Trator");
		init();
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		glutMainLoop();
}

