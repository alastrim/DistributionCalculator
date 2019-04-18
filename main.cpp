#include <QApplication>
#include "misc.h"
#include "distribution.h"
#include "target_function.h"
#include "standard_dice.h"
#include "modifiers.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  distribution damage_dice = great_weapon_fighting (d10) + 3;
  distribution attack_dice = d20 + 6;

  unsigned int AC = 15;
  distribution result_damage = damage_on_hit (attack_dice, damage_dice, AC);
  distribution two_attacks = result_damage + result_damage;

  two_attacks.show ();

  return a.exec ();
}
