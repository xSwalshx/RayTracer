//Local Includes
#include "Ray.h"
#include "Tracer.h"
#include "Camera.h"
#include "Geometry.h"
#include "ThreadContainer.h"

//Include Libraries
#include "../MCG_GFX_Framework/MCG_GFX_Lib.h"

//System Includes
#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <Windows.h>

//Forward declare functions:
void mainMenu();
void subMenu();
void printMainMenu();
void printSubMenu();
void printErrorMessage();
void drawEveryPixel(glm::ivec2 _windowSize);
void rayTracer(glm::ivec2 _windowSize);
void rayTracerMT(glm::ivec2 _windowSize, int _threadCount);
void rayTracerThread(glm::ivec2 _windowSize, ThreadContainer _threadContainer);
void rayTracerMTPF(glm::ivec2 _windowSize, int _threadCount);
void rayTracerThreadPF(glm::ivec2 _windowSize, ThreadContainer _threadContainer);

//Global Variables
std::mutex mutex;

//Main
int main(int argc, char *argv[])
{
	//Variables:
	glm::ivec2 windowSize(640, 480);

	//Call Menu Fucntion
	mainMenu();

	//Initialize
	if (!MCG::Init(windowSize)) { return -1; }

	//Blank Canvas
	MCG::SetBackground(glm::ivec3(0, 0, 0));

	//Drawing
	//drawEveryPixel(windowSize);

	//Using the RayTracer
	//rayTracer(windowSize);

	//Using Multithreaded RayTracer
	rayTracerMT(windowSize, 4);

	//Using Multithreaded RayTracer with Process Frame
	//rayTracerMTPF(windowSize, 4);

	return MCG::ShowAndHold();
}

//Menu System
void mainMenu()
{
	//Variables
	int menuSelection = 0;

	//Print Main Menu
	printMainMenu();

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
			break;

		case 2:
			//Using 2 Threads

			break;
		case 3:
			//Using 4 Threads

			break;
		case 4:
			//Using 8 Threads

			break;
		case 5:
			//Using Dynamic Thread List
			system("CLS");
			subMenu();
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

void subMenu()
{
	//Variables
	int threadCount = 0;

	//Print Menu
	printSubMenu();

	//While no input
	while (threadCount == 0)
	{
		//User Input
		std::cin >> threadCount;

		for (int i = 1; i <= 128; i += i)
		{
			if (threadCount == i)
			{
				//Call function using thread count
				std::cout << "\n\n number of threads " << i << std::endl;
				system("Pause");

			}
			else
			{
				//Invalid Option
				//Clear the screen and the input and reset the sub menu
				std::cin.clear();
				system("CLS"); //Clear the screen
				printErrorMessage(); //Print the error message

			}
		}
	}

	return;
}

//Printing to the Console
void printMainMenu()
{
	//Text to screen
	std::cout << "//---------- A MULT-THREADED RAY TRACER ----------//" << "\n"
		<< "                                                    " << "\n"
		<< " 1 -> Ray Tracer Using One Thread                   " << "\n"
		<< " 2 -> Ray Tracer Using Two Threads                  " << "\n"
		<< " 3 -> Ray Tracer Using Four Threads                 " << "\n"
		<< " 4 -> Ray Tracer Using Eight Threads                " << "\n"
		<< " 5 -> Ray Tracer Using a Dyanmic Threads List       " << "\n"
		<< "                                                    " << "\n"
		<< " 9 -> Exit                                          " << "\n"
		<< "                                                    " << "\n"
		<< " Choose and Option -> ";

	return;
}

void printSubMenu()
{
	//Text to screen
	std::cout << "//---------- A MULT-THREADED RAY TRACER ----------//" << "\n"
		<< "                                                    " << "\n"
		<< " In a Dynamic List of Threads, you as the user      " << "\n"
		<< " defines how many threads you would like to use.    " << "\n"
		<< "																								    " << "\n"
		<< " Using a geometric sequence of Xi*2 choose a number " << "\n"
		<< " of threads from 2, 4, 8, 16, 32 etc up to 128      " << "\n"
		<< "                                                    " << "\n"
		<< " Choose and Option -> ";
	return;
}

void printErrorMessage()
{
	//Text to screen
	std::cout << "//---------- A MULT-THREADED RAY TRACER ----------//" << "\n"
		<< "                                                    " << "\n"
		<< "****************************************************" << "\n"
		<< "                   INVALID INPUT                    " << "\n"
		<< "				  	 PLEASE TRY A VALID INPUT					      " << "\n"
		<< "****************************************************" << "\n";

	Sleep(2000); //Sleep for 2 seconds

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

	//Initialize Vector
	for (int i = 0; i < threadCount; i++)
	{
		//Create a temp ThreadContainer Obj
		ThreadContainer tempTC(startX, startY, endX, endY, offsetX, offsetY);

		//Set tempTC Thread to a make shared ptr
		tempTC.m_Thread = std::make_shared<std::thread>(rayTracerThread, _windowSize, tempTC);

		//Put into vector list
		vecThreadContainer.push_back(tempTC);

		//Offset
		startX += offsetX;
	}

	//Call each thread
	for (int i = 0; i < threadCount; i++)
	{
		vecThreadContainer[i].m_Thread->join();
	}

	return;
}

void rayTracerThread(glm::ivec2 _windowSize, ThreadContainer _threadContainer)
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

	return;
}


