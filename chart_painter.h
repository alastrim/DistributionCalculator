#pragma once
#include <cstdio>
#include <algorithm>
#include "stats.h"

#define BARNUM 16

struct val_range_and_prob
{
  val_range_and_prob () {}
  int beg;
  int end;
  double prob = 0;
};

template<typename T, typename A, template<typename, typename> class C>
C<C<T, A>, std::allocator<C<T, A>>> chunker (C<T, A> &c, const typename C<T, A>::size_type &k)
{
  if (k <= 0)
    throw std::domain_error ("chunker() requires k > 0");

  using INPUT_CONTAINER_TYPE = C<T, A>;
//  using INPUT_CONTAINER_VALUE_TYPE = typename INPUT_CONTAINER_TYPE::value_type;
  using OUTPUT_CONTAINER_TYPE = C<INPUT_CONTAINER_TYPE, std::allocator<INPUT_CONTAINER_TYPE>>;

  OUTPUT_CONTAINER_TYPE out_c;

  auto chunkBeg = begin (c);

  for (auto left = c.size (); left != 0;)
    {
      auto const skip = std::min (left, k);
      INPUT_CONTAINER_TYPE sub_container;
      std::back_insert_iterator<INPUT_CONTAINER_TYPE> back_v (sub_container);
      copy_n (chunkBeg, skip, back_v);
      out_c.push_back (sub_container);
      left -= skip;
      advance (chunkBeg, skip);
    }

  return out_c;
}

template<typename ElemT>
static std::vector<val_range_and_prob> format_for_showing (const std::vector<value_and_probability<ElemT>> &const_vals_and_probs)
{
  std::vector<value_and_probability<ElemT>> vals_and_probs = const_vals_and_probs;
  std::sort (vals_and_probs.begin (), vals_and_probs.end ());

  int chucksize = ceil (vals_and_probs.size () / (double) BARNUM);

  std::vector<std::vector<value_and_probability<ElemT>>> chunks = chunker (vals_and_probs, chucksize);
  std::vector<val_range_and_prob> bars (chunks.size ());
  al_assert (bars.size () <= BARNUM, "This doesnt work");

  for (size_t i = 0; i < bars.size (); i++)
    {
      std::vector<value_and_probability<ElemT>> &currchunk = chunks[i];
      val_range_and_prob &currbar = bars[i];
      currbar.beg = currchunk.front ().val ();
      currbar.end = currchunk.back ().val ();
      currbar.prob = 0;
      for (value_and_probability<ElemT> &curr : currchunk)
        bars[i].prob += curr.prob ();
    }

  return bars;
}

template<typename ElemT>
void chart (const std::vector<value_and_probability<ElemT>> &values_and_probabilities)
{
  std::vector<val_range_and_prob> bars = format_for_showing (values_and_probabilities);

  int len = 100;
  int chunk = 100 / len;
  al_assert (100 % len == 0, "Accuracy");

  printf ("Graph and probabilities:\n");

  bool longmode = false;
  for (const val_range_and_prob &bar : bars)
    if (bar.beg != bar.end)
      longmode = true;

  for (const val_range_and_prob &bar : bars)
    {
      int valb = bar.beg;
      int vale = bar.end;
      double prob = bar.prob * 100;
      int perc = (int) round (prob);

      if (valb == vale)
        {
          if (longmode)
            printf ("       %3d: ", valb);
          else
            printf ("%3d: ", valb);
        }
      else
        printf ("%3d to %3d: ", valb, vale);
      for (int i = 0; i < len; i++)
        printf ("%c", (perc > i * chunk) ? '#' : ' ');
      printf (" %5.2f%%\n", prob);
    }
}

