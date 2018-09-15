#include "glrenderer.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "slotmachine.h"

void display_fps(int x, int y, const char *fpsString)
{
  glColor3f(0.0, 1.0, 0.0);
  glRasterPos2i(x, y);
  while (*fpsString)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *fpsString);
    ++fpsString;
  }
}

size_t frames = 0;
char fpsString[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int lastX = 0;
int lastY = 0;

void display(void)
{
  /* clear all pixels  */
  glClear(GL_COLOR_BUFFER_BIT);

  /* */
  SlotMachine::getInstance().draw();

  float sz = 5;
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(lastX - sz, lastY - sz, 0.0);
  glVertex3f(lastX + sz, lastY - sz, 0.0);
  glVertex3f(lastX + sz, lastY + sz, 0.0);
  glVertex3f(lastX - sz, lastY + sz, 0.0);
  glEnd();

  /*
  * draw FPS string
  */
  display_fps(0, 10, fpsString);

  /* don't wait!  
 * start processing buffered OpenGL routines 
 */
  glFlush();

  ++frames;
}

void init(void)
{
  /* select clearing color 	*/
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 27)
  {
    exit(0);
  }
}

void mouse(int button, int state, int x, int y)
{
  printf("mouse button=%d, state=%d, x=%d, y=%d\n", button, state, x, y);
  if (button == 0 && state == 0)
  {
    lastX = x;
    lastY = glutGet(GLUT_WINDOW_HEIGHT) - y;

    glutPostRedisplay();
  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);

  /* initialize viewing values  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

  /* */
  SlotMachine::getInstance().reshape(w, h);
}

void update(int value)
{
  static double last_update_time = 0;
  double current_time = glutGet(GLUT_ELAPSED_TIME);
  double elapsed_time = current_time - last_update_time;

  if (SlotMachine::getInstance().update(elapsed_time))
  {
    last_update_time = current_time;
    glutPostRedisplay();
  }

  glutTimerFunc(16, update, 0);
}

void calculate_fps(int value)
{
  static double last_time = 0;

  double curr_time = glutGet(GLUT_ELAPSED_TIME);
  snprintf(fpsString, 64, "FPS:%.2f\n", frames * 1000.0 / (curr_time - last_time));

  frames = 0;
  last_time = curr_time;

  glutTimerFunc(1000, calculate_fps, 0);
}

/* 
 * Declare initial window size, position, and display mode
 * (single buffer and RGBA).  Open window with "hello"
 * in its title bar.  Call initialization routines.
 * Register callback function to display graphics.
 * Enter main loop and process events.
 */
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("hello");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutTimerFunc(16, update, 0);
  glutTimerFunc(1000, calculate_fps, 0);

//  glutFullScreen();
  glutMainLoop();
  return 0; /* ANSI C requires main to return int. */
}
