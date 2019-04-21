#pragma once
#include "misc.h"

class target_function;
typedef std::pair<int, int> ind_and_size;

std::vector<al_argtype> values (vals_and_bases src);
std::vector<al_argtype> bases (vals_and_bases src);


class distribution
{
public:
  distribution (const distribution &rhs);
//  distribution (std::vector<distribution> distibutions, target_function function, std::string name);
  distribution (std::vector<distribution> distibutions, target_function function, std::string name);
  distribution (std::vector<std::pair<double, double>> values_and_probabilities, std::string name);
  distribution operator + (distribution rhs);
  distribution operator + (al_argtype rhs);
  distribution operator * (al_argtype rhs);
  distribution get_base () const;
  void show ();

private:
  void simplify ();
  static complex_distribution recursive_helper (std::vector<distribution> &distributions);
  static void alt_recursive_helper(std::vector<distribution> &distributions,
                                   std::vector<ind_and_size> &levels,
                                   std::pair<std::vector<val_and_base>, double> &prev,
                                   int level_to_tick);

  static std::vector<std::pair<val_and_base, double>> from_complex (complex_distribution &complex, target_function function);
  std::vector<value_and_probability> m_values_and_probabilities;
  std::string m_name;
  std::unique_ptr<QWidget> m_view;
};

std::vector<distribution> distribution_vector (distribution etalon, unsigned int count);
