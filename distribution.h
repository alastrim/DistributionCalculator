#pragma once
#include "misc.h"

typedef std::vector<std::pair<std::vector<double>, double>> complex_distribution;
class target_function;

class distribution
{
public:
  distribution (const distribution &rhs);
  distribution (std::vector<distribution> distibutions, target_function function, std::string name);
  distribution (std::vector<std::pair<double, double>> values_and_probabilities, std::string name);
  distribution operator + (distribution rhs);
  distribution operator + (double rhs);
  distribution get_base ();
  void show ();

private:
  void simplify ();
  complex_distribution recursive_helper (std::vector<distribution> &distributions);
  std::vector<std::pair<double, double>> m_values_and_probabilities;
  std::string m_name;
  std::unique_ptr<distribution> m_base;
  std::unique_ptr<QWidget> m_view;
};

std::vector<distribution> distribution_vector (distribution etalon, unsigned int count);
