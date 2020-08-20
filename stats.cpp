#include "stats.h"
#include <algorithm>

#define EXACT_PRINT false

stats_t::stats_t (double average, double median) : m_average (average), m_median (median) {}

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
