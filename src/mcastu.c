/* NetHack 3.7	mcastu.c	$NHDT-Date: 1596498177 2020/08/03 23:42:57 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.68 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2011. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

/* monster mage spells */
enum mcast_mage_spells {
    MGC_PSI_BOLT = 0,
    MGC_CURE_SELF,
    MGC_HASTE_SELF,
    MGC_STUN_YOU,
    MGC_DISAPPEAR,
    MGC_WEAKEN_YOU,
    MGC_DESTRY_ARMR,
    MGC_CURSE_ITEMS,
    MGC_AGGRAVATION,
    MGC_SUMMON_MONS,
    MGC_CLONE_WIZ,
    MGC_DEATH_TOUCH,
    LAST_MGC
};

/* monster cleric spells */
enum mcast_cleric_spells {
    CLC_OPEN_WOUNDS = 0,
    CLC_CURE_SELF,
    CLC_CONFUSE_YOU,
    CLC_PARALYZE,
    CLC_BLIND_YOU,
    CLC_INSECTS,
    CLC_CURSE_ITEMS,
    CLC_LIGHTNING,
    CLC_FIRE_PILLAR,
    CLC_GEYSER,
    LAST_CLC
};

/* monster elven spells */
enum mcast_elven_spells {
    ELV_SLEEP = 0,
    ELV_PROTECTION,
    ELV_BLESS_ITEM,
    ELV_ENCHANT_ITEM,
    LAST_ELV
};

/* monster djinni spells */
enum mcast_djinni_spells {
    DJN_DEBRIS = 0,
    DJN_STEAL_JEWELRY,
    DJN_HALLUCINATE,
    DJN_MAKE_PIT,
    DJN_WARD_ELEMENTS,
    DJN_MAKE_GOLEM,
    DJN_PIN_ARMS,
    DJN_CURSE_YOU,
    DJN_BALEFUL_POLYMORPH,
    DJN_FLESH_TO_STONE
};

static void cursetxt(struct monst *, boolean);
static int choose_magic_spell(int);
static int choose_clerical_spell(int);
static int choose_elven_spell(int);
static int choose_djinni_spell(int);
static int m_cure_self(struct monst *, int);
static void m_protection(struct monst *);
static void m_bless_item(struct monst *);
static void m_enchant_item(struct monst *);
static void cast_wizard_spell(struct monst *, int, int);
static void cast_cleric_spell(struct monst *, int, int);
static void cast_elven_spell(struct monst *, int, int);
static int cast_djinni_spell(struct monst *, int, int);
static boolean is_undirected_spell(unsigned int, int);
static boolean spell_would_be_useless(struct monst *, unsigned int, int);

