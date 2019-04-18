#pragma once

#include <string>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <functional>
#include <memory>
#include <QWidget>

#define MIN_FOR_DIVISION 1e-16
#define MIN_FOR_COMPARISON 1e-16
#define ELEMS_ON_SCREEN 12
#define DEBUG 1

typedef char al_argtype;
typedef std::pair<al_argtype, al_argtype> val_and_base;
typedef const std::vector<val_and_base> & vals_and_bases;
typedef std::pair<val_and_base, double> value_and_probability;
typedef std::vector<std::pair<std::vector<val_and_base>, double>> complex_distribution;

void al_assert (bool check, std::string message);
int toi (size_t src);
unsigned int tou (int src);
int fuzzycmp (double a, double b = 0.0);
al_argtype sum (std::vector<al_argtype> values);
al_argtype min (std::vector<al_argtype> values);
al_argtype max (std::vector<al_argtype> values);
