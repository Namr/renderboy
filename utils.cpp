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

camera::camera(glm::vec3 origin, glm::vec3 focusPoint, float verticalFOV,
               float aspectRatio) {
  glm::vec3 up(0, 1, 0);
  glm::vec3 w, u, v;
  float theta = verticalFOV * M_PI / 180.0f; // convert to radians
  float halfHeight = tan(theta / 2.0f);
  float halfWidth = aspectRatio * halfHeight;
  this->origin = origin;
  w = glm::normalize(origin - focusPoint);
  u = glm::normalize(glm::cross(up, w));
  v = glm::cross(w, u);
  lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
  horizonal = 2.0f * halfWidth * u;
  vertical = 2.0f * halfHeight * v;
}

ray camera::getRay(float u, float v) {
  return ray(origin, lowerLeftCorner + u * horizonal + v * vertical - origin);
}
