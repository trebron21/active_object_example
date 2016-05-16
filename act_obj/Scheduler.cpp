#include "Scheduler.h"


#include <CallTraceMacros.hxx>

DEFINE_TRACE_ENGINE(ActiveObject, Scheduler)

Scheduler::Scheduler(void)
{
}


Scheduler::~Scheduler(void)
{
}

void Scheduler::enqueue(QRunnable * ptr)
{
  TRACE_OUT_E(ActiveObject_Scheduler::engine, _M("enqueue called"));
  myQueue.enqueue(ptr);
}

void Scheduler::dispatch()
{
  QRunnable * ptr = myQueue.dequeue();

  if (ptr)
  {
    TRACE_OUT_E(ActiveObject_Scheduler::engine, _M("executing item->run"));
    ptr->run();

    if (ptr->autoDelete())
      delete ptr;
  }
}
