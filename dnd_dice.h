#pragma once
#include "misc.h"
#include "distribution.h"

struct dnd
{
  bool operator == (const dnd &o) const { return m_modified == o.m_modified && m_base == o.m_base; }
  bool operator < (const dnd &o) const { return m_modified < o.m_modified; }
  dnd operator + (const dnd &rhs) const { return dnd (m_modified + rhs.m_modified, m_base + rhs.m_base); }
  dnd operator + (int rhs) const { return dnd (m_modified + rhs, m_base); }
  dnd () {}
  dnd (int modified, int base) : m_modified (modified), m_base (base) {}
  dnd (int val) : dnd (val, val) {}
  dnd (const dnd &o) : m_modified (o.m_modified), m_base (o.m_base) {}
  dnd &operator = (const dnd &o) { m_modified = o.m_modified; m_base = o.m_base; return *this; }
  int val () const { return m_modified; }
  int m_modified = 0;
  int m_base = 0;
};

std::vector<int> values (const std::vector<dnd> & src);
std::vector<int> bases (const std::vector<dnd> & src);

distribution<dnd> create_d_something (int size);
distribution<dnd> create_d_zero ();

const extern distribution<dnd> d0;
const extern distribution<dnd> d4;
const extern distribution<dnd> d6;
const extern distribution<dnd> d8;
const extern distribution<dnd> d10;
const extern distribution<dnd> d12;
const extern distribution<dnd> d20;
