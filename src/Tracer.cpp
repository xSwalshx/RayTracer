//Local Includes
#include "Tracer.h"
#include "Sphere.h"
#include "Geometry.h"
#include "Light.h"

//System Includes
#include <iostream>

///TRACER
//Trace Ray
glm::vec3 Tracer::traceRay(Ray _ray)
{
  //Colours
  glm::vec3 black(0, 0, 0); //Default Black
  glm::vec3 pixelCol(0, 0, 0); 
  glm::vec3 lightCol(1, 1, 1); //White
  glm::vec3 surfaceCol(1, 0, 0); //Red
  glm::vec3 surfaceColGreen(0, 1, 0); //Green
  
  //Create Objs
  Sphere sphere(2.0f, glm::vec3(0, 0, -10), surfaceColGreen);
  Light light(glm::vec3(-10, -10, 10), lightCol);

  //Geometry
  Geometry geometry;
  intersectionResult iR;
  iR = geometry.intersect(_ray, sphere.getCentrePoint(), sphere.getRadius());

  if (iR.hit == true)
  {
    //Call Sphere Normal
    glm::vec3 sphereNormal = geometry.sphereNormal(sphere.getCentrePoint(), iR.intersectionPoint, sphere); //Calculate sphere normal
    sphere.setSphereNormal(sphereNormal); //Set the sphere obj normal
    pixelCol = geometry.sphereColour(iR.intersectionPoint, light, sphere); //Calculate the pixel colour

    //pixelCol = glm::vec3(255, 0, 0); //Red
  }
  else if (iR.hit == false)
  {
    pixelCol = black;
    //std::cout << "False" << std::endl;
  }

  return pixelCol;
}