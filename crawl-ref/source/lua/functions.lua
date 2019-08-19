-- Options can be referenced by lua via "options.option_name"

--[[
  b "turn_is_over"
  s "turns"
  n "time"
  "spells"
  "spell_letters"
  "spell_table"
  "spell_levels"
  "mem_spells"
  "abilities"
  "ability_letters"
  "ability_table"
  s "name"
  s "race"
  s "class"
  s "genus"
  "monster"
  b "wizard"
  s "god"
  n "gold"
  b "good_god"
  b "evil_god"
  b "one_time_ability_used"
  n "hp"
  n "mp"
  n "base_mp"
  n "rot"
  n "hunger"
  s "hunger_name"
  n "strength"
  n "intelligence"
  n "dexterity"
  "skill"
  "base_skill"
  n "skill_progress"
  b "can_train_skill"
  s "best_skill"
  "train_skill"
  "skill_cost"
  n "xl"
  n "xl_progress"
  n "res_poison"
  n "res_fire"
  n "res_cold"
  n "res_draining"
  n "res_shock"
  n "res_mutation"
  b "see_invisible"
  n "spirit_shield"
  b "like_chunks"
  b "gourmand"
  b "res_corr"
  b "flying"
  s "transform"
  b "berserk"
  b "confused"
  b "paralysed"
  b "shrouded"
  b "swift"
  b "caught"
  b "asleep"
  b "hasted"
  b "slowed"
  b "exhausted"
  b "teleporting"
  b "anchored"
  b "rooted"
  b "poisoned"
  b "poison_survival"
  "corrosion"
  b "invisible"
  b "mesmerised"
  b "on_fire"
  b "petrifying"
  b "silencing"
  b "regenerating"
  b "breath_timeout"
  b "extra_resistant"
  b "mighty"
  b "agile"
  b "brilliant"
  b "silenced"
  b "sick"
  n "contaminated"
  b "feel_safe"
  n "deaths"
  n "lives"
  n "piety_rank"
  "under_penance"
  b "constricted"
  b "constricting"
  "status"
  "can_consume_corpses"
  "stop_activity"
  "taking_stairs"
  "floor_items"
  "where"
  "branch"
  "depth"
  "depth_fraction"
  "absdepth"
  "is_level_on_stack"
  "can_smell"
  "has_claws"
  "see_cell"
  "see_cell_no_trans"
  "see_cell_solid"
  "see_cell_solid_see"
  "get_base_mutation_level"
  "mutation"
  "temp_mutation"
  "how_mutated"
  "temp_mutations"
  "mutation_overview"
  "num_runes"
  "have_rune"
  "have_orb"
]]
-- Labyrinths: Macro the '<' key to ===safe_upstairs to use.
function safe_upstairs()
  if you.branch() == "Lab" then
     crawl.formatted_mpr("Really leave this labyrinth?", "prompt")
     local res = crawl.getch()
     if string.lower(string.char(res)) == "y" then
       crawl.sendkeys("<")
     end
  else
     crawl.sendkeys("<")
  end
end

-- Trog followers pick up books to burn.
add_autopickup_func(function (it, name)
  if you.god() == "Trog" then
    if it.class(true) == "book" and not it.name():find("manual") then
      return true
    end
  end
end)

-- Available equipment slots are filled.
add_autopickup_func(function(it, name)
  if it.is_useless then
    return
  end
  if it.class(true) == "armour" then
    local good_slots = {cloak="Cloak", helmet="Helmet", gloves="Gloves",
                        boots="Boots"}
    st, _ = it.subtype()
    if good_slots[st] ~= nil and items.equipped_at(good_slots[st]) == nil then
      return true
    end
  end
end)

-- Forbidden/Useless items like those already in inventory are still picked up.
add_autopickup_func(function(it, name)
  local itname = it.name(true)
  if it.is_forbidden or it.is_useless then
    for inv in iter.invent_iterator:new(items.inventory()) do
      if itname == inv.name() then
        return true
      end
    end
  end
  return
end)

