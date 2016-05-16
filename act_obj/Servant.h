#pragma once
#include <PrintInterface.h>

class Servant : public PrintInterface
{
public:
  Servant();

  ~Servant();

  void print(const CharString &text);
};