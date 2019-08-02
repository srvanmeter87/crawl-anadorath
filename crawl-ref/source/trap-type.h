#pragma once

enum trap_type
{
    TRAP_DART,
    TRAP_ARROW,
    TRAP_SPEAR,
#if TAG_MAJOR_VERSION > 34
    TRAP_DISPERSAL,
    TRAP_TELEPORT,
#endif
    TRAP_TELEPORT_PERMANENT,
    TRAP_ALARM,
    TRAP_BLADE,
    TRAP_BOLT,
    TRAP_NET,
    TRAP_ZOT,
#if TAG_MAJOR_VERSION == 34
    TRAP_NEEDLE,
#endif
    TRAP_SHAFT,
    TRAP_GOLUBRIA,
    TRAP_PLATE,
    TRAP_WEB,
#if TAG_MAJOR_VERSION == 34
    TRAP_GAS,
    TRAP_TELEPORT,
    TRAP_SHADOW,
    TRAP_SHADOW_DORMANT,
    TRAP_DISPERSAL,
#endif
    NUM_TRAPS,
    TRAP_MAX_REGULAR = TRAP_SHAFT,
    TRAP_UNASSIGNED = 100,
#if TAG_MAJOR_VERSION == 34
    TRAP_UNUSED1,                      // was TRAP_INDEPTH
    TRAP_UNUSED2,                      // was TRAP_NOTELEPORT
#endif
    TRAP_RANDOM,
};