/* feedback when frustrated monster couldn't cast a spell */
static void
cursetxt(struct monst *mtmp, boolean undirected)
{
    if (is_elf(mtmp->data))
        return;
    if (mtmp->data->msound == MS_SPELL && rn2(2))
        return;
    if (canseemon(mtmp) && couldsee(mtmp->mx, mtmp->my)) {
        const char *point_msg; /* spellcasting monsters are impolite */

        if (undirected)
            point_msg = "all around, then curses";
        else if ((Invis && !perceives(mtmp->data)
                  && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                 || is_obj_mappear(&gy.youmonst, STRANGE_OBJECT)
                 || u.uundetected)
            point_msg = "and curses in your general direction";
        else if (Displaced && (mtmp->mux != u.ux || mtmp->muy != u.uy))
            point_msg = "and curses at your displaced image";
        else
            point_msg = "at you, then curses";

        pline("%s points %s.", Monnam(mtmp), point_msg);
    } else if ((!(gm.moves % 4) || !rn2(4))) {
        if (!Deaf)
            Norep("You hear a mumbled curse.");   /* Deaf-aware */
    }
}

/* convert a level-based random selection into a specific mage spell;
   inappropriate choices will be screened out by spell_would_be_useless() */
static int
choose_magic_spell(int spellnum)
{
    /* for 3.4.3 and earlier, val greater than 22 selected default spell */
    if (spellnum > 25)
        spellnum = 25;
    if (spellnum < 1)
        spellnum = 1;
    spellnum = rn2(spellnum);

    switch (spellnum) {
    case 24:
    case 23:
        if (Antimagic || Hallucination)
            return MGC_PSI_BOLT;
        /*FALLTHRU*/
    case 22:
    case 21:
    case 20:
        return MGC_DEATH_TOUCH;
    case 19:
    case 18:
        return MGC_CLONE_WIZ;
    case 17:
    case 16:
    case 15:
        return MGC_SUMMON_MONS;
    case 14:
    case 13:
        return MGC_AGGRAVATION;
    case 12:
    case 11:
    case 10:
        return MGC_CURSE_ITEMS;
    case 9:
    case 8:
        return MGC_DESTRY_ARMR;
    case 7:
    case 6:
        return MGC_WEAKEN_YOU;
    case 5:
    case 4:
        return MGC_DISAPPEAR;
    case 3:
        return MGC_STUN_YOU;
    case 2:
        return MGC_HASTE_SELF;
    case 1:
        return MGC_CURE_SELF;
    case 0:
    default:
        return MGC_PSI_BOLT;
    }
}

/* convert a level-based random selection into a specific cleric spell */
static int
choose_clerical_spell(int spellnum)
{
    /* for 3.4.3 and earlier, num greater than 13 selected the default spell
     */
    if (spellnum > 16)
        spellnum = 16;
    if (spellnum < 1)
        spellnum = 1;
    spellnum = rn2(spellnum);
    switch (spellnum) {
    case 15:
    case 14:
        if (rn2(3))
            return CLC_OPEN_WOUNDS;
        /*FALLTHRU*/
    case 13:
        return CLC_GEYSER;
    case 12:
        return CLC_FIRE_PILLAR;
    case 11:
        return CLC_LIGHTNING;
    case 10:
    case 9:
        return CLC_CURSE_ITEMS;
    case 8:
        return CLC_INSECTS;
    case 7:
    case 6:
        return CLC_BLIND_YOU;
    case 5:
    case 4:
        return CLC_PARALYZE;
    case 3:
    case 2:
        return CLC_CONFUSE_YOU;
    case 1:
        return CLC_CURE_SELF;
    case 0:
    default:
        return CLC_OPEN_WOUNDS;
    }
}
/* convert a level-based random selection into a specific elven spell */
static int
choose_elven_spell(int spellnum)
{
    if (spellnum > 11)
        spellnum = 11;
    if (spellnum < 1)
        spellnum = 1;
    spellnum = rn2(spellnum);
    switch (spellnum) {
    case 10:
        return LAST_MGC + LAST_CLC + ELV_ENCHANT_ITEM;
    case 9:
        return LAST_MGC + LAST_CLC + ELV_BLESS_ITEM;
    case 8:
    case 7:
        return LAST_MGC + LAST_CLC + ELV_SLEEP;
    case 6:
    case 5:
        return LAST_MGC + LAST_CLC + ELV_PROTECTION;
    case 4:
        return MGC_DISAPPEAR;
    case 3:
    case 2:
        return MGC_HASTE_SELF;
    default:
        return MGC_CURE_SELF;
    }
}

/* convert a level-based random selection into a specific djinni spell */
static int
choose_djinni_spell(int spellnum)
{
    if (!rn2(6)) {
        if (spellnum > 8)
            return choose_magic_spell(8);
        else
            return choose_magic_spell(spellnum);
    }
    if (!rn2(3)) {
        
        int chosen_spell;
        for (int i = 0; i < 3; i++) {
            chosen_spell = choose_clerical_spell(spellnum);
            if (chosen_spell == CLC_GEYSER || chosen_spell == CLC_FIRE_PILLAR || chosen_spell == CLC_LIGHTNING)
                break;
        }
        return LAST_MGC + chosen_spell;
    }
    if (!rn2(6)) {
        if (spellnum > 9)
            spellnum = 9;
        int elven_spell = choose_elven_spell(spellnum);
        if (elven_spell < LAST_ELV)
            return LAST_MGC + LAST_CLC + elven_spell;
        else
            return LAST_MGC + LAST_CLC + choose_elven_spell(spellnum);
    }
    if (spellnum > 25)
        spellnum = 25;
    if (spellnum < 1)
        spellnum = 1;
    spellnum = rn2(spellnum);
    switch (spellnum) {
    case 24:
    case 23:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_FLESH_TO_STONE;
    case 22:
    case 21:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_BALEFUL_POLYMORPH;
    case 20:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_CURSE_YOU;
    case 19:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_PIN_ARMS;
    case 18:
    case 17:
    case 16:
    case 15:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_MAKE_GOLEM;
    case 14:
    case 13:
    case 12:
    case 11:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_WARD_ELEMENTS;
    case 10:
    case 9:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_MAKE_PIT;
    case 8:
    case 7:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_HALLUCINATE;
    case 6:
    case 5:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_STEAL_JEWELRY;
    default:
        return LAST_MGC + LAST_CLC + LAST_ELV + DJN_DEBRIS;
    }
}

static int
spell_level(int spellnum)
{
    if (spellnum < LAST_MGC) /* ASSUMPTION: more magical spells than any other class */
        return spellnum;
    spellnum -= LAST_MGC;
    if (spellnum < LAST_CLC)
        return spellnum;
    spellnum -= LAST_CLC;
    if (spellnum < LAST_ELV)
        return spellnum;
    spellnum -= LAST_ELV;
    return spellnum;
}

/* return values:
 * 1: successful spell
 * 0: unsuccessful spell
 */
int
castmu(
    register struct monst *mtmp,   /* caster */
    register struct attack *mattk, /* caster's current attack */
    boolean thinks_it_foundyou,    /* might be mistaken if displaced */
    boolean foundyou)              /* knows hero's precise location */
{
    int dmg, ml = mtmp->m_lev;
    int ret;
    int spellnum = 0;

    if (is_elf(mtmp->data)) {
        if (mtmp->data == &mons[PM_HIGH_ELF]) {
            if (rn2(2))
                return MM_MISS;
        }
        else if (mtmp->data == &mons[PM_ELVEN_MONARCH]) {
            if (rn2(5))
                return MM_MISS;
        }
        else if (mtmp->data == &mons[PM_ELF_NOBLE]) {
            if (rn2(10))
                return MM_MISS;
        }
        else
            if (rn2(20))
                return MM_MISS;
    }
    /* Three cases:
     * -- monster is attacking you.  Search for a useful spell.
     * -- monster thinks it's attacking you.  Search for a useful spell,
     *    without checking for undirected.  If the spell found is directed,
     *    it fails with cursetxt() and loss of mspec_used.
     * -- monster isn't trying to attack.  Select a spell once.  Don't keep
     *    searching; if that spell is not useful (or if it's directed),
     *    return and do something else.
     * Since most spells are directed, this means that a monster that isn't
     * attacking casts spells only a small portion of the time that an
     * attacking monster does.
     */
    if ((mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC
         || mattk->adtyp == AD_ELVN || mattk->adtyp == AD_DJIN) && ml) {
        int cnt = 40;

        do {
            spellnum = rn2(ml);
            if (mattk->adtyp == AD_SPEL)
                spellnum = choose_magic_spell(spellnum);
            else if (mattk->adtyp == AD_CLRC)
                spellnum = choose_clerical_spell(spellnum);
            else if (mattk->adtyp == AD_ELVN)
                spellnum = choose_elven_spell(spellnum);
            else if (mattk->adtyp == AD_DJIN)
                spellnum = choose_djinni_spell(spellnum);
            if (mtmp->data->mlet == S_LICH)
                if (rn2(2))
                    spellnum = MGC_PSI_BOLT;
            if (spellnum < 0)
                return MM_MISS;
            /* not trying to attack?  don't allow directed spells */
            if (!thinks_it_foundyou) {
                if (!is_undirected_spell(mattk->adtyp, spellnum)
                    || spell_would_be_useless(mtmp, mattk->adtyp, spellnum)) {
                    if (foundyou)
                        impossible(
                       "spellcasting monster found you and doesn't know it?");
                    return MM_MISS;
                }
                break;
            }
        } while (--cnt > 0
                 && spell_would_be_useless(mtmp, mattk->adtyp, spellnum));
        if (cnt == 0)
            return MM_MISS;
    }

    /* monster unable to cast spells? */
    if (mtmp->mcan || mtmp->mspec_used || !ml) {
        cursetxt(mtmp, is_undirected_spell(mattk->adtyp, spellnum));
        return MM_MISS;
    }
    if (is_undirected_spell(mattk->adtyp, spellnum) && rn2(2))
        return MM_MISS;

    if (mattk->adtyp == AD_SPEL || mattk->adtyp == AD_CLRC
        || mattk->adtyp == AD_ELVN || mattk->adtyp == AD_DJIN) {
        mtmp->mspec_used = 10 * (rn2(spell_level(spellnum) + 2) + 2);
        mtmp->mspec_used /= mtmp->m_lev;
        if (mtmp->data->msound == MS_SPELL)
            mtmp->mspec_used--;
        if (mtmp->mspec_used < 0)
            mtmp->mspec_used = 0;
    }

    /* monster can cast spells, but is casting a directed spell at the
       wrong place?  If so, give a message, and return.  Do this *after*
       penalizing mspec_used. */
    if (!foundyou && thinks_it_foundyou
        && !is_undirected_spell(mattk->adtyp, spellnum)) {
        pline("%s casts a spell at %s!",
              canseemon(mtmp) ? Monnam(mtmp) : "Something",
              is_waterwall(mtmp->mux,mtmp->muy) ? "empty water"
                                                : "thin air");
        return MM_MISS;
    }

    nomul(0);
    if (rn2(ml * 10) < (mtmp->mconf ? 100 : 20)) { /* fumbled attack */
        if (canseemon(mtmp) && !Deaf)
            if (mattk->adtyp != AD_ELVN)
                pline_The("air crackles around %s.", mon_nam(mtmp));
        return MM_MISS;
    }
    if (canspotmon(mtmp) || !is_undirected_spell(mattk->adtyp, spellnum)) {
        pline("%s casts a spell%s!",
              canspotmon(mtmp) ? Monnam(mtmp) : "Something",
              is_undirected_spell(mattk->adtyp, spellnum)
                  ? ""
                  : (Invis && !perceives(mtmp->data)
                     && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                        ? " at a spot near you"
                        : (Displaced
                           && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                              ? " at your displaced image"
                              : " at you");
    }

    /*
     * As these are spells, the damage is related to the level
     * of the monster casting the spell.
     */
    if (!foundyou) {
        dmg = 0;
        if (mattk->adtyp != AD_SPEL && mattk->adtyp != AD_CLRC
            && mattk->adtyp != AD_ELVN && mattk->adtyp != AD_DJIN) {
            impossible(
              "%s casting non-hand-to-hand version of hand-to-hand spell %d?",
                       Monnam(mtmp), mattk->adtyp);
            return MM_MISS;
        }
    } else if (mattk->damd)
        dmg = d((int) (spell_hit_dice((int) mtmp->m_lev) - 1 + mattk->damn),
                (int) mattk->damd);
    else
        dmg = d(spell_hit_dice((int) mtmp->m_lev), 6);
    if (Half_spell_damage && mtmp->data != &mons[PM_DJINNI]
        && mtmp->data != &mons[PM_AFRIT] && mtmp->data != &mons[PM_MARID]) /* half spell damage is applied later */
        dmg = (dmg + 1) / 2;

    ret = MM_HIT;
    switch (mattk->adtyp) {
    case AD_FIRE:
        pline("You're enveloped in flames.");
        if (Fire_resistance) {
            shieldeff(u.ux, u.uy);
            pline("But you mostly resist the effects.");
            monstseesu(M_SEEN_FIRE);
            dmg = resist_damage(AD_FIRE, dmg);
        }
        burn_away_slime();
        break;
    case AD_COLD:
        pline("You're covered in frost.");
        if (Cold_resistance) {
            shieldeff(u.ux, u.uy);
            pline("But you mostly resist the effects.");
            monstseesu(M_SEEN_COLD);
            dmg = resist_damage(AD_COLD, dmg);
        }
        break;
    case AD_MAGM:
        You("are hit by a shower of missiles!");
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            pline_The("missiles bounce off!");
            monstseesu(M_SEEN_MAGR);
            dmg = 0;
        } else
            dmg = d(spell_hit_dice((int) mtmp->m_lev), 6);
        break;
    case AD_SPEL: /* wizard spell */
    case AD_CLRC: /* clerical spell */
    case AD_ELVN: /* elven spell */
    case AD_DJIN: /* djinni spell */
    {
        if (mattk->adtyp == AD_SPEL)
            cast_wizard_spell(mtmp, dmg, spellnum);
        else if (mattk->adtyp == AD_CLRC)
            cast_cleric_spell(mtmp, dmg, spellnum);
        else if (mattk->adtyp == AD_ELVN)
            cast_elven_spell(mtmp, dmg, spellnum);
        else if (mattk->adtyp == AD_DJIN)
            if (cast_djinni_spell(mtmp, dmg, spellnum) == 1)
                ret |= MM_AGR_DONE; /* end monster turn */
        dmg = 0; /* done by the spell casting functions */
        break;
    }
    }
    if (dmg)
        mdamageu(mtmp, dmg);
    return ret;
}

static int
m_cure_self(struct monst *mtmp, int dmg)
{
    if (mtmp->mhp < mtmp->mhpmax) {
        if (canseemon(mtmp))
            pline("%s looks better.", Monnam(mtmp));
        /* note: player healing does 6d4; this used to do 1d8 */
        if ((mtmp->mhp += d(3, 6)) > mtmp->mhpmax)
            mtmp->mhp = mtmp->mhpmax;
        dmg = 0;
    }
    return dmg;
}

static void
m_protection(struct monst *mtmp)
{
    int l = mtmp->m_lev, loglev = 0;
    while (l) {
        loglev++;
        l /= 2;
    }
    mtmp->mprot = loglev;
    mtmp->mprotlen = 10;
    const char *hgolden = hcolor(NH_GOLDEN), *atmosphere;
    int rmtyp;
    rmtyp = levl[mtmp->mx][mtmp->my].typ;
    atmosphere = (rmtyp == CLOUD) ? "cloud"
                         : IS_TREE(rmtyp) ? "vegetation"
                           : IS_STWALL(rmtyp) ? "stone"
                             : "air";
    if (!Blind && cansee(mtmp->mx, mtmp->my) && canspotmon(mtmp))
        pline_The("%s around %s begins to shimmer with %s haze.",
                  atmosphere, mon_nam(mtmp), an(hgolden));
}

static void
m_bless_item(struct monst *mtmp)
{
    struct obj *obj, *otmp;
    int m, n = 0;
    for (obj = mtmp->minvent; obj; obj = otmp) {
        otmp = obj->nobj;
        if (is_elven_obj(obj))
            if (obj->cursed == 1)
                n++;
    }
    if (n) {
        m = rn2(n);
        n = 0;
        for (obj = mtmp->minvent; obj; obj = otmp) {
            otmp = obj->nobj;
            if (is_elven_obj(obj))
                if (obj->cursed == 1) {
                    if (m == n) {
                        obj->cursed = 0;
                        if (!Blind && cansee(mtmp->mx, mtmp->my) && canspotmon(mtmp)) {
                            pline("%c%s glow is visible around %s.", highc(an(hcolor(NH_AMBER))[0]), an(hcolor(NH_AMBER)) + 1, mon_nam(mtmp));
                            return;
                        }
                    }
                    n++;
                }
        }
    }
    for (obj = mtmp->minvent; obj; obj = otmp) {
        otmp = obj->nobj;
        if (is_elven_obj(obj))
            if (obj->blessed == 0)
                n++;
    }
    if (n) {
        m = rn2(n);
        n = 0;
        for (obj = mtmp->minvent; obj; obj = otmp) {
            otmp = obj->nobj;
            if (is_elven_obj(obj))
                if (obj->blessed == 0) {
                    if (m == n) {
                        obj->blessed = 1;
                        if (canseemon(mtmp)) {
                            pline("%c%s glow is visible around %s.", highc(an(hcolor(NH_LIGHT_BLUE))[0]), an(hcolor(NH_LIGHT_BLUE)) + 1, mon_nam(mtmp));
                            return;
                        }
                    }
                    n++;
                }
        }
    }
}

static void
m_enchant_item(struct monst *mtmp)
{
    struct obj *obj, *otmp;
    int m, n = 0;
    for (obj = mtmp->minvent; obj; obj = otmp) {
        otmp = obj->nobj;
        if (is_elven_obj(obj))
            if (obj->spe < 3 || (otmp->otyp != ELVEN_MITHRIL_COAT && obj->spe < 5))
                n++;
    }
    if (n) {
        m = rn2(n);
        n = 0;
        for (obj = mtmp->minvent; obj; obj = otmp) {
            otmp = obj->nobj;
            if (is_elven_obj(obj))
                if (obj->spe < 3 || (otmp->otyp != ELVEN_MITHRIL_COAT && obj->spe < 5)) {
                    if (m == n) {
                        obj->spe++;
                        if (!Blind && cansee(mtmp->mx, mtmp->my) && canspotmon(mtmp)) {
                            pline("%c%s glow is visible around %s.", highc(an(hcolor(NH_SILVER))[0]), an(hcolor(NH_SILVER)) + 1, mon_nam(mtmp));
                            return;
                        }
                    }
                    n++;
                }
        }
    }
}

static boolean
m_make_pit(struct monst *mtmp)
{
    struct trap *ttmp;
    boolean existing_pit = FALSE;
    if ((ttmp = t_at(u.ux, u.uy)) != 0)
        if (ttmp->ttyp == PIT)
            existing_pit = TRUE;
    if (existing_pit)
        digactualhole(u.ux, u.uy, mtmp, HOLE, TRUE);
    else
        digactualhole(u.ux, u.uy, mtmp, PIT, TRUE);
    if(u.utotype)
        return TRUE;
    return FALSE;
}

void
touch_of_death(void)
{
    static const char touchodeath[] = "touch of death";
    int dmg = 50 + d(8, 6);
    int drain = dmg / 2;

    You_feel("drained...");

    if (drain >= u.uhpmax) {
        gk.killer.format = KILLED_BY_AN;
        Strcpy(gk.killer.name, touchodeath);
        done(DIED);
    } else {
        u.uhpmax -= drain;
        losehp(dmg, touchodeath, KILLED_BY_AN);
    }
}

/*
 * Monster wizard and cleric spellcasting functions.
 */

/*
   If dmg is zero, then the monster is not casting at you.
   If the monster is intentionally not casting at you, we have previously
   called spell_would_be_useless() and spellnum should always be a valid
   undirected spell.
   If you modify either of these, be sure to change is_undirected_spell()
   and spell_would_be_useless().
 */
static
void
cast_wizard_spell(struct monst *mtmp, int dmg, int spellnum)
{
    if (dmg == 0 && !is_undirected_spell(AD_SPEL, spellnum)) {
        impossible("cast directed wizard spell (%d) with dmg=0?", spellnum);
        return;
    }

    switch (spellnum) {
    case MGC_DEATH_TOUCH:
        pline("Oh no, %s's using the touch of death!", mhe(mtmp));
        if (nonliving(gy.youmonst.data) || is_demon(gy.youmonst.data)) {
            You("seem no deader than before.");
        } else if (!Antimagic && rn2(mtmp->m_lev) > 12) {
            if (Hallucination) {
                You("have an out of body experience.");
            } else {
                touch_of_death();
            }
        } else {
            if (Antimagic) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_MAGR);
            }
            pline("Lucky for you, it didn't work!");
        }
        dmg = 0;
        break;
    case MGC_CLONE_WIZ:
        if (mtmp->iswiz && gc.context.no_of_wizards == 1) {
            pline("Double Trouble...");
            clonewiz();
            dmg = 0;
        } else
            impossible("bad wizard cloning?");
        break;
    case MGC_SUMMON_MONS: {
        int count = nasty(mtmp);

        if (!count) {
            ; /* nothing was created? */
        } else if (mtmp->iswiz) {
            verbalize("Destroy the thief, my pet%s!", plur(count));
        } else {
            boolean one = (count == 1);
            const char *mappear = one ? "A monster appears"
                                      : "Monsters appear";

            /* messages not quite right if plural monsters created but
               only a single monster is seen */
            if (Invis && !perceives(mtmp->data)
                && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                pline("%s %s a spot near you!", mappear,
                      one ? "at" : "around");
            else if (Displaced && (mtmp->mux != u.ux || mtmp->muy != u.uy))
                pline("%s %s your displaced image!", mappear,
                      one ? "by" : "around");
            else
                pline("%s from nowhere!", mappear);
        }
        dmg = 0;
        break;
    }
    case MGC_AGGRAVATION:
        You_feel("that monsters are aware of your presence.");
        aggravate();
        dmg = 0;
        break;
    case MGC_CURSE_ITEMS:
        You_feel("as if you need some help.");
        rndcurse();
        dmg = 0;
        break;
    case MGC_DESTRY_ARMR:
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            pline("A field of force surrounds you!");
        } else if (!destroy_arm(some_armor(&gy.youmonst))) {
            Your("skin itches.");
        }
        dmg = 0;
        break;
    case MGC_WEAKEN_YOU: /* drain strength */
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            You_feel("momentarily weakened.");
        } else {
            You("suddenly feel weaker!");
            dmg = mtmp->m_lev - 6;
            if (dmg < 1) /* paranoia since only chosen when m_lev is high */
                dmg = 1;
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            losestr(rnd(dmg), (const char *) 0, 0);
        }
        dmg = 0;
        break;
    case MGC_DISAPPEAR: /* makes self invisible */
        if (!mtmp->minvis && !mtmp->invis_blkd) {
            if (canseemon(mtmp))
                pline("%s suddenly %s!", Monnam(mtmp),
                      !See_invisible ? "disappears" : "becomes transparent");
            mon_set_minvis(mtmp);
            if (cansee(mtmp->mx, mtmp->my) && !canspotmon(mtmp))
                map_invisible(mtmp->mx, mtmp->my);
            dmg = 0;
        } else
            impossible("no reason for monster to cast disappear spell?");
        break;
    case MGC_STUN_YOU:
        if (Antimagic || Free_action) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            if (!Stunned)
                You_feel("momentarily disoriented.");
            make_stunned(1L, FALSE);
        } else {
            You(Stunned ? "struggle to keep your balance." : "reel...");
            dmg = d(ACURR(A_DEX) < 12 ? 6 : 4, 4);
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            make_stunned((HStun & TIMEOUT) + (long) dmg, FALSE);
        }
        dmg = 0;
        break;
    case MGC_HASTE_SELF:
        mon_adjust_speed(mtmp, 1, (struct obj *) 0);
        dmg = 0;
        break;
    case MGC_CURE_SELF:
        dmg = m_cure_self(mtmp, dmg);
        break;
    case MGC_PSI_BOLT:
        /* prior to 3.4.0 Antimagic was setting the damage to 1--this
           made the spell virtually harmless to players with magic res. */
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            dmg = (dmg + 1) / 2;
        }
        if (dmg <= 5)
            You("get a slight %sache.", body_part(HEAD));
        else if (dmg <= 10)
            Your("brain is on fire!");
        else if (dmg <= 20)
            Your("%s suddenly aches painfully!", body_part(HEAD));
        else
            Your("%s suddenly aches very painfully!", body_part(HEAD));
        break;
    default:
        impossible("mcastu: invalid magic spell (%d)", spellnum);
        dmg = 0;
        break;
    }

    if (dmg)
        mdamageu(mtmp, dmg);
}

