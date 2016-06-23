release: jogo.cpp
	g++ jogo.cpp Elemento.cpp Obstaculo.cpp Bonus.cpp Personagem.cpp Fase.cpp Desenho.cpp -o jogo -lGL -lGLU -lglut
	./jogo
