#pragma once


// Enumeration of Shop Types.
 enum shop_type
{
    SHOP_WEAPON,            // General weapon vendor
    SHOP_ARMOUR,            // General armour vendor
    SHOP_WEAPON_ANTIQUE,    // Antique weapon vendor
    SHOP_ARMOUR_ANTIQUE,    // Antique armour vendor
    SHOP_GENERAL_ANTIQUE,   // General antiques vendor
    SHOP_JEWELLERY,         // Wearable jewellery vendor
    SHOP_EVOKABLES,         // Wands and miscellaneous gadgets vendor
    SHOP_BOOKS,             // Skill and spell books vendor
    SHOP_DISTILLERY,        // Potions vendor
    SHOP_RUNESCRIBE,        // Scrolls vendor
    SHOP_GENERAL,           // General vendor
    NUM_SHOPS,              // Must remain last 'regular' member {dlb}

    SHOP_UNASSIGNED = 100,  // Unassigned shop (inventory depleted?)
    SHOP_RANDOM,            // Randomised vendor (0-10)
};
