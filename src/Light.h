#ifndef _LIGHT_
#define _LIGHT_

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

class Light
{
private:
  //Variables
  glm::vec3 m_LightPos;
  glm::vec3 m_LightColour;

public:
  //Constructor
  Light(glm::vec3 _lightPos, glm::vec3 _lightColour);

  //Destructor
  ~Light();
  
  //Variables



  //Setters & Getters
  void setLightPos(glm::vec3 _lightPos) { m_LightPos = _lightPos; }
  glm::vec3 getLightPos() { return m_LightPos; }

  void setLightColour(glm::vec3 _lightColour) { m_LightColour = _lightColour; }
  glm::vec3 getLightColour() { return m_LightColour; }


};

#endif // !_LIGHT_
