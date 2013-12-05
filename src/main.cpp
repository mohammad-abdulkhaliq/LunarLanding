#include "GL/freeglut.h"
#include "GL/gl.h"

float angle, dy;
int up = 1;
bool startAnimation;


void displayWire(void)
{
glMatrixMode(GL_PROJECTION); // set the view volume shape
glLoadIdentity();
gluPerspective(45.0f, 640/480, 0.1f, 100.0f);
glMatrixMode(GL_MODELVIEW); // position and aim the camera
glLoadIdentity();
gluLookAt(0.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT); // clear the screen
glColor3f(0, 0, 1);
glPushMatrix();
if (startAnimation)
glTranslated(0, dy, 0);
glScalef(0.3, 0.3, 0.3);
glRotated(90,1,0,0);
glutWireCylinder(1, 5, 6,1);
glPushMatrix();
glRotated(180,1,0,0);
glutWireCone(1, 3, 6, 1);
glPopMatrix();
glPushMatrix();
glutSolidCube(0.3);
glPopMatrix();
glPopMatrix();
glFlush();
angle++;
if (dy >= 1 || dy <= 0) up = -up;
dy += up * 0.005;
glutPostRedisplay();
}void myKeyboard(unsigned char thekey, int mouseX, int mouseY)
{
switch (thekey)
{
case 'A':
case 'a':
startAnimation = !startAnimation;
break;
}
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640, 480);
glutInitWindowPosition(100, 100);
glutCreateWindow("Transformation testbed - wireframes");
glutDisplayFunc(displayWire);
glutKeyboardFunc(myKeyboard);
glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // background is white
glutMainLoop();
return 0;
}