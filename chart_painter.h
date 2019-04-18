#pragma once
#include "misc.h"

std::unique_ptr<QWidget> create_chart (std::vector<std::pair<double, int>> values_and_case_counts, std::string name);
