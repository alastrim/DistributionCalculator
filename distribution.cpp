#include "distribution.h"
#include "chart_painter.h"
#include "target_function.h"

std::vector<al_argtype> values (vals_and_bases src)
{
  std::vector<al_argtype> result;
  for (const val_and_base &pair : src)
    result.push_back (pair.first);
  return result;
}

std::vector<al_argtype> bases (vals_and_bases src)
{
  std::vector<al_argtype> result;
  for (const val_and_base &pair : src)
    result.push_back (pair.second);
  return result;
}

std::vector<distribution> distribution_vector (distribution etalon, unsigned int count)
{
  std::vector<distribution> result (count, etalon);
  return result;
}

distribution distribution::operator + (distribution rhs)
{
  std::vector<distribution> v { *this, rhs };
  target_function f ([] (vals_and_bases vb)
  {
      return val_and_base (sum (values (vb)), sum (bases (vb)));
    }, v);
  return distribution (v, f, "result");
}

distribution distribution::operator + (al_argtype rhs)
{
  std::vector<distribution> v { *this };
  target_function f ([rhs] (vals_and_bases vb)
  {
      return val_and_base (values (vb)[0] + rhs, bases (vb)[0]);
    }, v);
  return distribution (v, f, "result");
}

distribution distribution::operator * (al_argtype rhs)
{
  std::vector<distribution> v = distribution_vector (*this, tou (rhs));
  target_function f ([] (vals_and_bases vb)
  {
      return val_and_base (sum (values (vb)), sum (bases (vb)));
    }, v);
  return distribution (v, f, "result");
}

complex_distribution distribution::recursive_helper (std::vector<distribution> &distributions)
{
  al_assert (!distributions.empty (), "Bad call to recursive thing");

  distribution outer = distributions.back ();
  distributions.pop_back ();

  complex_distribution result_values_and_probabilities;

  if (distributions.empty ())
    {
      for (const std::pair<val_and_base, double> &outer_value_and_probability : outer.m_values_and_probabilities)
        result_values_and_probabilities.push_back ({{outer_value_and_probability.first}, outer_value_and_probability.second});
      return result_values_and_probabilities;
    };

  complex_distribution inner = recursive_helper (distributions);
  for (const std::pair<std::vector<val_and_base>, double> &inner_value_and_probability : inner)
    {
      for (const std::pair<val_and_base, double> &outer_value_and_probability : outer.m_values_and_probabilities)
        {
          std::vector<val_and_base> new_value = inner_value_and_probability.first;
          new_value.push_back (outer_value_and_probability.first);
          double case_count = outer_value_and_probability.second * inner_value_and_probability.second;

          result_values_and_probabilities.push_back ({{new_value}, case_count});
        }
    }

  return result_values_and_probabilities;
}

distribution::distribution (std::vector<distribution> distibutions, target_function function, std::string name)
{
  complex_distribution complex = recursive_helper (distibutions);
  m_values_and_probabilities = from_complex (complex, function);
  m_name = name;
  simplify ();
}

std::vector<std::pair<val_and_base, double>> distribution::from_complex (complex_distribution &complex, target_function function)
{
  std::vector<std::pair<val_and_base, double>> values_and_probabilities;

  for (const std::pair<std::vector<val_and_base>, double> &value_and_case_count : complex)
    {
      val_and_base value = function (value_and_case_count.first);
      double case_count = value_and_case_count.second;

      auto it = std::find_if (values_and_probabilities.begin (), values_and_probabilities.end (),
                              [value] (const std::pair<val_and_base, double> &val_and_count)
      {
          return (!fuzzycmp (value.first, val_and_count.first.first)
                  && !fuzzycmp (value.second, val_and_count.first.second));
        });

      if (it == values_and_probabilities.end ())
        values_and_probabilities.push_back ({value, case_count});
      else
        it->second += case_count;
    }
  return values_and_probabilities;
}

distribution::distribution (const distribution &rhs)
{
  al_assert (!m_view && !rhs.m_view, "Dont copy view plz");
  m_values_and_probabilities = rhs.m_values_and_probabilities;
  m_name = rhs.m_name;
  simplify ();
}

distribution::distribution (std::vector<std::pair<double, double>> values_and_probabilities, std::string name)
  : m_name (name)
{
  for (const std::pair<double, double> &it : values_and_probabilities)
    m_values_and_probabilities.push_back ({{it.first, it.first}, it.second});
  simplify ();
}

void distribution::simplify ()
{
  std::vector<std::pair<val_and_base, double>> values_and_probabilities;
  double total_probability = 0;
  for (const std::pair<val_and_base, double> &value_and_case_count : m_values_and_probabilities)
    total_probability += value_and_case_count.second;
  for (const std::pair<val_and_base, double> &value_and_case_count : m_values_and_probabilities)
    {
      val_and_base value = value_and_case_count.first;
      double probability = static_cast<double> (value_and_case_count.second) / total_probability;
      values_and_probabilities.push_back ({value, probability});
    }
  m_values_and_probabilities = values_and_probabilities;
}

void distribution::show ()
{
  std::vector<std::pair<double, double>> result;
  for (const value_and_probability &pair : m_values_and_probabilities)
    result.push_back ({pair.first.first, pair.second});

  m_view = create_chart (result, m_name);
}
