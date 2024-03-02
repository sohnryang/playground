#define GL_SILENCE_DEPRECATION

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <memory>
#include <random>
#include <unordered_map>
#include <vector>

#include <GLUT/glut.h>

#include <glm/glm.hpp>

#include <glm/ext/matrix_transform.hpp>

namespace entities {
using EntityId = size_t;

class EntityManager {
private:
  EntityId current_id;

public:
  EntityManager() : current_id(0) {}
  EntityId next_id() { return current_id++; }
  EntityId end_id() { return current_id; }
};
} // namespace entities

namespace components {
struct Polygon {
  std::vector<glm::vec4> vertices;
};

struct Color {
  float r;
  float g;
  float b;
};

struct Transform {
  glm::vec3 displacement;
  glm::vec3 velocity;
};
} // namespace components

namespace systems {
class System {
public:
  virtual void update(struct Registry &registry, float delta_time) = 0;
  virtual ~System() {}
};

struct Registry {
  std::unordered_map<entities::EntityId, components::Polygon> polygons;
  std::unordered_map<entities::EntityId, components::Color> colors;
  std::unordered_map<entities::EntityId, components::Transform> transforms;
  entities::EntityManager manager;
  std::vector<std::unique_ptr<System>> systems;
  bool loop_started = false;
  std::chrono::time_point<std::chrono::system_clock> last_updated;

  void add_static_polygon(const components::Polygon &polygon,
                          const components::Color &color) {
    auto id = manager.next_id();
    polygons[id] = polygon;
    colors[id] = color;
  }

  void add_moving_polygon(const components::Polygon &polygon,
                          const components::Color &color,
                          const components::Transform transform) {
    auto id = manager.next_id();
    polygons[id] = polygon;
    colors[id] = color;
    transforms[id] = transform;
  }

  void main_loop() {
    auto now = std::chrono::system_clock::now();
    float delta_time;
    if (!loop_started) {
      delta_time = 0;
      loop_started = true;
    } else {
      auto duration = now - last_updated;
      delta_time =
          std::chrono::duration_cast<std::chrono::duration<float>>(duration)
              .count();
    }

    for (const auto &system : systems)
      system->update(*this, delta_time);

    last_updated = now;
  }
};

class Transform : public System {
public:
  void update(Registry &registry, float delta_time) override {
    for (entities::EntityId i = 0; i < registry.manager.end_id(); i++) {
      if (registry.transforms.count(i)) {
        auto &disp = registry.transforms[i].displacement;
        auto &vel = registry.transforms[i].velocity;
        disp += delta_time * registry.transforms[i].velocity;
        if (disp[0] < -1)
          vel[0] = abs(vel[0]);
        else if (disp[0] > 1)
          vel[0] = -abs(vel[0]);
        if (disp[1] < -1)
          vel[1] = abs(vel[1]);
        else if (disp[1] > 1)
          vel[1] = -abs(vel[1]);
      }
    }
  }
};

class Render : public System {
public:
  Render() {
    glClearColor(0, 0, 0, 1);
    glDepthFunc(GL_LESS);
    glDepthRange(0, 1);
    glClearDepth(1);
  }

  void update(Registry &registry, float delta_time) override {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (entities::EntityId i = 0; i < registry.manager.end_id(); i++)
      if (registry.polygons.count(i) && registry.colors.count(i)) {
        glColor3f(registry.colors[i].r, registry.colors[i].g,
                  registry.colors[i].b);
        glBegin(GL_POLYGON);
        for (const auto &v : registry.polygons[i].vertices) {
          glm::vec3 transformed(v);
          if (registry.transforms.count(i)) {
            glm::mat4 mat = glm::translate(glm::mat4(1),
                                           registry.transforms[i].displacement);
            transformed = glm::vec3(mat * v);
          }
          glVertex3f(transformed[0], transformed[1], transformed[2]);
        }
        glEnd();
      }

    glutSwapBuffers();
  }
};
}; // namespace systems

systems::Registry registry;

void main_loop() { registry.main_loop(); }

template <typename G>
std::vector<glm::vec4> random_n_gon(G &gen, int n, float radius) {
  std::uniform_real_distribution<> dist(0, 2 * M_PI);
  std::vector<float> angles;
  for (int i = 0; i < n; i++)
    angles.push_back(dist(gen));
  std::sort(angles.begin(), angles.end());
  std::vector<glm::vec4> vertices;
  std::transform(angles.begin(), angles.end(), std::back_inserter(vertices),
                 [radius](auto angle) {
                   return glm::vec4(radius * cos(angle), radius * sin(angle), 0,
                                    1);
                 });
  return vertices;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutCreateWindow("ECS Demo");

  registry.systems.emplace_back(new systems::Transform);
  registry.systems.emplace_back(new systems::Render);

  const int polygon_count = 100;
  std::random_device rd;
  std::default_random_engine gen(rd());
  for (int i = 0; i < polygon_count; i++) {
    std::uniform_int_distribution<> vertex_dist(3, 8);
    auto vertices = random_n_gon(gen, vertex_dist(gen), 0.1);
    components::Polygon polygon = {vertices};

    std::uniform_real_distribution<float> color_dist(0, 1);
    components::Color color = {color_dist(gen), color_dist(gen),
                               color_dist(gen)};

    std::uniform_real_distribution<float> coord_dist(-1, 1);
    components::Transform transform = {
        glm::vec3(coord_dist(gen), coord_dist(gen), 0),
        glm::vec3(coord_dist(gen), coord_dist(gen), 0)};

    registry.add_moving_polygon(polygon, color, transform);
  }

  glutDisplayFunc(main_loop);
  glutIdleFunc(glutPostRedisplay);
  glutMainLoop();
}
