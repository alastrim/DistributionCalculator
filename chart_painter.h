#pragma once
#include <cstdio>
#include <algorithm>
#include "stats.h"

#define BARNUM 10

template<typename ElemT>
struct val_range_and_prob
{
  val_range_and_prob () {}
  ElemT beg;
  ElemT end;
  double prob = 0;
};

template<typename ElemT>
static std::vector<val_range_and_prob<ElemT>> format_for_showing (const std::vector<value_and_probability<ElemT>> &const_vals_and_probs)
{
  std::vector<value_and_probability<ElemT>> vals_and_probs = const_vals_and_probs;
  std::sort (vals_and_probs.begin (), vals_and_probs.end ());

  int size = tou (vals_and_probs.size ());
  std::vector<val_range_and_prob<ElemT>> bars (BARNUM);
  int chunk_len = size / BARNUM;

  for (int i = 0; i < size; i++)
    {
      int internal_ind = i / chunk_len;
      if (internal_ind >= BARNUM)
        internal_ind = BARNUM - 1;

      if (!(i % chunk_len))
        bars[internal_ind].beg = vals_and_probs[i].m_val;
      else
        bars[internal_ind].end = vals_and_probs[i].m_val;
      bars[internal_ind].prob += vals_and_probs[i].m_probability;
    }

  return bars;
}

template<typename ElemT>
void chart (const std::vector<value_and_probability<ElemT>> &values_and_probabilities)
{
  std::vector<val_range_and_prob<ElemT>> bars = format_for_showing (values_and_probabilities);

  int len = 100;
  int chunk = 100 / len;
  al_assert (100 % len == 0, "Accuracy");

  for (const val_range_and_prob<ElemT> &bar : bars)
    {
      int valb = bar.beg.m_val;
      int vale = bar.end.m_val;
      double prob = bar.prob * 100;
      int perc = (int) round (prob);

      printf ("%3d to %3d: ", valb, vale);
      for (int i = 0; i < len; i++)
        printf ("%c", (perc > i * chunk) ? '#' : ' ');
      printf (" %5.2f%%\n", prob);
    }
}

