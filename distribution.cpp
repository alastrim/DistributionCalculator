#include "distribution.h"
#include "chart_painter.h"

distribution::distribution (std::vector<std::pair<double, int>> values_and_case_counts, std::string name)
  : m_values_and_case_counts (values_and_case_counts), m_name (name)
{

}

void distribution::show ()
{
  m_view = create_chart (m_values_and_case_counts, m_name);
}
