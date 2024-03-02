#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_POLYGON);
  glColor3f(1, 0, 0);
  glVertex3f(-0.5, -0.5, 0);
  glColor3f(0, 1, 0);
  glVertex3f(0.5, -0.5, 0);
  glColor3f(0, 0, 1);
  glVertex3f(0.5, 0.5, 0);
  glColor3f(1, 1, 1);
  glVertex3f(-0.5, 0.5, 0);
  glEnd();

  glColor3f(1, 1, 1);
  glBegin(GL_POLYGON);
  glVertex3f(0, 0, 0.5);
  glVertex3f(1.5, -0.5, 0.5);
  glVertex3f(1.5, 0.5, 0.5);
  glEnd();

  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("OpenGL Tutorial");
  glutDisplayFunc(display);

  glEnable(GL_DEPTH_TEST);
  glDepthRange(0, 1);
  glDepthFunc(GL_LESS);
  glClearDepth(1.0);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glutMainLoop();

  return 0;
}
