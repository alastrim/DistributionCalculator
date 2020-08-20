#include "standard_dice.h"

distribution<element_t> create_d_something (int size)
{
  std::vector<value_and_probability<element_t>> values_and_probabilities;
  for (int i = 1; i <= size; i++)
    values_and_probabilities.push_back ({i, 1});

  return distribution<element_t> (values_and_probabilities);
}

distribution<element_t> create_d_zero ()
{
  std::vector<value_and_probability<element_t>> values_and_probabilities = {{0, 1}};
  return distribution<element_t> (values_and_probabilities);
}

const distribution<element_t> d0 = create_d_zero ();
const distribution<element_t> d4 = create_d_something (4);
const distribution<element_t> d6 = create_d_something (6);
const distribution<element_t> d8 = create_d_something (8);
const distribution<element_t> d10 = create_d_something (10);
const distribution<element_t> d12 = create_d_something (12);
const distribution<element_t> d20 = create_d_something (20);

std::vector<int> values (const std::vector<element_t> & src)
{
  std::vector<int> result;
  for (const element_t &pair : src)
    result.push_back (pair.m_val);
  return result;
}

std::vector<int> bases (const std::vector<element_t> & src)
{
  std::vector<int> result;
  for (const element_t &pair : src)
    result.push_back (pair.m_base);
  return result;
}
