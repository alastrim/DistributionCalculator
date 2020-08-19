#pragma once

#include "misc.h"

struct stats_t
{
  double m_average = 0;
  double m_median = 0;

  stats_t (double average, double median);
  stats_t (const std::vector<value_and_probability> &vals_and_probs);
  bool operator == (const stats_t &other) const;
  void print (const std::string &name) const;
};
