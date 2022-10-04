#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// Camera position
float x = 0.0, y = -5.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts



#define PI 3.1415927
#define ESC 27


void display();
void reshape(int,int);
void timer(int);


void init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_DEPTH_TEST);
}






float x_position =0.0;
int state =1;


void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R-10,G,B);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
		// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	gluLookAt(
			x,      y,      1.0,
			x + lx, y + ly, 1.0,
			0.0,    0.0,    1.0);
	
	
	
	glTranslatef(2.0,0.0,-8.0);
	glRotatef(90.0,1.0,0.0,0.0);
	glTranslatef(0.0,8.0,-2.0);
	
	
	
	
	
	
	//Cube1	
	glBegin(GL_QUADS);
	//front
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-0.5,0.5,0.5);
    glVertex3f(-0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,0.5);
    glVertex3f(0.5,0.5,0.5);
    //back
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(0.5,-1.0,-0.5);
    glVertex3f(-0.5,-1.0,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
    //right
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,-0.5);
    glVertex3f(0.5,0.5,-0.5);
    //left
    glColor3f(1.0,1.0,0.0);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(-0.5,-1.0,-0.5);
    glVertex3f(-0.5,-1.0,0.5);
    glVertex3f(-0.5,0.5,0.5);
    //top
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(-0.5,0.5,0.5);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,0.5,-0.5);
    //bottom
    glColor3f(1.0,0.0,1.0);
    glVertex3f(-0.5,-1.0,-0.5);
    glVertex3f(-0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,-0.5);
   
    glEnd();
    
    //Cube2
    
    glTranslatef(-5.8,0.0,0.0);
    
    
    glBegin(GL_QUADS);
	//front
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-0.5,0.5,0.5);
    glVertex3f(-0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,0.5);
    glVertex3f(0.5,0.5,0.5);
    //back
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(0.5,-1.0,-0.5);
    glVertex3f(-0.5,-1.0,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
    //right
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,-0.5);
    glVertex3f(0.5,0.5,-0.5);
    //left
    glColor3f(1.0,1.0,0.0);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(-0.5,-1.0,-0.5);
    glVertex3f(-0.5,-1.0,0.5);
    glVertex3f(-0.5,0.5,0.5);
    //top
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(-0.5,0.5,0.5);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,0.5,-0.5);
    //bottom
    glColor3f(1.0,0.0,1.0);
    glVertex3f(-0.5,-1.0,-0.5);
    glVertex3f(-0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,0.5);
    glVertex3f(0.5,-1.0,-0.5);
   
    glEnd();
    
   
    
    
    
    
    
    
    
    
    
  //  glRotatef(-30.0,1.0,0.0,0.0);
    
    glBegin(GL_POLYGON);
    
    //floor
    glColor3f(0.2,0.8,0.6);
    glVertex3f(-16.0,-1.0,-16.0);
    glVertex3f(16.0,-1.0,-16.0);
    glVertex3f(16.0,-1.0,16.0);
    glVertex3f(-16.0,-1.0,16.0);
    
    glEnd();
	
    
    glBegin(GL_POLYGON);
    
    //wall
    glColor3f(0.99,0.95,0.85);
    glVertex3f(-16.0,16.0,-1.0);
    glVertex3f(16.0,16.0,-1.0);
    glVertex3f(16.0,-2.0,-1.0);
    glVertex3f(-16.0,-2.0,-1.0);
    
    glEnd();
	
	
	glTranslatef(5.5,0.90,-0.2);
	glRotatef(90.0,1.0,0.0,0.0);
    draw_cylinder(0.2,0.4,0.69,0,0);
    
    
	
	
	
	glutSwapBuffers();
}

void update(void) 
{
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1;
		y += deltaMove * ly * 0.1;
	}
	glutPostRedisplay(); // redisplay everything
}


void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);
} 

void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 1.0; break;
		case GLUT_KEY_DOWN : deltaMove = -1.0; break;
	}
} 

void releaseSpecialKey(int key, int x, int y) 
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.0; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0; break;
	}
} 

void mouseMove(int x, int y) 
{ 	
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
}


void reshape(GLint w, GLint h)
{
	glViewport(0,0,w,h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
        gluPerspective(70,(GLfloat(w)+2)/GLfloat(h),4.8,40.0);
	glMatrixMode(GL_MODELVIEW);
	
}

// The MAIN function, from here we start the application and run the game loop
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  
  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(320, 320);
  
  glutCreateWindow("Cube Test");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(update); // incremental update 
  glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove); // process mouse dragging motion
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
						
  glutSpecialUpFunc(releaseSpecialKey); // process special key release
  
  
  
  //glutTimerFunc(0,timer,0);
  
  
  
  init();
  glutMainLoop();
 
 return 0; 
  
  
}


void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60,timer,0);
}



