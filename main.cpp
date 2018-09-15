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

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  SlotMachine::getInstance().draw();
  display_fps(0, 10, fpsString);

  glFlush();
  glutSwapBuffers();

  ++frames;
}

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
  if (key == 27)
  {
    exit(0);
  }
}

void stop(int)
{
  SlotMachine::getInstance().stop();
  if (SlotMachine::getInstance().state() != SlotMachine::State::idle)
  {
    glutTimerFunc(500, stop, 0);
  }
}

void mouse(int button, int state, int x, int y)
{
  printf("mouse button=%d, state=%d, x=%d, y=%d\n", button, state, x, y);
  if (button == 0 && state == 0 && SlotMachine::getInstance().state() == SlotMachine::State::idle)
  {
    SlotMachine::getInstance().reset();
    glutTimerFunc(4000, stop, 0);
  }
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

  SlotMachine::getInstance().reshape(w, h);
}

void update(int)
{
  static double last_update_time = 0;
  double current_time = glutGet(GLUT_ELAPSED_TIME);
  double elapsed_time = current_time - last_update_time;

  SlotMachine::getInstance().update(elapsed_time);
  last_update_time = current_time;
  glutPostRedisplay();

  glutTimerFunc(10, update, 0);
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

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("hello");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);

  glutTimerFunc(10, update, 0);
  glutTimerFunc(1000, calculate_fps, 0);

  // glutFullScreen();
  glutMainLoop();
  return 0;
}
