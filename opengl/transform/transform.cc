#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>

#include <glm/glm.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0, 1, 1);

  auto translate = glm::translate(glm::mat4(1), glm::vec3(0.25, 0.25, 0)),
       rotate = glm::rotate(glm::mat4(1), (float)M_PI / 4, glm::vec3(0, 0, 1));

  auto mat = translate * rotate;
  glPushMatrix();
  glLoadMatrixf(glm::value_ptr(mat));
  glBegin(GL_POLYGON);
  glVertex2f(-0.5, -0.5);
  glVertex2f(0.5, -0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(-0.5, 0.5);
  glEnd();
  glPopMatrix();

  glColor3f(1, 1, 1);
  for (int step = -3; step <= 3; step++) {
    glBegin(GL_LINES);
    glVertex2f(-1, step * 0.25);
    glVertex2f(1, step * 0.25);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(step * 0.25, -1);
    glVertex2f(step * 0.25, 1);
    glEnd();
  }

  glutSwapBuffers();
}

void idle() { glutPostRedisplay(); }

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("OpenGL Tutorial");

  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();

  return 0;
}
