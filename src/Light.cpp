//Local Includes
#include "Light.h"

Light::Light(glm::vec3 _lightPos, glm::vec3 _lightColour)
{
  setLightPos(_lightPos);
  setLightColour(_lightColour);
}

Light::~Light()
{

}