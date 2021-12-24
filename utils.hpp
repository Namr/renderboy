#ifndef UTILSH
#define UTILSH

#include <glm/glm.hpp>

namespace rb {

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
  camera();
  ray getRay(float u, float v);

private:
  glm::vec3 origin;
  glm::vec3 lowerLeftCorner;
  glm::vec3 horizonal;
  glm::vec3 vertical;
};

} // namespace rb
#endif
