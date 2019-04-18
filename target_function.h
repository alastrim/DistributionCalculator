#pragma once
#include "misc.h"

class distribution;

class target_function
{
public:
  target_function (std::function<val_and_base (const std::vector<val_and_base> &)> function, std::vector<distribution> &base);
  val_and_base operator () (const std::vector<val_and_base> &);
  std::function<val_and_base (const std::vector<val_and_base> &)> m_function;
  int m_arg_count;
};
