#include "distribution.h"
#include "chart_painter.h"
#include "target_function.h"
#include <algorithm>

std::vector<al_argtype> values (vals_and_bases src)
{
  std::vector<al_argtype> result;
  for (const element_type &pair : src)
    result.push_back (pair.first);
  return result;
}

std::vector<al_argtype> bases (vals_and_bases src)
{
  std::vector<al_argtype> result;
  for (const element_type &pair : src)
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
      return element_type (sum (values (vb)), sum (bases (vb)));
    }, v);
  return distribution (v, f);
}

distribution distribution::operator + (al_argtype rhs)
{
  std::vector<distribution> v { *this };
  target_function f ([rhs] (vals_and_bases vb)
  {
      return element_type (values (vb)[0] + rhs, bases (vb)[0]);
    }, v);
  return distribution (v, f);
}

distribution distribution::operator * (al_argtype rhs)
{
  std::vector<distribution> v = distribution_vector (*this, tou (rhs));
  target_function f ([] (vals_and_bases vb)
  {
      return element_type (sum (values (vb)), sum (bases (vb)));
    }, v);
  return distribution (v, f);
}

distribution::distribution (std::vector<distribution> distributions, target_function function)
{
  size_t size = distributions.size ();
  size_t total_size = 1;
  size_t current_level;

  std::vector<ind_and_size> levels (size);
  std::pair<std::vector<element_type>, double> vals = { std::vector<element_type> (size), 1 };

  for (size_t i = 0; i < size; i++)
  {
    size_t sz = distributions[i].m_values_and_probabilities.size ();
    levels[i] = { 0, sz };
    total_size *= sz;
  }

  for (size_t i = 0; i < total_size; i++)
    {
      // create vector of values
      vals.second = 1;
      for (current_level = 0; current_level < size; current_level++)
        {
          size_t curr_ind = levels[current_level].first;
          value_and_probability vp = distributions[current_level].m_values_and_probabilities[curr_ind];
          vals.first[current_level] = vp.first;
          vals.second *= vp.second;
        }

      // tick indices
      levels[0].first++;
      for (size_t lv = 0; (lv < size && levels[lv].first == levels[lv].second); lv++)
        {
          levels[lv].first = 0;
          if (lv < size - 1)
            levels[lv + 1].first++;
          else
            al_assert (i == total_size - 1, "Should be in the end");
        }

      // add value to results
      element_type value = function (vals.first);
      double probability = vals.second;

      auto it = std::find_if (m_values_and_probabilities.begin (), m_values_and_probabilities.end (),
                              [value] (const std::pair<element_type, double> &val_and_count)
      {
          return (value.first == val_and_count.first.first
                  && value.second == val_and_count.first.second);
        });

      if (it == m_values_and_probabilities.end ())
        m_values_and_probabilities.push_back ({value, probability});
      else
        it->second += probability;
    }
  simplify ();
}

distribution::distribution (const distribution &rhs)
{
  m_values_and_probabilities = rhs.m_values_and_probabilities;
  simplify ();
}

distribution::distribution (std::vector<std::pair<double, double>> values_and_probabilities)
{
  for (const std::pair<double, double> &it : values_and_probabilities)
    m_values_and_probabilities.push_back ({{it.first, it.first}, it.second});
  simplify ();
}

void distribution::simplify ()
{
  std::vector<std::pair<element_type, double>> values_and_probabilities;
  double total_probability = 0;
  for (const std::pair<element_type, double> &value_and_case_count : m_values_and_probabilities)
    total_probability += value_and_case_count.second;
  for (const std::pair<element_type, double> &value_and_case_count : m_values_and_probabilities)
    {
      element_type value = value_and_case_count.first;
      double probability = static_cast<double> (value_and_case_count.second) / total_probability;
      values_and_probabilities.push_back ({value, probability});
    }
  m_values_and_probabilities = values_and_probabilities;
}

void distribution::show (const std::string &name)
{
  std::vector<std::pair<double, double>> result;
  for (const value_and_probability &pair : m_values_and_probabilities)
    result.push_back ({pair.first.first, pair.second});

  std::sort (result.begin (), result.end (), [] (std::pair<double, double> a, std::pair<double, double> b) {return a.first < b.first; });
  create_chart (result, name);
}
