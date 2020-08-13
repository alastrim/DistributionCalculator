#pragma once
#include "misc.h"

class target_function;
typedef std::pair<size_t, size_t> ind_and_size;

std::vector<int> values (const std::vector<element_t> & src);
std::vector<int> bases (const std::vector<element_t> & src);


class distribution
{
public:
  distribution (const distribution &rhs);
  distribution (std::vector<distribution> distributions, target_function function);
  distribution (std::vector<value_and_probability> values_and_probabilities);
  distribution operator + (distribution rhs);
  distribution operator + (int rhs);
  distribution operator * (int rhs);
  distribution get_base () const;
  void show (const std::string &name = "distribution");

private:
  void simplify ();
  std::vector<value_and_probability> m_values_and_probabilities;
};

std::vector<distribution> distribution_vector (distribution etalon, unsigned int count);
