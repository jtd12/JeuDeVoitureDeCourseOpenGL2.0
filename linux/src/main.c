#include"gameSetup.hpp"
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/freeglut.h>
#define LARGEUR 960
#define HAUTEUR 540

void display();
void init();
void mouseMove(int mx,int my);
void changeSize(int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void specialUpKey(int key, int x, int y);
void mouseState(int button, int state, int x, int y);
void passivekeyboard(unsigned char key, int x, int y);

int windowsName;
setup* game;

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(LARGEUR,HAUTEUR);
	glutInitWindowPosition(100,100); 
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH | GLUT_STENCIL);
	windowsName=glutCreateWindow("car game OpenGL 2.0");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouseState);
	glutMotionFunc(mouseMove);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(passivekeyboard);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);
	glutMainLoop();
	
	delete game;
	return 0;
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix


	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(200,0,200,0);
	gluPerspective(45,(float)w/(float)h,1.0,150000.0);
	glMatrixMode(GL_MODELVIEW);

          
	glEnable(GL_DEPTH_TEST);


	

}

void init()
{
	glClearColor(0.9,0.9,0.9,0.9);

	GLfloat ambient[] = {0.5f,0.7f,0.1f,0.9f};
            GLfloat diffuse[] = {0.9f,0.9f,0.9f,0.9f};
            GLfloat light0_position [] = {10.0f, 2000.0f, 1000.0f, 1.0f};
            GLfloat specular_reflexion[] = {0.6f,0.9f,0.9f,1.0f};
            GLubyte shiny_obj = 128;

                        //positionnement de la lumière avec les différents paramètres
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
            glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
     
			glEnable(GL_COLOR_MATERIAL);
            glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular_reflexion);
            glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,shiny_obj);
	game=new setup();

	

}

void mouseMove(int mx,int my)
{
	game->mouseMove(mx,my);
}
void keyboard(unsigned char key, int x, int y)
{
	game->keyboard(key,x,y);
}
void passivekeyboard(unsigned char key, int x, int y)
{
	game->passiveKeyboard(key,x,y);
}
void mouseState(int button, int state, int x, int y)
{
	game->mouseState( button,  state,  x,  y);
}
void specialKey(int key, int x, int y)
{
	game->specialKey(key,x,y);
}

void specialUpKey(int key, int x, int y)
{
	game->controlSpecialPassiveKeyboard(key,x,y);
}

void display()
{
	game->update();
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(0,15,20,0,0,0,0,1,0);
	game->draw();
	
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}


