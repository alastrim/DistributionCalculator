#include "dnd_dice.h"

distribution<dnd> create_d_something (int size)
{
  std::vector<value_and_probability<dnd>> values_and_probabilities;
  for (int i = 1; i <= size; i++)
    values_and_probabilities.push_back ({i, 1});

  return distribution<dnd> (values_and_probabilities);
}

distribution<dnd> create_d_zero ()
{
  std::vector<value_and_probability<dnd>> values_and_probabilities = {{0, 1}};
  return distribution<dnd> (values_and_probabilities);
}

const distribution<dnd> d0 = create_d_zero ();
const distribution<dnd> d4 = create_d_something (4);
const distribution<dnd> d6 = create_d_something (6);
const distribution<dnd> d8 = create_d_something (8);
const distribution<dnd> d10 = create_d_something (10);
const distribution<dnd> d12 = create_d_something (12);
const distribution<dnd> d20 = create_d_something (20);

std::vector<int> values (const std::vector<dnd> & src)
{
  std::vector<int> result;
  for (const dnd &pair : src)
    result.push_back (pair.m_modified);
  return result;
}

std::vector<int> bases (const std::vector<dnd> & src)
{
  std::vector<int> result;
  for (const dnd &pair : src)
    result.push_back (pair.m_base);
  return result;
}
