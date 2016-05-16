#include "PrintObject.h"

#include <CallTraceMacros.hxx>
DEFINE_TRACE_ENGINE(ActiveObject, PrintObject);

PrintObject::PrintObject(PrintInterface * ptr, const CharString & t)
{
  TRACE_OUT_E(ActiveObject_PrintObject::engine, _M("created"));

  target = ptr;
  text = t;
}

PrintObject::~PrintObject()
{
  TRACE_OUT_E(ActiveObject_PrintObject::engine, _M("deleted"));
}

void PrintObject::run()
{
  TRACE_OUT_E(ActiveObject_PrintObject::engine, _M("doing run"));
}