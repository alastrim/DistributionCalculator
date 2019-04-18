#pragma once
#include "misc.h"
#include "distribution.h"

template<int SIZE>
class d_something: public distribution
{
public:
  d_something () : distribution ({}, "")
  {
    int size = SIZE;
    std::vector<std::pair<double, double>> values_and_probabilities;
    for (int i = 1; i <= size; i++)
      values_and_probabilities.push_back ({i, 1});

    m_values_and_probabilities = values_and_probabilities;
    m_name = "d" + std::to_string (size);
  }
};

typedef d_something<4> d4_dice;
typedef d_something<6> d6_dice;
typedef d_something<8> d8_dice;
typedef d_something<10> d10_dice;
typedef d_something<12> d12_dice;
typedef d_something<20> d20_dice;

static d4_dice d4;
static d6_dice d6;
static d8_dice d8;
static d10_dice d10;
static d12_dice d12;
static d20_dice d20;
