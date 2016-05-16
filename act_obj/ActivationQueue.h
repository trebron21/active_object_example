#pragma once

#include <qmutex.h>
#include <qwaitcondition.h>
#include <qqueue.h>

#include <qrunnable.h>

class ActivationQueue
{
public:
  ActivationQueue(int slots = 100);

  ~ActivationQueue(void);

  void enqueue(QRunnable *);

  QRunnable * dequeue();

  bool isEmpty() const;

private:

  int maxSlots;
  QQueue<QRunnable *> myBuffer;

  QMutex mutex;
  QWaitCondition bufferIsNotFull;
  QWaitCondition bufferIsNotEmpty;
};