DISABLE_WARNING_FORMAT_NONLITERAL

static void
cast_cleric_spell(struct monst *mtmp, int dmg, int spellnum)
{
    if (dmg == 0 && !is_undirected_spell(AD_CLRC, spellnum)) {
        impossible("cast directed cleric spell (%d) with dmg=0?", spellnum);
        return;
    }

    switch (spellnum) {
    case CLC_GEYSER:
        /* this is physical damage (force not heat),
         * not magical damage or fire damage
         */
        if (mtmp->data->mlet == S_DEMON) {
            pline("A wall of water washes over you!");
            dmg += d(4, 3);
        }
        else {
            pline("A sudden geyser slams into you from nowhere!");
            dmg = d(8, 6);
        }
        if (Half_physical_damage)
            dmg = (dmg + 1) / 2;
        struct obj *otmp;
        dilutive_force = (dmg > 24) ? 2 : 1;
        dilutive_force *= (mtmp->m_lev > 10 + rn2(10)) ? 2 : 1;
        for (otmp = gi.invent; otmp; otmp = otmp->nobj) {
            /* if (otmp->lamplit)
                (void) splash_lit(otmp); */
            water_damage(otmp, (char *) 0, FALSE);
        }
        dilutive_force = 0;
        break;
    case CLC_FIRE_PILLAR:
        if (mtmp->data->mlet == S_DEMON) {
            You("are enveloped by fire!");
            dmg += d(4, 3);
        }
        else {
            pline("A pillar of fire strikes all around you!");
            dmg = d(8, 6);
        }
        if (Fire_resistance) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_FIRE);
            dmg = resist_damage(AD_FIRE, dmg);
        }
        if (Half_spell_damage)
            dmg = (dmg + 1) / 2;
        burn_away_slime();
        (void) burnarmor(&gy.youmonst);
        destroy_item(SCROLL_CLASS, AD_FIRE);
        destroy_item(POTION_CLASS, AD_FIRE);
        destroy_item(SPBOOK_CLASS, AD_FIRE);
        ignite_items(gi.invent);
        (void) burn_floor_objects(u.ux, u.uy, TRUE, FALSE);
        break;
    case CLC_LIGHTNING: {
        boolean reflects;
        if (mtmp->data->mlet == S_DEMON) {
            You("are hit by arcing bolts of electricity!");
            dmg += d(4, 3);
        }
        else {
            pline("A bolt of lightning strikes down at you from above!");
            dmg = d(8, 6);
            reflects = ureflects("It bounces off your %s%s.", "");
            if (reflects) {
                shieldeff(u.ux, u.uy);
                monstseesu(M_SEEN_REFL);
                dmg = 0;
                break;
            }
        }
        if (Shock_resistance) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_ELEC);
            dmg = resist_damage(AD_ELEC, dmg);
        }
        if (Half_spell_damage)
            dmg = (dmg + 1) / 2;
        destroy_item(WAND_CLASS, AD_ELEC);
        destroy_item(RING_CLASS, AD_ELEC);
        (void) flashburn((long) rnd(100));
        break;
    }
    case CLC_CURSE_ITEMS:
        You_feel("as if you need some help.");
        rndcurse();
        dmg = 0;
        break;
    case CLC_INSECTS: {
        /* Try for insects, and if there are none
           left, go for (sticks to) snakes.  -3. */
        struct permonst *pm = mkclass(S_ANT, 0);
        struct monst *mtmp2 = (struct monst *) 0;
        char whatbuf[QBUFSZ], let = (pm ? S_ANT : S_SNAKE);
        boolean success = FALSE, seecaster;
        int i, quan, oldseen, newseen;
        coord bypos;
        const char *fmt, *what;

        oldseen = monster_census(TRUE);
        quan = (mtmp->m_lev < 2) ? 1 : rnd((int) mtmp->m_lev / 2);
        if (quan < 3)
            quan = 3;
        for (i = 0; i <= quan; i++) {
            if (!enexto(&bypos, mtmp->mux, mtmp->muy, mtmp->data))
                break;
            if (let == S_ANT && rn2(mtmp->m_lev + 2) > rn2(20) && (mtmp2 = makemon(&mons[PM_BULLET_ANT], bypos.x, bypos.y, MM_ANGRY | MM_NOMSG))) {
                success = TRUE;
                mtmp2->msleeping = mtmp2->mpeaceful = mtmp2->mtame = 0;
                set_malign(mtmp2);
            } else if ((pm = mkclass(let, 0)) != 0
                && (mtmp2 = makemon(pm, bypos.x, bypos.y, MM_ANGRY | MM_NOMSG))
                   != 0) {
                success = TRUE;
                mtmp2->msleeping = mtmp2->mpeaceful = mtmp2->mtame = 0;
                set_malign(mtmp2);
            }
        }
        newseen = monster_census(TRUE);

        /* not canspotmon() which includes unseen things sensed via warning */
        seecaster = canseemon(mtmp) || tp_sensemon(mtmp) || Detect_monsters;
        what = (let == S_SNAKE) ? "snakes" : "insects";
        if (Hallucination)
            what = makeplural(bogusmon(whatbuf, (char *) 0));

        fmt = 0;
        if (!seecaster) {
            if (newseen <= oldseen || Unaware) {
                /* unseen caster fails or summons unseen critters,
                   or unconscious hero ("You dream that you hear...") */
                You_hear("someone summoning %s.", what);
            } else {
                char *arg;

                if (what != whatbuf)
                    what = strcpy(whatbuf, what);
                /* unseen caster summoned seen critter(s) */
                arg = (newseen == oldseen + 1) ? an(makesingular(what))
                                               : whatbuf;
                if (!Deaf)
                    You_hear("someone summoning something, and %s %s.", arg,
                             vtense(arg, "appear"));
                else
                    pline("%s %s.", upstart(arg), vtense(arg, "appear"));
            }

        /* seen caster, possibly producing unseen--or just one--critters;
           hero is told what the caster is doing and doesn't necessarily
           observe complete accuracy of that caster's results (in other
           words, no need to fuss with visibility or singularization;
           player is told what's happening even if hero is unconscious) */
        } else if (!success) {
            fmt = "%s casts at a clump of sticks, but nothing happens.%s";
            what = "";
        } else if (let == S_SNAKE) {
            fmt = "%s transforms a clump of sticks into %s!";
        } else if (Invis && !perceives(mtmp->data)
                   && (mtmp->mux != u.ux || mtmp->muy != u.uy)) {
            fmt = "%s summons %s around a spot near you!";
        } else if (Displaced && (mtmp->mux != u.ux || mtmp->muy != u.uy)) {
            fmt = "%s summons %s around your displaced image!";
        } else {
            fmt = "%s summons %s!";
        }
        if (fmt)
            pline(fmt, Monnam(mtmp), what);

        dmg = 0;
        break;
    }
    case CLC_BLIND_YOU:
        /* note: resists_blnd() doesn't apply here */
        if (!Blinded) {
            int num_eyes = eyecount(gy.youmonst.data);

            pline("Scales cover your %s!", (num_eyes == 1)
                                               ? body_part(EYE)
                                               : makeplural(body_part(EYE)));
            make_blinded(Half_spell_damage ? 100L : 200L, FALSE);
            if (!Blind)
                Your1(vision_clears);
            dmg = 0;
        } else
            impossible("no reason for monster to cast blindness spell?");
        break;
    case CLC_PARALYZE:
        if (Antimagic || Free_action) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            if (gm.multi >= 0)
                You("stiffen briefly.");
            dmg = 1; /* to produce nomul(-1), not actual damage */
        } else {
            if (gm.multi >= 0)
                You("are frozen in place!");
            dmg = 4 + (int) mtmp->m_lev;
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
        }
        nomul(-dmg);
        gm.multi_reason = "paralyzed by a monster";
        gn.nomovemsg = 0;
        dmg = 0;
        break;
    case CLC_CONFUSE_YOU:
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            You_feel("momentarily dizzy.");
        } else {
            boolean oldprop = !!Confusion;

            dmg = (int) mtmp->m_lev;
            if (Half_spell_damage)
                dmg = (dmg + 1) / 2;
            make_confused(HConfusion + dmg, TRUE);
            if (Hallucination)
                You_feel("%s!", oldprop ? "trippier" : "trippy");
            else
                You_feel("%sconfused!", oldprop ? "more " : "");
        }
        dmg = 0;
        break;
    case CLC_CURE_SELF:
        dmg = m_cure_self(mtmp, dmg);
        break;
    case CLC_OPEN_WOUNDS:
        if (Antimagic) {
            shieldeff(u.ux, u.uy);
            monstseesu(M_SEEN_MAGR);
            dmg = (dmg + 1) / 2;
        }
        if (dmg <= 5)
            Your("skin itches badly for a moment.");
        else if (dmg <= 10)
            pline("Wounds appear on your body!");
        else if (dmg <= 20)
            pline("Severe wounds appear on your body!");
        else
            Your("body is covered with painful wounds!");
        break;
    default:
        impossible("mcastu: invalid clerical spell (%d)", spellnum);
        dmg = 0;
        break;
    }

    if (dmg)
        mdamageu(mtmp, dmg);
}

