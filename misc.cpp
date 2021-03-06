#include "misc.h"
#include <algorithm>
#include <numeric>
#include <signal.h>

void al_assert (bool check, std::string message)
{
    if (!check)
    {
        fprintf (stderr, "WARNING: %s\n", message.c_str ());
#ifndef _WIN32
        ::raise (SIGTRAP);
#else
        __asm__("int $3");
#endif
        throw std::runtime_error (message);
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

int relfuzzycmp (double a, double b)
{
  if (fabs ((a - b) / b) < MIN_FOR_COMPARISON)
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
