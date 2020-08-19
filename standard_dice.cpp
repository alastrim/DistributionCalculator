#include "standard_dice.h"

distribution create_d_something (int size)
{
  std::vector<value_and_probability> values_and_probabilities;
  for (int i = 1; i <= size; i++)
    values_and_probabilities.push_back ({i, 1});

  return distribution (values_and_probabilities);
}

distribution create_d_zero ()
{
  std::vector<value_and_probability> values_and_probabilities = {{0, 1}};
  return distribution (values_and_probabilities);
}

const distribution d0 = create_d_zero ();
const distribution d4 = create_d_something (4);
const distribution d6 = create_d_something (6);
const distribution d8 = create_d_something (8);
const distribution d10 = create_d_something (10);
const distribution d12 = create_d_something (12);
const distribution d20 = create_d_something (20);
