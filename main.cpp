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

  // рапира, ловкость +5, скрытая атака 3д6, автокрит
  distribution rapier = damage_on_hit (auto_crit (d20 + 8, AC), d8 + d6 * 3 + 5, AC);
  rapier.show ();

  // то же самое с 9д6 скрытой атаки
  distribution stronger_rapier = damage_on_hit (auto_crit (d20 + 8, AC), d8 + d6 * 9 + 5, AC);
  stronger_rapier.show ();

  return a.exec ();
}
