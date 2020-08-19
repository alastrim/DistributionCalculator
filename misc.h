#pragma once

#include <string>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <functional>
#include <memory>

#define MIN_FOR_DIVISION 1e-16
#define MIN_FOR_COMPARISON 1e-16
#define ELEMS_ON_SCREEN 12
#define DEBUG 1

struct element_t
{
  bool operator == (const element_t &o) const { return m_val == o.m_val && m_base == o.m_base; }
  bool operator < (const element_t &o) const { return m_val < o.m_val; }
  element_t () {}
  element_t (int val, int base) : m_val (val), m_base (base) {}
  element_t (int val) : element_t (val, val) {}
  element_t (const element_t &o) : m_val (o.m_val), m_base (o.m_base) {}
  element_t &operator = (const element_t &o) { m_val = o.m_val; m_base = o.m_base; return *this; }
  int m_val = 0;
  int m_base = 0;
};

struct value_and_probability
{
  value_and_probability (element_t val, double probability) : m_val (val), m_probability (probability) {}
  bool operator < (const value_and_probability &o) const { return m_val < o.m_val; }
  element_t m_val;
  double m_probability = 0;
};

void al_assert (bool check, std::string message);
int toi (size_t src);
unsigned int tou (int src);
int fuzzycmp (double a, double b = 0.0);
int sum (const std::vector<int> &values);
int min (const std::vector<int> &values);
int max (const std::vector<int> &values);
