#pragma once

namespace itertools
{

template <typename IntType, class BinaryOperation>
std::vector<IntType> filterfalse(BinaryOperation op, std::vector<IntType> V)
{
  std::vector<IntType> result;
  for (int i=0;i<V.size();++i)
  {
    if (!op(V[i]))
    {
      result.push_back(V[i]);
    }
  }
  return result;
}
}
