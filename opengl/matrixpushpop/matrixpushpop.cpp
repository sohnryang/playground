#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>

#include <glm/glm.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

const float PI = 3.14159265359;
std::chrono::time_point<std::chrono::system_clock> last_updated;
float root_angle = 0, arm_angle = 0;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1, 1, 1);

  const auto now = std::chrono::system_clock::now();
  const auto duration = now - last_updated;
  const auto delta_time =
      std::chrono::duration_cast<std::chrono::duration<float>>(duration)
          .count();
  root_angle += delta_time * PI / 2;
  last_updated = now;

  const auto root_rotate =
      glm::rotate(glm::mat4(1), root_angle, glm::vec3(0, 0, 1));
  glLoadMatrixf(glm::value_ptr(root_rotate));
  glBegin(GL_POLYGON);
  glVertex2f(-0.25f, -0.25f);
  glVertex2f(0.25f, -0.25f);
  glVertex2f(0.25f, 0.25f);
  glVertex2f(-0.25f, 0.25f);
  glEnd();

  glPushMatrix();
  float current_mat[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, current_mat);
  const auto up_arm_transform =
      glm::translate(glm::make_mat4(current_mat), glm::vec3(0, 0.5, 0));
  glLoadMatrixf(glm::value_ptr(up_arm_transform));
  glBegin(GL_POLYGON);
  glVertex2f(-0.1f, -0.25f);
  glVertex2f(0.1f, -0.25f);
  glVertex2f(0.1f, 0.25f);
  glVertex2f(-0.1f, 0.25f);
  glEnd();

  glPushMatrix();
  arm_angle += delta_time * PI / 4;
  glGetFloatv(GL_MODELVIEW_MATRIX, current_mat);
  const auto arm_rotate = glm::rotate(
      glm::translate(glm::make_mat4(current_mat), glm::vec3(0, 0.25, 0)),
      arm_angle, glm::vec3(0, 0, 1));
  glLoadMatrixf(glm::value_ptr(arm_rotate));
  glBegin(GL_POLYGON);
  glVertex2f(-0.2f, -0.1f);
  glVertex2f(0.2f, -0.1f);
  glVertex2f(0.2f, 0.1f);
  glVertex2f(-0.2f, 0.1f);
  glEnd();
  glPopMatrix();

  glPopMatrix();

  glutSwapBuffers();
}

void idle() { glutPostRedisplay(); }

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutCreateWindow(argv[0]);

  last_updated = std::chrono::system_clock::now();

  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutMainLoop();
}
