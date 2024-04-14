#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>

void keyboard(unsigned char, int, int) { glutPostRedisplay(); }

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  glColor3f(1, 1, 1);
  glBegin(GL_POLYGON);
  glVertex3f(1, 0, -0.5);
  glVertex3f(2, 1, -0.5);
  glVertex3f(-2, 1, -0.5);
  glVertex3f(-1, 0, -0.5);
  glEnd();

  float mat[16] = {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1};
  glLoadMatrixf(mat);
  glColor3f(0, 0, 1);
  glBegin(GL_POLYGON);
  glVertex3f(1, 0, 0);
  glVertex3f(2, 1, 0);
  glVertex3f(-2, 1, 0);
  glVertex3f(-1, 0, 0);
  glEnd();
  glPopMatrix();

  glutSwapBuffers();
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("OpenGL Tutorial");
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-4, 4, -4, 4);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}
