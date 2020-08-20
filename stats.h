#pragma once
#include "misc.h"
#include <algorithm>

struct stats_t
{
  double m_average = 0;
  double m_median = 0;

  stats_t (double average, double median);
  bool operator == (const stats_t &other) const;
  void print (const std::string &name = "distribution") const;

  template<typename ElemT>
  stats_t (const std::vector<value_and_probability<ElemT>> &const_vals_and_probs)
  {
    if (const_vals_and_probs.empty ())
      return;
    if (const_vals_and_probs.size () == 1)
      {
        m_average = m_median = const_vals_and_probs[0].m_val.m_val;
        return;
      }

    std::vector<value_and_probability<ElemT>> vals_and_probs = const_vals_and_probs;
    std::sort (vals_and_probs.begin (), vals_and_probs.end ());

    double l_prob = 0;
    double r_prob = 1;
    double l_val = 0;
    double r_val = 0;

    for (const value_and_probability<ElemT> &val_and_prob : vals_and_probs)
      {
        double val = val_and_prob.m_val.m_val;
        double prob = val_and_prob.m_probability;
        m_average += val * prob;
      }

    for (auto it = vals_and_probs.begin ();
         fuzzycmp (l_prob, 0.5) < 0 && it < vals_and_probs.end (); it++)
      {
        value_and_probability<ElemT> val_and_prob = *it;
        l_prob += val_and_prob.m_probability;
        l_val = val_and_prob.m_val.m_val;
      }

  for (auto it = vals_and_probs.rbegin ();
       fuzzycmp (r_prob, 0.5) > 0 && it < vals_and_probs.rend (); it++)
    {
      value_and_probability<ElemT> val_and_prob = *it;
      r_prob -= val_and_prob.m_probability;
      r_val = val_and_prob.m_val.m_val;
    }

  if ((r_prob - l_prob) < MIN_FOR_DIVISION)
    m_median = (l_val + r_val) / 2;
  else
    m_median = l_val + (l_val - r_val) * (0.5 - l_prob) / (r_prob - l_prob);
  }
};
