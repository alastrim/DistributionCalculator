#include "distribution.h"
#include "chart_painter.h"

typedef std::vector<std::pair<std::vector<double>, int>> complex_distribution;

static complex_distribution recursive_helper (std::vector<distribution> &distributions)
{
  al_assert (!distributions.empty (), "Bad call to recursive thing");

  distribution outer = distributions.back ();
  distributions.pop_back ();

  complex_distribution result_values_and_case_counts;

  if (distributions.empty ())
    {
      for (const std::pair<double, int> &outer_value_and_case_count : outer.m_values_and_case_counts)
        result_values_and_case_counts.push_back ({{outer_value_and_case_count.first}, outer_value_and_case_count.second});
      return result_values_and_case_counts;
    };

  complex_distribution inner = recursive_helper (distributions);
  for (const std::pair<std::vector<double>, int> &inner_value_and_case_count : inner)
    {
      for (const std::pair<double, int> &outer_value_and_case_count : outer.m_values_and_case_counts)
        {
          std::vector<double> new_value = inner_value_and_case_count.first;
          new_value.push_back (outer_value_and_case_count.first);
          int case_count = outer_value_and_case_count.second * inner_value_and_case_count.second;

          result_values_and_case_counts.push_back ({{new_value}, case_count});
        }
    }

  return  result_values_and_case_counts;
}

distribution::distribution (std::vector<distribution> distibutions, target_function function, std::string name)
{
  std::vector<std::pair<double, int>> values_and_case_counts;
  complex_distribution complex = recursive_helper (distibutions);

  for (const std::pair<std::vector<double>, int> &value_and_case_count : complex)
    {
      double value = function (value_and_case_count.first);
      int case_count = value_and_case_count.second;

      auto it = std::find_if (values_and_case_counts.begin (), values_and_case_counts.end (), [value] (const std::pair<double, int> &val_and_count)
      {
          return (!fuzzycmp (value, val_and_count.first));
        });

      if (it == values_and_case_counts.end ())
        values_and_case_counts.push_back ({value, case_count});
      else
        it->second += case_count;
    }
  m_values_and_case_counts = values_and_case_counts;
  m_name = name;
}

distribution::distribution (const distribution &rhs)
{
  al_assert (!m_view && !rhs.m_view, "Dont copy view plz");
  m_values_and_case_counts = rhs.m_values_and_case_counts;
  m_name = rhs.m_name;
}

distribution::distribution (std::vector<std::pair<double, int>> values_and_case_counts, std::string name)
  : m_values_and_case_counts (values_and_case_counts), m_name (name)
{

}

void distribution::show ()
{
  m_view = create_chart (m_values_and_case_counts, m_name);
}
