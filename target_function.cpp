#include "target_function.h"
#include "distribution.h"

target_function::target_function (std::function<double (const std::vector<double> &)> function, std::vector<distribution> &base)
  : m_function (function), m_arg_count (toi (base.size ()))
{
}

double target_function::operator () (const std::vector<double> &values)
{
  al_assert (values.size () == tou (m_arg_count), "Bad value vector size");
  return m_function (values);
}
