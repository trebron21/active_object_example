#pragma once

#include <ActivationQueue.h>

class Scheduler
{
public:
  Scheduler(void);
  ~Scheduler(void);

  void enqueue(QRunnable *);

  void dispatch();

private:
  ActivationQueue myQueue;
};

