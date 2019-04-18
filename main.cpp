#include <QApplication>
#include "misc.h"
#include "distribution.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  distribution dice_roll ({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}}, "Dice roll");
  target_function func = [] (std::vector<double> values)
  {
    al_assert (values.size () == 4, "Bad value vector size");
    return std::accumulate (values.begin (), values.end (), 0.0) - *std::min_element (values.begin (), values.end ());
  };
  std::vector<distribution> four_dice_rolls = { dice_roll, dice_roll, dice_roll, dice_roll };
  distribution stat_roll (four_dice_rolls, func, "Stat value from four dice rolls");

  target_function highiest = [] (std::vector<double> values)
  {
    al_assert (values.size () == 6, "Bad value vector size");
    return *std::max_element (values.begin (), values.end ());
  };
  std::vector<distribution> six_stat_rolls = { stat_roll, stat_roll, stat_roll, stat_roll, stat_roll, stat_roll };
  distribution highiest_stat_roll (six_stat_rolls, highiest, "Highiest stat value from six stat rolls");
  highiest_stat_roll.show ();

  return a.exec ();
}
