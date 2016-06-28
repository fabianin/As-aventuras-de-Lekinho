#include "Fase.h"

fstream arquivoPontuacao;

float contadorImagem = HEIGHT;

float fatorVelocidade;	
float tempoPontuacao;
int tempoFase;
bool pausa;
long long int pontuacao;
long long int pontuacaoMaisAlta = 0;
bool fimJogo;
bool sim;
bool moverCenario;
MenuPausa menuPausa;
string imagem;

Personagem *lekinho;
Fase *fase;

GLuint texID;
FILE *textura;

void iniciarJogo () {	
	fatorVelocidade = 0.5;	
	tempoPontuacao = 0;
	tempoFase = 0;
	pausa = false;
	pontuacao = 0;
	fimJogo = false;
	sim = true;
	moverCenario = true;
	menuPausa = CONTINUAR;
	lekinho = new Personagem (LEKINHO, TERRESTRE, TRANSLADANDO, PISTA2, Y_LEKINHO, 0.06*HEIGHT, true, 1);
	fase = new Fase ();
}
	

void init() {
	if (ifstream ("Pontuacao.bin")) {
		arquivoPontuacao.open ("Pontuacao.bin", ios::in | ios::binary);
		arquivoPontuacao >> pontuacaoMaisAlta;
		arquivoPontuacao.close();
	}
      
	srand(time(NULL));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,WIDTH,0,HEIGHT,-100,100);
    
    iniciarJogo();
}

void atualizarPontuacao () {
	float tempoPontuacaoAnterior = tempoPontuacao;
	tempoPontuacao += 8*fatorVelocidade;
	if (TRANSLADOU_50 && pontuacao != 9999999999)
		pontuacao++;
}

void salvarRecord () {
	if (pontuacao > pontuacaoMaisAlta)
		pontuacaoMaisAlta = pontuacao;
	arquivoPontuacao.open ("Pontuacao.bin", ios::out | ios::binary);
	arquivoPontuacao << pontuacaoMaisAlta;
	arquivoPontuacao.close();
}

