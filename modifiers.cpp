#include "modifiers.h"
#include "distribution.h"
#include "target_function.h"

distribution great_weapon_fighting (distribution &base_damage_dice)
{
  std::vector<distribution> v = {base_damage_dice, base_damage_dice};
  target_function f ([] (auto vals)
    {
      int dmg_dice_1 = static_cast<int> (vals[0]);
      int dmg_dice_2 = static_cast<int> (vals[1]);

      if (dmg_dice_1 < 3)
        return dmg_dice_2;
      return dmg_dice_1;
     }, v);
  return distribution (v, f, "Result");
}

distribution advantage (distribution &base_attack_dice)
{
  std::vector<distribution> v = {base_attack_dice, base_attack_dice};
  target_function f ([] (auto vals)
    {
      int dmg_dice_1 = static_cast<int> (vals[0]);
      int dmg_dice_2 = static_cast<int> (vals[1]);

      return std::max (dmg_dice_1, dmg_dice_2);
     }, v);
  return distribution (v, f, "Result");
}

distribution damage_on_hit (distribution &attack_dice, distribution &damage_dice, unsigned int armor_class)
{
  std::vector<distribution> v = {attack_dice.get_base (), attack_dice, damage_dice.get_base (), damage_dice};
  target_function f ([=] (auto vals)
    {
      int base_attack_res = static_cast<int> (vals[0]);
      int attack_res = static_cast<int> (vals[1]);
      int base_damage_res = static_cast<int> (vals[2]);
      int damage_res = static_cast<int> (vals[3]);

      if (base_attack_res == 20)
        return base_damage_res + damage_res;
      if (base_attack_res == 1)
        return 0;
      if (attack_res >=  toi (armor_class))
        return damage_res;
      return 0;
    }, v);
  return distribution (v, f, "Result");

}
