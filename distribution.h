#pragma once
#include "misc.h"

class target_function;

std::vector<int> values (vals_and_bases src);
std::vector<int> bases (vals_and_bases src);


class distribution
{
public:
  distribution (const distribution &rhs);
  distribution (std::vector<distribution> distibutions, target_function function, std::string name);
  distribution (std::vector<std::pair<double, double>> values_and_probabilities, std::string name);
  distribution operator + (distribution rhs);
  distribution operator + (double rhs);
  distribution operator * (int rhs);
  distribution get_base () const;
  void show ();

private:
  void simplify ();
  static complex_distribution recursive_helper (std::vector<distribution> &distributions);
  static std::vector<std::pair<val_and_base, double>> from_complex (complex_distribution &complex, target_function function);
  std::vector<value_and_probability> m_values_and_probabilities;
  std::string m_name;
  std::unique_ptr<QWidget> m_view;
};

std::vector<distribution> distribution_vector (distribution etalon, unsigned int count);
