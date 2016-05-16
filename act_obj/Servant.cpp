#include <Servant.h>

#include <CallTraceMacros.hxx>

DEFINE_TRACE_ENGINE(ActiveObject, Servant);

Servant::Servant(void)
{

}

Servant::~Servant(void)
{

}

void Servant::print(const CharString &text)
{
  TRACE_OUT_E(ActiveObject_Servant::engine, _M("doing the print with text %1") << text);
}