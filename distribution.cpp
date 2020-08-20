#include "distribution.h"
#include "chart_painter.h"
#include "target_function.h"
#include "stats.h"
#include "dnd_dice.h"
#include <algorithm>

template<typename ElemT>
distribution<ElemT> distribution<ElemT>::operator + (const distribution<ElemT> &rhs) const
{
  std::vector<distribution> v { *this, rhs };
  target_function<ElemT> f ([] (const std::vector<ElemT> &vb) { return sum (vb); }, v);
  return distribution (v, f);
}

template<typename ElemT>
distribution<ElemT> distribution<ElemT>::operator + (int rhs) const
{
  std::vector<distribution> v { *this };
  target_function<ElemT> f ([rhs] (const std::vector<ElemT> &vb) { return vb[0] + rhs; }, v);
  return distribution (v, f);
}

template<typename ElemT>
distribution<ElemT> distribution<ElemT>::operator * (int rhs) const
{
  std::vector<distribution> v = distribution_vector (*this, tou (rhs));
  target_function<ElemT> f ([] (const std::vector<ElemT> &vb) { return sum (vb); }, v);
  return distribution (v, f);
}

template<typename ElemT>
distribution<ElemT>::distribution (std::vector<distribution<ElemT>> distributions, target_function<ElemT> function)
{
  size_t size = distributions.size ();
  size_t total_size = 1;
  size_t current_level;

  std::vector<std::pair<size_t, size_t>> levels (size);
  std::pair<std::vector<ElemT>, double> vals = { std::vector<ElemT> (size), 1 };

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
          value_and_probability<ElemT> vp = distributions[current_level].m_values_and_probabilities[curr_ind];
          vals.first[current_level] = vp.m_value;
          vals.second *= vp.prob ();
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
      ElemT value = function (vals.first);
      double probability = vals.second;

      auto it = std::find_if (m_values_and_probabilities.begin (), m_values_and_probabilities.end (),
                              [value] (const value_and_probability<ElemT> &val_and_count)
      {
          return value == val_and_count.m_value;
        });

      if (it == m_values_and_probabilities.end ())
        m_values_and_probabilities.push_back ({value, probability});
      else
        it->m_probability += probability;
    }
  simplify ();
}

template<typename ElemT>
distribution<ElemT>::distribution (const distribution<ElemT> &rhs)
{
  m_values_and_probabilities = rhs.m_values_and_probabilities;
  simplify ();
}

template<typename ElemT>
distribution<ElemT>::distribution (std::vector<value_and_probability<ElemT>> values_and_probabilities)
{
  m_values_and_probabilities = values_and_probabilities;
  simplify ();
}

template<typename ElemT>
void distribution<ElemT>::simplify ()
{
  std::vector<value_and_probability<ElemT>> values_and_probabilities;
  double total_probability = 0;
  for (const value_and_probability<ElemT> &value_and_case_count : m_values_and_probabilities)
    total_probability += value_and_case_count.prob ();
  for (const value_and_probability<ElemT> &value_and_case_count : m_values_and_probabilities)
    {
      ElemT value = value_and_case_count.m_value;
      double probability = static_cast<double> (value_and_case_count.prob ()) / total_probability;
      values_and_probabilities.push_back ({value, probability});
    }
  m_values_and_probabilities = values_and_probabilities;
}

template<typename ElemT>
stats_t distribution<ElemT>::stats () const
{
  return stats_t (m_values_and_probabilities);
}

template<typename ElemT>
void distribution<ElemT>::show (const std::string &name) const
{
  stats_t (m_values_and_probabilities).print (name);
  chart (m_values_and_probabilities);
}

template class distribution<element_t>;
