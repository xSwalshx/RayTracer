//Local Includes
#include "Ray.h"

//Constructor
Ray::Ray(glm::ivec2 _origin, glm::vec3 _direction)
{
  m_Origin.x = _origin.x;
  m_Origin.y = _origin.y;

  m_Direction = _direction;
}

//Destructor
Ray::~Ray()
{

}