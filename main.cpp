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

//  distribution superiority_glaive = damage_on_hit (d20 + 6, great_weapon_fighting (d10) + d8 + 3, AC);
//  distribution shaft = damage_on_hit (d20 + 6, great_weapon_fighting (d4) + 3, AC);
//  distribution hollen_round = superiority_glaive * 4 + shaft;
//  hollen_round.show ();

//  distribution direwolf = damage_on_hit (advantage (d20 + 5), d6 * 2 + 3, AC);
//  distribution wolf = damage_on_hit (advantage (d20 + 4), d4 * 2 + 2, AC);
//  distribution druid_round = direwolf + wolf * 8;
//  druid_round.show ();

  distribution rapier = damage_on_hit (auto_crit (d20 + 8, AC), d8 + d6 * 10 + 8, AC);
  rapier.show ();

  return a.exec ();
}
