#pragma once
#include "misc.h"

class distribution;

distribution great_weapon_fighting (distribution &base_damage_dice);
distribution advantage (distribution &base_attack_dice);
distribution damage_on_hit (distribution &attack_dice, distribution &damage_dice, unsigned int armor_class);
