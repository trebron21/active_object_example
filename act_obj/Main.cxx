// ----------------------------
// Multithreading workshop
// Producer - Consumer pattern
// with a Bounded-buffer
// ----------------------------

#include <iostream>
#include <stdio.h>

#include <qthread.h>
#include <qmutex.h>
#include <qsemaphore.h>
#include <qqueue.h>

#include <CharString.hxx>
#include <Scheduler.h>
#include <Proxy.h>

using namespace std;

#include <CallTraceMacros.hxx>
#define tr_engine ActiveObject_main
DEFINE_TRACE_ENGINE(ActiveObject, main)

// -----------------------------------------
// Bounded Buffer
QQueue<int> myBuffer;
// protect access to buffer
QMutex mutex;
// initialized with the max number of elements, that we want to have in the queue
// holds number of free slots
QSemaphore emptyBuffer(100);
// holds number of busy slots
QSemaphore fullBuffer(0);
// -----------------------------------------

Scheduler theScheduler;
Proxy theProxy;

// ---------------
// ClientThread
// ---------------
class ClientThread : public QThread
{
  public:
    ClientThread()
    {
      value = 0;
      stopped = false;
    }

    void setName(const CharString &newName)
    {
      myName = newName;
    }

    void stop();

  protected:
    void run();

  private:
    CharString myName;
    int value;
    volatile bool stopped;
};


void ClientThread::run()
{
  while (!stopped)
  {
    // output trace
    TRACE_OUT_E(tr_engine::engine, _M("calling print on proxy with value %1") << myName );

    theProxy.print( CharString("item") + value++ + "from thread " + myName);
    QThread::msleep(100);
  }
}

void ClientThread::stop()
{
  // output trace
  TRACE_OUT_E(tr_engine::engine, _M("Stopping thread %1") << myName);

  stopped = true;
}

// ---------------
// DispatchThread
// ---------------
class DispatchThread : public QThread
{
  public:
    DispatchThread()
    {
      stopped = false;
    }

    void setName(const CharString &newName)
    {
      myName = newName;
    }

    void stop();

  protected:
    void run();

  private:
    CharString myName;
    volatile bool stopped;
};


void DispatchThread::run()
{
  while (!stopped)
  {
    // output trace
    TRACE_OUT_E(tr_engine::engine, _M("calling dispatch") << myName);

    theScheduler.dispatch();
  }
}


void DispatchThread::stop()
{
  // output trace
  TRACE_OUT_E(tr_engine::engine, _M("Stopping thread %1") << myName);

  stopped = true;
}


int main(int argc, char *argv[])
{
  TRACE_OUT_E(tr_engine::engine, _M("Application started"));

  ClientThread client;
  client.setName("Client");
  client.start();

  DispatchThread dispatcher;
  dispatcher.setName("Dispatcher");
  dispatcher.start();

  cout << "press any key to stop ..." << endl;
  getchar();

  TRACE_OUT_E(tr_engine::engine, _M("Stopping threads ..."));
  dispatcher.stop();
  client.stop();

  while (client.isRunning() || dispatcher.isRunning())
  {
    QThread::msleep(10);
  }

  return 0;
}
