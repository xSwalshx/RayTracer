#ifndef _THREAD_CONTAINER_
#define _THREAD_CONTAINER_

//System Includes
#include <thread>

///THREAD CONTAINER
class ThreadContainer
{
private:
  //Variables
  int m_StartX;
  int m_StartY;
  int m_EndX;
  int m_EndY;
  int m_OffsetX;
  int m_OffsetY;

public:
  //Constructor
  ThreadContainer(int _StartX, int _StartY, int _EndX, int _EndY, int _OffsetX, int _OffsetY);

  //Destructor
  ThreadContainer();

  //Variables
  std::shared_ptr<std::thread> m_Thread;

  //Setters & Getters
  void setStartX(int _StartX) { m_StartX = _StartX; }
  int getStartX() { return m_StartX; }

  void setStartY(int _StartY) { m_StartY = _StartY; }
  int getStartY() { return m_StartY; }

  void setEndX(int _EndX) { m_EndX = _EndX; }
  int getEndX() { return m_EndX; }

  void setEndY(int _EndY) { m_EndY = _EndY; }
  int getEndY() { return m_EndY; }

  void setOffsetX(int _OffsetX) { m_OffsetX = _OffsetX; }
  int getOffsetX() { return m_OffsetX; }

  void setOffsetY(int _OffsetY) { m_OffsetY = _OffsetY; }
  int getOffsetY() { return m_OffsetY; }
};

#endif //!_THREAD_CONTAINER_