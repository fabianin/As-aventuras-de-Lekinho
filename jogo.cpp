#include "Obstaculo.h"
#include "Personagem.h"
#include "Fase.h"

string str="000000010";
float fatorVelocidade = 0.5;

Personagem *lekinho;
Fase *fase;

void init() {
        
	srand(time(NULL));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,WIDTH,0,HEIGHT,-100,100);
    
	lekinho = new Personagem (LEKINHO, TERRESTRE, PISTA2, Y_LEKINHO, 0.06*HEIGHT, true, 1);
	fase = new Fase (FLORESTA); //TESTE INICIANDO COM FLORESTA
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

bool colide (Elemento* elemento1, Elemento* elemento2) {
	return 	elemento1 != NULL &&
			elemento2 != NULL &&
			elemento1->podeColidir() &&
			elemento2->podeColidir() &&
			elemento2->yInferior() < elemento1->ySuperior() &&
			elemento2->ySuperior() > elemento1->yInferior() &&
			elemento1->getX() == elemento2->getX();
}	

bool lekinhoAtingido () {
	return 	colide(lekinho, fase->getObstaculo1()) ||
			colide(lekinho, fase->getObstaculo1()->getProjetil()) ||
			colide(lekinho, fase->getObstaculo2()) ||
			(fase->IsEmChefe() && colide(lekinho, fase->getChefe()) ||
			(fase->IsEmChefe() && fase->getChefe()->getProjetil() && colide(lekinho, fase->getChefe()->getProjetil())));
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
	if (fase->IsEmChefe()) {
		fase->getChefe()->atualizar(lekinho->getX(), fatorVelocidade);
		if (colide(fase->getChefe(), fase->getObstaculo1())) {
			if (!fase->getChefe()->IsEmColisao()) {
				fase->getChefe()->setEmColisao(true);
				fase->getObstaculo1()->setEmColisao(true);
				fase->getChefe()->decrementaVida();
				cout << fase->getChefe()->getVida() << endl;
			}
		}
		else {
			fase->getChefe()->setEmColisao(false);
			fase->getObstaculo1()->setEmColisao(false);
			if (!fase->getChefe()->getVida())
				fase->setEmChefe(false);
		}
	}
	if (lekinhoAtingido())
		exit(0);	
	if (fase->getObstaculo1()->getY() < Y_FINAL)
		fase->renovarObstaculos();
	fatorVelocidade+=0.0000001;
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
			fase = new Fase (FLORESTA);
			break;
		case '2':
			fase = new Fase (GELO);
			break;
		case '3':
			fase = new Fase (DESERTO);
			break;
		case '4':
			fase->setEmChefe(true);
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
	if (fase->IsEmChefe()) {
		desenha(fase->getChefe(), caracteristica);
		desenha(fase->getChefe()->getProjetil(), caracteristica);
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
