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

  // hollen
  distribution superiority_glaive = damage_on_hit (advantage (d20 + 8), great_weapon_fighting (d10) + d8 + 5, AC);
  distribution shaft = damage_on_hit (advantage (d20 + 8), great_weapon_fighting (d4) + 5, AC);
  distribution hollen_round = superiority_glaive * 1 + shaft;
  hollen_round.show ();

  return a.exec ();
}
