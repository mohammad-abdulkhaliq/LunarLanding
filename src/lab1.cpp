/*
** Author : Mohammad Khalid Abdulkhaliq
** ID : 22-2768
** Group : T-07
** Compile Machine: MAC OS X 
 */

// MAC OS X
// #include <sstream>
// #include <stdio.h>
// #include <GLUT/glut.h>

// FEDORA 27
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <GL/glut.h>
#include "SerialRead.h"

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
int moveX = 600; int moveY = 2000;
int speed = 25;
int g = 2;
int timeR = 30;
int fuel = 100;
bool over = false;
int fd = 0;
double cX = 0;
double cY = 0;
const char* cPos;

void myInit(void)
{
  glClearColor(1.0,1.0,1.0,0.0); // set white background color 
  glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color 
  glPointSize(4.0); // a ‘dot’ is 4 by 4 pixels 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, 640.0, 0.0, 480.0);
  fd = set_port();
}

void
output(GLfloat x, GLfloat y, GLfloat fontSize, char *text)
{
  char *p;

  glPushMatrix();
  glTranslatef(x, y, 0);
  glScalef(fontSize,fontSize,0);
  for (p = text; *p; p++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
  glPopMatrix();
}

void clearScreen(void){ glClear(GL_COLOR_BUFFER_BIT); }

void drawTerrain(void){

  glBegin(GL_LINE_STRIP);
  glVertex2i(0,0);
  glVertex2i(150,0);
  glVertex2i(150, 100);  //Landing pad
  glVertex2i(250, 100); //
  glVertex2i(250,0);
  glVertex2i(380,0);
  glVertex2i(395, 200);
  glVertex2i(400, 0);
  glVertex2i(640, 0);
  glEnd();
  //glFlush();
  
}

void drawFuelBar(int f) {
  if(f <= 0 )
    return;
  glBegin(GL_QUADS);
  glVertex2i(10,410);
  glVertex2i(10, 400);
  glVertex2i(f, 400);
  glVertex2i(f, 410);
  glEnd();
  //glFlush();

}


void drawLunarLander(void){

  
  glRecti(0,0,10,10);
  glRecti(60,0,70,10);
  glBegin(GL_LINE_STRIP);
  glVertex2i(10,10);
  glVertex2i(60,10);
  glVertex2i(60, 50);
  glVertex2i(40, 70);
  glEnd();
  glRecti(40,70, 30, 80);
  glRecti(40, 50, 30, 40);
  glBegin(GL_LINE_STRIP);
  glVertex2i(30,70);
  glVertex2i(10, 50);
  glVertex2i(10,10);
  glEnd();
  //glFlush(); // send all output to display

}

void printCoords(void){
  
  std::stringstream coords;
  coords << "x: " << moveX << ", y: " << moveY;
  char *o = const_cast<char*>(coords.str().c_str());
  std::stringstream controller;
  controller << "cx: " << cX << ", cy: " << cY;
  char *o3 = const_cast<char*>(controller.str().c_str());
  std::stringstream time;
  time << "time remaining: " << timeR;
  char *o2 = const_cast<char*>(time.str().c_str());
  output(530,400,0.1, o);
  output(530,380,0.1, o3);
  output(10, 390, 0.1, o2 );
}


void thrust(int x, int y) {
  
 
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); 
  glLoadIdentity();
  clearScreen();
  glScalef(0.5,0.5,0);
  glTranslatef(x,y, 0);
  drawLunarLander();
  glPopMatrix();
  drawTerrain();
  printCoords();
  drawFuelBar(fuel);
  glutSwapBuffers();
  
}

void gameOver(int why) {

  clearScreen();
  
  glutSwapBuffers();
  switch(why) {
  case 0 : output(640/8,480/2,0.35, "Congratulations Landed !"); break;
  case 1 : output(640/8,480/2,0.35, "Time Over Sorry !"); break;
  case 2 : output(640/8,480/2,0.35, "Fuel Ran Out Sorry !"); break;
  }
  glutIdleFunc(NULL);
  glutSwapBuffers();  
}




void myKeyboard(unsigned char thekey, int mouseX, int mouseY) {
  int i;
  switch(thekey) {
  case 'w':
    moveY += speed;  fuel--; if(fuel==0) gameOver(2);
    break;
  case 'a':
    moveX -= speed;  fuel--; if(fuel==0) gameOver(2);
    break;
  case 's':
    moveY -= speed;  fuel--; if(fuel==0) gameOver(2);
    break;
  case 'd':
    moveX += speed;  fuel--; if(fuel==0) gameOver(2);
    break;
  default:
   
    break;
  }
  thrust(moveX, moveY);
}
int charPos = 0;  
void renderChar(char c) {
  
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix(); 
  glLoadIdentity();
  glScalef(0.5,0.5,0);
  glTranslatef(charPos, 470, 0);
  glutStrokeCharacter(GLUT_STROKE_ROMAN, (int) c);
  glutSwapBuffers();
  glPopMatrix();
  
}

void renderString(char string [])
{  
  charPos = 0;
  for(int i = 0; i < strlen(string); i++) {
    renderChar(string[i]);
    charPos+=glutStrokeWidth(GLUT_STROKE_ROMAN, string[i]);
  }
}

void myController(void) {

    cPos = read_port(fd);
    while(cPos == NULL) 
      cPos = read_port(fd);
    // printf("%s", cPos);
    cX = readPosX(cPos);
    cY = readPosY(cPos);
    
    int oX = (int) cX * 0.25;
    int oY = (int) cY * 0.25;
    moveX += (1 * oX);
    moveY += (1 * oY);
  if(moveY == 192 && moveX > 227 && moveX < 500) { 
    gameOver(0); //reached landing pad;
    return;
  }
  
  if(moveY > 0) {
    moveY -= g;
    
  }

  thrust(moveX,moveY);
}


void gravitySimulator(void) {
  
 
  if(moveY == 192 && moveX > 227 && moveX < 500) { 
    gameOver(0); //reached landing pad;
    return;
  }
  
  if(moveY > 0) {
    moveY -= g;
    thrust(moveX,moveY);
  }
  // else{
  
    
  //   thrust(moveX, moveY);
    
  // }

    //BASICALLY thrust is the refresh function to plot time change and also move the lander
 
}








void timer(int value) {
  timeR;
  if(value > 0)
    glutTimerFunc(1000, timer, timeR);
  else
    gameOver(1);
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void drawLunarLanding(void)
{
  clearScreen();
  glTranslatef(0,50,0);
  drawLunarLander();
  drawTerrain();
  drawFuelBar(fuel);
  glutSwapBuffers();
  // glutIdleFunc(gravitySimulator);
  glutIdleFunc(myController);
  glutTimerFunc(0,timer,30);
 
 
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
  glutInit(&argc, argv); // initialize the toolkit 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode 
  glutInitWindowSize(640,480); // set window size glutInitWindowPosition(100, 150); // set window position on screen 
  glutCreateWindow("Lab1-Task1"); // open the screen window
  glutDisplayFunc(drawLunarLanding); // register redraw function
  myInit();
  glutMainLoop();
  

  return 0;
}
