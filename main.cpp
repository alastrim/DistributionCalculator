#include <QApplication>
#include "misc.h"
#include "distribution.h"
#include "target_function.h"
#include "standard_dice.h"
#include "modifiers.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  distribution base_damage_dice = great_weapon_fighting (d10);
  distribution damage_dice = base_damage_dice + 3;
  distribution base_attack_dice = d20;
  distribution attack_dice = base_attack_dice + 6;

  unsigned int AC = 7;
  distribution result_damage = damage_on_hit (base_attack_dice, attack_dice, base_damage_dice, damage_dice, AC);

  result_damage.show ();

  return a.exec ();
}
