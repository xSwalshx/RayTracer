#ifndef _RAY_
#define _RAY_

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

///RAY
class Ray
{
private:

public:
  //Constructor
  Ray(glm::ivec2 _pixelPos, glm::vec3 _direction);

  //Destructor
  ~Ray();

  //Variables:
  glm::vec3 m_Origin;
  glm::vec3 m_Direction;
};

#endif // !_RAY_
