#include <QApplication>
#include "misc.h"
#include "distribution.h"
#include "target_function.h"
#include "standard_dice.h"
#include "modifiers.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  unsigned int AC = 15;
  distribution result_damage = damage_on_hit (d20 + 6, great_weapon_fighting (d10) + 3, AC);
  result_damage.show ();

  return a.exec ();
}
