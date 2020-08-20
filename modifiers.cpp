#include "modifiers.h"
#include "distribution.h"
#include "target_function.h"

distribution<dnd> great_weapon_fighting (distribution<dnd> base_damage_dice)
{
  std::vector<distribution<dnd>> v = {base_damage_dice, base_damage_dice};
  target_function<dnd> f ([] (const std::vector<dnd> & vb)
    {
      int dmg_dice_1 = (values (vb)[0]);
      int dmg_dice_2 = (values (vb)[1]);

      if (dmg_dice_1 < 3)
        return dnd (dmg_dice_2, dmg_dice_2);
      return dnd (dmg_dice_1, dmg_dice_1);
     }, v);
  return distribution<dnd> (v, f);
}

distribution<dnd> advantage (distribution<dnd> base_attack_dice)
{
  std::vector<distribution<dnd>> v = {base_attack_dice, base_attack_dice};
  target_function<dnd> f ([] (const std::vector<dnd> & vb)
    {
      int base_1 = (bases (vb)[0]);
      int base_2 = (bases (vb)[1]);
      int val_1 = values (vb)[0];
      int val_2 = values (vb)[1];

      int base_max = std::max (base_1, base_2);
      int val_max = std::max (val_1, val_2);

      return dnd (val_max, base_max);
     }, v);
  return distribution<dnd> (v, f);
}

distribution<dnd> improved_critical_strike (distribution<dnd> base_attack_dice)
{
  std::vector<distribution<dnd>> v = {base_attack_dice};
  target_function<dnd> f ([] (const std::vector<dnd> & vb)
    {
      int val_dice = (values (vb)[0]);
      int base_dice = (bases (vb)[0]);

      if (base_dice == 19)
        return dnd (val_dice, 20);

      return dnd (val_dice, base_dice);
     }, v);
  return distribution<dnd> (v, f);
}

distribution<dnd> auto_crit (distribution<dnd> base_attack_dice, unsigned int armor_class)
{
  std::vector<distribution<dnd>> v = {base_attack_dice};
  target_function<dnd> f ([armor_class] (const std::vector<dnd> & vb)
    {
      int val_dice = values (vb)[0];
      int base_dice = bases (vb)[0];

      if (val_dice >= toi (armor_class))
        return dnd (val_dice, 20);

      return dnd (val_dice, base_dice);
     }, v);
  return distribution<dnd> (v, f);
}

distribution<dnd> damage_on_hit (distribution<dnd> attack_dice, distribution<dnd> damage_dice, unsigned int armor_class)
{
  std::vector<distribution<dnd>> v = {attack_dice, damage_dice};
  target_function<dnd> f ([=] (const std::vector<dnd> & vb)
    {
      int base_attack = (bases (vb)[0]);
      int val_attack = (values (vb)[0]);
      int base_damage = (bases (vb)[1]);
      int val_damage = (values (vb)[1]);

      if (base_attack == 20)
        return dnd (base_damage + val_damage, base_damage + val_damage);
      if (base_attack == 1)
        return dnd (0, 0);
      if (val_attack >=  toi (armor_class))
        return dnd (val_damage, val_damage);
      return dnd (0, 0);
    }, v);
  return distribution<dnd> (v, f);
}
