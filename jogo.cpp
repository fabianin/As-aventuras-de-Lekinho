#include "Fase.h"

string str="000000010";
float fatorVelocidade = 0.5;
int tempoFase = 0;

Personagem *lekinho;
Fase *fase; 

void init() {
        
	srand(time(NULL));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,WIDTH,0,HEIGHT,-100,100);
    
	lekinho = new Personagem (LEKINHO, TERRESTRE, TRANSLADANDO, PISTA2, Y_LEKINHO, 0.06*HEIGHT, true, 1);
	fase = new Fase (); 
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
}

void idle(){
	/*stringstream sstr;
	int a;
	sstr.clear();
	sstr << str;
	sstr >> a;
	a++;
	sstr << a;
	str.clear();
	str = sstr.str();*/
	fase->atualizarObstaculos(fatorVelocidade);
	fase->atualizarBonus(fatorVelocidade);
	if (fase->getChefe())
		fase->getChefe()->atualizar(lekinho->getX(), fatorVelocidade, fase->getChefe(), fase->getObstaculo1(), fase->getObstaculo2(),
									fase->getBonus());
	lekinho->atualizar(lekinho->getX(), fatorVelocidade, fase->getChefe(), fase->getObstaculo1(), fase->getObstaculo2(), fase->getBonus());
	if (fase->getObstaculo1()->getY() < Y_FINAL) {
		if (!fase->getChefe())
			if (tempoFase > TEMPO_FASE_MAX) {
				tempoFase = 0;
				fase->iniciarChefe();
			}
		if (fase->getChefe() && !fase->getChefe()->getVida()) {
			lekinho->setY(lekinho->getY() + 8*fatorVelocidade);
			if (lekinho->getY() > Y_INICIAL) {
				fase->terminarChefe();
				fase = new Fase ();
				lekinho->setY(Y_LEKINHO);
			}
		}
		else
			fase->renovarObstaculos();
		if (!fase->getChefe())
			fase->renovarBonus();
	}
	fatorVelocidade+=0.0000001;
	if (!fase->getChefe())
		tempoFase++;
	glutPostRedisplay();
}

void keyboard(unsigned char tecla, int x, int y){
	switch(tecla){
		case 'd':
			if(lekinho->getX() < PISTA3)
				lekinho->setX(lekinho->getX() + TAM_PISTA);
			break;
		case 'a':
			if(lekinho->getX() > PISTA1)
				lekinho->setX(lekinho->getX() - TAM_PISTA);
			break;
			
		//TESTE - APAGAR: apertar 1 para fase de floresta, 2 para fase de gelo e 3 para fase de deserto
		case '1':
			fase->iniciarChefe();
			break;
		//
	}
	glutPostRedisplay();
}

void desenha (Elemento* elemento, Caracteristica caracteristica) {
	if (elemento && elemento->getCaracteristica() == caracteristica)
		elemento->desenha();
}

void atualizarTela (Caracteristica caracteristica) {
	desenha(fase->getObstaculo1()->getProjetil(), caracteristica);
	desenha(fase->getObstaculo1(), caracteristica);
	desenha(fase->getObstaculo2(), caracteristica);
	desenha(fase->getBonus(), caracteristica);
	if (fase->getChefe()) {
		desenha(fase->getChefe()->getProjetil(), caracteristica);
		desenha(fase->getChefe(), caracteristica);
	}
	desenha(lekinho, caracteristica);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		print(490,380,str);
	glPopMatrix();
	
	
	atualizarTela (SUBTERRANEO);
	atualizarTela (TERRESTRE);
	atualizarTela (AEREO);

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
