//Local Includes
#include "Menu.h"

void Menu::printIntroduction()
{
  std::cout << "//---------- A MULT-THREADED RAY TRACER ----------//" << "\n"
    << "                                                    " << "\n"
    << "             When choosing the amount of            " << "\n"
    << "               threads to use for this              " << "\n"
    << "        be sure that your CPU has that amount       " << "\n"
    << "             of threads at its disposal.            " << "\n"
    << "                                                    " << "\n"
    << "             You can do this by pressing:           " << "\n"
    << "                 CTRL + SHIFT + ESC                 " << "\n"
    << "                                                    " << "\n"
    << "        This will bring up the 'TASK MANAGER'       " << "\n"
    << "                 Select 'PERFORMANCE'               " << "\n"
    << "          and at the bottom right there is          " << "\n"
    << "   how many 'LOGICAL PROCESSORS' that your CPU has  " << "\n"
    << "                                                    " << "\n"
    << "     ***** NOTE THIS IS THE MAX NUMBER OF *****     " << "\n"
    << "          ***** THREADS YOUR PC HAS *****           " << std::endl;
      

  Sleep(10000); //Sleep for 5 seconds

  return;
}

void Menu::printMain()
{
  //Clear the screen
  system("CLS");

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

void Menu::printSub()
{
  //Clear the screen
  system("CLS");

  //Text to screen
  std::cout << "//---------- A MULT-THREADED RAY TRACER ----------//" << "\n"
    << "                                                    " << "\n"
    << " In a Dynamic List of Threads, you as the user      " << "\n"
    << " defines how many threads you would like to use.    " << "\n"
    << "																								    " << "\n"
    << " Using a geometric sequence of Xi*2 choose a number " << "\n"
    << " of threads from 1, 2, 4, or 8                      " << "\n"
    << "                                                    " << "\n"
    << " Choose and Option -> ";

  return;
}

void Menu::printErrorMessage()
{
  //Clear the screen
  system("CLS");

  //Text to screen
  std::cout << "//---------- A MULT-THREADED RAY TRACER ----------//" << "\n"
    << "                                                    " << "\n"
    << "****************************************************" << "\n"
    << "                   INVALID INPUT                    " << "\n"
    << "             PLEASE TRY A VALID INPUT               " << "\n"
    << "****************************************************" << "\n";

  Sleep(2000); //Sleep for 2 seconds

  return;
}

void Menu::printThreadCount(int _threadCount)
{
  //Clear the screen
  system("CLS");

  //Text to Screen
  std::cout << "****************************************************" << "\n"
    << "                                                    " << "\n"
    << " Muti-Threaded Ray Tracer using " << _threadCount << " threads   " << "\n"
    << "                                                    " << "\n"
    << "****************************************************" << "\n"
    << std::endl;

  return;
}

void Menu::printInfo(int _startX, int _endX, int _offsetX)
{
  //Debuggin Information
  std::cout << "Start X " << _startX << "\n"
    << "End X " << _endX << "\n"
    << "Offset X " << _offsetX << "\n";

  return;
}