RESTORE_WARNING_FORMAT_NONLITERAL

static void
cast_elven_spell(struct monst *mtmp, int dmg, int spellnum)
{
    if (dmg == 0 && !is_undirected_spell(AD_ELVN, spellnum)) {
        impossible("cast directed elven spell (%d) with dmg=0?", spellnum);
        return;
    }

    switch (spellnum) {
    case MGC_DISAPPEAR: /* makes self invisible */
        if (!mtmp->minvis && !mtmp->invis_blkd) {
            if (canseemon(mtmp))
                pline("%s suddenly %s!", Monnam(mtmp),
                      !See_invisible ? "disappears" : "becomes transparent");
            mon_set_minvis(mtmp);
            if (cansee(mtmp->mx, mtmp->my) && !canspotmon(mtmp))
                map_invisible(mtmp->mx, mtmp->my);
            dmg = 0;
        } else
            impossible("no reason for monster to cast disappear spell?");
        break;
    case MGC_HASTE_SELF:
        mon_adjust_speed(mtmp, 1, (struct obj *) 0);
        dmg = 0;
        break;
    case MGC_CURE_SELF:
        dmg = m_cure_self(mtmp, dmg);
        break;
    case LAST_MGC + LAST_CLC + ELV_ENCHANT_ITEM:
        m_enchant_item(mtmp);
        break;
    case LAST_MGC + LAST_CLC + ELV_BLESS_ITEM:
        m_bless_item(mtmp);
        break;
    case LAST_MGC + LAST_CLC + ELV_SLEEP:
        if (Sleep_resistance) {
            shieldeff(u.ux, u.uy);
            You("don't feel sleepy.");
            monstseesu(M_SEEN_SLEEP);
        } else {
            You("are put to sleep!");
            fall_asleep(-d(6, 25), TRUE);
        }
        dmg = 0;
        break;
    case LAST_MGC + LAST_CLC + ELV_PROTECTION:
        m_protection(mtmp);
        break;
    case -1:
        return;
    default:
        impossible("mcastu: invalid elven spell (%d)", spellnum);
        dmg = 0;
        break;
    }

    if (dmg && !is_undirected_spell(AD_ELVN, spellnum))
        mdamageu(mtmp, dmg);
}

