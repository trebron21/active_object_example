#include "ActivationQueue.h"

#include <CallTraceMacros.hxx>

DEFINE_TRACE_ENGINE(ActiveObject, Servant)


ActivationQueue::ActivationQueue(int slots)
{
  maxSlots = slots;
}


ActivationQueue::~ActivationQueue(void)
{
  while (!myBuffer.isEmpty())
  {
    QRunnable * ptr = myBuffer.dequeue();
    delete ptr;
  }
}

void ActivationQueue::enqueue(QRunnable * ptr)
{
  QMutexLocker lock(&mutex);

  while (myBuffer.length() >= maxSlots)
  {
    bufferIsNotFull.wait(&mutex);
  }

  myBuffer.enqueue(ptr);
  bufferIsNotEmpty.wakeOne();

  TRACE_OUT_E(ActiveObject_Servant::engine, _M("added new item"));
}

QRunnable * ActivationQueue::dequeue()
{
  QMutexLocker lock(&mutex);

  while (myBuffer.isEmpty())
  {
    bufferIsNotEmpty.wait(&mutex);
  }

  QRunnable * ptr = myBuffer.dequeue();
  bufferIsNotFull.wakeOne();

  TRACE_OUT_E(ActiveObject_Servant::engine, _M("removed an item"));

  return ptr;
}

bool ActivationQueue::isEmpty() const
{
  return myBuffer.isEmpty();
}