#include "modifiers.h"
#include "distribution.h"
#include "target_function.h"

distribution great_weapon_fighting (distribution base_damage_dice)
{
  std::vector<distribution> v = {base_damage_dice, base_damage_dice};
  target_function f ([] (vals_and_bases vb)
    {
      int dmg_dice_1 = static_cast<int> (values (vb)[0]);
      int dmg_dice_2 = static_cast<int> (values (vb)[1]);

      if (dmg_dice_1 < 3)
        return val_and_base (dmg_dice_2, dmg_dice_2);
      return val_and_base (dmg_dice_1, dmg_dice_1);
     }, v);
  return distribution (v, f, "Result");
}

distribution advantage (distribution base_attack_dice)
{
  std::vector<distribution> v = {base_attack_dice, base_attack_dice};
  target_function f ([] (vals_and_bases vb)
    {
      int dmg_dice_1 = static_cast<int> (values (vb)[0]);
      int dmg_dice_2 = static_cast<int> (values (vb)[1]);

      int max = std::max (dmg_dice_1, dmg_dice_2);
      return val_and_base (max, max);
     }, v);
  return distribution (v, f, "Result");
}

distribution improved_critical_strike (distribution base_attack_dice)
{
  std::vector<distribution> v = {base_attack_dice};
  target_function f ([] (vals_and_bases vb)
    {
      int val_dice = static_cast<int> (values (vb)[0]);
      int base_dice = static_cast<int> (bases (vb)[0]);

      if (base_dice == 19)
        return val_and_base (val_dice, 20);

      return val_and_base (val_dice, base_dice);
     }, v);
  return distribution (v, f, "Result");
}

distribution auto_crit (distribution base_attack_dice, unsigned int armor_class)
{
  std::vector<distribution> v = {base_attack_dice};
  target_function f ([armor_class] (vals_and_bases vb)
    {
      int val_dice = static_cast<int> (values (vb)[0]);
      int base_dice = static_cast<int> (bases (vb)[0]);

      if (val_dice >= toi (armor_class))
        return val_and_base (val_dice, 20);

      return val_and_base (val_dice, base_dice);
     }, v);
  return distribution (v, f, "Result");
}

distribution damage_on_hit (distribution attack_dice, distribution damage_dice, unsigned int armor_class)
{
  std::vector<distribution> v = {attack_dice, damage_dice};
  target_function f ([=] (vals_and_bases vb)
    {
      int base_attack = static_cast<int> (bases (vb)[0]);
      int val_attack = static_cast<int> (values (vb)[0]);
      int base_damage = static_cast<int> (bases (vb)[1]);
      int val_damage = static_cast<int> (values (vb)[1]);

      if (base_attack == 20)
        return val_and_base (base_damage + val_damage, base_damage + val_damage);
      if (base_attack == 1)
        return val_and_base (0, 0);
      if (val_attack >=  toi (armor_class))
        return val_and_base (val_damage, val_damage);
      return val_and_base (0, 0);
    }, v);
  return distribution (v, f, "Result");
}
