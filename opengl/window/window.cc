#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>

#include <iostream>

void keyboard(unsigned char, int, int) { glutPostRedisplay(); }

void display() {
  std::cout << "render" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1, 1, 1);

  glBegin(GL_POLYGON);
  glVertex2f(-0.5, -0.5);
  glVertex2f(0.5, -0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(-0.5, 0.5);
  glEnd();

  glutSwapBuffers();
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("OpenGL Tutorial");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}
