#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>

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

  int width = glutGet(GLUT_WINDOW_WIDTH);
  int height = glutGet(GLUT_WINDOW_HEIGHT);
  float x = (float)lastX / width;
  float y = (float)(height - lastY) / height;
  float sz = .05f;

  /* draw white polygon (rectangle) with corners at
 * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 */
  glColor3f(1.0, 1.0, 1.0);
  // unsigned int
  // glColor3bv (1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(x - sz, y - sz, 0.0);
  glVertex3f(x + sz, y - sz, 0.0);
  glVertex3f(x + sz, y + sz, 0.0);
  glVertex3f(x - sz, y + sz, 0.0);
  glEnd();

  /*
  * draw FPS string
  */
  display_fps(0, 0, fpsString);

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

  /* initialize viewing values  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
  printf("keyboard->key: %d\n", key);

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
    lastY = y;
    glutPostRedisplay();
  }
}

void reshape(int w, int h)
{
  printf("reshape: w=%d h=%d\n", w, h);
}

void update(int value)
{
  double a = 2;
  for (size_t i = 0; i < 1000000; ++i)
    a *= a;

  glutPostRedisplay();

  glutTimerFunc(16.6666666667, update, 0);
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

  glutTimerFunc(16.6666666667, update, 0);
  glutTimerFunc(1000, calculate_fps, 0);

  glutFullScreen();
  glutMainLoop();
  return 0; /* ANSI C requires main to return int. */
}
