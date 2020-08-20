#pragma once
#include "misc.h"

template<typename ElemT>
class target_function;
struct stats_t;

template<typename ElemT>
class distribution
{
public:
  void show (const std::string &name = "distribution") const;
  stats_t stats () const;
  distribution (const distribution &rhs);
  distribution (std::vector<distribution> distributions, target_function<ElemT> function);
  distribution (std::vector<value_and_probability<ElemT>> values_and_probabilities);
  distribution operator + (const distribution &rhs) const;
  distribution operator + (int rhs) const;
  distribution operator * (int rhs) const;
  distribution get_base () const;

private:
  void simplify ();
  std::vector<value_and_probability<ElemT>> m_values_and_probabilities;
};

template<typename ElemT>
std::vector<distribution<ElemT>> distribution_vector (distribution<ElemT> etalon, unsigned int count)
{ return std::vector<distribution<ElemT>> (count, etalon); }
