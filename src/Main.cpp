//Local Includes
#include "Ray.h"
#include "Tracer.h"
#include "Camera.h"
#include "Geometry.h"
#include "ThreadContainer.h"
#include "Menu.h"

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

//System Includes
#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <Windows.h>
#include <chrono>
#include <ctime>

//Forward declare functions:
void mainMenu(glm::ivec2 _windowSize);
void subMenu(glm::ivec2 _windowSize);
void drawEveryPixel(glm::ivec2 _windowSize);
void rayTracer(glm::ivec2 _windowSize);
void rayTracerMT(glm::ivec2 _windowSize, int _threadCount);
void rayTracerThread(glm::ivec2 _windowSize, ThreadContainer _threadContainer, int _i);

//Global Variables
std::mutex mutex;
//-------------------------------------------------------------------------------------------------//
///Main
int main(int argc, char *argv[])
{
	//Variables:
	glm::ivec2 windowSize(640, 480);

  //Print the Intro
  Menu menuObj;
  menuObj.printIntroduction();

	//Call Menu Fucntion
	mainMenu(windowSize);

	return MCG::ShowAndHold();
}
//-------------------------------------------------------------------------------------------------//
///Menu System
//Main Menu
void mainMenu(glm::ivec2 _windowSize)
{
	//Variables
	int menuSelection = 0;
  glm::ivec2 windowSize = _windowSize;

	//Print Main Menu
  Menu menuObj;
	menuObj.printMain(); //Print Menu

	//While no Input
	while (menuSelection == 0)
	{
		//User Input
		std::cin >> menuSelection;

		//Menu Switch
		switch (menuSelection)
		{
		case 1:
			//Using 1 Thread
      if (!MCG::Init(windowSize)) { return; } //Initialize
      MCG::SetBackground(glm::ivec3(0, 0, 0)); //Blank Canvas
      rayTracerMT(windowSize, 1); //Ray Tracer Multi-Threaded Func

			break;
		case 2:
			//Using 2 Threads
      if (!MCG::Init(windowSize)) { return; } //Initialize
      MCG::SetBackground(glm::ivec3(0, 0, 0)); //Blank Canvas
      rayTracerMT(windowSize, 2); //Ray Tracer Multi-Threaded Func

			break;
		case 3:
			//Using 4 Threads
      if (!MCG::Init(windowSize)) { return; } //Initialize
      MCG::SetBackground(glm::ivec3(0, 0, 0)); //Blank Canvas
      rayTracerMT(windowSize, 4); //Ray Tracer Multi-Threaded Func

			break;
		case 4:
			//Using 8 Threads
      if (!MCG::Init(windowSize)) { return; } //Initialize
      MCG::SetBackground(glm::ivec3(0, 0, 0)); //Blank Canvas
      rayTracerMT(windowSize, 8); //Ray Tracer Multi-Threaded Func

			break;
		case 5:
			//Using Dynamic Thread List
			subMenu(windowSize);
			break;
		case 9:
			//Exit the Program

			break;
		default:
			//Clear the input and loop
			break;
		}
	}

	return;
}
//Sub Menu - Dynamic Thread Count
void subMenu(glm::ivec2 _windowSize)
{
	//Variables
	int threadCount = 0;
  glm::ivec2 windowSize = _windowSize;

	//While no input
	while (threadCount == 0)
	{
	  //Print Menu
    Menu menuObj;
	  menuObj.printSub(); //Print Menu

		//User Input
		std::cin >> threadCount;

    //For Loop for valid thread count
		for (int i = 1; i <= 8; i += i)
		{
      //Debug Stuff
      /*std::cout << "Value of i = " << i << std::endl;
      Sleep(2000);*/
			
      //Success Criteria
      if (threadCount == i)
			{
        //Print To Console
        menuObj.printThreadCount(threadCount); //Print Thread Count

        //Using Multithreaded RayTracer
        if (!MCG::Init(windowSize)) { return; } //Initialize
        MCG::SetBackground(glm::ivec3(0, 0, 0)); //Blank Canvas
        rayTracerMT(windowSize, threadCount); //Ray Tracer Multi-Threaded Func

        break;
			}
      //Fail Criteria
			else if (i != threadCount && i >= 128)
			{
        //Reset Thread Count
        threadCount = 0; 
        
        //Print to console
				menuObj.printErrorMessage(); //Print the error message

        break; //Break out of for loop
 			}
		}
	}

	return;
}
//-------------------------------------------------------------------------------------------------//
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
//-------------------------------------------------------------------------------------------------//
//Multi-Threaded Ray Tracer
void rayTracerMT(glm::ivec2 _windowSize, int _threadCount)
{
	//Create Local Variables
	int windowX = _windowSize.x;            // 640
	int windowY = _windowSize.y;            // 480

	const int threadCount = _threadCount;   // 4

	int startX = 0; //Starting Point        // 0
	int startY = 0; //Starting Point        // 0

	int endX = windowX; //End Point         // 640
	int endY = windowY; //End Point         // 480

	int offsetX = windowX / threadCount;    // 640 / 4
	int offsetY = windowY;                  // 480

	//Vector of ThreadContainer
	std::vector<ThreadContainer> vecThreadContainer;

  //Clear the screen
  system("CLS");

  //Start Time of Ray Tracer
  std::cout << "****************************************************" << std::endl;

  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);

  std::cout << "**Ray Tracer Started at : " << std::ctime(&start_time) << "\n"
            << "****************************************************" << "\n" << std::endl;

	//Initialize Vector
	for (int i = 0; i < threadCount; i++)
	{
    //End X
    endX = startX + offsetX;
    
		//Create a temp ThreadContainer Obj
		ThreadContainer tempTC(startX, startY, endX, endY, offsetX, offsetY);

		//Set tempTC Thread to a make shared ptr
		tempTC.m_Thread = std::make_shared<std::thread>(rayTracerThread, _windowSize, tempTC, i);

		//Put into vector list
		vecThreadContainer.push_back(tempTC);

		//Offset
		startX += offsetX;
	}

	//Wait for each thread to finish
	for (int i = 0; i < threadCount; i++)
	{
    vecThreadContainer[i].m_Thread->join();
  }

  //End Time of Ray Tracer 
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "****************************************************" << "\n"
            << "**Finished Ray Tracer at " << std::ctime(&end_time)
            << "**Elapsed time: " << elapsed_seconds.count() << "s\n"
            << "****************************************************" << "\n" << std::endl;
 
	return;
}

