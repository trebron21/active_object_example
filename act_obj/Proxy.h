#pragma once
#include "printinterface.h"

class Proxy : public PrintInterface
{
public:
  Proxy(void);
  ~Proxy(void);
  void print(const CharString &text);
};

