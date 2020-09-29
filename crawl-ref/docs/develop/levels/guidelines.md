# Guidelines for specific types of vaults

- [Guidelines for specific types of vaults](#guidelines-for-specific-types-of-vaults)
  - [Guidelines for D:1 arrival vaults](#guidelines-for-d1-arrival-vaults)
    - [We need more arrival vaults!](#we-need-more-arrival-vaults)
    - [Some guidelines for arrival vault creators](#some-guidelines-for-arrival-vault-creators)
    - [Naming conventions](#naming-conventions)
  - [Guidelines for creating serial vaults](#guidelines-for-creating-serial-vaults)
  - [Guidelines for creating ghost vaults](#guidelines-for-creating-ghost-vaults)
    - [Organization and setup](#organization-and-setup)
    - [Basic guidelines](#basic-guidelines)
    - [Distribution](#distribution)
    - [Custom Tags](#custom-tags)
  - [Guidelines for `no_tele_into`](#guidelines-for-no_tele_into)
    - [Good places to use `no_tele_into`:](#good-places-to-use-no_tele_into)
    - [Bad places to use `no_tele_into`:](#bad-places-to-use-no_tele_into)

***

## [Guidelines for D:1 arrival vaults](#guidelines-for-specific-types-of-vaults)

Arrival vaults should provide atmosphere and a nice starting point. The idea
is neither to get a grip on most of D:1 nor to hand out starting gear.
Playing Crawl a bit will show you a number of arrival vaults, which live in
[dat/des/arrival/](../../../source/dat/des/arrival/)

### [We need more arrival vaults!](#guidelines-for-specific-types-of-vaults)

We love new arrival vaults, and it is easy to make new ones. Coding abilities
are not required. If you are completely new to making maps, have a look at
simple.des. After that, glance through the [Introduction](./introduction.txt),
which will allow you to make
your own maps already! Once you are familiar with this, you may look at more
complicated vaults and read the more [advanced documentation](./advanced.txt).
Crawl also employs vaults in many other places; check the various `.des` files
in [dat/des/](../../../source/dat/des/) for what is going on.
New maps are always welcome.

### [Some guidelines for arrival vault creators](#guidelines-for-specific-types-of-vaults)

* Try to come up with *small* maps.
* *Avoid* placing guaranteed items.
* The same holds for any features which might trigger start-scumming, like
  altars.
* Also *avoid ASCII art*. It probably won't work in Tiles anyway.
* Also *avoid monsters-behind-glass-wall vaults*. We already have enough of these.
* Note that at the start of the game, the dungeon builder removes *all*
  monsters in view of the player. Zero experience monsters like plants
  are exempt.
* Arrival vaults should have *multiple* entry points, escape hatches, or enough
  space to permit tactics.

### [Naming conventions](#guidelines-for-specific-types-of-vaults)

Entry vaults should be NAMEd as follows:

``` NAME:  nick_arrival_name ```

where `nick` is the name/nick of the *vault designer* and `name` is a somewhat
descriptive label for the vault. *Avoid numbers, please*.

The actual maps can be found in the following files:

| File        |  Contents |
|-------------|--------------------------------|
| [simple.des](../../../source/dat/des/arrival/simple.des) | Particularly simple maps: no more than **five** header lines! |
| [small.des](../../../source/dat/des/arrival/small.des) | Small maps with neither lua nor complicated syntax. |
| [twisted.des](../../../source/dat/des/arrival/twisted.des) | Maps which either use **a lot of lua** or **heavy `SUBST`ing** etc. |
| [large.des](../../../source/dat/des/arrival/large.des) | Sizes of about 30x30 and up. |

If a map is both big and complex, file under [twisted.des](../../../source/dat/des/arrival/twisted.des).

If a map is both plain and small, file under [simple.des](../../../source/dat/des/arrival/simple.des).

***

## [Guidelines for creating serial vaults](#guidelines-for-specific-types-of-vaults)

Sometimes, we want flavour (or also other) vaults to be placed several times,
so as to make the level feel more coherent; this is called a **serial vault**.
The lua calls for such serial vaults are in the files in the folder
[dat/des/serial/](../../../source/dat/des/serial/).
Each serial vault has its own file.

The vaults eventually could be just copies of one map, or (much better) come
from a list of thematically linked maps. This is mostly for flavour, although
it may be interesting to created serial vaults around threats.

In general, we don't want more than one serial vault on a level. Use the

``` TAGS: luniq_serial ```

in the serial vault's header map for this.

Often, it will be fine to allow the individual maps comprising a serial vault
to be chosen by the level builder as usual minivaults. If you want to do that,
there are two ways to proceed:

* A default-depth line before all maps.
* Or non-empty `DEPTH` statements in each map definition.
  * (You can still do
    this even if there is a default-depth. It allows you tweak the depths for
    specific maps.)

If you want to disable all or some the maps for from normal minivault
placement, you can:

* Give them no `DEPTH` line when you have no preceding default-depth.
* Explicitly remove them with an empty depth line like this:

``` DEPTH: ```

***

## [Guidelines for creating ghost vaults](#guidelines-for-specific-types-of-vaults)

Ghost vaults are vaults that place a player ghost, which is an undead monster
with properties derived from a player who died. These vaults should place some
amount of additional loot to offer some enticement for players where the XP
from killing the ghost isn't sufficient reward. Often these vaults place
monsters in addition to the ghost. Ghost vaults usually place one ghost, but
may less often place multiple ghosts.

### [Organization and setup](#guidelines-for-specific-types-of-vaults)

All ghost vaults not placing in the Vaults branch should go in
[ghost.des](../../../source/dat/des/variable/ghost.des)
and call the lua ghost setup function the following way:

``` : ghost_setup(_G) ```

This will set the common tags we want for all ghost vaults as well as the
common `CHANCE` to place these vaults, as described in sections below. These
vaults can be minivaults or have any of the usual kinds of `ORIENT` statements.

For the Vaults branch, a ghost vault will be a vault room in
[vaults_room_ghost.des](../../../source/dat/des/branches/vaults_room_ghost.des)
and it should call the vault lua ghost setup function:

``` : vaults_ghost_setup(_G) ```

This setup will set common tags for ghost rooms and set a `vaults_ghost` tag
recognized by the Vaults layout. Vaults calling `vaults_ghost_setup()` do not
need to set the `vaults_ghost` tag on their own.

### [Basic guidelines](#guidelines-for-specific-types-of-vaults)

Ghost vaults should always be ***sealed*** and ideally not diggable by monsters that
have a dig wand or the dig spell. This means the vault should have **non-rock**
outer walls and use either **runed doors** or **transporters** for entry. The vaults
should have **transparent walls** so that it's always possible for the player to
see the ghost *before* entering, even if the ghost is awake and wandering.

For placement in early dungeon levels, relatively less additional loot is
necessary, since ghost XP is more impactful then. However it's recommended to
place at least some loot in early levels, and more strongly recommended for
later depths where ghost XP provides much less incentive on its own. It's fine
to place monsters in addition to the ghost monsters; just keep in mind that
player ghosts are relatively difficult to kill compared to a large majority of
crawl monsters. See the aforementioned
[ghost.des](../../../source/dat/des/variable/ghost.des) and
[vaults_room_ghost.des](../../../source/dat/des/branches/vaults_room_ghost.des)
for examples and inspiration.

### [Distribution](#guidelines-for-specific-types-of-vaults)

The current range of levels that place ghost vaults is:

```
default-depth: D:3-, Lair, Elf, Orc, Snake, Shoals, Swamp, Spider, Depths, Crypt, Zot
```

Every ghost vault uses a common chance value defined in
[ghost.lua](../../../crawl-ref/source/dat/dlua/ghost.lua)
that dictates the chance a level will place a ghost vault. This chance is
currently `10%`. Ghost vaults that call one of the lua setup functions mentioned
above will have this chance set automatically and do not need their own `CHANCE`
statement.

To make a ghost vault relatively more or less commonly chosen among the set of
ghost vaults, use a `WEIGHT` statement to set a weight other than `10`, the
default. A vault can use `WEIGHT` to set different weights for different
branches/levels. See examples in
[ghost.des](../../../source/dat/des/variable/ghost.des) and
[syntax.txt](./syntax.txt).

### [Custom Tags](#guidelines-for-specific-types-of-vaults)

If the tags set by `ghost_setup()` or `vaults_ghost_setup()` are somehow not
appropriate, ghost vaults can set their own tags instead of calling these
functions. For ghost vaults not in the Vaults branch, the vault should at a
minimum call the following function to set the `CHANCE` and set the
`chance_player_ghost` tag:

``` : chance_player_ghost(_G) ```

It's strongly recommended that you use this function instead of setting a
`CHANCE` directly in the vault. For ghost vault rooms for Vaults, instead set the
`vaults_ghost` tag; these vaults should not have a `CHANCE` statement at all.

Other tags we generally require for ghost vaults are `no_tele_into` and
`no_trap_gen`. If you use `allow_dup` in your vault, also use
`luniq_player_ghost` to avoid multiple vault placement on the same level.

***

## [Guidelines for `no_tele_into`](#guidelines-for-specific-types-of-vaults)

The `no_tele_into` `KPROP` prevents teleports landing you on the tagged locations.

Example:

```
NAME:  example_vault
KPROP: - = no_tele_into
SUBST: - = .
MAP
xxxxxx
+.m--x
xxxxxx
ENDMAP
```

Teleports will never land the player behind the glass wall.

*Don't overuse this property*. It's a hidden mechanic not exposed to the player.

### [Good places to use `no_tele_into`:](#guidelines-for-specific-types-of-vaults)

* Vaults which need the player to enter in a controlled manner to understand/enjoy. For example
  [`gammafunk_steamed_eel`](../../../source/dat/des/variable/float.des) (line 4291).
* Teleport closets: areas the player cannot escape without a scroll of teleportation (or similar).
  For example [`lemuel_altar_in_water`](../../../source/dat/des/altar/altar.des) (line 108).
* Egregiously dangerous/unfair situations. For example
  [`chequers_guarded_unrand_ignorance`](../../../source/dat/des/variable/mini_monsters.des)
  (line 6959) (four orange crystal statues).

### [Bad places to use `no_tele_into`:](#guidelines-for-specific-types-of-vaults)

* Any old runed door / transporter vault. It's fine for players to teleport into tough or scary situations.
* Islands: areas the player can also reach with flight or similar tools. `no_tele_into` would be
  an incomplete solution. It's better to place a hatch/shaft, which solves all cases.
