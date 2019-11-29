#ifndef _TRACER_
#define _TRACER_

//Local Includes
#include "Ray.h"

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

///TRACER
class Tracer
{
private:

public:
  glm::vec3 traceRay(Ray _ray);
};

#endif // !_TRACER_