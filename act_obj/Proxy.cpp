#include "Proxy.h"
#include <PrintObject.h>
#include <Servant.h>
#include <Scheduler.h>

Servant theServant;

extern Scheduler theScheduler;

Proxy::Proxy(void)
{
}

Proxy::~Proxy(void)
{
}

void Proxy::print(const CharString &text)
{
  PrintObject * ptr = new PrintObject(&theServant, text);
  theScheduler.enqueue(ptr);
}
