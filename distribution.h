#pragma once
#include "misc.h"

class target_function;

class distribution
{
public:
  distribution (const distribution &rhs);
  distribution (std::vector<distribution> distibutions, target_function &function, std::string name);
  distribution (std::vector<std::pair<double, double>> values_and_probabilities, std::string name);
  distribution operator + (distribution rhs);
  distribution operator + (double rhs);
  void show ();
  void simplify ();

  std::vector<std::pair<double, double>> m_values_and_probabilities;
  std::string m_name;
  std::unique_ptr<QWidget> m_view;
};

std::vector<distribution> distribution_vector (distribution etalon, unsigned int count);
