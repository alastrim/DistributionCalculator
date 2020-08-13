#pragma once
#include "misc.h"
#include "distribution.h"

template<int SIZE>
distribution create_d_something ()
{
  int size = SIZE;
  std::vector<std::pair<double, double>> values_and_probabilities;
  for (int i = 1; i <= size; i++)
    values_and_probabilities.push_back ({i, 1});

  return distribution (values_and_probabilities);
}

distribution create_zero ();
distribution create_zero ()
{
  std::vector<std::pair<double, double>> values_and_probabilities = {{0, 1}};
  return distribution (values_and_probabilities);
}

static distribution d0 = create_zero ();
static distribution d4 = create_d_something<4> ();
static distribution d6 = create_d_something<6> ();
static distribution d8 = create_d_something<8> ();
static distribution d10 = create_d_something<10> ();
static distribution d12 = create_d_something<12> ();
static distribution d20 = create_d_something<20> ();
