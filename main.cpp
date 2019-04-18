#include <QApplication>
#include "misc.h"
#include "distribution.h"
#include "target_function.h"
#include "standard_dice.h"
#include "modifiers.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  unsigned int AC = 19;

  distribution rapier = damage_on_hit (auto_crit (d20 + 8, AC), d8 + d6 + d6 + d6 + 5, AC);
  rapier.show ();

  return a.exec ();
}
