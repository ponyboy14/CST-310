// This program is a flyby around the RGB color cube.  One intersting note
// is that because the cube is a convex polyhedron and it is the only thing
// in the scene, we can render it using backface culling only. i.e., there
// is no need for a depth buffer.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>


GLfloat yMove  = 0.0;
GLint counter = 0;
GLfloat rotate = 0.0;
GLfloat shift = 0.0;
GLfloat zoom = 0.0;

bool moveUp = true;
bool moveDown = false;
bool stop = false;
bool go = true;
bool rotateImg = false;
bool shiftUp =false;
bool shiftDown = false;
bool zoomIn = false;
bool zoomOut = false;


// The cube has opposite corners at (0,0,0) and (1,1,1), which are black and
// white respectively.  The x-axis is the red gradient, the y-axis is the
// green gradient, and the z-axis is the blue gradient.  The cube's position
// and colors are fixed.

const int NUM_VERTICES = 8;
const int NUM_FACES = 6;

GLint vertices[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint faces[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors[NUM_VERTICES][3] = {
  {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
  {1.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};


GLint vertices1[NUM_VERTICES][3] = {
  {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
  {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};

GLint faces1[NUM_FACES][4] = {
  {1, 5, 7, 3}, {5, 4, 6, 7}, {4, 0, 2, 6},
  {3, 7, 6, 2}, {0, 1, 3, 2}, {0, 4, 5, 1}};

GLfloat vertexColors1[NUM_VERTICES][3] = {
  {0.0, 1.0, 0.0}, {0.0, 0.5, 1.0}, {0.6542, 0.0, 0.0}, {0.3, 1.0, 1.0},
  {0.0, 0.0, 0.0}, {1.0, 0.867456476889, 1.0}, {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}};

void draw(GLint vert[][3], GLint face[][4],GLfloat color [][3] ) {
  glBegin(GL_QUADS);
  for (int i = 0; i < NUM_FACES; i++) {
    for (int j = 0; j < 4; j++) {
      glColor3fv((GLfloat*)&color[faces[i][j]]);
      glVertex3iv((GLint*)&vertices[faces[i][j]]);
    }
  }
  glEnd();
}




// Display and Animation. To draw we just clear the window and draw the cube.
// Because our main window is double buffered we have to swap the buffers to
// make the drawing visible. Animation is achieved by successively moving our
// camera and drawing. The function nextAnimationFrame() moves the camera to
// the next point and draws. The way that we get animation in OpenGL is to
// register nextFrame as the idle function; this is done in main().
void display() {


  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  
  glRotatef(rotate, 0,0,1);
  glTranslatef(0, shift,zoom);

  
   glBegin(GL_QUADS);
  	glVertex3f(-4.0,5,-4);
  	glVertex3f(4.0,5,-4);
  	glVertex3f(4.0,5,4.0);
  	glVertex3f(-4.0,5,4.0);
  glEnd();
  
  
  
  
  draw(vertices, faces, vertexColors);
  glTranslatef(0,yMove,0);
  glTranslatef(3.0,0,0);
  draw(vertices, faces, vertexColors1);
  glTranslatef(-6.0,0,0);
  glTranslatef(0,-2*yMove,0);
  draw(vertices, faces, vertexColors1);
  glTranslatef(3,yMove,0);
   
  
  	glBegin(GL_QUADS);
  	glVertex3f(-4.0,-4.5,-6);
  	glVertex3f(4.0,-4.5,-6);
  	glVertex3f(4.0,-4.5,4.0);
  	glVertex3f(-4.0,-4.5,4.0);
  glEnd();
  
  
  glFlush();
  glutSwapBuffers();
  
}

// We'll be flying around the cube by moving the camera along the orbit of the
// curve u->(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2).  We keep the camera looking
// at the center of the cube (0.5, 0.5, 0.5) and vary the up vector to achieve
// a weird tumbling effect.
void timer(int v) {



 if(stop)
  {
  
 	rotate = 0;
 	
 	 	

 
  
   	  if(zoomIn)
  {
  
  	zoom += 0.02;
  	zoomIn = false;
  }
  
  if(zoomOut)
  {
  
  	zoom -= 0.02;
  	zoomOut = false;
  }
  
 	
 	
 	
 	  


  if(shiftUp)
  {
  
  	shift += 0.01;
  	shiftUp = false;
  }
  
  if(shiftDown)
  {
  
  	shift -= 0.01;
  	shiftDown = false;
  }
 	
 	
 	// glutPostRedisplay();
  }



if(go)
{

	zoom = 0;
	//shift = 0;

   if(moveUp)
  {
  	yMove += 0.05;
  	glutPostRedisplay();
  	counter++;
  	glutPostRedisplay();
  	
  	
  	if(yMove > 4.0)
  	{
  	    moveUp = false;
  	    moveDown = true;
  	    //counter =0;
  	   
  	}
  	
  	
  }
  
  if(moveDown)
  {
  	yMove -= 0.05;
  	glutPostRedisplay();
  	counter++;
  	if(yMove < -4.0)
  	{
  	    moveUp = true;
  	    moveDown = false;
  	    //counter = 0;
  	    
  	}
  	
  	
  }
  
  
  
 

  
  
  
  static GLfloat u = 0.0;
  u += 0.01;
  glLoadIdentity();
  gluLookAt(8*cos(u), 7*cos(u)-1, 4*cos(u/3)+2, .5, .5, .5, cos(u), 1, 0);
  
  
  
  	if(rotateImg)
  {
  	
  	rotate += 20;
  	glutPostRedisplay();
  	rotateImg = false;
  }
  
  }
  
  


  


  glutPostRedisplay();
  
  
  
  
  
  
  glutTimerFunc(1000/60.0, timer, v);
}


void processNormalKeys(unsigned char key, int x, int y)
{
	
	const char r = 'r';
	const char s = 's';
	const char c = 'c';
	const char u = 'u';
	const char d = 'd';
	const char z = '+';
	const char o = '-';


	switch (key) {
		
		case r: rotateImg = true; break;
		case s: stop = true; go = false; break;
		case c: go = true; stop = false; break;
		case u: shiftUp = true; break;
		case d: shiftDown = true; break;
		case z: zoomIn = true; break;
		case o: zoomOut = true; break;
		
		
	}
} 





// When the window is reshaped we have to recompute the camera settings to
// match the new window shape.  Set the viewport to (0,0)-(w,h).  Set the
// camera to have a 60 degree vertical field of view, aspect ratio w/h, near
// clipping plane distance 0.5 and far clipping plane distance 40.
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
  
  
  
  
}

// Application specific initialization:  The only thing we really need to do
// is enable back face culling because the only thing in the scene is a cube
// which is a convex polyhedron.
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);
}

// The usual main for a GLUT application.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  
  glutCreateWindow("The RGB Color Cube");
  glutReshapeFunc(reshape);
  glutTimerFunc(100, timer, 0);
  glutKeyboardFunc(processNormalKeys);
  glutDisplayFunc(display);
  init();
  glutMainLoop();
}
