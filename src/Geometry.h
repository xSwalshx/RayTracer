#ifndef _GEOMETRY_
#define _GEOMETRY_

//Local Includes
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

struct intersectionResult
{
public:
  bool hit;
  float distance;
  glm::vec3 intersectionPoint;
};

///GEOMETRY
class Geometry
{
private:

public:
  intersectionResult intersect(Ray _ray, glm::vec3 _sphereCentre, float _radius);
  glm::vec3 sphereNormal(glm::vec3 _sphereCentre, glm::vec3 _samplePoint, Sphere _sphere);
  glm::vec3 sphereColour(glm::vec3 _samplePoint, Light _light, Sphere _sphere);
};

#endif // !_GEOMETRY_
