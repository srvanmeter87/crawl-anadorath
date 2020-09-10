/**
 * @file
 * @brief Character choice restrictions.
 *
 * The functions in this file are "pure": They don't
 * access any global data.
**/

#include "AppHdr.h"

#include "ng-restr.h"

#include "jobs.h"
#include "newgame.h"
#include "newgame-def.h"
#include "size-type.h"
#include "species.h"

static bool _banned_combination(job_type job, species_type species)
{
    switch (species)
    {
    case SP_FELID:
        if (job == JOB_GLADIATOR
            || job == JOB_BRIGAND
            || job == JOB_HUNTER
            || job == JOB_ARCANE_MARKSMAN)
        {
            return true;
        }
        break;
    case SP_DEMIGOD:
        if (job == JOB_BERSERKER
            || job == JOB_CHAOS_KNIGHT
            || job == JOB_ABYSSAL_KNIGHT
            || job == JOB_MONK
            || job == JOB_PRIMALIST)
        {
            return true;
        }
        break;
    case SP_PYROLITH:
        if (job == JOB_ABYSSAL_KNIGHT
            || job == JOB_AIR_ELEMENTALIST
            || job == JOB_ARTIFICER
            || job == JOB_BERSERKER
            || job == JOB_CHAOS_KNIGHT
            || job == JOB_ENCHANTER
            || job == JOB_ICE_ELEMENTALIST
            || job == JOB_MONK
            || job == JOB_NECROMANCER
            || job == JOB_TRANSMUTER
            || job == JOB_VENOM_MAGE
            || job == JOB_WANDERER
            || job == JOB_WARPER)
        {
            return true;
        }
        break;
    default:
        break;
    }

    if (job == JOB_TRANSMUTER
        && (species_undead_type(species) == US_UNDEAD
           || species_undead_type(species) == US_HUNGRY_DEAD))
    {
        return true;
    }
    if (job == JOB_PRIMALIST
        && ((species == SP_BARACHI)
            || (species == SP_CENTAUR)
            || (species == SP_FORMICID)
            || (species == SP_GHOUL)
            || (species == SP_HALFLING)
            || (species == SP_HILL_ORC)
            || (species == SP_KOBOLD)
            || (species == SP_MERFOLK)
            || (species == SP_MINOTAUR)
            || (species == SP_OGRE)
            || (species == SP_RANDOM)
            || (species == SP_SPRIGGAN)
            || (species == SP_TROLL)))
    {
        return true;
    }

    return false;
}

char_choice_restriction species_allowed(job_type job, species_type speci)
{
    if (!is_starting_species(speci) || !is_starting_job(job))
        return CC_BANNED;

    if (_banned_combination(job, speci))
        return CC_BANNED;

    if (job_recommends_species(job, speci))
        return CC_UNRESTRICTED;

    return CC_RESTRICTED;
}

bool character_is_allowed(species_type species, job_type job)
{
    return !_banned_combination(job, species);
}

char_choice_restriction job_allowed(species_type speci, job_type job)
{
    if (!is_starting_species(speci) || !is_starting_job(job))
        return CC_BANNED;

    if (_banned_combination(job, speci))
        return CC_BANNED;

    if (species_recommends_job(speci, job))
        return CC_UNRESTRICTED;

    return CC_RESTRICTED;
}

// Is the given god restricted for the character defined by ng?
// Only uses ng.species and ng.job.
char_choice_restriction weapon_restriction(weapon_type wpn,
                                           const newgame_def &ng)
{
    ASSERT(is_starting_species(ng.species));
    ASSERT(is_starting_job(ng.job));

    // Some special cases:

    if (ng.species == SP_FELID && wpn != WPN_UNARMED)
        return CC_BANNED;

    // These recommend short blades because they're good at stabbing,
    // but the fighter's armour hinders that.
    if ((ng.species == SP_NAGA || ng.species == SP_VAMPIRE)
         && ng.job == JOB_FIGHTER && wpn == WPN_RAPIER)
    {
        return CC_RESTRICTED;
    }

    if (wpn == WPN_QUARTERSTAFF && ng.job != JOB_GLADIATOR
        && !(ng.job == JOB_FIGHTER && ng.species == SP_FORMICID))
    {
        return CC_BANNED;
    }

    // Javelins are always good, boomerangs not so much.
    if (wpn == WPN_THROWN)
    {
        return species_size(ng.species) >= SIZE_MEDIUM ? CC_UNRESTRICTED
                                                       : CC_RESTRICTED;
    }

    if (species_recommends_weapon(ng.species, wpn))
        return CC_UNRESTRICTED;

    return CC_RESTRICTED;
}
