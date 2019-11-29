//Local Includes
#include "Ray.h"
#include "Tracer.h"
#include "Camera.h"
#include "Geometry.h"

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

//System Includes
#include <iostream>
#include <cmath>

//Forward declare functions:
void drawEveryPixel(glm::ivec2 _windowSize);
void rayTracer(glm::ivec2 _windowSize);

//Main
int main(int argc, char *argv[])
{
  //Variables:
  glm::ivec2 windowSize(640, 480);

  //Initialize
  if (!MCG::Init(windowSize)) { return -1; }

  //Blank Canvas
  MCG::SetBackground(glm::ivec3(0, 0, 0));

  //Drawing
  //drawEveryPixel(windowSize);

  //Using the RayTracer
  rayTracer(windowSize);

  return MCG::ShowAndHold();
}

//Not Used
void drawEveryPixel(glm::ivec2 _windowSize)
{
  //Variables:
  glm::ivec2 pixelPos;
  glm::ivec3 pixelCol(255, 0, 0);

  //Nested for
  for (int y = 0; y <= _windowSize.y; y++)
  {
    for (int x = 0; x <= _windowSize.x; x++)
    {
      pixelPos = glm::ivec2(x, y);
      MCG::DrawPixel(pixelPos, pixelCol);
    }
  }

  return;
}

//Ray Tracer
void rayTracer(glm::ivec2 _windowSize)
{
  //Variables:
  glm::ivec2 pixelPos;
  glm::ivec3 pixelCol(255, 0, 0);

  Camera camera(glm::mat4(1), glm::perspective(0.7f, ((float)_windowSize.x / (float)_windowSize.y), 0.1f, 100.0f));
  Tracer tracer;

  //Nested for
  for (int y = 0; y <= _windowSize.y; y++)
  {
    for (int x = 0; x <= _windowSize.x; x++)
    {
      pixelPos = glm::ivec2(x, y);

      Ray ray = camera.createRay(pixelPos, _windowSize);

      glm::vec3 pixelCol = tracer.traceRay(ray);

      MCG::DrawPixel(pixelPos, pixelCol);
    }
  }

  std::cout << "Sphere has been rendered" << std::endl;

  return;
}

// Advanced access - comment out the above DrawPixel and MCG::ShowAndHold lines, then uncomment the following:
/*
// Variable to keep track of time
float timer = 0.0f;

// This is our game loop
// It will run until the user presses 'escape' or closes the window
while( MCG::ProcessFrame() )
{
  // Set every pixel to the same colour
  MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

  // Change our pixel's X coordinate according to time
  pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
  // Update our time variable
  timer += 1.0f / 60.0f;

  // Draw the pixel to the screen
  MCG::DrawPixel( pixelPosition, pixelColour );

}

return 0;
*/