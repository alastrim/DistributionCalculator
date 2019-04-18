#pragma once
#include "misc.h"

class distribution;

class target_function
{
public:
  target_function (std::function<double (const std::vector<double> &)> function, std::vector<distribution> &base);
  double operator () (const std::vector<double> &);
  std::function<double (const std::vector<double> &)> m_function;
  int m_arg_count;
};
