#include "surfaces.hpp"

using namespace rb;

sphere::sphere() {}
sphere::sphere(glm::vec3 center, float radius, rb::material *mat) {
  this->center = center;
  this->radius = radius;
  this->mat = mat;
}

bool sphere::hit(const rb::ray &r, float t_min, float t_max,
                 hit_record &rec) const {

  glm::vec3 offsetFromCenter = r.origin() - center;
  float a = glm::dot(r.direction(), r.direction());
  float b = 2.0f * glm::dot(r.direction(), offsetFromCenter);
  float c = glm::dot(offsetFromCenter, offsetFromCenter) - radius * radius;

  float discriminant = b * b - 4 * a * c;

  if (discriminant > 0) {
    float t = (-b - sqrt(discriminant)) / (2.0f * a);
    if (t < t_min || t > t_max) {
      t = (-b + sqrt(discriminant)) / (2.0f * a);
      if (t < t_min || t > t_max)
        return false;
    }

    rec.t = t;
    rec.p = r.pointAtParameter(t);
    rec.normal = glm::normalize(rec.p - center);
    rec.mat = this->mat;
    return true;
  }
  return false;
}

sphere::~sphere() { delete mat; }

diffuse::diffuse(glm::vec3 color) : albedo(color) {}

bool diffuse::scatter(const rb::ray &input, const rb::hit_record &record,
                      glm::vec3 &attenuation, rb::ray &output) const {
  glm::vec3 target = record.p + record.normal + glm::ballRand(1.0f);
  output = rb::ray(record.p, target - record.p);
  attenuation = albedo;
  return true;
}

metal::metal(glm::vec3 color) : albedo(color) {}

bool metal::scatter(const rb::ray &input, const rb::hit_record &record,
                    glm::vec3 &attenuation, rb::ray &output) const {
  glm::vec3 reflectedRay =
      rb::reflect(glm::normalize(input.direction()), record.normal);

  output = rb::ray(record.p, reflectedRay);
  attenuation = albedo;
  return glm::dot(output.direction(), record.normal) > 0;
}

world::world() : surfaceList() {}

world::~world() {
  for (surface *s : surfaceList) {
    delete s;
  }
}

bool world::castRay(const rb::ray &r, float t_min, float t_max,
                    hit_record &record) const {
  rb::hit_record temp;
  bool hasHit = false;
  double closestHit = t_max;

  // check every surface to see which the ray hits first
  for (surface *s : surfaceList) {
    if (s->hit(r, t_min, closestHit, temp)) {
      hasHit = true;
      closestHit = temp.t;
      record = temp;
    }
  }

  return hasHit;
}

glm::vec3 world::colorRay(const rb::ray &r, int bounce) const {
  rb::hit_record record;

  // does this ray hit anything?
  if (castRay(r, 0.001, MAXFLOAT, record)) {
    // bounce the ray again to get the color of the hit surface
    // direction of bounce is determined by the surface material
    rb::ray bounceRay;
    glm::vec3 attenuation;

    if (bounce < 50 && record.mat->scatter(r, record, attenuation, bounceRay)) {
      return attenuation * colorRay(bounceRay, bounce + 1);
    } else {
      return glm::vec3(0, 0, 0);
    }
  }

  // otherwise color in the sky
  glm::vec3 unit_direction = glm::normalize(r.direction());
  float d = 0.5f * (unit_direction.y + 1.0f);
  return (1.0f - d) * glm::vec3(1.0, 1.0, 1.0) + d * glm::vec3(0.5, 0.7, 1.0);
}

void world::addSphere(glm::vec3 center, float radius, rb::material *mat) {
  surfaceList.push_back(new sphere(center, radius, mat));
}
