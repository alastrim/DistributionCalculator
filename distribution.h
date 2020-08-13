#pragma once
#include "misc.h"

class target_function;
typedef std::pair<size_t, size_t> ind_and_size;

std::vector<al_argtype> values (vals_and_bases src);
std::vector<al_argtype> bases (vals_and_bases src);


class distribution
{
public:
  distribution (const distribution &rhs);
  distribution (std::vector<distribution> distributions, target_function function);
  distribution (std::vector<std::pair<double, double>> values_and_probabilities);
  distribution operator + (distribution rhs);
  distribution operator + (al_argtype rhs);
  distribution operator * (al_argtype rhs);
  distribution get_base () const;
  void show (const std::string &name = "distribution");

private:
  void simplify ();
  std::vector<value_and_probability> m_values_and_probabilities;
};

std::vector<distribution> distribution_vector (distribution etalon, unsigned int count);
