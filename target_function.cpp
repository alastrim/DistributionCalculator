#include "target_function.h"
#include "distribution.h"

target_function::target_function (std::function<element_type (const std::vector<element_type> &)> function, std::vector<distribution> &base)
  : m_function (function), m_arg_count (toi (base.size ()))
{
}

element_type target_function::operator () (const std::vector<element_type> &values)
{
  al_assert (values.size () == tou (m_arg_count), "Bad value vector size");
  return m_function (values);
}
