/*
 * Author: Ben Humphrey 2001
 *         A. Carl Douglas (converted to use GLUT library)
 *         Robert Duvall (simplified)
 *
 * Creates cool looking terrain from a height map.  A height map is a
 * displacement from a surface. Basically, it represents low and
 * height points for our landscape. It is completely up to you to
 * decide which shades represent low points and which shades represent
 * high points.  Note that height maps do not have to be images, you
 * can create a height map from just about any type of data. For
 * instance, you could use an audio stream to create a visual height
 * map representation.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "pixmap.h"


const char * MAP_FILE = "data/bigger.pgm";
const float HEIGHT_RATIO = 1.5f;    // Ratio That The Y Is Scaled According To The X And Z (NEW)


float scaleValue = 0.15f;
unsigned int stepSize = 16;                // Width And Height Of Each Quad
GLenum toRender = GL_QUADS;                // how to render surface
Pixmap * g_HeightMap;                      // height data


int Height (Pixmap * pHeightMap, int x, int y)
// Returns Height From A Image Map
{
  return pHeightMap->data[x % pHeightMap->sizeX][y % pHeightMap->sizeY];
}

void SetVertexColor (Pixmap * pHeightMap, int x, int y)
// Returns Color For A Particular Height
{
  float fColor = -1.0f + (Height(pHeightMap, x, y) / 256.0f);
  glColor3f (0, fColor, 0);
}


void RenderHeightMap (Pixmap * pHeightMap)
// Renders Height Map As Quads or Lines
{
  glBegin(toRender);
  for (unsigned long X = 0; X < pHeightMap->sizeX; X += stepSize)
  {
    for (unsigned long Y = 0; Y < pHeightMap->sizeY; Y += stepSize)
    {
      // Get The (X, Y, Z) Value For The Bottom Left Vertex
      int x0 = X, x = x0;
      int y0 = Height (pHeightMap, X, Y), y = y0;
      int z0 = Y, z = z0;
      SetVertexColor (pHeightMap, x, z);
      glVertex3i (x, y, z);

      // Get The (X, Y, Z) Value For The Top Left Vertex
      x = X;
      y = Height (pHeightMap, X, Y + stepSize);
      z = Y + stepSize;
      SetVertexColor (pHeightMap, x, z);
      glVertex3i (x, y, z);
      if (toRender == GL_LINES) glVertex3i (x, y, z);

      // Get The (X, Y, Z) Value For The Top Right Vertex
      x = X + stepSize;
      y = Height (pHeightMap, X + stepSize, Y + stepSize);
      z = Y + stepSize;
      SetVertexColor (pHeightMap, x, z);
      glVertex3i (x, y, z);
      if (toRender == GL_LINES) glVertex3i (x, y, z);
	
      // Get The (X, Y, Z) Value For The Bottom Right Vertex
      x = X + stepSize;
      y = Height (pHeightMap, X + stepSize, Y);
      z = Y;
      SetVertexColor (pHeightMap, x, z);
      glVertex3i (x, y, z);
      if (toRender == GL_LINES) { glVertex3i (x, y, z); glVertex3i (x0, y0, z0); }
    }
  }
  glEnd ();
}


void InitGL (const char * mapFile)
{
  glClearColor (0.0, 0.0f, 0.0f, 0.0f);  // sky background
  glEnable (GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);

  glEnable(GL_LIGHT0);
  GLfloat light0pos[4] = {0.0, 100.0, 0.0, 1.0};
  GLfloat light0dir[4] = {0.0, -1.0, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0dir);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 70.0);
  glEnable(GL_COLOR_MATERIAL);

  g_HeightMap = new Pixmap(mapFile);
}


void DrawGLScene ()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity ();
  gluLookAt (100, 40, 194, 186, 55, 171, 0, 1, 0);
  glScalef (scaleValue, scaleValue * HEIGHT_RATIO, scaleValue);
  RenderHeightMap (g_HeightMap);

  glutSwapBuffers();
}


void ReSizeGLScene (GLsizei width, GLsizei height) 
{
  glViewport (0, 0, width, height);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 500.0f);

  glMatrixMode (GL_MODELVIEW);
}


void Keyboard (unsigned char key, int x, int y) 
{
  switch (key)
  {
    case ' ':  
      toRender = ((toRender == GL_QUADS) ? GL_LINES : GL_QUADS);
      break;

    case '+':
    case '=':
      glEnable(GL_LIGHTING);
      break;  
    case '-':
    case '_':
      glDisable(GL_LIGHTING);
      break;

    case '>':
    case '.':
      scaleValue += 0.01f;
      break;  
    case '<':
    case ',':
      scaleValue -= 0.01f;
      break;

    case '{':
    case '[':
      if (stepSize > 2)	   stepSize /= 2;
      break;  
    case '}':
    case ']':
      if (stepSize < (g_HeightMap->sizeX / 2))  stepSize *= 2;
      break;

    case 'q':
    case 27:
      exit (0);
  }

  glutPostRedisplay ();
}


int main (int argc, char *argv[]) 
{
  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (640, 480);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);

  InitGL((argc > 1) ? argv[1] : MAP_FILE);
  glutDisplayFunc (DrawGLScene);
  glutReshapeFunc (ReSizeGLScene);
  glutKeyboardFunc (Keyboard);

  glutMainLoop ();
  return 0;
}