-- Branded/Ego items are picked up.
add_autopickup_func(function(it, name)
  if it.class(true) == "armour" or it.class(true) == "weapon" then
    if it.branded ~= nil then
      if not it.fully_identified then
        return true
      end
    end
  end
  return
end)

-- XP evokers not already in inventory are picked up.
add_autopickup_func(function (it, name)
  local itname = it.name(true)
  if string.find(itname, "lamp of fire")
  or string.find(itname, "phial of floods")
  or string.find(itname, "fan of gales")
  or string.find(itname, "lightning rod")
  or string.find(itname, "crystal ball of energy") then
    for _, inv_it in pairs(items.inventory()) do
      if itname == inv_it.name() then
        return false
      end
    end
  end
  return
end)

-- Rings not already in inventory are picked up.
add_autopickup_func(function (it, name)
  local itsubtype = it.subtype()
  if you.mutation("missing a hand") == 1
  and it.class(true) == "jewellery"
  and (itsubtype == "ring of positive energy"
    or itsubtype == "ring of flight"
    or itsubtype == "ring of poison resistance"
    or itsubtype == "ring of wizardry"
    or itsubtype == "ring of stealth"
    or itsubtype == "ring of teleportation"
    or itsubtype == "ring of protection from fire"
    or itsubtype == "ring of protection from cold"
    or itsubtype == "ring of resist corrosion"
    or itsubtype == "ring of see invisible"
    or itsubtype == "ring of magical power"
    or itsubtype == "ring of ice"
    or itsubtype == "ring of fire") then
      for _, inv_it in pairs(items.inventory()) do
        if it.class(true) == inv_it.class(true)
          and itsubtype == inv_it.subtype() then
        return false
      end
    end
  end
  return
end)

-- Useful staves relative to background are picked up.
--[[ add_autopickup_func(function(it, name)
  local bg = you.class()
  local st = it.subtype()
  if it.class(true) == "staff" then
    if st == "staff of fire" then
      if bg == "JOB_WIZARD"
      or bg == "JOB_CONJURER"
      or bg == "JOB_FIRE_ELEMENTALIST" then
        return true
      end
    elseif st == "staff of cold" then
      if bg == "JOB_WIZARD"
      or bg == "JOB_CONJURER"
      or bg == "JOB_ICE_ELEMENTALIST" then
        return true
      end
    elseif st == "staff of poison" then
      if bg == "JOB_WIZARD"
      or bg == "JOB_CONJURER"
      or bg == "JOB_VENOM_MAGE" then
        return true
      end
    elseif st == "staff of death" then
      if bg == "JOB_NECROMANCER" then
        return true
      end
    elseif st == "staff of earth" then
      if bg == "JOB_EARTH_ELEMENTALIST" then
        return true
      end
    elseif st == "staff of air" then
      if bg == "JOB_AIR_ELEMENTALIST" then
        return true
      end
    elseif st == "staff of summoning" then
      if bg == "JOB_SUMMONER" then
        return true
      end
    elseif st == "staff of conjuration" then
      if bg == "JOB_CONJURER" then
        return true
      end
    elseif st == "staff of wizardry" then
      if bg == "JOB_WIZARD" then
        return true
      end
    elseif st == "staff of energy" then
      if bg == "JOB_WARPER" then
        return true
      end
    elseif st == "staff of power" then
      if bg == "JOB_WIZARD" then
        return true
      end
    else
      return true
    end
  end
  return
end)
 ]]
-- Stacking items are picked up.
add_autopickup_func(function (it, name)
  return it.stacks() or nil
end)

-- All items except forbidden/useless already in inventory are picked up.
add_autopickup_func(function(it, name)
  local itname = it.name(true)
  if not it.is_forbidden and not it.is_useless then
    for _, inv_it in pairs(items.inventory()) do
      if itname == inv_it.name() then
        return true
      end
    end
  end
  return
end)

-- Automatically open the skill menu on start of a new game.
--[[
local need_skills_opened = true
function ready()
  if you.turns() == 0 and need_skills_opened then
    need_skills_opened = false
    crawl.sendkeys("m")
  end
end
]]
