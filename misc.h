#pragma once

#include <string>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <memory>

#define MIN_FOR_DIVISION 1e-15
#define MIN_FOR_COMPARISON 1e-15
#define ELEMS_ON_SCREEN 12
#define DEBUG 1

template<typename ElemT>
struct value_and_probability
{
  value_and_probability (ElemT val, double probability) : m_value (val), m_probability (probability) {}
  bool operator < (const value_and_probability<ElemT> &o) const { return m_value < o.m_value; }
  int val () const { return m_value.val (); }
  double prob () const { return m_probability; }
private:
  ElemT m_value;
  double m_probability = 0;
  template<typename T>
  friend class distribution;
};

void al_assert (bool check, std::string message);
int toi (size_t src);
unsigned int tou (int src);
int fuzzycmp (double a, double b = 0.0);
int relfuzzycmp (double a, double b = 0.0);

template<typename T>
T sum (const std::vector<T> &values) { return std::accumulate (values.begin (), values.end (), T { 0 }); }
template<typename T>
T min (const std::vector<T> &values) { return *std::min_element (values.begin (), values.end ()); }
template<typename T>
T max (const std::vector<T> &values) { return *std::max_element (values.begin (), values.end ()); }