static int
cast_djinni_spell(struct monst *mtmp, int dmg, int spellnum)
{
    if (dmg == 0 && !is_undirected_spell(AD_DJIN, spellnum)) {
        impossible("cast directed djinni spell (%d) with dmg=0?", spellnum);
        return -1;
    }
    if (spellnum < LAST_MGC) {
        cast_wizard_spell(mtmp, dmg, spellnum);
        return 1;
    }
    spellnum -= LAST_MGC;
    if (spellnum < LAST_CLC) {
        cast_cleric_spell(mtmp, dmg, spellnum);
        return 1;
    }
    spellnum -= LAST_CLC;
    if (spellnum < LAST_ELV) {
        cast_elven_spell(mtmp, dmg, spellnum);
        return 1;
    }
    spellnum -= LAST_ELV;

    boolean stop_monster = 0;
    if (spellnum != DJN_DEBRIS)
        dmg = 0;
    switch (spellnum) {
    case DJN_DEBRIS:
        You("are pummeled by rocks.");
        dmg = armor_reduction(dmg);
        dmg = Maybe_Half_Phys(dmg);
        struct obj *obj;
        obj = mksobj(ROCK, TRUE, FALSE);
        if (!flooreffects(obj, u.ux, u.uy, "fall")) {
            place_object(obj, u.ux, u.uy);
            stackobj(obj);
        }
        break;
    case DJN_MAKE_PIT:
        stop_monster = m_make_pit(mtmp);
        dmg = 0;
        break;
    case DJN_HALLUCINATE:
        dmg = 0;
        long val = (HHallucination & TIMEOUT) + (long) rn1(20, 60);
        if (val >= TIMEOUT)
            val = TIMEOUT;
        else if (val < 1)
            val = 0;
        (void) make_hallucinated(val, TRUE, 0L);
        break;
    case DJN_MAKE_GOLEM:
        dmg = 0;
        struct permonst *pm = mkclass(S_GOLEM, 0);
        if (!pm)
            break;
        struct monst *mtmp2 = (struct monst *) 0;
        boolean success = FALSE, partial_success = FALSE, seecaster;
        int oldseen, newseen;
        coord bypos;
        char what[BUFSZ], outof[BUFSZ];
            
        oldseen = monster_census(TRUE);
        if (!enexto(&bypos, mtmp->mx, mtmp->my, mtmp->data))
            break;
        if ((mtmp2 = makemon(pm, bypos.x, bypos.y, MM_ANGRY | MM_NOMSG)) != 0) {
            partial_success = TRUE;
            if (rn2(mtmp->m_lev + 2) < rn2(mtmp2->m_lev + 2))
                unmakemon(mtmp2, NO_MM_FLAGS); /* confusingly, this seems to mean the golem's creation is not counted
                                                which is probably what we want, but fortunately either outcome is ok */
            else {
                success = TRUE;
                mtmp2->msleeping = mtmp2->mpeaceful = mtmp2->mtame = 0;
                set_malign(mtmp2);
            }
        }
        if (!partial_success)
            break;
        newseen = monster_census(TRUE);

        /* not canspotmon() which includes unseen things sensed via warning */
        seecaster = canseemon(mtmp) || tp_sensemon(mtmp) || Detect_monsters;
        if (Hallucination) {
            bogusmon(what, (char *) 0);
            sprintf(outof, "gloop");
        }
        else {
            sprintf(what, "a golem");
            sprintf(outof, "%s", mtmp2->data->pmnames[NEUTRAL]);
            for (unsigned int j = 0; j < strlen(outof); j++)
                if(outof[j] == ' ') {
                    outof[j] = '\0';
                    break;
                }
        }

        if (!seecaster) {
            if (newseen <= oldseen || Unaware) {
                /* unseen caster fails or summons unseen golem,
                   or unconscious hero ("You dream that you hear...") */
                You_hear("someone summoning %s.", what);
            } else {
                char *arg;

                /* unseen caster summoned seen golem */
                arg = what;
                if (!Deaf)
                    You_hear("someone summoning something, and %s %s.", arg,
                             vtense(arg, "appear"));
                else
                    pline("%s %s.", upstart(arg), vtense(arg, "appear"));
            }

        
        /* seen caster, possibly producing unseen golem;
           hero is told what the caster is doing and doesn't necessarily
           observe complete accuracy of that caster's results (in other
           words, no need to fuss with visibility or singularization;
           player is told what's happening even if hero is unconscious) */
        } else if (!success) {
            pline("%s casts at a clump of %s, but nothing happens.", Monnam(mtmp), outof);
        } else {
            pline("%s transforms a clump of %s into %s!", Monnam(mtmp), outof, what);
        }
        break;
    case DJN_PIN_ARMS:
        dmg = 0;
        set_pinned_arms(rn2(mtmp->m_lev + 2) + 1);
        Your("%s are frozen in place.", makeplural(body_part(ARM)));
        break;
    case DJN_FLESH_TO_STONE:
        dmg = 0;
        if (!(poly_when_stoned(gy.youmonst.data) && polymon(PM_STONE_GOLEM))) {
            int kformat = KILLED_BY_AN;
            const char *kname = pmname(mtmp->data, Mgender(mtmp));
            
            if (mtmp->data->bani & G_UNIQ) { /* false */
                if (!type_is_pname(mtmp->data))
                    kname = the(kname);
                kformat = KILLED_BY;
            }
            make_stoned(5L, (char *) 0, kformat, kname);
        }
        break;
    case DJN_BALEFUL_POLYMORPH:
        dmg = 0;
        if (polymon(PM_NEWT)) {
            mtmp->mpeaceful = TRUE;
            stop_monster = TRUE;
        }
        break;
    case DJN_WARD_ELEMENTS:
        dmg = 0;
        int desired[8];
        int ndesired = 0;
        for (int i = 1; i <= 8; i++)
            if ((mtmp->mwantedintrinsics & (1 << (i - 1))) && !active_res(mtmp, i))
                desired[ndesired++] = i;
        if (ndesired == 0)
            break;
        int chosen = desired[rn2(ndesired)];
        actually_givit(mtmp, chosen, canseemon(mtmp), TRUE);
        break;
    case DJN_CURSE_YOU:
        dmg = 0;
        if (Serendipitous)
            You("no longer feel like everything is going your way.");
        else
            You_feel("like things are going to go badly for you.");
        incr_itimeout(&ESerendipitous, rn1(10, 10));
        break;
    case DJN_STEAL_JEWELRY:
        dmg = 0;
        int tmp = 0;
        struct obj *otmp;
        int not_worn_bonus = 5 - mtmp->m_lev / 5;
        if (not_worn_bonus < 1)
            not_worn_bonus = 1;
        for (otmp = gi.invent; otmp; otmp = otmp->nobj)
            if (otmp->oclass == AMULET_CLASS || otmp->oclass == RING_CLASS)
                tmp += (otmp->owornmask & W_ACCESSORY) ? 1 : not_worn_bonus;
        if (!tmp)
            break;
        tmp = rn2(tmp);
        for (otmp = gi.invent; otmp; otmp = otmp->nobj)
            if (otmp->oclass == AMULET_CLASS || otmp->oclass == RING_CLASS) {
                tmp -= (otmp->owornmask & W_ACCESSORY) ? 1 : not_worn_bonus;
                if (tmp < 0)
                    break;
            }
        char objbuf[BUFSZ];
        sprintf(objbuf, "%s", Yname2(otmp));
        char *pointtoobjname = objbuf;
        if (strncmp(objbuf, "Your ", 5) == 0) {
            objbuf[1] = 'T';
            objbuf[2] = 'h';
            objbuf[3] = 'e';
            pointtoobjname++;
        }
        if (otmp->owornmask & W_ACCESSORY) {
            if (otmp->oclass == AMULET_CLASS)
                urgent_pline("%s slips off your %s and floats to %s.", pointtoobjname, body_part(NECK), mon_nam(mtmp));
            else
                urgent_pline("%s slips off your %s %s and floats to %s.", pointtoobjname, (otmp == uright) ? "right" : "left", body_part(FINGER), mon_nam(mtmp));
            remove_worn_item(otmp, TRUE);
        } else {
            if (!canspotmon(mtmp))
                urgent_pline("%s floats away... into their clutches.", Yname2(otmp));
            else
                urgent_pline("%s floats away... into the clutches of %s.", Yname2(otmp), mon_nam(mtmp));
        }
        freeinv(otmp);
        if (steal_powerful) {
            if (last_powerful_message >= gm.moves - 10 && positive_message == -1)
                You("feel even less powerful!");
            else
                You("feel less powerful!");
            positive_message = -1;
            last_powerful_message = gm.moves;
            steal_powerful = 0;
        }
        (void) encumber_msg();
        (void) mpickobj(mtmp, otmp); /* may free otmp */
        break;

    case -1:
        return -1;
    default:
        impossible("mcastu: invalid djinni spell (%d)", spellnum);
        dmg = 0;
        break;
    }

    if (dmg && !is_undirected_spell(AD_DJIN, spellnum))
        mdamageu(mtmp, dmg);
    return stop_monster;
}

