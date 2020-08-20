#pragma once
#include "misc.h"
#include "distribution.h"

struct element_t
{
  bool operator == (const element_t &o) const { return m_modified == o.m_modified && m_base == o.m_base; }
  bool operator < (const element_t &o) const { return m_modified < o.m_modified; }
  element_t operator + (const element_t &rhs) const { return element_t (m_modified + rhs.m_modified, m_base + rhs.m_base); }
  element_t operator + (int rhs) const { return element_t (m_modified + rhs, m_base); }
  element_t () {}
  element_t (int modified, int base) : m_modified (modified), m_base (base) {}
  element_t (int val) : element_t (val, val) {}
  element_t (const element_t &o) : m_modified (o.m_modified), m_base (o.m_base) {}
  element_t &operator = (const element_t &o) { m_modified = o.m_modified; m_base = o.m_base; return *this; }
  int val () const { return m_modified; }
  int m_modified = 0;
  int m_base = 0;
};

std::vector<int> values (const std::vector<element_t> & src);
std::vector<int> bases (const std::vector<element_t> & src);

distribution<element_t> create_d_something (int size);
distribution<element_t> create_d_zero ();

const extern distribution<element_t> d0;
const extern distribution<element_t> d4;
const extern distribution<element_t> d6;
const extern distribution<element_t> d8;
const extern distribution<element_t> d10;
const extern distribution<element_t> d12;
const extern distribution<element_t> d20;
