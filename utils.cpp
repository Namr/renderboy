#include "utils.hpp"

using namespace rb;

glm::vec3 rb::reflect(glm::vec3 direction, glm::vec3 normal) {
  return direction - 2 * glm::dot(direction, normal) * normal;
}

bool rb::refract(const glm::vec3 &input, const glm::vec3 &normal,
                 float niOverNt, glm::vec3 &output) {
  glm::vec3 nInput = glm::normalize(input);
  float dt = glm::dot(nInput, normal);
  float discriminant = 1.0f - niOverNt * niOverNt * (1.0f - dt * dt);

  if (discriminant > 0) {
    output =
        niOverNt * (nInput - normal * dt) - (float)sqrt(discriminant) * normal;
    return true;
  } else {
    return false;
  }
}

float rb::shlick(float cosine, float ref_idx) {
  float r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow(1 - cosine, 5);
}

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