static boolean
is_undirected_spell(unsigned int adtyp, int spellnum)
{
    if (adtyp == AD_SPEL) {
        switch (spellnum) {
        case MGC_CLONE_WIZ:
        case MGC_SUMMON_MONS:
        case MGC_AGGRAVATION:
        case MGC_DISAPPEAR:
        case MGC_HASTE_SELF:
        case MGC_CURE_SELF:
            return TRUE;
        default:
            break;
        }
    } else if (adtyp == AD_CLRC) {
        switch (spellnum) {
        case CLC_INSECTS:
        case CLC_CURE_SELF:
            return TRUE;
        default:
            break;
        }
    }
    else if (adtyp == AD_ELVN) {
        switch (spellnum) {
        case MGC_DISAPPEAR:
        case MGC_HASTE_SELF:
        case MGC_CURE_SELF:
        case LAST_MGC + LAST_CLC + ELV_ENCHANT_ITEM:
        case LAST_MGC + LAST_CLC + ELV_BLESS_ITEM:
        case LAST_MGC + LAST_CLC + ELV_PROTECTION:
            return TRUE;
        default:
            break;
        }
    }
    else if (adtyp == AD_DJIN) {
        if (spellnum < LAST_MGC)
            return is_undirected_spell(AD_SPEL, spellnum);
        spellnum -= LAST_MGC;
        if (spellnum < LAST_CLC)
            return is_undirected_spell(AD_CLRC, spellnum);
        spellnum -= LAST_CLC;
        if (spellnum < LAST_ELV)
            return is_undirected_spell(AD_ELVN, spellnum);
        spellnum -= LAST_ELV;
        switch (spellnum) {
        case DJN_MAKE_GOLEM:
        case DJN_WARD_ELEMENTS:
            return TRUE;
        default:
            break;
        }
    }
    return FALSE;
}

