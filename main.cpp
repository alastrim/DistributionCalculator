#include <QApplication>
#include "misc.h"
#include "distribution.h"

int main (int argc, char **argv)
{
  QApplication a (argc, argv);

  d10 base_damage_dice;
  std::vector<distribution> base_damage_dice_v = distribution_vector (base_damage_dice, 2);

  target_function great_weapon_fighting ([] (auto vals) { return (vals[0] < 3 ? vals[1] : vals[0]); }, base_damage_dice_v);
  distribution gwf_damage_dice (base_damage_dice_v, great_weapon_fighting, "Damage roll after gwf");
  std::vector<distribution> gwf_damage_dice_v = distribution_vector (gwf_damage_dice, 1);

  target_function plus_three_to_dmg ([] (auto vals) { return max (vals) + 3; }, gwf_damage_dice_v);
  distribution damage_dice (gwf_damage_dice_v, plus_three_to_dmg, "Damage roll");

  d20 base_attack_dice;
  std::vector<distribution> base_attack_dice_v = distribution_vector (base_attack_dice, 1);

  target_function plus_six_to_attack ([] (auto vals) { return max (vals) + 6; }, base_attack_dice_v);
  distribution attack_dice (base_attack_dice_v, plus_six_to_attack, "Attack roll");

  std::vector<distribution> full_dice_v ({ base_attack_dice, attack_dice, gwf_damage_dice, damage_dice });

  int AC = 16;
  target_function deal_dmg_if_hits ([=] (auto vals)
    {
      int base_attack_res = static_cast<int> (vals[0]);
      int attack_res = static_cast<int> (vals[1]);
      int base_damage_res = static_cast<int> (vals[2]);
      int damage_res = static_cast<int> (vals[3]);

      if (base_attack_res == 20)
        return base_damage_res + damage_res;
      if (attack_res >=  AC)
        return damage_res;
      return 0;
    }, full_dice_v);
  distribution result_dmg_dice (full_dice_v, deal_dmg_if_hits, "Resulting damage roll");

  std::vector<distribution> result_dmg_dice_v = distribution_vector (result_dmg_dice, 2);
  target_function two_attacks ([] (auto vals) { return sum (vals); }, result_dmg_dice_v);
  distribution two_result_dice (result_dmg_dice_v, two_attacks, "Resulting damage of two attacks");
  two_result_dice.show ();


//  d6 dice;
//  auto four_dice_rolls = distribution_vector (dice, 4);
//  target_function f ([] (auto vals) { return sum (vals) - min (vals); }, four_dice_rolls);
//  distribution stat_roll (four_dice_rolls, f, "Stat value from four dice rolls");

//  auto six_stat_rolls = distribution_vector (stat_roll, 6);
//  target_function g ([] (auto vals) { return max (vals); }, six_stat_rolls);
//  distribution highiest_stat_roll (six_stat_rolls, g, "Highiest stat value from six stat rolls");
//  highiest_stat_roll.show ();

  return a.exec ();
}
