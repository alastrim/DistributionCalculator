#include "stats.h"
#include <algorithm>

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

  double total_probability = 0;
  double l_prob = -1;
  double r_prob = -1;
  double l_val = 0;
  double r_val = 0;
  for (const value_and_probability &val_and_prob : vals_and_probs)
    {
      double val = val_and_prob.m_val.m_val;
      double prob =  val_and_prob.m_probability;

      m_average += val * prob;

      total_probability += prob;
      if (total_probability < 0.5)
        {
          l_prob = total_probability;
          l_val = val;
        }
      if (r_prob < 0 && total_probability >= 0.5)
        {
          r_prob = total_probability;
          r_val = val;
        }
    }

  m_median = l_val + (l_val - r_val) * (0.5 - l_prob) / (r_prob - l_prob);
}

bool stats_t::operator == (const stats_t &other) const
{
  return
      !fuzzycmp (m_average, other.m_average)
      && !fuzzycmp (m_median, other.m_median);
}

void stats_t::print (const std::string &name) const
{
  printf ("\n");
  printf ("Stats for %s:\n", name.c_str ());
  printf ("Median  = %f\n", m_median);
  printf ("Average = %f\n", m_average);
}
