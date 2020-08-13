#include "chart_painter.h"
#include <cstdio>
#include <algorithm>

#define BARNUM 10

struct value_range_and_probability
{
  value_range_and_probability () {}
  element_t beg;
  element_t end;
  double prob = 0;
};

static std::vector<value_range_and_probability> format_for_showing (const std::vector<value_and_probability> &const_values_and_probabilities)
{
  std::vector<value_and_probability> values_and_probabilities = const_values_and_probabilities;
  std::sort (values_and_probabilities.begin (), values_and_probabilities.end ());

  std::vector<value_range_and_probability> bars (BARNUM);

  int size = tou (values_and_probabilities.size ());
  for (int i = 0; i < size; i++)
    {
      int internal_ind = i / BARNUM;
      if (internal_ind == 0)
        bars[internal_ind].beg = values_and_probabilities[i].m_val;
      else
        bars[internal_ind].end = values_and_probabilities[i].m_val;
      bars[internal_ind].prob += values_and_probabilities[i].m_probability;
    }

  return bars;
}

void create_chart (const std::vector<value_and_probability> &values_and_probabilities, const std::string &name)
{
  double average = 0;
  for (const value_and_probability &value_and_case_count : values_and_probabilities)
    {
      int value = value_and_case_count.m_val.m_val;
      double probability = value_and_case_count.m_probability;
      average += value * probability;
    }

  printf ("Stats for %s:\n", name.c_str ());
  printf ("Average = %f\n", average);

  std::vector<value_range_and_probability> bars = format_for_showing (values_and_probabilities);

  for (const value_range_and_probability &bar : bars)
    printf ("%3d to %3d: %.2f%%\n", bar.beg.m_val, bar.end.m_val, bar.prob * 100);

}
