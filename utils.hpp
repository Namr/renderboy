#ifndef UTILSH
#define UTILSH

#include <cmath>
#include <glm/glm.hpp>

namespace rb {

// vector math helpers
glm::vec3 reflect(glm::vec3 direction, glm::vec3 normal);
bool refract(const glm::vec3 &input, const glm::vec3 &normal, float niOverNt,
             glm::vec3 &output);
float shlick(float cosine, float ref_idx);

class ray {

public:
  ray();
  ray(const glm::vec3 &a, const glm::vec3 &b);
  glm::vec3 origin() const;
  glm::vec3 direction() const;
  glm::vec3 pointAtParameter(float t) const;

private:
  glm::vec3 o;
  glm::vec3 dir;
};

class camera {
public:
  camera(glm::vec3 origin, glm::vec3 focusPoint, float verticalFOV,
         float aspectRatio);
  ray getRay(float u, float v);

private:
  glm::vec3 origin;
  glm::vec3 lowerLeftCorner;
  glm::vec3 horizonal;
  glm::vec3 vertical;
};

} // namespace rb
#endif
