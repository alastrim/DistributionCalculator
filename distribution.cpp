#include "distribution.h"
#include "chart_painter.h"
#include "target_function.h"
#include <algorithm>

std::vector<int> values (const std::vector<element_t> & src)
{
  std::vector<int> result;
  for (const element_t &pair : src)
    result.push_back (pair.m_val);
  return result;
}

std::vector<int> bases (const std::vector<element_t> & src)
{
  std::vector<int> result;
  for (const element_t &pair : src)
    result.push_back (pair.m_base);
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
  target_function f ([] (const std::vector<element_t> & vb)
  {
      return element_t (sum (values (vb)), sum (bases (vb)));
    }, v);
  return distribution (v, f);
}

distribution distribution::operator + (int rhs)
{
  std::vector<distribution> v { *this };
  target_function f ([rhs] (const std::vector<element_t> & vb)
  {
      return element_t (values (vb)[0] + rhs, bases (vb)[0]);
    }, v);
  return distribution (v, f);
}

distribution distribution::operator * (int rhs)
{
  std::vector<distribution> v = distribution_vector (*this, tou (rhs));
  target_function f ([] (const std::vector<element_t> & vb)
  {
      return element_t (sum (values (vb)), sum (bases (vb)));
    }, v);
  return distribution (v, f);
}

distribution::distribution (std::vector<distribution> distributions, target_function function)
{
  size_t size = distributions.size ();
  size_t total_size = 1;
  size_t current_level;

  std::vector<ind_and_size> levels (size);
  std::pair<std::vector<element_t>, double> vals = { std::vector<element_t> (size), 1 };

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
          vals.first[current_level] = vp.m_val;
          vals.second *= vp.m_probability;
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
      element_t value = function (vals.first);
      double probability = vals.second;

      auto it = std::find_if (m_values_and_probabilities.begin (), m_values_and_probabilities.end (),
                              [value] (const value_and_probability &val_and_count)
      {
          return value == val_and_count.m_val;
        });

      if (it == m_values_and_probabilities.end ())
        m_values_and_probabilities.push_back ({value, probability});
      else
        it->m_probability += probability;
    }
  simplify ();
}

distribution::distribution (const distribution &rhs)
{
  m_values_and_probabilities = rhs.m_values_and_probabilities;
  simplify ();
}

distribution::distribution (std::vector<value_and_probability> values_and_probabilities)
{
  m_values_and_probabilities = values_and_probabilities;
  simplify ();
}

void distribution::simplify ()
{
  std::vector<value_and_probability> values_and_probabilities;
  double total_probability = 0;
  for (const value_and_probability &value_and_case_count : m_values_and_probabilities)
    total_probability += value_and_case_count.m_probability;
  for (const value_and_probability &value_and_case_count : m_values_and_probabilities)
    {
      element_t value = value_and_case_count.m_val;
      double probability = static_cast<double> (value_and_case_count.m_probability) / total_probability;
      values_and_probabilities.push_back ({value, probability});
    }
  m_values_and_probabilities = values_and_probabilities;
}

void distribution::show (const std::string &name)
{
  std::vector<value_and_probability> result = m_values_and_probabilities;
  std::sort (result.begin (), result.end ());//, [] (value_and_probability a, value_and_probability b) {return a.first < b.first; });
  create_chart (result, name);
}
