#include "chart_painter.h"
#include <cstdio>

void create_chart (std::vector<std::pair<double, double> > values_and_probabilities, std::string name)
{
  double average = 0;
  for (const std::pair<double, double> &value_and_case_count : values_and_probabilities)
    {
      double value = value_and_case_count.first;
      double probability = value_and_case_count.second;
      average += value * probability;
    }

  printf ("Stats for %s:\n", name.c_str ());
  printf ("Average = %f\n", average);

  for (const std::pair<double, double> &value_and_probability : values_and_probabilities)
    {
      double value = value_and_probability.first;
      double probability = value_and_probability.second;
      std::string value_label = (!fuzzycmp (round (value), value) ? std::to_string (static_cast<int> (value)) : std::to_string (value));
      printf ("%s: %.2f%%\n", value_label.c_str (), probability * 100);
    }

}
