#pragma once
#include "misc.h"

class distribution;

class target_function
{
public:
  target_function (std::function<double (const std::vector<double> &)> function, std::vector<distribution> &base);
  double operator () (const std::vector<double> &);
  std::function<double (const std::vector<double> &)> m_function;
  int m_arg_count;
};

class distribution
{
public:
  distribution (const distribution &rhs);
  distribution (std::vector<distribution> distibutions, target_function function, std::string name);
  distribution (std::vector<std::pair<double, double>> values_and_probabilities, std::string name);
  void show ();
  void simplify ();

  std::vector<std::pair<double, double>> m_values_and_probabilities;
  std::string m_name;
  std::unique_ptr<QWidget> m_view;
};

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

typedef d_something<4> d4;
typedef d_something<6> d6;
typedef d_something<8> d8;
typedef d_something<10> d10;
typedef d_something<12> d12;
typedef d_something<20> d20;

