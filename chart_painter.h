#pragma once
#include "misc.h"

std::unique_ptr<QWidget> create_chart (std::vector<std::pair<double, uint64_t>> values_and_case_counts, std::string name);
