#pragma once


namespace itertools
{

template <typename IntType>
std::vector<IntType> compress(std::vector<IntType> S, std::vector<bool> V)
{
  std::vector<IntType> result;
  for (int i=0;i<V.size();++i)
  {
    if ((V[i]))
    {
      result.push_back(S[i]);
    }
  }
  return result;
}

std::vector<char> compress(std::string S, std::vector<bool> V)
{
  std::vector<char> result;
  for (int i=0;i<V.size();++i)
  {
    if ((V[i]))
    {
      result.push_back(S[i]);
    }
  }
  return result;
}
}
