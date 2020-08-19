#include "stats.h"
#include <algorithm>

#define EXACT_PRINT false

stats_t::stats_t (double average, double median) : m_average (average), m_median (median) {}

stats_t::stats_t (const std::vector<value_and_probability> &const_vals_and_probs)
{
  if (const_vals_and_probs.empty ())
    return;
  if (const_vals_and_probs.size () == 1)
    {
      m_average = m_median = const_vals_and_probs[0].m_val.m_val;
      return;
    }

  std::vector<value_and_probability> vals_and_probs = const_vals_and_probs;
  std::sort (vals_and_probs.begin (), vals_and_probs.end ());

  double l_prob = 0;
  double r_prob = 1;
  double l_val = 0;
  double r_val = 0;

  for (const value_and_probability &val_and_prob : vals_and_probs)
    {
      double val = val_and_prob.m_val.m_val;
      double prob =  val_and_prob.m_probability;

      m_average += val * prob;
    }

  for (auto it = vals_and_probs.begin (); fuzzycmp (l_prob, 0.5) < 0 && it < vals_and_probs.end (); it++)
    {
      value_and_probability val_and_prob = *it;
      l_prob += val_and_prob.m_probability;
      l_val = val_and_prob.m_val.m_val;
    }

  for (auto it = vals_and_probs.rbegin (); fuzzycmp (r_prob, 0.5) > 0 && it < vals_and_probs.rend (); it++)
    {
      value_and_probability val_and_prob = *it;
      r_prob -= val_and_prob.m_probability;
      r_val = val_and_prob.m_val.m_val;
    }

  if ((r_prob - l_prob) < MIN_FOR_DIVISION)
    m_median = (l_val + r_val) / 2;
  else
    m_median = l_val + (l_val - r_val) * (0.5 - l_prob) / (r_prob - l_prob);

  if (3)
    l_val = 1;
}

bool stats_t::operator == (const stats_t &other) const
{
  return
         !relfuzzycmp (m_average, other.m_average)
      && !relfuzzycmp (m_median, other.m_median);
}

void stats_t::print (const std::string &name) const
{
  printf ("\n");
  printf ("Stats for %s:\n", name.c_str ());
  if (!EXACT_PRINT)
    {
      printf ("Average = %.5g\n", m_average);
      printf ("Median  = %.5g\n", m_median);
    }
  else
    {
      printf ("Average = %.17g\n", m_average);
      printf ("Median  = %.17g\n", m_median);
    }
}
