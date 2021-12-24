#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>

#include "surfaces.hpp"
#include "utils.hpp"

const int IMAGE_WIDTH = 200;
const int IMAGE_HEIGHT = 50;
const int SAMPLES = 100;

int main(int argc, char const *argv[]) {
  std::ofstream imageFile("output.ppm");

  if (imageFile.is_open()) {

    // insert ppm image header
    imageFile << "P3" << std::endl;
    imageFile << IMAGE_WIDTH << " " << IMAGE_HEIGHT << std::endl;
    imageFile << "255" << std::endl;

    // setup camera variables
    glm::vec3 cLowerLeft(-2.0, -1.0, -1.0); // lower left corner of the camera
    glm::vec3 cHorizontal(4.0, 0.0, 0.0);   // horizontal size of the camera
    glm::vec3 cVertical(0.0, 2.0, 0.0);     // vertical size of the camera
    glm::vec3 origin(0.0, 0.0, 0.0);        // camera center

    // create world and populate it with surfaces
    rb::world world;
    world.addSphere(glm::vec3(0, 0, -1), 0.5,
                    new rb::diffuse(glm::vec3(0.8, 0, 0)));
    world.addSphere(glm::vec3(0, -100.4, -1), 100,
                    new rb::diffuse(glm::vec3(0.0, 0.4, 0.0)));
    world.addSphere(glm::vec3(1, 0, -1), 0.5,
                    new rb::metal(glm::vec3(0.4, 0.4, 0.4)));

    // iterate over every pixel (x,y) on screen
    for (int y = IMAGE_HEIGHT - 1; y >= 0; y--) {
      for (int x = 0; x < IMAGE_WIDTH; x++) {

        glm::vec3 col(0.0f, 0.0f, 0.0f);

        // each pixel is the average of multiple ray samples within that pixel
        for (int s = 0; s < SAMPLES; s++) {
          // u,v are normalized x,y between 0 -> 1
          // plus some variation for the sample
          float u = float(x + drand48()) / float(IMAGE_WIDTH);
          float v = float(y + drand48()) / float(IMAGE_HEIGHT);

          // create a ray and find its color
          rb::ray ray(origin, cLowerLeft + u * cHorizontal + v * cVertical);
          col += world.colorRay(ray, 0);
        }
        col /= float(SAMPLES);

        // gamma correction
        col = glm::sqrt(col);

        // pixels are 8bit unsigned ints, but our color space is in 0.0 -> 1.0
        // make the needed conversion
        int r = int(255.99 * col.x);
        int g = int(255.99 * col.y);
        int b = int(255.99 * col.z);
        imageFile << r << " " << g << " " << b << std::endl;
      }
      // print progress report
      if (y % 5 == 0)
        std::cout << (((float)IMAGE_HEIGHT - y) / IMAGE_HEIGHT) * 100 << "%"
                  << std::endl;
    }
  }

  imageFile.close();
}
