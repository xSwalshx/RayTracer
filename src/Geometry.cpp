//Local Includes
#include "Geometry.h"

///GEOMETRY
//Ray-Sphere Intersection
intersectionResult Geometry::intersect(Ray _ray, glm::vec3 _sphereCentre, float _radius)
{
  intersectionResult iR;
  iR.hit = false;

  //Equation Variables:
  glm::vec3 a = _ray.m_Origin;
  glm::vec3 P = _sphereCentre;
  glm::vec3 n = _ray.m_Direction;
  float d = 0.0f;

  //Get X First
  glm::vec3 One = P - a; // (P - a)
  glm::vec3 Two = n; // n
  float Three = glm::dot(One, Two); // ((P - a) dot n)
  glm::vec3 Four = Three * Two; // ((P - a) dot n) * n

  glm::vec3 x = a + Four; // X = a + ((P - a) dot n) * n

  d = glm::length((P - a) - Four); // d = ||P - a - ((P - a) dot n) * n||

  if (d <= _radius)
  {
    iR.hit = true;

    //Calculate the Distance
    float xx = glm::sqrt((_radius * _radius) - (d * d)); // x = sqrt(r^2 - d^2)
    iR.distance = (Three - xx); // ((P - a) dot n) - x

    //Calculate the Intersection Point
    glm::vec3 iP = a + iR.distance * n; // a + (((P- a) dot n) - x) * n
    iR.intersectionPoint = iP;

    if (iR.distance < 0)
    {
      iR.hit = false;
    }
  }

  return iR;
}

glm::vec3 Geometry::sphereNormal(glm::vec3 _sphereCentre, glm::vec3 _samplePoint, Sphere _sphere)
{ 
  ///Calculate the Normal
  glm::vec3 sphereNormal = _samplePoint -_sphereCentre;
  sphereNormal = glm::normalize(sphereNormal);
  
  //_sphere.setSphereNormal(sphereNormal);

  return sphereNormal;
}

glm::vec3 Geometry::sphereColour(glm::vec3 _samplePoint, Light _light, Sphere _sphere)
{
  //Variables
  glm::vec3 pixelCol = _sphere.getSphereColour();
  
  //Equation Variables
  glm::vec3 w = (-_samplePoint + _light.getLightPos()); //w = -intersectionPoint + Light Pos
  w = glm::normalize(w); //Normalize w
  glm::vec3 Li = _light.getLightColour(); //Li is Light Colour so vec3
  glm::vec3 Kd = _sphere.getSphereColour(); //Kd is surface colour so vec3

  //Calculate the Colour
  float x = glm::dot(w, _sphere.getSphereNormal()); // (w dot N)
  pixelCol = glm::max(x, 0.0f) * Li * Kd; //L = (w dot N) * Li * Kd
  pixelCol *= 255.0f;

  return pixelCol;
}
