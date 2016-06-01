all: jogo.cpp
	g++ jogo.cpp Elemento.cpp -o jogo -lGL -lGLU -lglut
	./jogo
