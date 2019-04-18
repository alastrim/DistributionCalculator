#pragma once
#include "misc.h"

class distribution
{
public:
  distribution (std::vector<std::pair<double, int>> values_and_case_counts, std::string name);
  void show ();
private:
  std::vector<std::pair<double, int>> m_values_and_case_counts;
  std::string m_name;
  std::unique_ptr<QWidget> m_view;
};
