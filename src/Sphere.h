#ifndef _SPHERE_
#define _SPHERE_

//Local Includes
#include "Ray.h"

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

///SPHERE
class Sphere
{
private:
  float m_Radius;
  glm::vec3 m_CentrePoint;
  glm::vec3 m_SphereColour;
  glm::vec3 m_SphereNormal;

public:
  //Constructor
  Sphere(float _radius, glm::vec3 _CentrePoint, glm::vec3 _sphereColour);

  //Destructor
  ~Sphere();
  
  //Getters & Setters
  void setRadius(float _radius) { m_Radius = _radius; }
  float getRadius() { return m_Radius; }

  void setCentrePoint(glm::vec3 _centrePoint) { m_CentrePoint = _centrePoint; }
  glm::vec3 getCentrePoint() { return m_CentrePoint; }

  void setSphereColour(glm::vec3 _sphereColour) { m_SphereColour= _sphereColour; }
  glm::vec3 getSphereColour() { return m_SphereColour; }

  void setSphereNormal(glm::vec3 _sphereNormal) { m_SphereNormal = _sphereNormal; }
  glm::vec3 getSphereNormal() { return m_SphereNormal; }

  //Functions:
  glm::vec3 shadePixel(Ray _ray, glm::vec3 _intersectPoint);
};

#endif // !_SHPERE_
