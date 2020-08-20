#pragma once
#include "misc.h"
#include "dnd_dice.h"

template<typename ElemT>
class distribution;

distribution<element_t> great_weapon_fighting (distribution<element_t> base_damage_dice);
distribution<element_t> advantage (distribution<element_t> base_attack_dice);
distribution<element_t> improved_critical_strike (distribution<element_t> base_attack_dice);
distribution<element_t> auto_crit (distribution<element_t> base_attack_dice, unsigned int armor_class);
distribution<element_t> damage_on_hit (distribution<element_t> attack_dice, distribution<element_t> damage_dice, unsigned int armor_class);
