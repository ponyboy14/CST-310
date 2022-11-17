

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#define STB_IMAGE_IMPLEMENTATION




// Camera position
float x = 2.0, y = -4.15; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = -0.5, ly = 1.0; // camera points initially along y-axis
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


void plot_rect(float xmax, float xmin, float ymax, float ymin, float zmax, float zmin, float colors[][3]) {
    glColor3f(colors[0][0], colors[0][1], colors[0][2]);
    glVertex3f(xmin,ymax,zmax);
    glVertex3f(xmin,ymin,zmax);
    glVertex3f(xmax,ymin,zmax);
    glVertex3f(xmax,ymax,zmax);
    //back
    glColor3f(colors[1][0], colors[1][1], colors[1][2]);
    glVertex3f(xmax,ymax,zmin);
    glVertex3f(xmax,ymin,zmin);
    glVertex3f(xmin,ymin,zmin);
    glVertex3f(xmin,ymax,zmin);
    //right
    glColor3f(colors[2][0], colors[2][1], colors[2][2]);
    glVertex3f(xmax,ymax,zmax);
    glVertex3f(xmax,ymin,zmax);
    glVertex3f(xmax,ymin,zmin);
    glVertex3f(xmax,ymax,zmin);
    //left
    glColor3f(colors[3][0], colors[3][1], colors[3][2]);
    glVertex3f(xmin,ymax,zmin);
    glVertex3f(xmin,ymin,zmin);
    glVertex3f(xmin,ymin,zmax);
    glVertex3f(xmin,ymax,zmax);
    //top
    glColor3f(colors[4][0], colors[4][1], colors[4][2]);
    glVertex3f(xmin,ymax,zmin);
    glVertex3f(xmin,ymax,zmax);
    glVertex3f(xmax,ymax,zmax);
    glVertex3f(xmax,ymax,zmin);
    //bottom
    glColor3f(colors[5][0], colors[5][1], colors[5][2]);
    glVertex3f(xmin,ymin,zmin);
    glVertex3f(xmin,ymin,zmax);
    glVertex3f(xmax,ymin,zmax);
    glVertex3f(xmax,ymin,zmin);	
}



float x_position =0.0;
int state =1;


void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLfloat R,
                   GLfloat G,
                   GLfloat B,
                   bool shade)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    if(!shade) {
        glColor3f(R,G,B);
    }
    else {
        glColor3f(R-.05,G-.05,B-.05);
    }
    
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
    glColor3f(R,G,B);
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





void draw_rect(float xmax, float xmin, float ymax, float ymin) {
  glBegin(GL_POLYGON);
    	glVertex3f(xmax,ymax,0.0);
    	glVertex3f(xmax,ymin,0.0);
    	glVertex3f(xmin,ymin,0.0);
    	glVertex3f(xmin,ymax,0.0);
	
	 glEnd();
}


void drawCar()
{


    glTranslatef(0,2,-2.0);

    glBegin(GL_QUADS);
     float colors[][3] = {{0.8,0.2353,0.1765}, {0.8,0.2353,0.1765}, {0.8,0.2353,0.1765},  	{0.8,0.2353,0.1765}, {0.8,0.2353,0.1765}, {0.8,0.2353,0.1765}};
     
    plot_rect(1.5,-0.5,0.5,0.0,0.5,-0.5, colors);
    
    plot_rect(2.5,-1.5,0,-1,0.5,-0.5,colors);
    
    
    
    glEnd();




    glTranslatef(-0.4,-1.0,0.0);

    
    draw_cylinder(0.4,0.8,0.34,0.27,0.20, true);
    glRotatef(-90.0,0.0,0.0,1.0);
    glTranslatef(-1.8,0.0,0.15);
    
    
    glTranslatef(0.4,0.0,0.0);
    glRotatef(90.0,0.0,0.0,1.0);
    
    
    draw_cylinder(0.4,0.8,0.34,0.27,0.20, true);
    glRotatef(-90.0,0.0,0.0,1.0);
    glTranslatef(-1.8,0.0,0.15);

    //glTranslatef(-1.8,0.0,0.);
    //glRotatef(90.0,0.0,0.0,1.0);
    
   // draw_cylinder(0.25,0.8,0.34,0.27,0.20, true);
    //glRotatef(-90.0,0.0,0.0,1.0);
    //glTranslatef(1.8,0.0,0.15);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	
	
	
			// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	gluLookAt(
			x,      y,      2.0,
			x + lx, y + ly, 2.0,
			0.0,    0.0,    2.0);
	
	
	
	
	
	glTranslatef(2.0,0.0,-8.0);
	glRotatef(90.0,1.0,0.0,0.0);
	glTranslatef(0.0,8.0,-23.0);

	
	
	//Cube1	
	glBegin(GL_QUADS);
     float colors[][3] = {{0.3098,0.2353,0.1765}, {0.309,0.247,0.188}, {0.309,0.247,0.188}, {0.3098,0.2353,0.1765}, {0.3087,0.233,0.171}, {0.3089,0.243,0.176}};
    float tableBase[][3] = {{0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,0.5,0.5}};
    float table[][3] = {{0.1,0.1,0.1}, {0.1,0.1,0.1}, {0.0,0.0,0.0}, {0.0,0.0,0.0}, {0.2,0.2,0.2}, {0.0,0.0,0.0}};
    plot_rect(0.5,-0.5,0.25,-0.85,0.5,-0.5, table);
    glEnd();
    // cube1 base
    glBegin(GL_QUADS);
    plot_rect(0.475,-0.475,-0.85,-1.0,0.475,-0.475, tableBase);
   
    glEnd();


    glTranslatef(0.0,8.0,0.0);

    glColor3f(.61,.75,.9);
    gluSphere(gluNewQuadric(), 2, 20, 20);

    glColor3f(.727,.727,.727);
    glTranslatef(0.0,-0.8,0.0);
    glScalef(2.0,0.6,1.0);
    gluSphere(gluNewQuadric(), 2, 20, 20);
    glScalef(0.5,1.8,1.0);
    glTranslatef(0.0,-7.2,0.0);
    
    
      
    
  //  glRotatef(-30.0,1.0,0.0,0.0);
    
    glBegin(GL_POLYGON);
    
    //floor
    glColor3f(0.0, 0.8, 0.1);
    glVertex3f(-100.0,-1.0,-100.0);
    glVertex3f(100.0,-1.0,-100.0);
    glVertex3f(100.0,-1.0,100.0);
    glVertex3f(-100.0,-1.0,100.0);
    
    glEnd();
    
     glBegin(GL_POLYGON);
    
    //wall
    glColor3f(.4,0.8,1.99);
    glVertex3f(-100.0,100.0,-1.0);
    glVertex3f(100.0,100.0,-1.0);
    glVertex3f(100.0,-1.0,-1.0);
    glVertex3f(-100.0,-1.0,-1.0);
    
    glEnd();
	
	
	

   glTranslatef(2.0,0.0,8.0);
    
   drawCar();

    
    



  
      
  
    
    

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
  glutInitWindowPosition(100, 100);
  
 
 
 
 
 	
  
  
  
  
  glutCreateWindow("Cube Test");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(update); // incremental update 
  glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove); // process mouse dragging motion
  //glutKeyboardFunc(processNormalKeys);
  //glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
						
  //glutSpecialUpFunc(releaseSpecialKey); // process special key release
   
  
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
