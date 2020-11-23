#pragma once
#include "misc.h"
#include "dnd_dice.h"

template<typename ElemT>
class distribution;

distribution<dnd> highiest (std::vector<distribution<dnd>> distributions);
distribution<dnd> roll4drop1 ();
distribution<dnd> great_weapon_fighting (distribution<dnd> base_damage_dice);
distribution<dnd> advantage (distribution<dnd> base_attack_dice);
distribution<dnd> improved_critical_strike (distribution<dnd> base_attack_dice);
distribution<dnd> auto_crit (distribution<dnd> base_attack_dice, unsigned int armor_class);
distribution<dnd> damage_on_hit (distribution<dnd> attack_dice, distribution<dnd> damage_dice, unsigned int armor_class);