/* Some spells are useless under some circumstances. */
static boolean
spell_would_be_useless(struct monst *mtmp, unsigned int adtyp, int spellnum)
{
    /* Some spells don't require the player to really be there and can be cast
     * by the monster when you're invisible, yet still shouldn't be cast when
     * the monster doesn't even think you're there.
     * This check isn't quite right because it always uses your real position.
     * We really want something like "if the monster could see mux, muy".
     */
    boolean mcouldseeu = couldsee(mtmp->mx, mtmp->my);

    if (adtyp == AD_SPEL) {
        /* demons have other ways of summoning monsters */
        if (mtmp->data->mlet == S_DEMON && spellnum == MGC_SUMMON_MONS)
            return TRUE;
        /* aggravate monsters, etc. won't be cast by peaceful monsters */
        if (mtmp->mpeaceful
            && (spellnum == MGC_AGGRAVATION || spellnum == MGC_SUMMON_MONS
                || spellnum == MGC_CLONE_WIZ))
            return TRUE;
        /* haste self when already fast */
        if (mtmp->permspeed == MFAST && spellnum == MGC_HASTE_SELF)
            return TRUE;
        /* invisibility when already invisible */
        if ((mtmp->minvis || mtmp->invis_blkd) && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* peaceful monster won't cast invisibility if you can't see
           invisible,
           same as when monsters drink potions of invisibility.  This doesn't
           really make a lot of sense, but lets the player avoid hitting
           peaceful monsters by mistake */
        if (mtmp->mpeaceful && !See_invisible && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* healing when already healed */
        if (mtmp->mhp == mtmp->mhpmax && spellnum == MGC_CURE_SELF)
            return TRUE;
        /* don't summon monsters if it doesn't think you're around */
        if (!mcouldseeu && (spellnum == MGC_SUMMON_MONS
                            || (!mtmp->iswiz && spellnum == MGC_CLONE_WIZ)))
            return TRUE;
        if ((!mtmp->iswiz || gc.context.no_of_wizards > 1)
            && spellnum == MGC_CLONE_WIZ)
            return TRUE;
        /* aggravation (global wakeup) when everyone is already active */
        if (spellnum == MGC_AGGRAVATION) {
            /* if nothing needs to be awakened then this spell is useless
               but caster might not realize that [chance to pick it then
               must be very small otherwise caller's many retry attempts
               will eventually end up picking it too often] */
            if (!has_aggravatables(mtmp))
                return rn2(100) ? TRUE : FALSE;
        }
    } else if (adtyp == AD_CLRC) {
        /* summon insects/sticks to snakes won't be cast by peaceful monsters
         */
        if (mtmp->mpeaceful && spellnum == CLC_INSECTS)
            return TRUE;
        /* healing when already healed */
        if (mtmp->mhp == mtmp->mhpmax && spellnum == CLC_CURE_SELF)
            return TRUE;
        /* don't summon insects if it doesn't think you're around */
        if (!mcouldseeu && spellnum == CLC_INSECTS)
            return TRUE;
        /* blindness spell on blinded player */
        if (Blinded && spellnum == CLC_BLIND_YOU)
            return TRUE;
    } else if (adtyp == AD_ELVN) {
        /* haste self when already fast */
        if (mtmp->permspeed == MFAST && spellnum == MGC_HASTE_SELF)
            return TRUE;
        /* invisibility when already invisible */
        if ((mtmp->minvis || mtmp->invis_blkd) && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* peaceful monster won't cast invisibility if you can't see
           invisible,
           same as when monsters drink potions of invisibility.  This doesn't
           really make a lot of sense, but lets the player avoid hitting
           peaceful monsters by mistake */
        if (mtmp->mpeaceful && !See_invisible && spellnum == MGC_DISAPPEAR)
            return TRUE;
        /* healing when already healed */
        if (mtmp->mhp == mtmp->mhpmax && spellnum == MGC_CURE_SELF)
            return TRUE;
        if (mtmp->mprot && spellnum == LAST_MGC + LAST_CLC + ELV_PROTECTION)
            return TRUE;
        /* to make matters a bit fairer, you will get at least one turn before another sleep attack */
        if (u.usleep && spellnum == LAST_MGC + LAST_CLC + ELV_SLEEP)
            return TRUE;
        if (spellnum == LAST_MGC + LAST_CLC + ELV_BLESS_ITEM || spellnum == LAST_MGC + LAST_CLC + ELV_ENCHANT_ITEM) {
            struct obj *obj, *otmp;
            int n = 0;
            for (obj = mtmp->minvent; obj; obj = otmp) {
                otmp = obj->nobj;
                if (is_elven_obj(obj)) {
                    if (spellnum == LAST_MGC + LAST_CLC + ELV_ENCHANT_ITEM && (obj->spe < 3 || (otmp->otyp != ELVEN_MITHRIL_COAT && obj->spe < 5))) {
                        n = 1;
                        break;
                    }
                    if (spellnum == LAST_MGC + LAST_CLC + ELV_BLESS_ITEM && (obj->cursed || !obj->blessed)) {
                        n = 1;
                        break;
                    }
                }
            }
            if (!n)
                return TRUE;
        }
    }
    else if (adtyp == AD_DJIN) {
        if (spellnum < LAST_MGC)
            return spell_would_be_useless(mtmp, AD_SPEL, spellnum);
        spellnum -= LAST_MGC;
        if (spellnum < LAST_CLC)
            return spell_would_be_useless(mtmp, AD_CLRC, spellnum);
        spellnum -= LAST_CLC;
        if (spellnum < LAST_ELV)
            return spell_would_be_useless(mtmp, AD_ELVN, spellnum);
        spellnum -= LAST_ELV;
        if (mtmp->mpeaceful)
            return TRUE;
        if (!mcouldseeu)
            return TRUE;
        if (spellnum == DJN_MAKE_PIT) {
            if (!Is_airlevel(&u.uz) && !Is_waterlevel(&u.uz) && !Underwater && !On_stairs(u.ux, u.uy) && !Levitation && !Flying)
                if (dighole(FALSE, TRUE, (coord *) 0, TRUE)) {
                    struct trap *ttmp;
                    boolean existing_pit = FALSE;
                    if ((ttmp = t_at(u.ux, u.uy)) != 0)
                        if (ttmp->ttyp == PIT || ttmp->ttyp == HOLE)
                            existing_pit = TRUE;
                    if (existing_pit && !Can_dig_down(&u.uz) && !(levl[u.ux][u.uy].candig))
                        return TRUE;
                    return FALSE;
                }
            return TRUE;
        }
        if (spellnum == DJN_DEBRIS) {
            if (passes_rocks(gy.youmonst.data))
                return TRUE;
            if (!Is_rogue_level(&u.uz) && has_ceiling(&u.uz)
                && (!In_endgame(&u.uz) || Is_earthlevel(&u.uz)))
                return FALSE;
            return TRUE;
        }
        if (spellnum == DJN_HALLUCINATE) {
            if (Halluc_resistance || Hallucination)
                return TRUE;
            return FALSE;
        }
        if (spellnum == DJN_PIN_ARMS) {
            if(nohands(gy.youmonst.data))
                return TRUE;
            if (Pinned)
                return TRUE;
            return FALSE;
        }
        if (spellnum == DJN_FLESH_TO_STONE) {
            if (!Stoned && !Stone_resistance)
                return FALSE;
            return TRUE;
        }
        if (spellnum == DJN_BALEFUL_POLYMORPH) {
            if (Antimagic || Polymorph_control || Unchanging)
                return TRUE;
            return FALSE;
        }
        if (spellnum == DJN_WARD_ELEMENTS) {
            for (int i = 1; i <= 8; i++)
                if ((mtmp->mwantedintrinsics & (1 << (i - 1))) && !active_res(mtmp, i))
                    return FALSE;
            return TRUE;
        }
        if (spellnum == DJN_CURSE_YOU) {
            if (ESerendipitous)
                return TRUE;
            return FALSE;
        }
        if (spellnum == DJN_STEAL_JEWELRY) {
            for (struct obj *otmp = gi.invent; otmp; otmp = otmp->nobj)
                if (otmp->oclass == AMULET_CLASS || otmp->oclass == RING_CLASS)
                    return FALSE;
            return TRUE;
        }
    }
    return FALSE;
}

/* monster uses spell (ranged) */
int
buzzmu(register struct monst *mtmp, register struct attack *mattk)
{
    /* don't print constant stream of curse messages for 'normal'
       spellcasting monsters at range */
    if (!BZ_VALID_ADTYP(mattk->adtyp))
        return MM_MISS;

    if (mtmp->mcan || m_seenres(mtmp, cvt_adtyp_to_mseenres(mattk->adtyp))) {
        cursetxt(mtmp, FALSE);
        return MM_MISS;
    }
    if (lined_up(mtmp) && rn2(3)) {
        nomul(0);
        if (canseemon(mtmp))
            pline("%s zaps you with a %s!", Monnam(mtmp),
                  flash_str(BZ_OFS_AD(mattk->adtyp), FALSE));
        buzz(BZ_M_SPELL(BZ_OFS_AD(mattk->adtyp)), (int) mattk->damn, mtmp->mx,
             mtmp->my, sgn(gt.tbx), sgn(gt.tby));
        return MM_HIT;
    }
    return MM_MISS;
}

/*mcastu.c*/
