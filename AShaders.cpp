
// This application shows balls bouncing on a checkerboard, with no respect
// for the laws of Newtonian Mechanics.  There's a little spotlight to make
// the animation interesting, and arrow keys move the camera for even more
// fun.

#include <GL/glut.h>
#include <cmath>
#include "stb_image.h"

GLuint texture;

GLuint glInitTexture(char* filename)
{
    GLuint t = 0;
    int width, height, nrChannels;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //unsigned char data[] = { 255, 0, 0, 255 };
    if (data)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    return t;
}

// Colors
GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
GLfloat GREEN[] = {0, 1, 0};
GLfloat MAGENTA[] = {1, 0, 1};
GLfloat BLUE[] = {0, 0, 1};
GLfloat YELLOW[] = {1, 1, 0};
GLfloat xShift = 1;
GLfloat yShift = 0;
GLfloat zShift = 0;
GLfloat rot = 0;
GLfloat yaw = 0;
GLfloat pitch = 0;
GLfloat roll = 0;
bool control = false;
bool shift = false;

// A camera.  It moves horizontally in a circle centered at the origin of
// radius 10.  It moves vertically straight up and down.
class Camera {
  double theta;      // determines the x and z positions
  double y;          // the current y position
  double dTheta;     // increment in theta for swinging the camera around
  double dy;         // increment in y for moving the camera up/down
public:
  Camera(): theta(0), y(3), dTheta(0.04), dy(0.2) {}
  double getX() {return 10 * cos(theta);}
  double getY() {return y;}
  double getZ() {return 10 * sin(theta);}
  void moveRight() {theta += dTheta;}
  void moveLeft() {theta -= dTheta;}
  void moveUp() {y += dy;}
  void moveDown() {if (y > dy) y -= dy;}
};

// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.
class Ball {
  double radius;
  GLfloat* color;
  double maximumHeight;
  double x;
  double y;
  double z;
  int direction;
  

public:
  Ball(double r, GLfloat* c, double h, double x, double z):
      radius(r), color(c), maximumHeight(h), direction(-1),
      y(h), x(x), z(z) {
  }
  void update() {
    y = 1.1;
    if (y > maximumHeight) {
     // y = maximumHeight; direction = -1;
    } else if (y < radius) {
      //y = radius; direction = 1;
    }
    
    glPushMatrix();
    char fn[] = "Bump-Map.jpg";
    texture = glInitTexture(fn);
    glEnable(GL_TEXTURE_2D);

    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);
    gluSphere(qobj, radius, 20, 20);
    gluDeleteQuadric(qobj);

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }
};


class Cube {
  GLfloat* color;
  double maximumHeight;
  double x;
  double y;
  double z;
  int direction;
  

public:
  Cube(GLfloat* c, double h, double x, double z):
       color(c), maximumHeight(h), direction(-1),
      y(h), x(x), z(z) {
  }
  void update() {
    y = 1;
    
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glTranslated(x, 1, z);
    glutSolidCube(2);
    glPopMatrix();
  }
};


class Cyl {
  double radius;
  GLfloat* color;
  double maximumHeight;
  double x;
  double y;
  double z;
  int direction;
  

public:
  Cyl(double r, GLfloat* c, double h, double x, double z):
      radius(r), color(c), maximumHeight(h), direction(-1),
      y(h), x(x), z(z) {
  }
  void update() {
    y = 1;
    
    glPushMatrix();
    GLUquadric *quad = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glTranslated(x, 2*y, z);
    glRotated(90, 1,0,0);
    gluCylinder(quad, radius, radius, 2*y, 30, 30);
    gluDisk(quad, 0, 0, 30, radius);
    gluDisk(quad, 0, y, 30, radius);
    glPopMatrix();
  }
};