void idle(){
	if (!pausa && !fimJogo) {
		fase->atualizarObstaculos(fatorVelocidade);
		
		atualizarPontuacao();
		
		fase->atualizarBonus(fatorVelocidade);
		
		if (fase->getChefe())
			fase->getChefe()->atualizar(lekinho->getX(), fatorVelocidade, fase->getChefe(), fase->getObstaculo1(), fase->getObstaculo2(),
										fase->getBonus());
										
		lekinho->atualizar(lekinho->getX(), fatorVelocidade, fase->getChefe(), fase->getObstaculo1(), fase->getObstaculo2(), fase->getBonus());
		if (!lekinho->getVida()) {
			fimJogo = true;
			salvarRecord();
		}
		else {
			if (fase->getObstaculo1()->getY() < Y_FINAL) {
				if (!fase->getChefe())
					if (tempoFase > TEMPO_FASE_MAX) {
						tempoFase = 0;
						fase->iniciarChefe();
					}
				if (fase->getChefe() && !fase->getChefe()->getVida() && fase->getChefe()->getY() < Y_FINAL) {
					moverCenario = false;
					lekinho->setY(lekinho->getY() + 8*fatorVelocidade);
					if (lekinho->getY() > Y_INICIAL) {
						fase->terminarChefe();
						fase = new Fase ();
						lekinho->setY(Y_LEKINHO);
						moverCenario = true;
					}
				}
				else
					fase->renovarObstaculos();
				if (!fase->getChefe())
					fase->renovarBonus();
			}
			fatorVelocidade += INCREMENTO_VELOCIDADE;
			if (!fase->getChefe())
				tempoFase++;
		}
		if (moverCenario)
			contadorImagem -= 8*fatorVelocidade;
		if (contadorImagem < 0)
			contadorImagem = HEIGHT;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char tecla, int x, int y){
	switch(tecla){
		case 'D':
		case 'd':
			if (!pausa && !fimJogo)
				if(lekinho->getX() < PISTA3)
					lekinho->setX(lekinho->getX() + TAM_PISTA);
			break;
		case 'A':
		case 'a':
			if (!pausa && !fimJogo)
				if(lekinho->getX() > PISTA1)
					lekinho->setX(lekinho->getX() - TAM_PISTA);
			break;
		case 's':
		case 'S':
			if (pausa)
				if (menuPausa == CONTINUAR)
					menuPausa = REINICIAR;
				else if (menuPausa == REINICIAR)
					menuPausa = SAIR;
			if (fimJogo && sim)
				sim = !sim;
			break;
		case 'w':
		case 'W':
			if (pausa)
				if (menuPausa == SAIR)
					menuPausa = REINICIAR;
				else if (menuPausa == REINICIAR)
					menuPausa = CONTINUAR;
			if (fimJogo && !sim)
				sim = !sim;
			break;
		case ENTER:
			if (!pausa)
				pausa = true;
			else
				if (menuPausa == CONTINUAR)
					pausa = false;
				else if (menuPausa == REINICIAR) {
					salvarRecord();
					iniciarJogo();
				}
				else if (menuPausa == SAIR) {
					salvarRecord();
					exit(0);
				}
			if (fimJogo)
				if (sim)
					iniciarJogo();
				else
					exit(0);
			break;
		//CHEAT
		case '1':
			fase->iniciarChefe();
			break;
	}
	glutPostRedisplay();
}

void setas (int tecla, int x, int y) {
	switch(tecla){
		case GLUT_KEY_RIGHT:
			if (!pausa && !fimJogo)
				if(lekinho->getX() < PISTA3)
					lekinho->setX(lekinho->getX() + TAM_PISTA);
			break;
		case GLUT_KEY_LEFT:
			if (!pausa && !fimJogo)
				if(lekinho->getX() > PISTA1)
					lekinho->setX(lekinho->getX() - TAM_PISTA);
			break;
		case GLUT_KEY_DOWN:
			if (pausa)
				if (menuPausa == CONTINUAR)
					menuPausa = REINICIAR;
				else if (menuPausa == REINICIAR)
					menuPausa = SAIR;
			if (fimJogo && sim)
				sim = !sim;
			break;
		case GLUT_KEY_UP:
			if (pausa)
				if (menuPausa == SAIR)
					menuPausa = REINICIAR;
				else if (menuPausa == REINICIAR)
					menuPausa = CONTINUAR;
			if (fimJogo && !sim)
				sim = !sim;
			break;
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

string zerosEsquerda (int pontos) {
	string zeros ("");
	int contaAlgarismos = 0;
	if (!pontos)
		contaAlgarismos = 1;
	while (pontos) {
		contaAlgarismos++;
		pontos /= 10;
	}
	for (int i = 0; i < 10 - contaAlgarismos; i++)
		zeros.push_back('0');
	return zeros;
} 

void geraViewportTexto (float xTexto, float yTexto, string texto, void* fonte) {
	glRasterPos2f(xTexto, yTexto);
	for (int i = 0; i < texto.length(); i++){
		glutBitmapCharacter(fonte, texto[i]);
	}
}

void geraViewportPontuacao (float x, float y, float xTexto, string texto, void* fonte, bool imprimirPontos, int pontos = 0) {
	glViewport(x, y, WIDTH/2, 20);
	stringstream ssTexto;
	ssTexto << texto;
	if (imprimirPontos)
		ssTexto << zerosEsquerda(pontos) << pontos;
	string stexto = ssTexto.str();
	geraViewportTexto(xTexto, 0, stexto, fonte);
}

void geraViewportFimJogo () {
	glTranslatef(0, 0, 0);
	desenhaQuadro();
	glViewport(WIDTH/12, HEIGHT/8, 5*WIDTH/6, 3*HEIGHT/4);
	glColor3f(1, 1, 1);
	geraViewportTexto(0.35*WIDTH, 0.8*HEIGHT, "FIM DE JOGO", GLUT_BITMAP_TIMES_ROMAN_24);
	geraViewportTexto(0.32*WIDTH, 0.55*HEIGHT, "Tentar novamente?", GLUT_BITMAP_TIMES_ROMAN_24);
	if (sim)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);
	geraViewportTexto(0.46*WIDTH, 0.35*HEIGHT, "Sim", GLUT_BITMAP_TIMES_ROMAN_24);
	if (!sim)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);
	geraViewportTexto(0.46*WIDTH, 0.15*HEIGHT, "Nao", GLUT_BITMAP_TIMES_ROMAN_24);
}

void geraViewportPausa () {
	glTranslatef(0, 0, 0);
	desenhaQuadro();
	glViewport(WIDTH/12, HEIGHT/8, 5*WIDTH/6, 3*HEIGHT/4);
	glColor3f(1, 1, 1);
	geraViewportTexto(0.43*WIDTH, 0.8*HEIGHT, "PAUSA", GLUT_BITMAP_TIMES_ROMAN_24);
	if (menuPausa == CONTINUAR)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);
	geraViewportTexto(0.41*WIDTH, 0.55*HEIGHT, "Continuar", GLUT_BITMAP_TIMES_ROMAN_24);
	if (menuPausa == REINICIAR)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);
	geraViewportTexto(0.42*WIDTH, 0.35*HEIGHT, "Reiniciar", GLUT_BITMAP_TIMES_ROMAN_24);
	if (menuPausa == SAIR)
		glColor3f(1, 1, 0);
	else
		glColor3f(1, 1, 1);
	geraViewportTexto(0.46*WIDTH, 0.15*HEIGHT, "Sair", GLUT_BITMAP_TIMES_ROMAN_24);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	glViewport(0, 0, WIDTH, HEIGHT);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);
		glTexCoord2i(0,0); glVertex3f(0, 		contadorImagem - HEIGHT, 		0);
		glTexCoord2i(1,0); glVertex3f(WIDTH, 	contadorImagem - HEIGHT,		0);
		glTexCoord2i(1,1); glVertex3f(WIDTH, 	contadorImagem, 0);
		glTexCoord2i(0,1); glVertex3f(0, 		contadorImagem, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture (GL_TEXTURE_2D, texID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);
		glTexCoord2i(0,0); glVertex3f(0, 		contadorImagem, 		0);
		glTexCoord2i(1,0); glVertex3f(WIDTH, 	contadorImagem, 		0);
		glTexCoord2i(1,1); glVertex3f(WIDTH, 	contadorImagem + HEIGHT, 0);
		glTexCoord2i(0,1); glVertex3f(0, 		contadorImagem + HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	atualizarTela (SUBTERRANEO);
	atualizarTela (TERRESTRE);
	atualizarTela (AEREO);

	if (fimJogo)
		geraViewportFimJogo();
	
	if (pausa)
		geraViewportPausa();

	glColor3f(1,1,1);
	geraViewportPontuacao(0, HEIGHT - 20, 10, "PONTUACAO:", GLUT_BITMAP_HELVETICA_18, false);
	geraViewportPontuacao(0, HEIGHT - 45, 10, "", GLUT_BITMAP_TIMES_ROMAN_24, true, pontuacao); 
	geraViewportPontuacao(WIDTH/2, HEIGHT - 20, WIDTH/5, "PONTUACAO MAIS ALTA:", GLUT_BITMAP_HELVETICA_18, false); 
	geraViewportPontuacao(WIDTH/2, HEIGHT - 45, 0.55*WIDTH, "", GLUT_BITMAP_TIMES_ROMAN_24, true, pontuacaoMaisAlta);
	
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
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(setas);
	glutMainLoop();
}
