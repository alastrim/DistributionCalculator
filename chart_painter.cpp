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

  int size = tou (values_and_probabilities.size ());
  std::vector<value_range_and_probability> bars (BARNUM);
  int chunk_len = size / BARNUM;

  for (int i = 0; i < size; i++)
    {
      int internal_ind = i / chunk_len;
      if (internal_ind >= BARNUM)
        internal_ind = BARNUM - 1;

      if (!(i % chunk_len))
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

  printf ("\n");
  printf ("Stats for %s:\n", name.c_str ());
  printf ("Average = %f\n", average);

  std::vector<value_range_and_probability> bars = format_for_showing (values_and_probabilities);

  int len = 100;
  int chunk = 100 / len;
  al_assert (100 % len == 0, "Accuracy");

  for (const value_range_and_probability &bar : bars)
    {
      int valb = bar.beg.m_val;
      int vale = bar.end.m_val;
      double prob = bar.prob * 100;
      int perc = (int) round (prob);

      printf ("%3d to %3d: ", valb, vale);
      for (int i = 0; i < len; i++)
        printf ("%c", (perc > i * chunk) ? '#' : ' ');
      printf (" %5.2f%%\n", prob);
    }

}
