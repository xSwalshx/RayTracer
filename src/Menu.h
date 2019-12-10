#ifndef _MENU_
#define _MENU_

//System Includes
#include <iostream>
#include <Windows.h>

//Menu Class
class Menu
{
public:
  //Functions
  void printIntroduction();
  void printMain();
  void printSub();
  void printErrorMessage();
  void printThreadCount(int _threadCount);
  void printInfo(int _startX, int _endX, int _offsetX);
};

#endif // !_MENU_
