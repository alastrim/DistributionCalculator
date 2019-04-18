#pragma once
#include "misc.h"

std::unique_ptr<QWidget> create_chart (std::vector<std::pair<double, double>> values_and_probabilities, std::string name);
