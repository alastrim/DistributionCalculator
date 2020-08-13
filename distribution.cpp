#include "distribution.h"
#include "chart_painter.h"
#include "target_function.h"
#include <algorithm>

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

distribution::distribution (std::vector<distribution> distributions, target_function function, std::string name)
{
  m_name = name;
  std::vector<ind_and_size> levels;
  size_t levels_size = distributions.size ();
  size_t total_size = 1;
  size_t level_to_tick = 0;
  size_t current_level;

  std::for_each (distributions.begin (), distributions.end (), [&] (const distribution & d)
  {
      size_t sz = d.m_values_and_probabilities.size ();
      levels.push_back ({0, sz});
      total_size *= sz;
    });


  for (size_t i = 0; i < total_size; i++)
    {
      // create vector of values
      std::pair<std::vector<val_and_base>, double> emp = {{}, 1};
      while ((current_level = emp.first.size ()) < levels_size)
        {
          al_assert (current_level < levels.size (), "");
          size_t curr_ind = levels[current_level].first;

          value_and_probability vp = distributions[current_level].m_values_and_probabilities[curr_ind];
          emp.first.push_back (vp.first);
          emp.second *= vp.second;
        }

      // tick indices
      levels[level_to_tick].first++;
      for (size_t lv = level_to_tick; (lv < levels_size && levels[lv].first == levels[lv].second); lv++)
        {
          al_assert (lv < levels.size (), "");
          levels[lv].first = 0;
          levels[lv + 1].first++;
        }
      level_to_tick = 0;

      // add value to results
      val_and_base value = function (emp.first);
      double case_count = emp.second;

      auto it = std::find_if (m_values_and_probabilities.begin (), m_values_and_probabilities.end (),
                              [value] (const std::pair<val_and_base, double> &val_and_count)
      {
          return (!fuzzycmp (value.first, val_and_count.first.first)
                  && !fuzzycmp (value.second, val_and_count.first.second));
        });

      if (it == m_values_and_probabilities.end ())
        m_values_and_probabilities.push_back ({value, case_count});
      else
        it->second += case_count;
    }
  simplify ();
}

distribution::distribution (const distribution &rhs)
{
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

  std::sort (result.begin (), result.end (), [] (std::pair<double, double> a, std::pair<double, double> b) {return a.first < b.first; });
  create_chart (result, m_name);
}
