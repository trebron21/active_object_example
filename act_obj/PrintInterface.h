#pragma once
#include <CharString.hxx>

class PrintInterface
{
public:
  virtual void print(const CharString &text) = 0;
};