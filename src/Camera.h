#ifndef _CAMERA_
#define _CAMERA_

//Local Includes
#include "Ray.h"

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

///CAMERA
class Camera
{
private:

public:
  //Constructor
  Camera(glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix);

  //Destructor
  ~Camera();

  //Variables

  glm::mat4 m_ViewMatrix;
  glm::mat4 m_ProjectionMatrix;

  //Functions
  Ray createRay(glm::ivec2 _pixelPos, glm::ivec2 _windowSize);
};

#endif // !_CAMERA_
