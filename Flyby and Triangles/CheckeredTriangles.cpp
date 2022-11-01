// This application is a trivial illustration of texture mapping.  It draws
// several triangles, each with a texture mapped on to it.  The same texture
// is used for each triangle, but the mappings vary quite a bit so it looks as
// if each triangle has a different texture.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>


//set to true to animate
static bool spinning = true;

//number of frames per second to render
static const int FPS = 60;


//To move the object up, down, left, and right
static bool up = false;
static bool down = false; 
static bool left = false;
static bool right = false;
static bool plus = false;
static bool minus = false;

GLfloat Trans = 0.0;
GLfloat shift = 0.0;
GLfloat zoom = 0.0;

//Global variable to track orientation
static GLfloat currentAngleOfRotation = 0.0;

// Define a 2 x 2 red and yellow checkered pattern using RGB colors.
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

// Fixes up camera and remaps texture when window reshaped.
void reshape(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(80, GLfloat(width)/height, 1, 40);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(2, -1, 5, 0, 0, 0, 0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D,
               0,                    // level 0
               3,                    // use only R, G, and B components
               2, 2,                 // texture has 2x2 texels
               0,                    // no border
               GL_RGB,               // texels are in RGB format
               GL_UNSIGNED_BYTE,     // color components are unsigned bytes
               texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Draws three textured triangles.  Each triangle uses the same texture,
// but the mappings of texture coordinates to vertex coordinates is
// different in each triangle.
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  
 
 
  glRotatef(currentAngleOfRotation, 0.0, 0.0, 1.0);
  
 
  glBegin(GL_TRIANGLES);
    glTexCoord3f(0.5, 1.0, 0.0);    glVertex3f(-3, 3, 0.0);
    glTexCoord3f(0.0, 0.0, 0.0);    glVertex3f(-3, 0, 0.0);
    glTexCoord3f(1.0, 0.0, 0.0);    glVertex3f(0, 0, 0.0);

    glTexCoord3f(4, 8, 0.0);        glVertex3f(3, 3, 0.0);
    glTexCoord3f(0.0, 0.0, 0.0);    glVertex3f(0, 0, 0.0);
    glTexCoord3f(8, 0.0, 0.0);      glVertex3f(3, 0, 0.0);

    glTexCoord3f(5, 5, 0.0);        glVertex3f(0, 0, 0.0);
    glTexCoord3f(0.0, 0.0, 0.0);    glVertex3f(-1.5, -3, 0.0);
    glTexCoord3f(4, 0.0, 0.0);      glVertex3f(1.5, -3, 0.0);
  glEnd();
  glRotatef(-currentAngleOfRotation, 0.0, 0.0, 1.0);
  glTranslatef(shift,Trans,zoom);
  
  Trans = 0;
  shift = 0;
  zoom = 0;
  glFlush();
  glutSwapBuffers();
}


//increments the angle of rotation and redisplays window
void timer(int v) {
  if (spinning) {
    currentAngleOfRotation += 1;
    if (currentAngleOfRotation > 360.0) {
      currentAngleOfRotation -= 360.0;
    }
    glutPostRedisplay();
 }
 
   if(up)
  {
  	Trans += 0.05;
  	glutPostRedisplay();
  	up = false;
  }
  
  if(down)
  {
  	Trans -=0.05;
  	glutPostRedisplay();
  	down = false;
  }
  if(right)
  {
  	shift =0.05;
  	glutPostRedisplay();
  	right = false;
  }
  if(left)
  {
  	shift -=0.05;
  	glutPostRedisplay();
  	left = false;
  }
   if(plus)
  {
  	zoom +=0.1;
  	glutPostRedisplay();
  	plus = false;
  }
  if(minus)
  {
  	zoom -=0.1;
  	glutPostRedisplay();
  	minus = false;
  }
 
 
  glutTimerFunc(1000/FPS, timer, v);
}

// Handles mouse events as follows: when the left button is pressed, generate
// new animation frames while the application is idle; when the right button
// is pressed, remove any idle-time callbacks, thus stopping the animation.
void processNormalKeys(unsigned char key, int x, int y)
{
	const char p = 'p';
	const char c = 'c';
	const char u = 'u';
	const char d = 'd';
	const char l = 'l';
	const char r = 'r';
	const char cPlus = '+';
	const char cMinus = '-';

	switch (key) {
		case p : spinning = false; break;
		case c : spinning = true; break;
		case u : up = true; break;
		case d : down = true; break;
		case l : left = true; break;
		case r: right = true; break;
		case cPlus: plus = true; break;
		case cMinus: minus = true; break;
		
	}
} 






// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(520, 390);
  glutCreateWindow("Textured Triangles");
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutTimerFunc(100,timer,0);
  glutKeyboardFunc(processNormalKeys);
  glutMainLoop();
}
