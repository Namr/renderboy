#include "utils.hpp"

using namespace rb;

ray::ray(){};

ray::ray(const glm::vec3 &a, const glm::vec3 &b) {
  o = a;
  dir = b;
}

glm::vec3 ray::origin() const { return o; }

glm::vec3 ray::direction() const { return dir; }

glm::vec3 ray::pointAtParameter(float t) const { return o + t * dir; }

camera::camera() {
  lowerLeftCorner = glm::vec3(-2.0f, -1.0f, -1.0f);
  horizonal = glm::vec3(4.0f, 0.0f, 0.0f);
  vertical = glm::vec3(0.0f, 2.0f, 0.0f);
  origin = glm::vec3(0.0f, 0.0f, 0.0f);
}

ray camera::getRay(float u, float v) {
  return ray(origin, lowerLeftCorner + u * horizonal + v * vertical - origin);
}
