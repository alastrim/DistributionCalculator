#include "misc.h"

void al_assert (bool check, std::string message)
{
  if (!check)
    {
      fprintf (stderr, "WARNING: %s\n", message.c_str());
      throw std::exception ();
    }
}

int fuzzycmp (double a, double b)
{
  if (fabs (a - b) < MIN_FOR_COMPARISON)
    return 0;
  if (a > b)
    return 1;
  return -1;
}

int toi (size_t src)
{
  return static_cast<int> (src);
}

unsigned int tou (int src)
{
  return static_cast<unsigned int> (src);
}

al_argtype sum (std::vector<al_argtype> values)
{
  return std::accumulate (values.begin (), values.end (), static_cast<al_argtype> (0));
}

al_argtype min (std::vector<al_argtype> values)
{
  return *std::min_element (values.begin (), values.end ());
}

al_argtype max (std::vector<al_argtype> values)
{
  return *std::max_element (values.begin (), values.end ());
}
