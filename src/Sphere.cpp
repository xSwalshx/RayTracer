//Local Includes
#include "Sphere.h"

///SPHERE
//Constructor
Sphere::Sphere(float _radius, glm::vec3 _CentrePoint, glm::vec3 _sphereColour)
{
  setRadius(_radius);
  setCentrePoint(_CentrePoint);
  setSphereColour(_sphereColour);
}

//Destructor
Sphere::~Sphere()
{

}

//Shade Pixel
glm::vec3 Sphere::shadePixel(Ray _ray, glm::vec3 _intersectPoint)
{
  glm::vec3 pixelCol(0, 0, 255); //Blue

  return pixelCol;
}