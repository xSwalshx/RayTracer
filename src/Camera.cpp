//Local Includes
#include "Camera.h"

///CAMERA
//Constructor
Camera::Camera(glm::mat4 _viewMatrix, glm::mat4 _projectionMatrix)
{
  m_ViewMatrix = _viewMatrix;
  m_ProjectionMatrix = _projectionMatrix;
}

//Destructor
Camera::~Camera()
{

}

//Create Ray
Ray Camera::createRay(glm::ivec2 _pixelPos, glm::ivec2 _windowSize)
{
  //Variables
  glm::vec2 mapping;
  glm::vec4 nearPlane;
  glm::vec4 farPlane;

  //Mapping Coordinates
  mapping.x = (((float)_pixelPos.x / (float)_windowSize.x) * 2.0f) - 1.0f;
  mapping.y = (((float)_pixelPos.y / (float)_windowSize.y) * 2.0f) - 1.0f;

  //Near and Far Planes
  nearPlane = glm::vec4(mapping.x, mapping.y, -1.0f, 1.0f);
  farPlane = glm::vec4(mapping.x, mapping.y, 1.0f, 1.0f);

  //Apply Inverse Projection Matrix
  nearPlane = glm::inverse(m_ProjectionMatrix) * nearPlane;
  farPlane = glm::inverse(m_ProjectionMatrix) * farPlane;

  //Divide by 'w'
  nearPlane /= nearPlane.w;
  farPlane /= farPlane.w;

  //Apply Inverse View Matrix
  nearPlane = glm::inverse(m_ViewMatrix) * nearPlane;
  farPlane = glm::inverse(m_ViewMatrix) * farPlane;

  //Calculate Origin and Direction
  glm::vec3 origin = glm::vec3(nearPlane.x, nearPlane.y, nearPlane.z);
  glm::vec3 direction = glm::normalize(glm::vec3(farPlane.x, farPlane.y, farPlane.z) - origin);

  //Create a Ray
  Ray ray(origin, direction);

  return ray;
}