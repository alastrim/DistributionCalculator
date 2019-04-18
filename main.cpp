#include <QApplication>
#include "misc.h"
#include "distribution.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  d6 dice;
  std::vector<distribution> four_dice_rolls = { dice, dice, dice, dice };
  target_function f ([] (auto vals) { return sum (vals) - min (vals); }, four_dice_rolls);
  distribution stat_roll (four_dice_rolls, f, "Stat value from four dice rolls");
  stat_roll.show ();

//  target_function highiest = [] (std::vector<double> values)
//  {
//    al_assert (values.size () == 6, "Bad value vector size");
//    return *std::max_element (values.begin (), values.end ());
//  };
//  std::vector<distribution> six_stat_rolls = { stat_roll, stat_roll, stat_roll, stat_roll, stat_roll, stat_roll };
//  distribution highiest_stat_roll (six_stat_rolls, highiest, "Highiest stat value from six stat rolls");
//  highiest_stat_roll.show ();

  return a.exec ();
}
