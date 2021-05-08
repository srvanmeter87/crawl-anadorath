# Level Creation for Dungeon Crawl Stone Soup, Part II: Syntax

NOTE: This document contains the syntax needed for making maps and vaults. It
does not say anything about principles of vault making; for this, see
[Part I: Introduction](introduction.md).

For more technical aspects, including tests, lua and portal vaults, refer to
[Part III: Advanced](advanced.md).

For Triggerables, please see [triggerables.txt](triggerables.txt).

## [Table of Contents](#table-of-contents)

- [Level Creation for Dungeon Crawl Stone Soup, Part II: Syntax](#level-creation-for-dungeon-crawl-stone-soup-part-ii-syntax)
  - [Table of Contents](#table-of-contents)
  - [8. Glyphs](#8-glyphs)
    - [8A. Terrain](#8a-terrain)
    - [8B. Features](#8b-features)
    - [8C. Items](#8c-items)
    - [8D. Monsters](#8d-monsters)
  - [9. Header Information](#9-header-information)
    - [9A. `NAME:`](#9a-name)
    - [9B. `DESC:`](#9b-desc)
    - [9C. `ORDER:`](#9c-order)
    - [9D. `ORIENT:`](#9d-orient)
    - [9E. `DEPTH:`](#9e-depth)
    - [9F. `CHANCE:`](#9f-chance)
    - [9G. `WEIGHT:`](#9g-weight)
    - [9H. `PLACE:`](#9h-place)
    - [9I. `TAGS:`](#9i-tags)
    - [9J. `LFLOORCOL:`](#9j-lfloorcol)
    - [9K. `LROCKCOL:`](#9k-lrockcol)
    - [9L. `LFLOORTILE:`](#9l-lfloortile)
    - [9M. `LROCKTILE:`](#9m-lrocktile)
    - [9N. `ITEM:`](#9n-item)
    - [9O. `MONS:`](#9o-mons)
    - [9P. `FHEIGHT`](#9p-fheight)
    - [9Q. `COLOUR:`](#9q-colour)
    - [9R. `FTILE:`](#9r-ftile)
    - [9S. `RTILE:`](#9s-rtile)
    - [9T. `TILE:`](#9t-tile)
    - [9U. `SHUFFLE:`](#9u-shuffle)
    - [9V. `SUBST:`](#9v-subst)
    - [9W. `NSUBST:`](#9w-nsubst)
    - [9X. `CLEAR:`](#9x-clear)
    - [9Y. `KFEAT:`](#9y-kfeat)
    - [9Z. `KMONS:`](#9z-kmons)
    - [9a. `KMASK:`](#9a-kmask)
    - [9b. `KPROP:`](#9b-kprop)
    - [9c. `KITEM:`](#9c-kitem)
    - [9d. `MARKER:`](#9d-marker)
    - [9e. `SUBVAULT:`](#9e-subvault)
  - [Handling long lines](#handling-long-lines)
  - [Assigning multiple glyphs at once](#assigning-multiple-glyphs-at-once)
  - [Transporters](#transporters)

***

## [8. Glyphs](#table-of-contents)

- By default, a glyph that has no mapping is turned into floor (DNGN_FLOOR).

### [8A. Terrain](#table-of-contents)

| Glyph | Name | Tile | Notes |
|:-:|---|---|---|
| `x` | rock wall | DNGN_ROCK_WALL |  |
| `X` | permanent rock wall | DNGN_PERMAROCK_WALL | always undiggable |
| `c` | stone wall | DNGN_STONE_WALL |  |
| `m` | clear rock wall | DNGN_CLEAR_ROCK_WALL |  |
| `n` | clear stone wall | DNGN_CLEAR_STONE_WALL |  |
| `o` | clear permanent rock wall | DNGN_CLEAR_PERMAROCK_WALL | always undiggable |
| `v` | metal wall | DNGN_METAL_WALL | grounds electricity |
| `b` | crystal wall | DNGN_CRYSTAL_WALL | reflects cold and fire |
| `t` | tree | DNGN_TREE | combustible |
| `.` | floor | DNGN_FLOOR |  |
| `+` | closed door | DNGN_CLOSED_DOOR |  |
| `=` | runed door | DNGN_RUNED_DOOR |  |
| `W` | shallow water |  |  |
| `w` | deep water |  | Can be randomly turned into shallow water by the level-builder. Prevent this conversion by using the `no_pool_fixup` TAG. Also, water may automatically receive water creatures! You can avoid this with the `no_monster_gen` TAG or KMASK. |
| `l` | lava |  | Use the `no_monster_gen` TAG or KMASK when appropriate. |

***

### [8B. Features](#table-of-contents)

| Glyph(s) | Brief | Description |
|:-:|---|---|
| `@` | entry point | Must be on outside edge. This point will be connected to the rest of the level with a corridor for both normal vaults and minivaults. If a vault has no entry points defined, random traversable squares on its edge will be chosen and connected, as if they had the `@` glyph. (In the rare event where you don't want this - usually completely enclosed vaults accessible through some other means - use the `no_exits` TAG.) |
| `+ =` |  | Considered entry points when placed on the edge of the map. |
| `} {` | stone stairs (Set 1) | You must be able to reach these from each other. The `{` upstair is also the stair on which the player will enter the dungeon for arrival vaults. |
| `) (` | stone stairs (Set 2) |  |
| `] [` | stone stairs (Set 3) | Minivaults often fail to get this pair if the level isn't very interconnected or if any larger vaults are using any stairs. |
| `> <` | escape hatches | You can leave the level by these but will usually not land on stairs/hatches. |
| `^` | DEPRECATED | ~~A random trap~~ |
| `~` | DEPRECATED | ~~A random trap suitable for the branch and depth the map is being used.~~ |
| `A` | stone arch |  |
| `B` | altar | These are assigned specific types (e.g. of Zin etc) in [dungeon.cc](../../../source/dungeon.cc), in order. |
| `C` | random altar |  |
| `G` | granite statue | Does nothing. You can see through but not walk through. Also, sight-based effects like smiting work past granite statues, as does apportation. |
| `I` | orcish idol | As granite statue, generally used for theme. |
| `T` | water fountain |  |
| `U` | magic fountain |  |
| `V` | dry fountain |  |
| `Y` | blood fountain | Use sparingly. |

***

### [8C. Items](#table-of-contents)

| Glyph(s) | Description |
|:-:|---|
| `$` | gold |
| `%` | normal item |
| `*` | Item ranked by quality level, increasing with absolute depth. The formula is `2 * absdepth + 5`, capped at `50`. |
| `|` | superb quality item: the highest quality level. It's a special class above the `*` glyph, similar to the `good_item` modifier described below, but with a different distribution of item classes: this glyph generates only weapons, armour, jewellery, books, staves, rods, and miscellaneous items. |
| `d-k` | item-array item. See section below on `ITEM:` arrays for more info. |

***

### [8D. Monsters](#table-of-contents)

| Glyph(s) | Description |
|:-:|---|
| `0` | normal `absdepth` monster |
| `9` | `absdepth + 5` depth monster |
| `8` | `(absdepth + 2) * 2` depth monster |
| `1-7` | monster-array monster. See section below on `MONS:` arrays for more information. |

***

## [9. Header Information](#table-of-contents)

NOTE: All declarations apart from `NAME:` are translated to Lua function calls
behind the scenes. See the Lua reference for more information.

Try to respect line lengths of `80` characters. Should some line exceed that
(which is quite possible, especially for `ITEM` and `MONS` lines), you can use
the `\` symbol to break a line. You can break a line anywhere, with the
exception of comma-separated lists, where you cannot start a new line with
a comma. See the end of this section for examples.

### [9A. `NAME:`](#table-of-contents)

- String value.
- Each map must have a unique name. Underscores and digits are ok.

### [9B. `DESC:`](#table-of-contents)

- String value of readable text.
- A map may optionally have a description. If provided, and if the character
  dies in the vault, the map description will be shown along with the place at
  end of game. This is normally used only for the Sprint game type. Map
  descriptions are also written to scores and logfile entries.

### [9C. `ORDER:`](#table-of-contents)

- Integer value.
- Used only for special game types (Sprint, Tutorial). When the user is
  prompted to select a map, the available maps are sorted by the integer value
  (ascending). Maps without an `ORDER:` line follow those that have one. Maps
  with the same value of `ORDER:` are sorted by description (if present) or
  name.

### [9D. `ORIENT:`](#table-of-contents)

- An `ORIENT:` line is not mandatory for vaults; skipping `ORIENT:` makes your
  map a minivault. As a rule of thumb, if you're writing a small random map,
  skip the `ORIENT:` line and make it a minivault.
- String value: `float` or `encompass`|`north`|`northwest`|...|`southeast`
  - `float`: The dungeon builder puts your vault wherever it wants to.
    - This gives a lot of flexibility to the dungeon generator; `float` should
      generally be preferred to other `ORIENT:` settings for new vaults.
  - `<some_direction>`: The vault lies along that side of the map:
    - ```
      xxxxxxxxxx       xxxxxxxxxxxxx
      xORIENT:Nx       xORIENT:NW|..
      x.VAULT..x       x.VAULT...|..
      x--------x       x---------|..
      xrest....x       xrest........
      x...of...x       x.....of.....
      x...levelx       x.......level
      ```

### [9E. `DEPTH:`](#table-of-contents)

```
DEPTH:    For random vaults, branch entry vaults, and minivaults, this
          specifies the range of levels where the vault may be placed
          in the dungeon. E.g.

            DEPTH: D:7-13

          DEPTH: does not force a map to be placed in a particular place; it
          applies only when the dungeon builder is looking for a random vault
          or minivault, so you can control at what depths your vault gets
          placed.

          You can constrain a map by branch:

            DEPTH: Lair:3-6

          (Anywhere between levels 3-6 of the Lair, inclusive.)

            DEPTH: Lair

          (Anywhere in the Lair. Can also be expressed as "DEPTH: Lair:*".)

          You can apply multiple constraints in one DEPTH line,
          comma-separated:

            DEPTH: Lair, !Lair:4-6

          (Anywhere in the Lair, except for Lair:4, Lair:5, or Lair:6.)

            DEPTH: Orc, !Orc:$

          (Anywhere in Orc except for the last level.)

          Maps that do not specify a DEPTH: attribute will inherit their depth
          constraints from the closest preceding default-depth: line. If there
          is no preceding default-depth directive in the .des file, the map will
          have no DEPTH: constraint. Note that maps without a DEPTH: constraint
          cannot be selected as random vaults or minivaults. It can make sense
          to use an empty DEPTH line as in

            DEPTH:

          if these maps are otherwise chosen, e.g. by TAG. See serial_ponds.des
          for an example. When doing this, make sure that there is no
          default-depth line handing out a depth! (This can mean that you are
          better off with a new des file for elaborate vaults.)

          A plain DEPTH: declaration that does not specify a branch applies
          to all branches. A map declared with depth 7-20 could be used in the
          Lair, for instance (Lair is treated as depth 10 for this purpose.)
          In general, you should avoid using such unconstrained DEPTHs.

          If there are multiple DEPTH: declarations, later ones will be added
          to previous ones.
```

### [9F. `CHANCE:`](#table-of-contents)

```
CHANCE:   <roll> [ (<depth-ranges>) ]

          CHANCE allows you to control the probability that your map is used on
          any given level with an absolute roll.

          There are two ways to specify the CHANCE roll:

          CHANCE: 501
          or
          CHANCE: 5.01%

          If specified as a raw number, the chance of selecting the vault is
          <number> in 10000. If specified as a percentage, the chance of
          selecting the vault is <perc> * 100 in 10000.

          CHANCE is useful for random vaults with a DEPTH (or default-depth)
          setting that want to ensure a certain chance of being placed per
          level.

          If a map in the current depth range has a CHANCE, Crawl will roll a
          random number in the range 1-10000, and select the map if the CHANCE
          is >= the rolled random number.

          Dummy vaults (vaults with the "dummy" tag) use CHANCE to specify
          an absolute chance of using the dummy instead of a real map. A CHANCE
          of 80% means the dummy will be used in 80% of vault placement
          attempts.

          The Lua equivalent of CHANCE is:

          : chance(<number>)

          These lines are all equivalent:
          CHANCE: 5%
          CHANCE: 500
          : chance(500)

          A common case when using CHANCE is to assign a CHANCE to a set of
          maps. For instance, if you have a set of portal vault entries, and
          you want one of the set to be used on 5% of all levels, you can do
          this:

          NAME: portal_a
          CHANCE: 5%
          TAGS: chance_portal_group
          ...

          NAME: portal_b
          CHANCE: 5%
          TAGS: chance_portal_group
          ...

          That is, if you have a set of maps that use CHANCE and are tagged
          chance_xxx, then one map of that set will be used when the chance is
          met. You can combine use of CHANCE with WEIGHT (see below) to have
          the same overall chance of selecting from the set while giving
          different likelihoods to maps within the set.

          In some cases you'd like to set a different CHANCE based on where the
          vault is being placed. For instance:

          NAME: ziggurat_portal CHANCE: 5% (Pan), 2% (D:*, Lair:2-4), 3%

          If you specify a depth range in parentheses after a chance spec, that
          spec applies only in that depth range. Each chance's depth range will
          be checked in the order specified, with the exception of the default
          chance (3% in this example) which is always checked last.

          The Lua equivalent of depth-constrained CHANCE:
          CHANCE: 2% (D:*, Lair:2-4), 50% (Geh)
          is as:
          : depth_chance("D:*, Lair:2-4", 200)
          : depth_chance("Geh", 5000)
```

### [9G. `WEIGHT:`](#table-of-contents)

```
WEIGHT:   (number with 10 being default)
          For entry vaults and any other vaults randomly picked from among
          a set, this type of line affects the likelihood of the given vault
          being picked in a given game. The default WEIGHT: is 10. The
          likelihood of a vault getting picked is:
          [vault's WEIGHT: / sum of all WEIGHT:s of vaults of that type]

          As with CHANCE, you may constrain weights to apply only in certain
          depths:

          WEIGHT: 100 (D:2-4), 20 (Crypt, Zot)

          (Note that the default weight is always 10 unless explicitly
          changed)

          The Lua equivalent of a depth-constrained WEIGHT:
          WEIGHT: 100 (D:2-4)
          is
          : depth_weight("D:2-4", 100)
```

### [9H. `PLACE:`](#table-of-contents)

```
PLACE:    Used to specify certain special levels. Existing special levels
          include most branch ends.
          The branches need to use the official abbreviations also used e.g. in
          the overmap (Ctrl-O): D, Temple, Orc, Elf, Lair, Swamp, Shoals,
          Spider, Snake, Slime, Vaults, Blade, Crypt, Forest, Tomb, Hell, Dis,
          Geh, Coc, Tar, Zot.

          PLACE can also be used to specify arbitrary places, like D:3, which
          will force the map (or one of the maps with PLACE: D:3) to be picked
          when D:3 is generated.

          PLACE cannot be used to specify places in the Abyss or Pandemonium.

          PLACE can be used with random vaults and minivaults for testing them.
```

### [9I. `TAGS:`](#table-of-contents)

```
TAGS:     Tags go on a TAGS: line and are space-separated. You can have several
          TAGS: lines, or use \ for very long ones. Valid tags are:
          * Any KPROP name ("no_tele_into", "no_tide", etc.): applies the
             property to every square of the vault. See KPROP: below.
          * "allow_dup": Vaults are normally used only once per game. If you
             have a vault that can be used more than once, use allow_dup to tell
             the dungeon builder that the vault can be reused. This is tracked
             separately for the abyss and the rest of the dungeon.
          * "chance_FOO": Maps can be tagged chance_ with any unique suffix
             to indicate that if the map's CHANCE roll is made, one of the maps
             tagged chance_FOO should be picked.
          * "decor": this tag indicates that the vault is purely decorative, and
             has neither threats nor items. Levels of the main Dungeon deeper
             than D:12 have an 80% chance to place an extra vault with this tag;
             see dungeon_decor in builder/decor.des .
          * "dummy": this tag indicates that the vault is a stub; if the dungeon
             builder picks a dummy vault, it pretends no vault was selected.
             Dummies are used to reduce the probability of other vaults at the
             same depth / place. These vaults should have a CHANCE statement to
             define this probability; see CHANCE: above.
          * "arrival": this tag MUST be there for a vault to be pickable as a
             D:1 arrival vault.
          * "extra": requests that the dungeon builder treat this as
             an extra vault. This forbids the vault from being placed as
             a primary vault if it has an ORIENT: tag; instead it will be
             placed after all other vaults. For minivaults, if the map is
             selected, the builder will attempt to place another minivault
             immediately afterwards. "extra" is good to use for things like
             labyrinth entries that should not affect the chance of other
             minivaults on the level. If you use "extra" and your map is
             tagged "allow_dup", it is a good idea to use a "luniq" tag so
             that the same map does not place more than once on a given level.
          * "generate_awake": Monsters placed (using MONS, KMONS) in this vault
             will be generated awake.
          * "patrolling": Monsters placed (using MONS, KMONS) in this vault
             will be generated with their starting position as patrol point.
             If not otherwise occupied (fighting, seeking) they will patrol
             the area.
          * "no_item_gen": Prevents random item generation in the vault.
             Items explicitly placed by the vault are not affected.
          * "no_exits": In the absence of explicit exits, requests that the
             dungeon builder does not try to pick its own exits from the
             (mini)vault. Usually only used when the vault is completely
             enclosed and accessible through other means.
          * "no_monster_gen": Prevents random monster generation at the time of
             the vault's creation. Highly advised for arrival vaults with a
             player-hostile geography, MUST-HAVE for those with water/lava.
             Can be applied only to particular symbols with KMASK.
          * "no_pool_fixup": prevents water squares next to land from being
             randomly converted from deep water (the default) to shallow.
          * "no_wall_fixup": In Dis, the Vaults and the Crypt a vault's
             rock walls will be changed to be the same as the wall type of
             the rest of the level. If you don't want that to happen then
             use this tag.
          * "no_trap_gen": Prevents random trap generation at the time of the
             vault's creation.
          * "uniq_BAR": (uniq_ with any suffix) specifies that only one of
             the vaults with this tag can be used in a game. In particular,
             late-Dungeon encompass vaults have the tag uniq_d_encompass, so
             that only one will occur per game. This is tracked separately
             for the abyss and the rest of the dungeon.
          * "luniq": specifies that this vault can be used only once on a
             given level. "luniq" is only relevant when used with "allow_dup".
          * "luniq_BAR": (luniq_ with any suffix) specifies that only one
             of the vaults with this tag can be used on any given level.
             "luniq_BAR" is only relevant when used with "allow_dup".
          * "branch_entry" eg. "orc_entry", "lair_entry" etc.
             If chosen, these maps will contain the stairs for that branch.
             If a branch has very few entries, a dummy entry is advisable to
             make sure the player doesn't get bored of the same few entries
             recycled ad nauseam.
             Note: if any TAG argument contains an "entry", the vault will
                   be no longer eligible for random placement. (Currently,
                   this just affects your choice of BAR when using uniq_BAR.)
          * "mnoleg" or the name of some other pandemonium lord. This makes
             the map eligible for said pan lord's lair. See pan.des.
          * "no_rotate":  Normally, the dungeon builder can, at its whim,
             rotate your vault. This flag tells it, "hey, don't do that to my
             vault!"
          * "no_hmirror": Like no_rotate, but for horizontal mirroring.
          * "no_vmirror": Like no_rotate, but for vertical mirroring.
          * "overwritable": Lets the dungeon builder overwrite this vault with
             other ones. Don't use this casually.
          * "overwrite_floor_cell": Tells the dungeon builder that this vault
             intends to overwrite a single floor cell, possibly inside another
             vault, even if that vault does not have the "overwritable" tag.
             This tag can only be applied to 1x1 vaults. Don't use it casually.
          * "layout": Makes the vault eligible for use as a level layout. Do
             not use this unless you know what you are doing.
          * "layout_foo": Indicates what sort of level layouts this vault is
             compatible with, for vaults that don't fit in with all layouts;
             the absence of this type of tags means it can go with any
             layout. Multiple layout_foo tags can be used if it can be used
             with multiple layouts. Current values for "foo" are:
             * corridors: Mostly 1-cell-wide corridors
             * rooms: Corridors connecting rooms
             * passages: Mostly multi-cell corridors
             * narrow_caves: Corridor-like caves
             * open_caves: Open caves
             * city: A large open room with "building" rooms in it
             * open: Layout is mostly open but not cavelike
             * divisions: Just ajoining rooms
             * vaults: Used in the Vaults branch (no normal vault placement)
             * shoals: Used in the Shoals branch
             * swamp: Used in the Swamp branch
             * forest: Was used in the now-defunct Forest branch
             For more details on the layout types and the layouts that place
             there, see Layout Types on the devwiki at
             crawl.develz.org/wiki/doku.php?id=dcss:brainstorm:dungeon:layout_types
          * "no_species_xx": Disables the vault for a given player species
             (two-letter abbreviation). Note that the current design rules
             strictly disallow varying the map generation based on the
             character -- this tag is only for acquirement-like effects,
             sprint, or tutorial.
          * "ruin": requests the level builder to damage the vault by
             removing walls near the edges, making it look like a ruin.
             You can request that a vault be ruined only in a particular
             branch using "ruin_<branch>". For instance: "ruin_lair".
          * "no_dump": Don't dump out this vault's name in the list of
             vaults generated during the game. Use this if the vault
             is predictable (like the Vaults:5 and Slime:6 vaults) or
             are for weird internal uses (like the shoalhut vaults).
          * "unrand": Don't pick this vault randomly by DEPTH. Can still be
             picked by tag or PLACE. Almost exclusively used by layouts and
             subvaults.
          * "transparent": Marks the vault as potentially passable for the
             purposes of level connectivity. By default, vaults are considered
             non-passable regardless of their contents. With this tag, the
             actual terrain of the vault affects its passability as seen by the
             dungeon builder. A disconnected region inside a transparent vault
             will cause a veto of the level (but see the "opaque" KMASK below).
```

### [9J. `LFLOORCOL:`](#table-of-contents)

```
LFLOORCOL: blue
          LFLOORCOL: allows you to set the floor colour for the level the
          vault appears in. Should only be used for bazaars and other
          portal vaults.
```

### [9K. `LROCKCOL:`](#table-of-contents)

```
LROCKCOL: yellow
          LROCKCOL: allows you to set the colour of rock walls for the level
          the vault appears in. Should only be used for bazaars and other
          portal vaults.
```

### [9L. `LFLOORTILE:`](#table-of-contents)

```
LFLOORTILE: (tile name string, e.g. "floor_tomb")
          Like LFLOORCOL, this overrides the default floor tiles used for
          this level. If the tile specified has variations, those will be
          used automatically.
```

### [9M. `LROCKTILE:`](#table-of-contents)

```
LROCKTILE: (tile name string, e.g. "wall_hive")
          Same as LFLOORTILE, but for rock walls.
```

### [9N. `ITEM:`](#table-of-contents)

```
ITEM:     (list of items, separated by comma)
          These are used to help place specified items at specific places
          within a vault. They create an array with up to 8 positions. What's
          in the first position in the array will be used when the dungeon
          builder sees a "d" in the vault definition, the second will be used
          for "e"s, etc. Positions are comma-separated; several ITEM: lines
          are possible as well. The following defines letters "d" - "g":
            ITEM: stone, ring mail, meat ration, ring of hunger

          Positions can contain multiple possibilities, one of which the
          builder will choose randomly. Separate such multiple possibilities
          using a slash. Note that "nothing" (without the quotes) is a valid
          possibility. The random choice is done for each individual occurrence
          of the letter. You can also give possibilities a "weight," which
          affects their chance of being picked. The default weight is 10. You
          can abbreviate "weight:30" by "w:30". The chance to pick a
          possibility is
          [possibility's weight: / sum of all weight:s in that array position]

          For example, the following line makes letter "d" into a bread ration
          with 50% chance, or apple or orange with 25% chance each:

            ITEM: bread ration / w:5 apple / w:5 orange

          Modifiers:
          * "q:N" sets the item quantity to N (if N > 0). Does nothing
             if the item is not stackable.
          * "charges:N" sets the number of charges for wands.
          * "plus:N" and "plus2:N" set the item pluses for weapons, armour,
            jewellery (such as rings of intelligence or slaying), and
            throwing nets.
          * "no_uniq" prevents the item from being turned into an artefact,
            unless cancelled by an "allow_uniq" modifier.
          * "good_item" makes the builder try to make the item a good one
            (acquirement quality). This is independent of the level's depth, in
            contrast to placing items with the "*" glyph, which just adds a
            bonus to depth for the item generation. The "|" item glyph uses
            this quality level (but with a different distribution of item
            classes, see above).
          * "acquire" requests the use of the acquirement code
            itself, ensuring that the player gets wearable armour, etc. You can
            also use acquire:<god> to request that the acquired item be
            treated as a god gift. Examples: "acquire any", "acquire armour",
            "acquire:sif_muna book", "acquire:trog weapon". Use of this outside
            of specialized portals as part of the builder is *deprecated*,
            because conditioning level generation on player properties
            interferes with seeding.
          * "level:N" sets the object's item level (can't be used with
            "good_item"). If set to -2 then the object's item level will
            be the same as a "*" symbol item (five plus twice the
            vault's level number).
          * "damaged" sets the item plusses to -1..-4. This modifier (and
            the corresponding effect of the "cursed" modifier) does not
            affect jewellery.
          * "cursed" gets a curse plus plusses as in "damaged"; but the latter
            may be overridden with "mundane", "good_item", "level:N", etc.
          * "not_cursed" forces an item to have any curse placed on it to be
            removed.
          * "any" by itself gives a random choice; you can combine "any" with
            "good_item". A lone "%" may be used as an alias for "any".
          * "useful" tries to select an item usable by the player, but may
            give an useless one if it has trouble finding one
          * "star_item" by itself makes an item equivalent to the "*" glyph.
            A lone "*" may be used as an alias for "star_item".
          * "superb_item" by itself makes an item equivalent to the "|" glyph.
            A lone "|" may be used as an alias for "superb_item".
          * "any book", "any misc" etc. gives a random item of that class.
            Valid item class names are: gold, weapon, missile, armour, wand,
            food, scroll, jewellery, potion, book, magical staff, orb, misc,
            carrion.
            All of these are usable in map definitions, apart from "orb" and
            "carrion".
          * "ego:ego_name", where "ego_name" is something like "running" or
            "fire_resistance", and so on; "none" can be used to prevent the
            item from getting an ego. The item must be fully specified, so
            trying "any weapon ego:vorpal" or "any armour ego:positive_energy"
            will result in an error. Trying to give an ego to something which
            can't accept an ego will also result in an error. The full lists
            are in the str_to_ego() function in mapdef.cc.
          * "randart" will force a randart. Most of the above modifiers
            will be ignored, except for "ego" (for weapons only).
          * "mundane" acts as a shortcut for "ego:none" and forces the plusses
             to be +0.
          * "ident:" will make the item pre-identified. You need to specify
            a "|"-separated list of what is to be known:
            * "curse"
            * "type"
            * "pluses"
            * "properties"
            * "all"
          * "unobtainable" hints that the item is supposed to never fall into
            the player's hands. It doesn't actually keep it from doing so,
            just tells that to acquirement and (TODO) troves.
          * "mimic:N" gives the item one chance in N of being turned into a
            mimic. The ":N" can also be omitted for a guaranteed mimic.
          * "no_pickup" prevents monsters from picking up the item, for vaults
            intending to have an impressive display of loot (although in most
            cases monsters should be allowed to pick up and use loot against
            the player).
          * "tile:" and "wtile:" will set the item's inventory/ground and
            worn (player/monster doll) tiles. Generally you'd want to set
            both to ensure they match.

          WARNING: While checks are done to make sure that an armour ego
          isn't given to a weapon, a weapon ego to a missile, and so on, and
          also to make sure that egos are only given to armours, weapons and
          missiles, no other checking is done. Thus it is possible to create
          a demonic weapon of holy wrath or a helmet of running.

          Corpses
          -------
          You can create corpses, skeletons and chunks using
          "<monster> corpse", "<monster> skeleton", or "<monster> chunk".

          For instance: "rat corpse", "18-headed hydra skeleton",
          "griffon chunk".

          Corpses, skeletons and chunks are by default created with maximum
          freshness (210). They may still rot away before the player finds your
          vault. To prevent corpses from decaying, you can define them using a
          "never_decay" property as:

          ITEM: never_decay griffon corpse

          However, direct use of "never_decay" is not recommended,
          since such items will not behave as the player expects.
          Instead, you can set corpses to stay fresh until seen by the
          player with a delayed_decay marker. Instead of:

             KITEM: e = griffon corpse / griffon skeleton

          you'd use:
             : dgn.delayed_decay(_G, "e","griffon corpse / griffon skeleton")

          (Note the leading ":" - this is a Lua call).

          delayed_decay generates the corpse with the "never_decay"
          item property and creates a trigger that fires when the
          player enters LOS of the square in question. When triggered,
          it clears the "never_decay" property, allowing the item to
          start decaying normally. Note that this does not work with
          "/ nothing" alternatives (or other non-chunk, non-corpse items);
          for those cases, use SUBST with a second glyph and KITEM.

          If you need to put additional non-corpse, non-chunk items at
          the same location, use delayed_decay_extra:
             : dgn.delayed_decay_extra(_G, "e", "human corpse", "mace, shield")

          IMPORTANT: the delayed_decay line should always come after any
          shuffles or substitutions of the relevant glyphs. This is because
          it is equivalent to a KITEM plus a MARKER; the former applies to
          the glyph after all substitutions, while the latter considers only
          those substitutions that precede the delayed_decay call.

          Unrands
          -------------------
          You can specify fixed artefacts, e.g. the scythe of curses, by
          naming them: "KITEM: e = scythe of curses". If the desired unrand's
          names has something between double quotes, use that: e.g, bloodbane.

          If this unrand has already been placed, a randart of the same type
          will be created instead. Staff unrands, since they have no
          corresponding type that can be transformed into a randart, are
          replaced by an appropriate magical staff. (E.g. a staff of poison.)
          You should not use `you.unrands` to check whether an unrand has been
          seen in normal levelgen scenarios, as it will impact seeding. Some
          details about default fallbacks can be specified in art-data.txt.

          Randart spell books
          -------------------
          You can specify random artefact spell books using:

          * "any fixed theme book" will generate a book with a fixed theme
            (set of spell schools).
          * "any fixed level book" will generate a book with a fixed set of
            spells around the same level.

          You can further specify artefact spell books using "randbook" and any
          combination of the following tags:

          * "numspells:number" maximum number of spells to include in the book.
            A book may contain at most 8 spells.
          * "owner:name" will be used to make the title include the
            apostrophised owner (or author) of the book if provided. For
            example, "owner:Roxanne" may create "Roxanne's Treatise on
            Mountains". You can use the keyword "player" (i.e. "owner:player")
            to use the player's name instead.

          In addition, themed books allow the use of the following tags:

          * "disc:spell_school", the first spell school that should be included
            in the book. For example, "disc:earth" or "disc:ice".
          * "disc2:spell_school" an optional second spell school that can be
            included in the book. Note: specifying two spell schools doesn't
            mean that they will both definitely be included, just that they
            might be.
          * "slevels:max_levels" the total, combined level of spells to include
            in the book. "slevels:6" will use three level two spells, two level
            three spells, a level two and a level four spell, and so on.
          * "spells:spell_1&spell_2" a list of spells to include in the book.
            Spells must be separated by "&" without spaces. Within a spell name,
            all of "_" will be replaced with " " and will be parsed as such.
            A book may contain at most 8 spells.
          * "title:title" will define the title of the book.

          NOTE: You can place multiple items on the same square by using the
          KITEM directive. See that section for more information.

          Decks
          -----
          You can specify decks with like this:
          "deck", "ornate deck", "deck of war", "legendary deck of wonders"

          Note the following synonyms:
          common = plain, rare = ornate
```

### [9O. `MONS:`](#table-of-contents)

```
MONS:     (list of monsters)
          These are used to help place specific monsters at specific places
          in a vault. They create an array with up to 7 positions. What's in
          the first position in the array will be used when the dungeon
          builder sees a "1" in the vault definition, the second for "2,"
          etc. Note that if, for example, you place a 3 on the map, but your
          MONS: line has no third position, the 3 will be filled with
          RANDOM_MONSTER. Also note that for arrival vaults (D:1), all
          monsters in sight of the hero are removed. This does not hold for
          plants. You can use weights as for ITEM: lines.

          A hydra can be given a specific number of heads by calling it
          an "n-headed hydra" (with a maximum of 20 heads):
              MONS: four-headed hydra

          A mutant beast can be customized by prefacing it with a maturity level
          and/or hyphen-separated set of traits, as follows:
              MONS: mature shock-weird mutant beast

          A slime creature's size can be set to other than normal using
          the prefixes "large", "very large", "enormous" or "titanic":
              MONS: very large slime creature

          Individual monsters may be prefixed with the "generate_awake"
          (without the quotes). Use this sparingly:
              MONS: generate_awake goliath beetle

          Individual monsters may be prefixed with the "patrolling"
          (without the quotes). Use this sparingly:
              MONS: patrolling guardian serpent

          Monsters can also be given colours that override their default
          colour. Use this *very* sparingly:
              MONS: col:darkgrey fungus

          The colour "any" can be given, in which case a random colour
          will be chosen when the monster is placed.

          You can override the displayed monster tile using the "tile:"
          specifier as follows:
              MONS: rat tile:mons_giant_bat

          In tiles version, this would create a monster that uses the
          "mons_giant_bat" tile, but is otherwise identical to a rat.
          Obviously, this substitution of one monster onto another should
          never be used, but it can be useful for customised vault monsters
          if an alternate tile exists. In ASCII mode, this will do nothing.

          You can set the monster's god using the "god:" specifier as
          follows:
              MONS: orc god:the_shining_one

          If the monster is to be a gift of the specified god, this should
          be suffixed with "god_gift" (without the quotes):
              MONS: orc god:the_shining_one god_gift

          Note that the monster will not be considered a god gift unless
          god_gift is explicitly set.

          You can set the monster's faction by specifying "att:" one of:

          * att:hostile -- the default
          * att:friendly -- tame, will follow you
          * att:neutral -- hostile to both you and att:hostile monsters
          * att:good_neutral -- hostile to att:hostile
          * att:fellow_slime -- tame, won't follow you

          Note that the glyphs 8, 9, 0 (without MONS) also place monsters:
             0 - normal monster (this is equivalent to MONS: random)
             9 - +5 depth monster
             8 - (+2) * 2 depth monster.

          If you want to place a random monster suitable for the level
          the map is generated on, you can use
              MONS: random

          If you want to place a random monster suitable for some other
          place, you can use a place: tag in the monster spec:
              MONS: place:Abyss
          or
              MONS: place:Slime:6

          Using place: with MONS implies that you want a random monster.
          You can also request zombies from random monsters suitable
          for some other depth as:
              MONS: place:Elf:3 zombie
          or
              MONS: place:Zot:5 simulacrum
          or
              MONS: place:Vaults:5 spectre

          The available modifiers are "zombie", "skeleton",
          "simulacrum", "spectre" and "chimera".

          If a monster is a member of a band, you can request that it
          be eligible for band members by adding the keyword "band" to
          the name. For instance:
              MONS: orc warlord band

          Specifying "band" doesn't force bands to be placed - it
          requests that the game use the normal chances of creating a
          band. If you use "band", leave some empty space around the
          monster for its band members to be placed.

          A monster can be given specific items by following the monster
          name with a semi-colon and then with an item list as described
          in ITEM:, but with slashes replaced with pipes and commas replaced
          with periods. For example:
              MONS: orc ; sabre | quick blade . chain mail | plate armour

          will generate an orc wielding either a sabre or a quick blade
          and wearing either chain mail or plate armour. Randarts and
          ego items are only generated if they are explicitly requested.
          Note that any items that the monster was originally generated
          with will be removed and destroyed. This can be used to force
          a monster to have no items whatsoever:
              MONS: orc; nothing

          Limitations: If an item in the item list has alternatives,
          there's no way to force all monsters derived from that monster
          spec to choose the same alternative. If a monster is given
          a random launcher, there is no way to force the ammo type to
          match the launcher type.

          You can specify that a monster will always generate a corpse by
          using the tag "always_corpse", and that it will never generate
          a corpse by using "never_corpse". This should only be used in
          vaults where it is absolutely necessary, tutorial maps, etc.

          Overriding Monster Names:
          -------------------------

          Individual monsters can be given names as follows:
              MONS: kobold name:Durwent

          This will cause the monster to appear as "Durwent the kobold".
          Spaces can be placed in the name by substituting them with the _
          symbol. It is worth noting that "the <race>" will be appended
          to all names, which should be considered when coming up with them.

          The name tag is also useable in KMONS. It should be used carefully
          to avoid having multiple monsters named the same (ie, as above,
          and then using the glyph "1" multiple times will result in multiple
          "Durwent the Kobold"s).

          There are three different modifiers that by used on a name:
          name_adjective, name_suffix and name_replace. name_adjective
          makes the name act as an adjective. For example:
              MONS: kobold name:ugly name_adjective

          Will cause "An ugly kobold", "The ugly kobold hits you",
          and so on.

          name_suffix does the same, but after the monster's base name:
              MONS: kobold name:wearing_mittens name_suffix

          Will give "A kobold wearing mittens", "The kobold wearing
          mittens hits you", and so on.

          name_replace causes the base name to be replaced by given
          name, as if the monster was a unique:
              MONS: kobold name:Durwent name_replace

          Will result in "Durwent" rather than "Durwent the Kobold". The
          corpse will still be a "kobold corpse of Durwent".

          In combination with name_replace or name_species, there are two
          further tags that can be used when renaming monsters, but not
          giving them an actual "name": name_descriptor, and name_definite.

          For example:
              MONS: kobold name:goblin name_replace

          Will result in "goblin hits you". However, adding name_descriptor
          from the above flags will result in "The goblin hits you" and in the
          description of the monster, "A goblin".
              MONS: kobold name:goblin name_replace name_descriptor

          The name_definite flag ensures that it is never referred to as "a" or
          "an", but that the definite object is always used. Therefore, you will
          see "The goblin hits you", as per above, but also "The goblin" in its
          description. Setting name_definite will automatically set the flag
          name_descriptor, therefore meaning that:
              MONS: kobold name:goblin name_replace name_definite

          Is exactly the same as:
              MONS: kobold name:goblin name_replace name_descriptor name_definite

          name_species uses the name for corpses as-is, without prefixing it
          with "kobold corpse of X" for name_replace. It also avoids the usual
          name tag that displays above unique and renamed monsters in local
          tiles.

          name_zombie can be used to redefine already zombified monsters
          (including skeletons, simulacra and spectrals).

          Finally, name_nocorpse will cause the name to be completely ignored
          for corpses. For example:
              MONS: wizard name:sad name_adjective name_nocorpse
          will result in "a sad wizard" that leaves "a wizard corpse".

          For instances where space in definitions is limited, you can use
          abbreviated forms of these tags:

              name_suffix     -> n_suf
              name_adjective  -> n_adj
              name_replace    -> n_rpl
              name_species    -> n_spe
              name_descriptor -> n_des
              name_definite   -> n_the
              name_zombie     -> n_zom
              name_nocorpse   -> n_noc

          Monster names should be used very sparingly.

          Every renamed monster needs a description as well (place it in
          dat/descript/monsters.txt). If you want to have multiple monsters
          share descriptions and speech, you can do it with "dbname:".

          Overriding Monster Stats:
          -------------------------

          Further monster customisation can be made by using "hd" and "hp".
          These two tags allow you to completely overwrite the original hit dice
          and hit points of a monster:
              MONS: kobold hd:20

          Creates a kobold with a hit dice of 20. As its hp is randomised, based
          on its hit dice, this will also be re-rolled. Monsters with a specific
          hit point value will not have this value change.

          You can also have a specific value for hit points:
              MONS: kobold hp:20

          Creates a kobold with 20 hit points. This is also useful for monsters
          (such as statues) which come with non-randomised HP values.

          Monsters can be marked as summoned by using "dur" and "sum" tags. The
          "dur" tag accepts an integer between 1 and 6 inclusive. The "sum" tag
          accepts the name of a spell (parsed as per the spells tag, described
          below) or any of "clone" (Rakshasa), "animate" (from animate dead),
          "chaos" (made from pure chaos), "miscast" (summoned from by spell
          miscast effect), "zot" (summoned by a Zot trap), "wrath" (summoned by
          a god in an act of retribution), "aid" (summoned by a god in order to
          give aid).

          Of the spells, "shadow_creatures" has the most significant effect, in
          that monsters will dissipate into the shadows rather than disappear in
          a puff of smoke. Using non-summoning spells will also have no effect.

          Tagging a monster with "seen" will override the system and force that
          player to be marked as already viewed; this means that it won't
          generate messages such as "XYZ comes into view".

          Overriding Monster Spells:
          --------------------------
          Monster spell sets can be overridden with a spells: tag,
          used as follows:

              MONS: goblin spells:throw_flame.50.wizard
              MONS: ancient lich spells:symbol_of_torment.26.wizard;\
                                        glaciate.51.wizard

          (a list of spell slots, consisting of a spell name with
          spaces replaced with underscores, a frequency of casting and
          set of spell slot flags specified afterwards with .,
          with slots separated by ";" with no spaces around the ";" or
          after the spells: prefix)

          Spell names must exactly match the names in spl-data.h, with
          spaces replaced by underscores. Spell frequencies are an
          (x in 200) chance that that spell will be cast. Spell flags
          include:
          - "natural", "magical", "demonic", "wizard", or "priest" -
            the manner in which this spell is being cast. Wizards and
            priests can be silenced and will trigger appropriate conducts
            (Trog will appreciate killing wizards, Beogh will appreciate
            killing priests). Magical, demonic, and wizard spells
            are subject to anti-magic effects. Natural spells do not
            generate noise.
          - "emergency" - the monster will only cast the spell when low
            on health.
          - "breath" - the spell is a breath weapon, and using it
            triggers a breath timeout during which the spell cannot be
            cast again.
          - "no_silent" - the spell cannot be used while silent, even if
            it is an ability type normally not subject to silence.
          - "instant" - the spell does not expend the monster's energy;
            they may take another action on the same turn.
          - "noisy" - forces the spell to make noise even if it is a
            natural ability.

          You may use "none" specify that a slot should be left empty.
          You can force a spell-less monster with:
              MONS: orc wizard spells:none

          Setting enchantments:
          ---------------------
          You may give a monster any number of enchantments. It may
          start hasted, blind, have permanent RMsl, etc. The syntax is
          "ench:<name>:<degree>:<duration>" or "perm_ench:<name>:<degree>".
          The <degree> and <duration> fields may be omitted. Note that
          the enchantment will start the moment the monster is created and
          thus most likely time out before the player has a chance to
          notice the monster -- non-permanent ones make sense mostly only
          if created from a lua trigger.

          MONS: orc perm_ench:blind perm_ench:mad
          MONS: sheep ench:sticky_flame
          MONS: stone giant dur:1 ench:berserk
```

### [9P. `FHEIGHT`](#table-of-contents)

```
FHEIGHT:  xyz = 40

          FHEIGHT sets the height in the level's heightmap for any
          specified features. If the level does not already have a heightmap,
          a heightmap will be attached to it when the dungeon builder
          sees FHEIGHT used.

          Heightmaps are currently only useful in the Shoals, as a means of
          influencing how the tide interacts with your vault. The Shoals
          heightmap uses these heights when the tide's height is 0, i.e.
          at neutral tide:
               >= 0     Floor
               >= -14   Shallow water
               <= -15   Deep water

          In general, you do not need to use explicit FHEIGHT lines in
          your vaults. The Shoals dungeon builder will automatically
          assign suitable heights to features in vaults. FHEIGHT is
          primarily useful to override the default heights of
          features. If you use FHEIGHT to set nonstandard heights for
          features such as deep water (if you want deep water at
          heights > 0, for instance), you must also use KPROP to set
          the no_tide flag on that square, or the Shoals level builder
          will undo your height changes.
```

### [9Q. `COLOUR:`](#table-of-contents)

```
COLOUR:   . = green / blue:5 / red / none
          COLOUR: allows you to attach explicit colours to any feature.
          Explicit colours will override the default colour for that
          feature. The example shown above colours all . (floor) in the
          map green, blue, red, or unchanged (use the default colour).

          You can use : to specify that all glyphs get the same colour:
          COLOUR: x : red / blue
          will colour all rock walls in the map red, or all rock
          walls blue.

          COLOUR: should be used very sparingly, and only for features
          where it won't cause confusion (i.e.: never re-colour features
          like lava or traps unless you really know what you do!)

          If you apply COLOUR to a glyph and then apply a SUBST,
          the COLOUR will transfer to the resulting transformed glyph.

          There are two types of basic colours available: base and
          "elemental". Available base colours are as follows: blue, green,
          cyan, red, magenta, brown, lightgrey, darkgrey, lightblue,
          lightgreen, lightcyan, lightred, lightmagenta, yellow and white.

          Elemental colours are: fire, ice, earth, electricity, air, poison,
          water, magic, mutagenic, warp, enchant, heal, holy, dark, death,
          necro, unholy, vehumet, beogh, crystal, blood, smoke, slime, jewel,
          elven, dwarven, orcish, gila, kraken, floor, rock, stone, mist,
          shimmer_blue, decay, silver, gold, iron, bone, elven_brick, waves,
          tree, random. See colour.h for comments on each.

          Elemental colours can be based on both random numbers (for things
          that repeatedly change colour, such as Xom altars which use
          "random") and on the map location where they are placed (for
          example, trees use "tree"), as well as any other part of the global
          state that is accessible (for example, shallow water in the Shoals
          uses "waves", which is based on the current turn count and the
          height map of the map location). The majority of predefined
          elemental colours are based on random numbers, but you can easily
          define new colours to suit your maps. In the global prelude, define
          new colours like this:

          {{
              colour.add_colour("checkerboard", function(rand, x, y)
                  if (x + y) % 2 == 0 then
                      return "red"
                  else
                      return "white"
                  end
              end)
          }}

          and then in your map definition, you can use "checkerboard" as a
          valid colour name. In the colour definition function, "rand" is a
          random number between 0 and 119 (chosen randomly each time this
          function is called), and "x" and "y" are the coordinates of the tile
          that this is supposed to be colouring.

          Even more so than base colours, elemental colours should be used
          very, very, very sparingly.

          Colours apply automatically to floor and rock wall tiles, although
          not all branches have coloured variations for their tile set.
```

### [9R. `FTILE:`](#table-of-contents)

```
FTILE:    . = floor_grass:20 / floor_dirt / none
          Similar to COLOUR, FTILE allows you to attach explicit floor
          tiles to any glyph. In non-tiles builds, this does nothing.
          If the tile specified has variations, those will be used
          automatically. Only tiles from the dungeon image can be used.

          This will not (necessarily) replace the feature tile itself,
          only the floor. If you set the FTILE on a fountain glyph,
          then the fountain will still appear normally, but the floor
          underneath it will be the tile that was specified.

          If a feature that normally covers the floor (e.g. rock walls) is
          destroyed, this floor tile will be used in place of the normal
          floor. Thus, it can be useful even for non-floor features.

          Like COLOUR, this should be used sparingly.

          If COLOUR is also specified and there is a coloured variation
          of this tile, then it will be used.
```

### [9S. `RTILE:`](#table-of-contents)

```
RTILE:    x = wall_hive:15 / wall_lair / none
          Identical to FTILE, but for rock walls. Not useful for anything
          but the rock wall feature.
```

### [9T. `TILE:`](#table-of-contents)

```
TILE:     x = wall_flesh
          Identical to FTILE and RTILE in syntax, but closer to COLOUR in
          functionality. Instead of replacing the floor or relevant rock tiles,
          this can be used to replace the tile used for any specific feature.

          This can be used in combination with FTILE and RTILE to change the
          appearance of features. It can only be used with previously specified
          tiles, however.

          Like COLOUR and FTILE, this should be used sparingly and to good
          effect.

          If COLOUR is also specified and there is a coloured variation
          of this tile, then it will be used.

          To override doors, use the specific tile set in combination with the
          "no_random" specifier. Example:
              + = no_random dngn_fleshy_orifice
```

### [9U. `SHUFFLE:`](#table-of-contents)

```
SHUFFLE:  def, 12/3?
          This allows you to randomly permute glyphs on the map. There are
          two ways:

          SHUFFLE: 123w     (i.e. list of glyphs, NOT slash-separated)
          could, for example, swap all occurrences of "1" with "2", as well as
          swapping all "3" with "w" (or any other of the 24 possibilities).

          SHUFFLE: 12/3w    (i.e. list of slash-separated blocks of same size)
          will either do nothing or swap all "1" with "3" and then also swap
          "2" with "w" everywhere.

          Several SHUFFLE: lines can be used, and mixed with SUBST:, and the
          shuffles and substitutions will be applied in order. You can also
          put multiple SHUFFLEs on one line, comma-separated. Shuffles cannot
          use , or /. All spaces are stripped before shuffling.
```

### [9V. `SUBST:`](#table-of-contents)

```
SUBST:    ?=xc, !:bv, 1=2 1:100
          The SUBST: directive allows you to specify a placeholder symbol
          that is replaced with a random glyph from a set. For instance:

          SUBST: ? = TUV
          replaces occurrences of ? with one of TUV. Since whitespaces are
          irrelevant, this is the same as
          SUBST: ? = T U V

          SUBST: ? = T:20 U V
          makes T twice as likely to be used as U or V (the default weight
          is 10). Note that there has to be at least one space before and
          after T:20 and that whitespace in T:20 is not permitted.

          SUBST: ? : TUV
          replaces occurrences of ? with one of TUV, and guarantees that all
          occurrences of ? will get the same replacement symbol.

          The placeholder and replacement symbols can be any non-space,
          printable character, including : and =, apart from commas. For
          example, the following is valid:
          SUBST: = = +=:123def"

          SUBST: lines can safely replace symbols with themselves, as in:
          SUBST: w = wW

          Multiple SUBST: lines can be used, and mixed with SHUFFLE:, and
          will be applied in order. Multiple substitutions can be performed
          on one line, using commas.
```

### [9W. `NSUBST:`](#table-of-contents)

```
NSUBST:   ? = 3:w / *:l

          NSUBST is similar to SUBST, replacing placeholders with
          replacement values. Unlike SUBST, however, it allows you to
          replace different instances of the same placeholder with
          completely different substitutions. For instance:

          ? = 3:w / *:l

          replaces three occurrences (randomly selected) of ? with w
          and all others with l.

          You can use complex SUBST specifications:

          ? = 3= w .:15 A / *: =+CF

          This is equivalent to SUBST: ? = w .:15 A for three ? and
          SUBST: ? : =+CF for all the others.

          You can use any number of NSUBST specifiers:

          ? = wW / l / A / 1234

          Each specifier is preceded by the number of symbols to apply
          it to, followed by : or = (: to use one substitution for all
          occurrences, = to randomly pick for each occurrence). If you
          omit the initial N: or N=, then 1= is assumed, except for the
          last spec where *= is assumed.
          The parser can get confused with NSUBST specifications like
          wW / nc=. If you use replacement symbols from * or = (perhaps
          also for / and numbers), it is safer to spell out the N:
          preceding the replacement symbols.
```

### [9X. `CLEAR:`](#table-of-contents)

```
CLEAR:    Clear is a special kind of SUBST that only swaps glyphs to " ",
          i.e. a blank space. This makes the resulting areas not part of
          the map, so they won't overwrite the underlying level. The
          syntax is simply:

          CLEAR: xyz

          This will erase the glyphs x, y and z from the map by turning
          them into spaces.
```

### [9Y. `KFEAT:`](#table-of-contents)

```
KFEAT:    G = C / needle trap / antique armour shop / altar_zin
          The KFEAT: directive allows you to specify a placeholder symbol
          that is replaced with another symbol, named feature, trap, or
          shop. For example, the line above will replace occurrences of G
          with C (random altar), a needle trap, an antique armour shop, or
          an altar of Zin. Different instances of G may receive different
          replacements. To force a single replacement for all G,  use:

          KFEAT: G : C / needle trap / antique armour shop

          You'll notice that "G" is the symbol of a granite statue. Kxxx
          directives allow you to assign arbitrary definitions to any symbol.

          KFEAT features are specified as a feature name (see feature-data.h
          in the source/ directory for a full list of feature names). As
          another example, you can place a portal to the Abyss as:

          KFEAT: A = enter_abyss

          If you want no feature as an option in a KFEAT line, use "." or
          "floor". If you do not want to specify the type of shop, use "any
          shop" or "random shop". If you wish to specify more complex options
          for shops, see the section on shop definitions at the end of this
          document.

          You can also place feature mimics using the same syntax as item
          mimics. For example this altar has a 1 in 10 chance of being
          turned into a mimic:

          KFEAT: C = C mimic:10

          Some features (specifically shops and portal vault entries) may
          be randomly turned into mimics by the dungeon builder. You can
          prevent this with "no_mimic":

          KFEAT: S = any shop no_mimic

          The placeholder used by KFEAT can be shared by KITEM and KMONS;
          see below. If the placeholder is shared, all defined Kxxxx
          operations for the placeholder are performed. Also, all Kxxx
          lines accept weights as for MONS or ITEM.

          KFEAT overrides the normal meaning of the glyph: In the absence
          of further declarations,
            KFEAT: 1 = shallow_water
          will result in 1 producing shallow water with no monster.

          KFEAT applies to cells that have the specified glyph after applying
          all shuffles and substitutions.

          Shop definitions
          ----------------

          It's possible to customise shops further than simply specifying the
          type of shop to place. There are a number of options, which are
          enumerated below:

            use_all:    If true, and items have been specified, all items
                        specified will be placed in the shop, without using
                        random selection to determine a number of items from
                        the list.
            name:       If provided, this is apostrophised and becomes the
                        shop-keeper's name. For example, name:Ploog would
                        result in "Ploog's <X shop>".
            type:       If provided, this is used as the "type" name for the
                        shop. For example, type:Wand would result in "X's Wand
                        shop". Please note: this is *not* the type of shop,
                        simply the name. Setting this will not change the
                        content of the shop. You will still need to specify the
                        type in the definition, i.e., "antique armour shop".
            suffix:     If provided, this is used instead of "Emporium",
                        "Shop", etc, in the shop name. For example,
                        suffix:Bazaar results in "X's x Bazaar".
            count:      If specified, this restricts the number of items placed
                        in the shop to this number. For example, "any shop
                        count:1" results in a single shop with a single item in
                        it.
            greed:      If specified, this increases the cost of items for sale
                        in the shop. Someone should fill the algorithm here!

          Shop items
          ----------

          It's possible to also specify a list of items that should be placed
          in a shop. This syntax specifies a number of items separated with |,
          which is further separated from the individual shop specification
          using the ; symbol. Individual shop items are parsed as per standard
          item definitions, identical to those used for monster items, and
          so-on.

          Examples
          --------

          KFEAT: a = any shop name:Ploog type:Wand suffix:Emporium count:3
                       use_all greed:10 ; any wand | any wand | any wand

          In theory, this will create "Ploog's Wand Emporium", which has
          exactly three items, each of which is a randomly chosen wand.

          Note: Transporters are placed in vaults via lua markers, and
          shouldn't need placement via KFEAT. See the Transporters section
          below.
```

### [9Z. `KMONS:`](#table-of-contents)

```
KMONS:    ? = orc priest / w:3 deep elf priest

          KMONS: allows you to specify a placeholder symbol that indicates
          the position of a monster (or monsters).
          Using KMONS: allows you to exceed the 7 slot limit for monsters.
          It is also useful if you want to place a monster on a non-floor
          square (used in association with a KFEAT:). For example,
            KFEAT: Z = W
            KMONS: Z = rat
          places a rat on a shallow water square for all occurrences of Z.

          KMONS: also allows you to specify alternative monsters if the
          primary monster you want to place is unavailable (because it
          is a unique that was already generated). For instance, if you want
          to generate one of Terence, Michael or Erica or a generic human
          (whoever is available, in that order, you can use):
            KMONS: n = Terence, Michael, Erica, human
          Or if you want to pick randomly:
            KMONS: n = Terence / Michael / Erica, human

          KMONS overrides the normal meaning of the glyph: In the absence
          of further declarations,
            KMONS: W = rat
          will result in W producing a rat on a floor tile, not shallow water.

          Like KFEAT, KMONS applies to cells that have the specified glyph
          after applying all shuffles and substitutions.
```

### [9a. `KMASK:`](#table-of-contents)

```
KMASK:    Z = no_monster_gen

          KMASK allows you set or unset various masks for particular
          symbols, rather than for the entire vault like if you did it
          with TAGS. Valid masks are

          * "no_item_gen": Prevents random item on that symbol. Items
             explicitly placed on that symbol aren't affected.
          * "no_monster_gen": Prevents random monster generation on that
             symbol.
          * "no_trap_gen": Prevents random trap generation on that symbol.
          * "no_pool_fixup": Prevents a water square next to land from being
             randomly converted from deep water (the default) to shallow.
          * "no_wall_fixup": Prevents (rock) walls from being converted to
             the level's default wall type, such as in Vaults.
          * "opaque": Overrides the "transparent" tag for this particular
             symbol. The symbol is considered impassible for level-building
             purposes. A "transparent" vault with a deliberately disconnected
             region must use this mask on the disconnected part.

          For example

            KMASK: W = no_monster_gen

          will prevent monsters from randomly being generated on shallow water
          squares. Note that if shuffling and substitutions cause W to end up
          as water 10% of the time and floor 90% of the time, then those floor
          squares will still have no_monster_gen set, but that's still a higher
          degree of control than you get with TAGS.

          If TAGS has been used to set a mask for the entire vault, you can use
          KMASK to remove that mask from particular symbols. For instance:

            TAGS:  no_monster_gen
            KMASK: W = !no_monster_gen

          would make it so that monsters are only randomly generated on shallow
          water squares. Or, to make only part of a vault transparent for
          level-connectivity purposes:

            KMASK: .12 = !opaque

          Unlike KFEAT, KITEM, and KMONS, KMASK does not override the normal
          meaning of the glyph.

          Like KFEAT, KMASK applies to cells that have the specified glyph
          after applying all shuffles and substitutions.
```

### [9b. `KPROP:`](#table-of-contents)

```
KPROP:    x = bloody
          KPROP: allows you to assign a specific property to a feature. Like
          KFEAT: and KMONS:, it can be combined with these for the same place-
          holder.

          Unlike KFEAT etc., KPROP is applied to the cells of the map that
          currently have that glyph, applying only the shuffles and
          substitutions before the KPROP declaration. That is:
            KFEAT: ' = rock_wall
            KPROP: ' = bloody
            SUBST: ' = '.
          causes ' to produce a bloody wall or a bloody floor at random,
          while:
            KFEAT: ' = rock_wall
            SUBST: ' = '.
            KPROP: ' = bloody
          causes ' to produce either a bloody wall or a bloodless floor.

          Unlike KFEAT, KITEM, and KMONS, KPROP: does not override the normal
          meaning of the glyph.

          Available properties are:

          * "bloody": Causes features to appear as though splattered with
             blood. This should be used very, very sparingly!
          * "no_cloud_gen": Prevents clouds from being generated over this
             feature (usually lava). Does not stop fog generators or clouds
             entering from nearby squares.
          * "no_tele_into": Prevents teleportation from choosing to use this
             square. Also prevents this square from being the destination of
             a shaft or hatch. Use this tag to prevent nasty situations like
             the player ending up in a closet or an extremely dense monster
             array (like a hellion island); or for vaults with loot where the
             player is not supposed to get it by teleporting alone.
          * "no_submerge": Monsters will not submerge in this square.
          * "no_tide": Shoals tides will not affect this square.
          * "no_jiyva": No spawning jellies, no off-level eating.

          Two additional named properties exist, but should be avoided:

          * "highlight": The square will be highlighted in the X map in wizard
            mode, and will appear in dumps as "?". For debugging use only; this
            property should be removed before submitting vaults.
          * "mold": The square is covered with mold. This property is reserved
            for use by ballistomycetes and should in general not be set by
            vaults.

          Properties can also be used as tags to apply to the entire vault:
            TAGS: no_tele_into no_tide
```

### [9c. `KITEM:`](#table-of-contents)

```
KITEM:    ? = potion of healing / potion of restore abilities
          KITEM: places the specified item at all occurrences of the
          placeholder. It can be combined with KFEAT: and KMONS: lines for
          the same placeholder.

          You can use "gold" or "$" to place gold:
            KITEM: ? = nothing / gold
            KITEM: ? = nothing / $

          You can use q: to specify quantities:
            KITEM: ? = q:100 gold

          KITEM: allows you to place multiple items on the same square:
            KITEM: ? = bread ration, potion of water, potion of porridge

          KITEM overrides the normal meaning of the glyph: In the absence
          of further declarations,
            KITEM: W = any weapon
          will result in W producing a weapon on a floor tile, not shallow
          water.

          Like KFEAT, KITEM applies to cells that have the specified glyph
          after applying all shuffles and substitutions.
```

### [9d. `MARKER:`](#table-of-contents)

```
MARKER:   A = feat:<feature_name> or lua:<marker_expr>

          A marker ties a square on the map to a game-trigger of some sort
          (which depends on the marker and what feature it is on).

          Lua markers are used for more complex triggers such as entry to the
          Slime loot areas when the Royal Jelly dies, fog generators,
          transporters, etc.

          Here's a Lua marker that creates a cloud generator. For a
          full explanation of the various parameters, read the header
          of dat/dlua/lm_fog.lua.

          MARKER:  A = lua:fog_machine { \
                       pow_max = 15, delay_min = 100, delay_max = 150, \
                       size = 1, size_buildup_amnt = 29, \
                       size_buildup_time = 1000 }

          Feature names used in markers must be names matching the names in
          the source code. There's a full list of feature names in section I
          (Feature names) at the end of this document.

          An important note about markers is that they are also considered map
          transforms along with SUBST, NSUBST and SHUFFLE. You usually want
          to place a MARKER line after all SUBST, NSUBST and SHUFFLE lines so
          that the final position of the marker key is used. For instance, if
          you want to attach a marker to the rune in a map which randomises
          the position of the rune, this is a mistake:

          MARKER: O = lua:<expr>
          SHUFFLE: Oa/|c

          because the marker will be placed at O (the rune), then O may be
          shuffled to a different position. The correct order in this case is:

          SHUFFLE: Oa/|c
          MARKER: O = lua:<expr>
```

### [9e. `SUBVAULT:`](#table-of-contents)

```
SUBVAULT: X : some_vault_tag / some_other_vault_tag:20

          Pick a vault that matches the tag and replace matching glyphs in
          the current map with the cells from that vault.

          Multiple glyphs can be specified on the left hand side and
          weighted sets of tags can be used on the right hand side.

          The use of an equal sign to pick a different subvault per-glyph,
          e.g. "X = some_vault_tag" is not supported at this time. Use
          a ":" instead to fix the choice of vault tag among all glyphs.

          When a subvault is applied, the first step is finding the smallest
          bounding box around the glyphs. For example, in the following vault
          definition, the smallest bounding box around the X glyph is a 4x3
          rectangle:

              ......
              ..XXX.
              ..XXX.
              .XXX..
              ......

          After the bounding box is calculated, a valid subvault that matches
          the given tags and is no larger than the bounding box will be found.
          If no subvault can be found, the vault will throw an error. If a
          subvault is found that is smaller than the provided bounding box,
          then it will be randomly placed and possibly rotated within the
          bounding box.

          There is not much optimization to best fit a subvault into the
          glyphs provided by the parent vault. So, take some care when using
          non-rectangular subvaults. The only special case is if you provide
          a subvault that is the exact same shape as what the parent vault
          requests.

          Everything from the subvault cell (feature, items, monsters,
          properties, markers) overwrite the glyph in the parent map.
          Once replaced, this cell is immutable and cannot be changed
          with something like SUBST, MARKER, or KFEAT.

          Additional glyphs that are not replaced by the subvault will be left
          untouched so that the parent vault can replace them with whatever
          feature it desires. These untouched glyphs can occur either because
          the subvault was smaller than the bounding box or because the
          subvault left the glyph blank (" "). Because of this, a SUBVAULT
          command should usually be followed by a SUBST command to clean up
          these remaining glyphs.

          Subvaults are allowed to include subvaults themselves, recursively.
          However, there is no checking for infinite loops or cycles of
          subvaults, so use this feature with some care.

          During map verification, the SUBVAULT command does not do anything.
          Therefore, the compilation step for Lua vaults will not catch errors
          where no maps exist for a given tag or where all maps that do exist
          are too big to fit into the provided space in the parent map. (The
          reasoning for not verifying the subvault command is so that you can
          specify maps by tag that may be defined later in the file or even in
          another file that hasn't been loaded yet.) So, test your subvaults!

          As the size of the subvault may vary depending on the parent vault,
          there are some helpful Lua functions (in the dgn library) that can
          be used to get more information about what the parent vault is
          requesting. Here's a quick reference:

          is_subvault()

              This function returns true if the current map is being used as a
              subvault and false if the current map is a normal vault.

          local width, height = subvault_size()

              This function returns the width and height of the subvault.
              If not a subvault, it returns 0.

          iter.subvault_iterator(_G)

              Can be used to iterate through all the 0-indexed coordinates
              in the subvault that will get copied back to the parent vault.
              It will return no points if this is not a subvault.

          default_subvault_glyphs()

              This is a convenience function that replaces the current
              subvault map with one that is the exact size of the bounding
              box. For any valid square that the parent map will replace with
              the subvault, it will place a "." in the map. For any invalid
              square that will not be replaced by the subvault, it will place
              a " " in the map. If not a subvault, it does nothing.

              The advantage of this is that a vault author can then use nsubst
              on the "." feature to ensure that a fixed number of objects will
              be created in the parent vault.

              NOTE: This function will also entirely clear the current map, so
              call it first in the subvault definition.
```

Handling long lines
-------------------

For most map headers, you can split long lines by ending the line that will be
continued on the next line with \ as:

KMONS: * = orc ; sabre | quick blade . chain mail | scale mail / \
           goblin ; dagger

If you're using continuation lines for comma-separated lists of monsters or
items, split your line after the comma, not before. For example:

Wrong:
        ITEM: potion of healing \
              , potion of haste
Right:
        ITEM: potion of healing, \
              potion of haste

But in general, it is preferable to use multiple ITEM or MONS lines if you're
splitting comma-separated values:

Preferred:
        ITEM: potion of healing
        ITEM: potion of haste

Spaces before the \ of the continued line are significant, leading spaces of
the next (continuing) line are not. In other words, given:

ITEM: potion of\
      healing

Crawl will see "potion ofhealing", not "potion of healing".

Assigning multiple glyphs at once
---------------------------------

Declarations that modify glyphs allow multiple glyphs to be assigned
simultaneously as a convenience. For example, the following declaration will
assign floor_orc as the tile to be used for all up stair cases and floor:

    FTILE: .[{( = floor_orc

This case is identical to the longer syntax:

    FTILE: . = floor_orc
    FTILE: [ = floor_orc
    FTILE: { = floor_orc
    FTILE: ( = floor_orc

Using : instead of = while assigning glyphs will assign the same value to all
glyphs. In the following example, the glyphs A, B, and C will either all
contain gold or all contain nothing:

    KITEM: ABC : gold / nothing

Note: The number of items assigned in an NSUBST expression applies to the
entire group of glyphs being assigned. For example:

    # Among all A, B, and C glyphs, make one a floor and the rest walls.
    NSUBST: ABC = 1:. / *:x

    # Make one A glyph floor, one B glyph floor, and one C glyph floor.
    # Make the rest of the A, B, and C glyphs walls.
    NSUBST: A = 1:. / *:x
    NSUBST: B = 1:. / *:x
    NSUBST: C = 1:. / *:x

Transporters
------------

Transporters are placed in vaults via two lua marker classes, which can be
created with the functions transp_loc(name) and transp_dest_loc(name). Here
`name' is a string shared between the transporter marker and the the
transporter destination marker. For example,

    MARKER: E = lua:transp_loc("the_bubble_entry")
    MARKER: F = lua:transp_dest_loc("the_bubble_entry")

will place a transporter on any glyph E that leads to the location of glyph F.
This form of placement works both within a vault and when the transporter and
its destination are in different vaults/subvaults, since transporters are
placed from the markers after the level is generated.

You may have multiple glyphs with the same transporter markers name, and they
will all lead to the same destination after placement. Note that it's not valid
to have multiple glyphs with the same destination marker. Any randomization of
destinations can be done through normal SUBST/NSUBST/SHUFFLE operations before
the MARKER statements.