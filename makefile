release: jogo.cpp
	g++ jogo.cpp Elemento.cpp Obstaculo.cpp Bonus.cpp Personagem.cpp Fase.cpp Desenho.cpp Texture.cpp -o jogo -lGL -lGLU -lglut
	./jogo
