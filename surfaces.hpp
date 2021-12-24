#ifndef SURFACESH
#define SURFACESH

#include "utils.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <vector>

namespace rb {

class material;
struct hit_record {
  float t;
  glm::vec3 p;
  glm::vec3 normal;
  material *mat;
};

class surface {
public:
  virtual bool hit(const rb::ray &r, float t_min, float t_max,
                   hit_record &rec) const = 0;

protected:
  rb::material *mat;
};

class sphere : public surface {
public:
  sphere();
  sphere(glm::vec3 center, float radius, rb::material *mat);
  virtual bool hit(const rb::ray &r, float t_min, float t_max,
                   hit_record &rec) const override;

  ~sphere();

protected:
  rb::material *mat;

private:
  glm::vec3 center;
  float radius;
};

class material {
public:
  virtual bool scatter(const rb::ray &input, const rb::hit_record &record,
                       glm::vec3 &attenuation, rb::ray &output) const = 0;
};

class diffuse : public material {
public:
  diffuse(glm::vec3 color);
  virtual bool scatter(const rb::ray &input, const rb::hit_record &record,
                       glm::vec3 &attenuation, rb::ray &output) const;

private:
  glm::vec3 albedo;
};

class metal : public material {
public:
  metal(glm::vec3 color);
  virtual bool scatter(const rb::ray &input, const rb::hit_record &record,
                       glm::vec3 &attenuation, rb::ray &output) const;

private:
  glm::vec3 albedo;
};

class world {
public:
  world();
  glm::vec3 colorRay(const rb::ray &r, int bounce) const;
  bool castRay(const rb::ray &r, float t_min, float t_max,
               hit_record &record) const;
  void addSphere(glm::vec3 center, float radius, rb::material *mat);
  ~world();

private:
  std::vector<surface *> surfaceList;
};

} // namespace rb

#endif
