#include "distribution.h"
#include "chart_painter.h"

typedef std::vector<std::pair<std::vector<double>, double>> complex_distribution;

std::vector<distribution> distibution_vector (distribution etalon, unsigned int count)
{
  std::vector<distribution> result (count, etalon);
  return result;
}

target_function::target_function (std::function<double (const std::vector<double> &)> function, std::vector<distribution> &base)
  : m_function (function), m_arg_count (toi (base.size ()))
{
}

double target_function::operator () (const std::vector<double> &values)
{
  al_assert (values.size () == tou (m_arg_count), "Bad value vector size");
  return m_function (values);
}

static complex_distribution recursive_helper (std::vector<distribution> &distributions)
{
  al_assert (!distributions.empty (), "Bad call to recursive thing");

  distribution outer = distributions.back ();
  distributions.pop_back ();

  complex_distribution result_values_and_probabilities;

  if (distributions.empty ())
    {
      for (const std::pair<double, double> &outer_value_and_probability : outer.m_values_and_probabilities)
        result_values_and_probabilities.push_back ({{outer_value_and_probability.first}, outer_value_and_probability.second});
      return result_values_and_probabilities;
    };

  complex_distribution inner = recursive_helper (distributions);
  for (const std::pair<std::vector<double>, double> &inner_value_and_probability : inner)
    {
      for (const std::pair<double, double> &outer_value_and_probability : outer.m_values_and_probabilities)
        {
          std::vector<double> new_value = inner_value_and_probability.first;
          new_value.push_back (outer_value_and_probability.first);
          double case_count = outer_value_and_probability.second * inner_value_and_probability.second;

          result_values_and_probabilities.push_back ({{new_value}, case_count});
        }
    }

  return  result_values_and_probabilities;
}

distribution::distribution (std::vector<distribution> distibutions, target_function function, std::string name)
{
  std::vector<std::pair<double, double>> values_and_probabilities;
  complex_distribution complex = recursive_helper (distibutions);

  for (const std::pair<std::vector<double>, double> &value_and_case_count : complex)
    {
      double value = function (value_and_case_count.first);
      double case_count = value_and_case_count.second;

      auto it = std::find_if (values_and_probabilities.begin (), values_and_probabilities.end (), [value] (const std::pair<double, int> &val_and_count)
      {
          return (!fuzzycmp (value, val_and_count.first));
        });

      if (it == values_and_probabilities.end ())
        values_and_probabilities.push_back ({value, case_count});
      else
        it->second += case_count;
    }
  m_values_and_probabilities = values_and_probabilities;
  m_name = name;
  simplify ();
}

distribution::distribution (const distribution &rhs)
{
  al_assert (!m_view && !rhs.m_view, "Dont copy view plz");
  m_values_and_probabilities = rhs.m_values_and_probabilities;
  m_name = rhs.m_name;
  simplify ();
}

distribution::distribution (std::vector<std::pair<double, double>> values_and_probabilities, std::string name)
  : m_values_and_probabilities (values_and_probabilities), m_name (name)
{
  simplify ();
}

void distribution::simplify ()
{
  std::vector<std::pair<double, double>> values_and_probabilities;
  double total_probability = 0;
  for (const std::pair<double, double> &value_and_case_count : m_values_and_probabilities)
    total_probability += value_and_case_count.second;
  for (const std::pair<double, double> &value_and_case_count : m_values_and_probabilities)
    {
      double value = value_and_case_count.first;
      double probability = static_cast<double> (value_and_case_count.second) / total_probability;
      values_and_probabilities.push_back ({value, probability});
    }
  m_values_and_probabilities = values_and_probabilities;
}

void distribution::show ()
{
  m_view = create_chart (m_values_and_probabilities, m_name);
}
