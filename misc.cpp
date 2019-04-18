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

double sum (std::vector<double> values)
{
  return std::accumulate (values.begin (), values.end (), 0.0);
}

double min (std::vector<double> values)
{
  return *std::min_element (values.begin (), values.end ());
}

double max (std::vector<double> values)
{
  return *std::max_element (values.begin (), values.end ());
}
