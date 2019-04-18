#include <QApplication>
#include "misc.h"
#include "distribution.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  distribution dice_roll ({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}}, "Dice roll");
  target_function sum = [] (std::vector<double> values)
  {
    al_assert (values.size () == 2, "Bad value vector size");
    return values[0] + values[1];
  };
  std::vector<distribution> two_dice_rolls = { dice_roll, dice_roll };
  distribution sum_of_two_dice_rolls (two_dice_rolls, sum, "Sum of two dice rolls");
  sum_of_two_dice_rolls.show ();

  return a.exec ();
}
