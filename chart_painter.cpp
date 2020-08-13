#include "chart_painter.h"
#include <cstdio>

void create_chart (std::vector<value_and_probability> values_and_probabilities, std::string name)
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

  for (const value_and_probability &value_and_probability : values_and_probabilities)
    {
      int value = value_and_probability.m_val.m_val;
      double probability = value_and_probability.m_probability;
      printf ("%d: %.2f%%\n", value, probability * 100);
    }

}