// A checkerboard class.  A checkerboard has alternating red and white
// squares.  The number of squares is set in the constructor.  Each square
// is 1 x 1.  One corner of the board is (0, 0) and the board stretches out
// along positive x and positive z.  It rests on the xz plane.  I put a
// spotlight at (4, 3, 7).
class Checkerboard {
  int displayListId;
  int width;
  int depth;
public:
  Checkerboard(int width, int depth): width(width), depth(depth) {}
  double centerx() {return width / 2;}
  double centerz() {return depth / 2;}
  void create() {
  
    glRotatef(25+180,0,1,0);
    displayListId = glGenLists(1);
    glNewList(displayListId, GL_COMPILE);
    GLfloat lightPosition[] = {4, 3, 7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    for (int x = 0; x < width - 1; x++) {
      for (int z = 0; z < depth - 1; z++) {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                     (x + z) % 2 == 0 ? RED : WHITE);
        glVertex3d(x, 0, z);
        glVertex3d(x+1, 0, z);
        glVertex3d(x+1, 0, z+1);
        glVertex3d(x, 0, z+1);
      }
    }
    glEnd();
    glEndList();
   // glRotatef(-25-180,0,1,0);
  }
  void draw() {
    glCallList(displayListId);
  }
};

// Global variables: a camera, a checkerboard and some balls.
Checkerboard checkerboard(8, 8);
Camera camera;
Ball balls[] = {
  Ball(1.1, GREEN, 8, 6, 3.5)
};
Cube cubes[] = {
  Cube(BLUE,0, 3.6, 3.5)
};
Cyl cyls[] = {
  Cyl(1, YELLOW, 70, 1.3,3.5)
};


// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  checkerboard.create();
}

// Draws one frame, the checkerboard then the balls, from the current camera
// position.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  //camera.getZ()
  gluLookAt(4+yaw, camera.getY()-2+pitch, camera.getZ()+15,
            checkerboard.centerx(), 0.0, checkerboard.centerz(),
            0.0, 1.0, 0.0);
            
  glRotatef(rot, 0, 0, 1);
  glTranslatef(xShift, yShift, zShift);
  
 
  checkerboard.draw();
  for (int i = 0; i < sizeof balls / sizeof(Ball); i++) {
    balls[i].update();
  }
  for (int i = 0; i < sizeof cubes / sizeof(Cube); i++) {
    cubes[i].update();
  }
  for (int i = 0; i < sizeof cyls / sizeof(Cyl); i++) {
    cyls[i].update();
  }
  glFlush();
  glutSwapBuffers();
}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
  glMatrixMode(GL_MODELVIEW);
}

// Requests to draw the next frame.
void timer(int v) {
  glutPostRedisplay();
  glutTimerFunc(1000/60, timer, v);
}

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int) {

  int mod_key = glutGetModifiers();
  if(mod_key!= 0) {
     if(mod_key == GLUT_ACTIVE_CTRL)
  {     control = true; }
     if(mod_key == GLUT_ACTIVE_SHIFT){
     shift = true;
  }
  }

  switch (key) {
    case GLUT_KEY_LEFT:if(control){yaw-=2; control = false;}  else{ xShift -=1;} break;
    case GLUT_KEY_RIGHT: if(control){yaw+=2; control = false;} else{ xShift+=1;} break;
    case GLUT_KEY_UP: if(control){ pitch+= 2; control = false;} else if(shift){zShift+=1; shift=false;} else {yShift+=1;} break;
    case GLUT_KEY_DOWN: if(control){ pitch-= 2; control = false;} else if(shift){zShift-=1; shift=false;} else {yShift-=1;} break;
    //case GLUT_ACTIVE_CTRL: yaw+=2; break;
  }
  glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	const char Rrot = '<';
	const char Lrot = '>';
	const char reset = 'r';

	switch (key) {
    case Rrot: rot+=2; break;
    case Lrot: rot-=2; break;
    case reset: rot= 0; yShift =0; xShift =0; yaw = 0; pitch = 0; break;
    
  }
  glutPostRedisplay();
} 

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Bouncing Balls");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(special);
  glutKeyboardFunc(processNormalKeys);
  glutTimerFunc(100, timer, 0);
  init();
  glutMainLoop();
}
    
