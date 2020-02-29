#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include "GameOfLife.h"
#include "ConfigFile.h"

#include <iostream>

#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

// values are read from "game.config"
GLint FPS = 24;
GLint window_width = 600;
GLint window_height = 600;
GLfloat left = 0.0;
GLfloat right = 1.0;
GLfloat bottom = 0.0;
GLfloat top = 1.0;
GLint game_width = 100;
GLint game_height = 100;

GameOfLife *game;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
    GLfloat xSize = (right - left) / game_width;
	GLfloat ySize = (top - bottom) / game_height;
	
	glBegin(GL_QUADS);
	for (GLint x = 0; x < game_width; ++x) {
		for (GLint y = 0; y < game_height; ++y) {
		    switch(game->organismAt(x, y)) {
                case DEAD: // No life
                    glColor3f(BLACK);
                    break;
                case NEWBORN: // Just born
                    glColor3f(0,1,0);
                    break;
                case DYING: // Dying
                    glColor3f(1,0,0);
                    break;
                case OLD: // Old life
                    glColor3f(WHITE);
                    break;
            }
            
			glVertex2f(    x*xSize+left,    y*ySize+bottom);
			glVertex2f((x+1)*xSize+left,    y*ySize+bottom);
			glVertex2f((x+1)*xSize+left,(y+1)*ySize+bottom);
			glVertex2f(    x*xSize+left,(y+1)*ySize+bottom);
		}
	}
	glEnd();
    	
	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}

void update(int value) {

	game->iterate();

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, update, 0);
}

void readConfiguration(char* file) {
	ConfigFile config(file);
	
	config.readInto(FPS, "fps" );
	
	config.readInto(window_width, "window_width" );
	config.readInto(window_height, "window_height" );
	
	config.readInto(left, "left" );
	config.readInto(right, "right" );
	config.readInto(bottom, "bottom" );
	config.readInto(top, "top" );
	
	config.readInto(game_width, "game_width" );
	config.readInto(game_height, "game_height" );
}

bool checkConfiguration() {
	if (left > right) {
		std::cout << "Ortographic projection values error: 'left' must be less than 'right'" << std::endl;
		return false;
	}
	if (bottom > top) {
		std::cout << "Ortographic projection values error: 'bottom' must be less than 'top'" << std::endl;
		return false;
	}
	if (window_width <= 0 || window_height <= 0 || game_width <= 0 || game_height <= 0) {
		std::cout << "The window's and game's 'width' and 'height' must be greater than 0" << std::endl;
		return false;
	}
	if (game_width >= window_width || game_height >= window_height) {
		std::cout << "Try reducing the game dimensions or increasing the window size for a better visualization" << std::endl;
	}
	
	return true;
}

int main(int argc, char **argv) {
  	glutInit(&argc, argv);
	
	if (argc > 1) {
		readConfiguration(argv[1]);
	}
	
	if (!checkConfiguration()) {
		return 0;
	}
     
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Game of Life");
	glClearColor(1, 1, 1, 1);
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	game = new GameOfLife(game_width, game_height);
	game->randomInit();
		
	update(0);
	glutMainLoop();
		
  	return 0;
}
