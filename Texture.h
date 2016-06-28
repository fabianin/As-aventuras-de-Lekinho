//OpenGL Libs
#if defined __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif

//General Libs
#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;

class Texture{
	private:
		FILE *file;
        	GLuint textureID;
	public:
		Texture( FILE *fp );
		~Texture( void );
		void setTexFile( FILE *fp ) { file = fp; }
		void setTexID( void ) { textureID = loadBMP_custom(); }
		GLuint getTexID( void ) { return textureID; }
		GLuint loadBMP_custom( void );
};
