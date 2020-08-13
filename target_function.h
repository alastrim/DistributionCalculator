#pragma once
#include "misc.h"

class distribution;

class target_function
{
public:
  target_function (std::function<element_type (const std::vector<element_type> &)> function, std::vector<distribution> &base);
  element_type operator () (const std::vector<element_type> &);
  std::function<element_type (const std::vector<element_type> &)> m_function;
  int m_arg_count;
};
