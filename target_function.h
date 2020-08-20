#pragma once
#include "misc.h"

template<typename ElemT>
class distribution;

template<typename ElemT>
class target_function
{
public:
  target_function (
      std::function<ElemT (const std::vector<ElemT> &)> function,
      std::vector<distribution<ElemT>> &base)
    : m_function (function), m_arg_count (toi (base.size ()))
  {
  }

  ElemT operator () (const std::vector<ElemT> &values)
  {
    al_assert (values.size () == tou (m_arg_count), "Bad value vector size");
    return m_function (values);
  }

  std::function<ElemT (const std::vector<ElemT> &)> m_function;
  int m_arg_count;
};
