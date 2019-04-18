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

void al_assert (bool check, std::string message);
int toi (size_t src);
unsigned int tou (int src);
int fuzzycmp (double a, double b = 0.0);
