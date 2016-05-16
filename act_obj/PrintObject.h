#pragma once

#include <qrunnable.h>

#include "PrintInterface.h"

#include <CharString.hxx>

class PrintObject : public QRunnable
{
public:
  PrintObject(PrintInterface *, const CharString &);

  ~PrintObject(void);

  virtual void run();

private:
  PrintInterface * target;
  CharString text;
};
