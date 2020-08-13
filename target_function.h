#pragma once
#include "misc.h"

class distribution;

class target_function
{
public:
  target_function (std::function<element_t (const std::vector<element_t> &)> function, std::vector<distribution> &base);
  element_t operator () (const std::vector<element_t> &);
  std::function<element_t (const std::vector<element_t> &)> m_function;
  int m_arg_count;
};
