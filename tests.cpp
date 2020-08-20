#include "tests.h"

#include "distribution.h"
#include "dnd_dice.h"
#include "modifiers.h"
#include "misc.h"
#include "stats.h"

void run_tests ()
{
  {
    stats_t expected = stats_t (10.5, 10.5);
    stats_t got = d20.stats ();
    al_assert (expected == got, "test fail");
  }

  {
    unsigned int AC = 15;

    distribution<dnd> superiority_glaive = damage_on_hit (d20 + 6, great_weapon_fighting (d10) + d8 + 3, AC);
    distribution<dnd> shaft = damage_on_hit (d20 + 6, great_weapon_fighting (d4) + 3, AC);
    distribution<dnd> hollen_round = superiority_glaive * 4 + shaft;

    stats_t expected = stats_t (39.030000000000015, 39);
    stats_t got = hollen_round.stats ();
    al_assert (expected == got, "test fail");
  }

  {
    unsigned int AC = 15;

    distribution<dnd> direwolf = damage_on_hit (advantage (d20 + 5), d6 * 2 + 3, AC);
    distribution<dnd> wolf = damage_on_hit (advantage (d20 + 4), d4 * 2 + 2, AC);
    distribution<dnd> druid_round = direwolf + wolf * 4;

    stats_t expected = stats_t (31.607500000000016, 32);
    stats_t got = druid_round.stats ();
    al_assert (expected == got, "test fail");
  }
}