void rayTracerThread(glm::ivec2 _windowSize, ThreadContainer _threadContainer, int _i)
{
	//Here is where the pixel for loop and drawing will happen 
	//Variables:
	glm::ivec2 pixelPos;
	glm::ivec3 pixelCol(255, 0, 0);

	Camera camera(glm::mat4(1), glm::perspective(0.7f, ((float)_windowSize.x / (float)_windowSize.y), 0.1f, 100.0f));
	Tracer tracer;

	//Get the variables from the pass through obj and store as local variables
	int startX = _threadContainer.getStartX();
	int startY = _threadContainer.getStartY();
	int endX = _threadContainer.getEndX();
	int endY = _threadContainer.getEndY();
	int offsetX = _threadContainer.getOffsetX();
	int offsetY = _threadContainer.getOffsetY();

  //printInfo(startX, endX, offsetX);

  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);

	//Nested For
	for (int y = startY; y <= endY; y++)
	{
		for (int x = startX; x <= endX; x++)
		{
			pixelPos = glm::ivec2(x, y);

			Ray ray = camera.createRay(pixelPos, _windowSize);

			glm::vec3 pixelCol = tracer.traceRay(ray);

			mutex.lock();

			MCG::DrawPixel(pixelPos, pixelCol);

			mutex.unlock();
		}
	}
  
  std::cout << "****************************************************" << std::endl;

  std::cout << "Thread " << _i << " Started at : " << std::ctime(&start_time) << '\n';
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "Finished computation at " << std::ctime(&end_time)
    << "Elapsed time: " << elapsed_seconds.count() << "s\n";

  std::cout << "****************************************************" << "\n" << std::endl;

	return;
}
//-------------------------------------------------------------------------------------------------//