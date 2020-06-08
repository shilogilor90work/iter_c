//
// template <typename IntType>
// std::vector<IntType> accumulate(std::vector<IntType> V);

#pragma once
#include <vector>
#include <stdexcept>
namespace itertools
{
  template <typename IntType>
  std::vector<IntType> accumulate(std::vector<IntType> V)
  {
    std::vector<IntType> result;
    result.push_back(V[0]);
    for (int i=1;i<V.size();++i)
    {
      result.push_back(result[i-1]+V[i]);
    }
    return result;
  }
  
  template <typename IntType, class BinaryOperation>
  std::vector<IntType> accumulate(std::vector<IntType> V, BinaryOperation op)
  {
    std::vector<IntType> result;
    result.push_back(V[0]);
    for (int i=1;i<V.size();++i)
    {
      result.push_back(op(result[i-1],V[i]));
    }
    return result;
  }
}
