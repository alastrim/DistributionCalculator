#include <QApplication>
#include "misc.h"
#include "distribution.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  d6 dice;
  std::vector<distribution> four_dice_rolls = distibution_vector (dice, 4);
  target_function f ([] (auto vals) { return sum (vals) - min (vals); }, four_dice_rolls);
  distribution stat_roll (four_dice_rolls, f, "Stat value from four dice rolls");

  std::vector<distribution> six_stat_rolls = distibution_vector (stat_roll, 6);
  target_function g ([] (auto vals) { return max (vals); }, six_stat_rolls);
  distribution highiest_stat_roll (six_stat_rolls, g, "Highiest stat value from six stat rolls");
  highiest_stat_roll.show ();

  return a.exec ();
}
