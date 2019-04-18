#include "target_function.h"
#include "distribution.h"

target_function::target_function (std::function<val_and_base (const std::vector<val_and_base> &)> function, std::vector<distribution> &base)
  : m_function (function), m_arg_count (toi (base.size ()))
{
}

val_and_base target_function::operator () (const std::vector<val_and_base> &values)
{
  al_assert (values.size () == tou (m_arg_count), "Bad value vector size");
  return m_function (values);
}
