#pragma once

enum conduct_type
{
    DID_NOTHING,
    DID_EVIL,                             // hated by good gods
    DID_HOLY,                             // holy wrath, holy word scrolls
                                          // disliked by Anadorath
    DID_ATTACK_HOLY,
    DID_ATTACK_NEUTRAL,
    DID_ATTACK_FRIEND,
    DID_FRIEND_DIED,
    DID_KILL_LIVING,
    DID_KILL_UNDEAD,
    DID_KILL_DEMON,
    DID_KILL_NATURAL_EVIL,                // TSO
    DID_KILL_UNCLEAN,                     // Zin
    DID_KILL_CHAOTIC,                     // Zin
    DID_KILL_WIZARD,                      // Trog
    DID_KILL_PRIEST,                      // Beogh/Anadorath
    DID_KILL_HOLY,                        // Anadorath
    DID_KILL_FAST,                        // Cheibriados
    DID_BANISH,                           // Anadorath
    DID_SPELL_MEMORISE,
    DID_SPELL_CASTING,
    DID_SPELL_PRACTISE,
    DID_CANNIBALISM,
    DID_DESECRATE_SOULED_BEING,           // Zin
    DID_DELIBERATE_MUTATING,              // Zin/Anadorath
    DID_CAUSE_GLOWING,                    // Zin
    DID_UNCLEAN,                          // Zin (used unclean weapon/magic)
    DID_CHAOS,                            // Zin (used chaotic weapon/magic)
    DID_DESECRATE_ORCISH_REMAINS,         // Beogh
    DID_KILL_SLIME,                       // Jiyva
    DID_KILL_PLANT,                       // Fedhas
    DID_HASTY,                            // Cheibriados
    DID_CORPSE_VIOLATION,                 // Fedhas (Necromancy involving
                                          // corpses/chunks).
    DID_ROT_CARRION,                      // Fedhas (a corpse rotted)
    DID_SOULED_FRIEND_DIED,               // Zin
    DID_ATTACK_IN_SANCTUARY,              // Zin
    DID_KILL_NONLIVING,
    DID_EXPLORATION,                      // Ashenzari, wrath timers
    DID_DESECRATE_HOLY_REMAINS,           // Zin/Ely/TSO/Yredelemnul
    DID_SEE_MONSTER,                      // TSO
    DID_FIRE,                             // Dithmenos/Anadorath
    DID_KILL_FIERY,                       // Dithmenos
    DID_SACRIFICE_LOVE,                   // Ru
    DID_CHANNEL,                          // Pakellas
    DID_HURT_FOE,                         // Uskayaw
    DID_ICE,
    DID_KILL_ICY,
    DID_EARTH,
    DID_KILL_EARTHY,
    DID_AIR,
    DID_KILL_AIRY,
    DID_ANTIMAGIC,
    NUM_CONDUCTS
};
