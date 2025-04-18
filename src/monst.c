/* NetHack 3.7	monst.c	$NHDT-Date: 1616891049 2021/03/28 00:24:09 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.85 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Michael Allison, 2006. */
/* NetHack may be freely redistributed.  See license for details. */

#include "config.h"
#include "permonst.h"
#include "wintype.h"
#include "sym.h"

#ifdef C
#undef C
#endif
#ifdef TEXTCOLOR
#include "color.h"
#define C(color) color
#define HI_DOMESTIC NO_COLOR /* use for player + friendlies */
#define HI_LORD CLR_MAGENTA
#else
#define C(color)
#endif

#define NO_ATTK    \
    {              \
        0, 0, 0, 0 \
    }

#define WT_ELF 800
#define WT_DRAGON 4500

#define MON(nam, sym, lvl, gen, atk, siz, mr1, mr2, flg1, flg2, flg3, d, col, bn) \
    {                                                                      \
        {(const char *) 0, (const char *) 0, nam}, \
        sym, lvl, gen, atk, siz, mr1, mr2, flg1, flg2, flg3, d, C(col)   \
    }

#define MON3(namm, namf, namn, sym, lvl, gen, atk, siz, mr1, mr2, flg1, flg2, flg3, d, col, bn) \
    {                                                                      \
        {namm, namf, namn}, \
        sym, lvl, gen, atk, siz, mr1, mr2, flg1, flg2, flg3, d, C(col)   \
    }
/* LVL() and SIZ() collect several fields to cut down on number of args
 * for MON()
 */
#define LVL(lvl, mov, ac, mr, aln) lvl, mov, ac, mr, aln
#define SIZ(wt, nut, snd, siz) wt, nut, snd, siz
/* ATTK() and A() are to avoid braces and commas within args to MON() */
#define ATTK(at, ad, n, d) \
    {                      \
        at, ad, n, d       \
    }
#define A(a1, a2, a3, a4, a5, a6) \
    {                             \
        a1, a2, a3, a4, a5, a6    \
    }

struct permonst mons_init[NUMMONS + 1] = {
#include "monsters.h"
    /*
     * array terminator
     */
    MON("", 0, LVL(0, 0, 0, 0, 0), (0),
        A(NO_ATTK, NO_ATTK, NO_ATTK, NO_ATTK, NO_ATTK, NO_ATTK),
        SIZ(0, 0, 0, 0), 0, 0, 0L, 0L, 0, 0, 0, 0)
};

void monst_globals_init(void); /* in hack.h but we're using config.h */

struct permonst mons[SIZE(mons_init)];

void
monst_globals_init(void)
{
    memcpy(mons, mons_init, sizeof(mons));
    return;
}

const struct attack c_sa_yes[NATTK] = SEDUCTION_ATTACKS_YES;
const struct attack c_sa_no[NATTK] = SEDUCTION_ATTACKS_NO;

/*monst.c*/