//Multi-Threaded Ray Tracer Process Frame
void rayTracerMTPF(glm::ivec2 _windowSize, int _threadCount)
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

	//Initialize Vector
	for (int i = 0; i < threadCount; i++)
	{
		//Create a temp ThreadContainer Obj
		ThreadContainer tempTC(startX, startY, endX, endY, offsetX, offsetY);

		//Set tempTC Thread to a make shared ptr
		tempTC.m_Thread = std::make_shared<std::thread>(rayTracerThreadPF, _windowSize, tempTC);

		//Put into vector list
		vecThreadContainer.push_back(tempTC);

		//Offset
		startX += offsetX;
	}

	//Call each thread
	for (int i = 0; i < threadCount; i++)
	{
		vecThreadContainer[i].m_Thread->join();
	}

	return;
}

void rayTracerThreadPF(glm::ivec2 _windowSize, ThreadContainer _threadContainer)
{
	//Variables:
	glm::ivec2 pixelPos;
	glm::ivec3 pixelCol(255, 0, 0);

	//Keep track of time
	float timer = 0.0f;

	Camera camera(glm::mat4(1), glm::perspective(0.7f, ((float)_windowSize.x / (float)_windowSize.y), 0.1f, 100.0f));
	Tracer tracer;

	//Get the variables from the pass through obj and store as local variables
	int startX = _threadContainer.getStartX();
	int startY = _threadContainer.getStartY();
	int endX = _threadContainer.getEndX();
	int endY = _threadContainer.getEndY();
	int offsetX = _threadContainer.getOffsetX();
	int offsetY = _threadContainer.getOffsetY();

	while (MCG::ProcessFrame())
	{
		// Set every pixel to the same colour
		MCG::SetBackground(glm::ivec3(0, 0, 0));

		// Update our time variable
		timer += 1.0f / 60.0f;

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

			mutex.lock();

			MCG::ProcessFrame();

			mutex.unlock();

		}
	}

	return;
}


//Not Used
/*void drawEveryPixel(glm::ivec2 _windowSize)
{
	//variables:
	glm::ivec2 pixelpos;
	glm::ivec3 pixelcol(255, 0, 0);

	//nested for
	for (int y = 0; y <= _windowsize.y; y++)
	{
		for (int x = 0; x <= _windowsize.x; x++)
		{
			pixelpos = glm::ivec2(x, y);
			mcg::drawpixel(pixelpos, pixelcol);
		}
	}

	return;
}*/

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