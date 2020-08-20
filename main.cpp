#include "misc.h"
#include "distribution.h"
#include "target_function.h"
#include "dnd_dice.h"
#include "modifiers.h"
#include "tests.h"

int main ()
{
  run_tests ();

  unsigned int AC = 15;

  distribution<element_t> superiority_glaive = damage_on_hit (d20 + 6, great_weapon_fighting (d10) + d8 + 3, AC);
  distribution<element_t> shaft = damage_on_hit (d20 + 6, great_weapon_fighting (d4) + 3, AC);
  distribution<element_t> hollen_round = superiority_glaive * 4 + shaft;
  hollen_round.show ("Hollen round");

  distribution<element_t> direwolf = damage_on_hit (advantage (d20 + 5), d6 * 2 + 3, AC);
  distribution<element_t> wolf = damage_on_hit (advantage (d20 + 4), d4 * 2 + 2, AC);
  distribution<element_t> druid_round = direwolf + wolf * 4;
  druid_round.show ();

//  distribution rapier = damage_on_hit (auto_crit (d20 + 8, AC), d8 + d6 * 10 + 8, AC);
//  rapier.show ();

  return 0;
}
