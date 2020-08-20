#include "modifiers.h"
#include "distribution.h"
#include "target_function.h"

distribution<element_t> great_weapon_fighting (distribution<element_t> base_damage_dice)
{
  std::vector<distribution<element_t>> v = {base_damage_dice, base_damage_dice};
  target_function<element_t> f ([] (const std::vector<element_t> & vb)
    {
      int dmg_dice_1 = (values (vb)[0]);
      int dmg_dice_2 = (values (vb)[1]);

      if (dmg_dice_1 < 3)
        return element_t (dmg_dice_2, dmg_dice_2);
      return element_t (dmg_dice_1, dmg_dice_1);
     }, v);
  return distribution<element_t> (v, f);
}

distribution<element_t> advantage (distribution<element_t> base_attack_dice)
{
  std::vector<distribution<element_t>> v = {base_attack_dice, base_attack_dice};
  target_function<element_t> f ([] (const std::vector<element_t> & vb)
    {
      int base_1 = (bases (vb)[0]);
      int base_2 = (bases (vb)[1]);
      int val_1 = values (vb)[0];
      int val_2 = values (vb)[1];

      int base_max = std::max (base_1, base_2);
      int val_max = std::max (val_1, val_2);

      return element_t (val_max, base_max);
     }, v);
  return distribution<element_t> (v, f);
}

distribution<element_t> improved_critical_strike (distribution<element_t> base_attack_dice)
{
  std::vector<distribution<element_t>> v = {base_attack_dice};
  target_function<element_t> f ([] (const std::vector<element_t> & vb)
    {
      int val_dice = (values (vb)[0]);
      int base_dice = (bases (vb)[0]);

      if (base_dice == 19)
        return element_t (val_dice, 20);

      return element_t (val_dice, base_dice);
     }, v);
  return distribution<element_t> (v, f);
}

distribution<element_t> auto_crit (distribution<element_t> base_attack_dice, unsigned int armor_class)
{
  std::vector<distribution<element_t>> v = {base_attack_dice};
  target_function<element_t> f ([armor_class] (const std::vector<element_t> & vb)
    {
      int val_dice = values (vb)[0];
      int base_dice = bases (vb)[0];

      if (val_dice >= toi (armor_class))
        return element_t (val_dice, 20);

      return element_t (val_dice, base_dice);
     }, v);
  return distribution<element_t> (v, f);
}

distribution<element_t> damage_on_hit (distribution<element_t> attack_dice, distribution<element_t> damage_dice, unsigned int armor_class)
{
  std::vector<distribution<element_t>> v = {attack_dice, damage_dice};
  target_function<element_t> f ([=] (const std::vector<element_t> & vb)
    {
      int base_attack = (bases (vb)[0]);
      int val_attack = (values (vb)[0]);
      int base_damage = (bases (vb)[1]);
      int val_damage = (values (vb)[1]);

      if (base_attack == 20)
        return element_t (base_damage + val_damage, base_damage + val_damage);
      if (base_attack == 1)
        return element_t (0, 0);
      if (val_attack >=  toi (armor_class))
        return element_t (val_damage, val_damage);
      return element_t (0, 0);
    }, v);
  return distribution<element_t> (v, f);
}
