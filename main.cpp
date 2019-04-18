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

//  // all-out without advantage for Hollen Rid
//  distribution superiority_glaive = damage_on_hit (d20 + 6, great_weapon_fighting (d10) + d8 + 3, AC);
//  distribution shaft = damage_on_hit (d20 + 6, great_weapon_fighting (d4) + 3, AC);
//  distribution hollen_full_round = superiority_glaive + superiority_glaive + superiority_glaive + superiority_glaive + shaft;
//  hollen_full_round.show ();

  // all-out for crow without advantage
  distribution rapier = damage_on_hit (improved_critical_strike (d20 + 7), d8 + d8 + d8 + d8 + 6, AC);
  distribution crow_full_round = rapier + rapier + rapier + rapier;
  crow_full_round.show ();
//  distribution test = damage_on_hit (improved_critical_strike (d20 + 7), d4, AC);
//  test.show ();

  return a.exec ();
}
