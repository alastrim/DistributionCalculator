#include <QApplication>
#include "misc.h"
#include "distribution.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  distribution dice_roll ({{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}}, "Dice roll");
  dice_roll.show ();

  return a.exec ();
}
