/* NetHack 3.7	optlist.h */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef OPTLIST_H
#define OPTLIST_H

/*
 *  NOTE:  If you add (or delete) an option, please review:
 *             doc/options.txt
 *
 *         It contains how-to info and outlines some required/suggested
 *         updates that should accompany your change.
 */

static int optfn_boolean(int, int, boolean, char *, char *);
enum OptType { BoolOpt, CompOpt, OthrOpt };
enum Y_N { No, Yes };
enum Off_On { Off, On };
/* Advanced options are only shown in the full, traditional options menu */
enum OptSection {
    OptS_General, OptS_Behavior, OptS_Map, OptS_Status, OptS_Advanced
};

struct allopt_t {
    const char *name;
    enum OptSection section;
    int minmatch;
    int expectedbuf;
    int idx;
    enum optset_restrictions setwhere;
    enum OptType opttyp;
    enum Y_N negateok;
    enum Y_N valok;
    enum Y_N dupeok;
    enum Y_N pfx;
    boolean opt_in_out, *addr;
    int (*optfn)(int, int, boolean, char *, char *);
    const char *alias;
    const char *descr;
    const char *prefixgw;
    boolean initval, has_handler, dupdetected;
};

#endif /* OPTLIST_H */

#if defined(NHOPT_PROTO) || defined(NHOPT_ENUM) || defined(NHOPT_PARSE)
/* clang-format off */
/* *INDENT-OFF* */

#define NoAlias ((const char *) 0)

#if defined(NHOPT_PROTO)
#define NHOPTB(a, sec, b, c, s, i, n, v, d, al, bp) /*empty*/
#define NHOPTC(a, sec, b, c, s, n, v, d, h, al, z)               \
static int optfn_##a(int, int, boolean, char *, char *);
#define NHOPTP(a, sec, b, c, s, n, v, d, h, al, z)               \
static int pfxfn_##a(int, int, boolean, char *, char *);
#define NHOPTO(m, sec, a, b, c, s, n, v, d, al, z)               \
static int optfn_##a(int, int, boolean, char *, char *);

#elif defined(NHOPT_ENUM)
#define NHOPTB(a, sec, b, c, s, i, n, v, d, al, bp) opt_##a,
#define NHOPTC(a, sec, b, c, s, n, v, d, h, al, z)  opt_##a,
#define NHOPTP(a, sec, b, c, s, n, v, d, h, al, z)  pfx_##a,
#define NHOPTO(m, sec, a, b, c, s, n, v, d, al, z)  opt_##a,

#elif defined(NHOPT_PARSE)
#define NHOPTB(a, sec, b, c, s, i, n, v, d, al, bp) \
    { #a, OptS_##sec, 0, b, opt_##a, s, BoolOpt, n, v, d, No, c,        \
      bp, &optfn_boolean, al, (const char *) 0, (const char *) 0, i, 0, 0 },
#define NHOPTC(a, sec, b, c, s, n, v, d, h, al, z) \
    { #a, OptS_##sec, 0, b, opt_##a, s, CompOpt, n, v, d, No, c,        \
      (boolean *) 0, &optfn_##a, al, z, (const char *) 0, Off, h, 0 },
#define NHOPTP(a, sec, b, c, s, n, v, d, h, al, z) \
    { #a, OptS_##sec, 0, b, pfx_##a, s, CompOpt, n, v, d, Yes, c,       \
      (boolean *) 0, &pfxfn_##a, al, z, #a, Off, h, 0 },
#define NHOPTO(m, sec, a, b, c, s, n, v, d, al, z) \
    { m, OptS_##sec, 0, b, opt_##a, s, OthrOpt, n, v, d, No, c,         \
      (boolean *) 0, &optfn_##a, al, z, (const char *) 0, On, On, 0 },

/* this is not reliable because USE_TILES might be defined in a
   multi-interface binary but not apply to the current interface */
#ifdef USE_TILES
#define tiled_map_Def On
#define ascii_map_Def Off
#else
#define ascii_map_Def On
#define tiled_map_Def Off
#endif
#endif

/* B:nm, ln, opt_*, setwhere?, on?, negat?, val?, dup?, hndlr? Alias, bool_p */
/* C:nm, ln, opt_*, setwhere?, negateok?, valok?, dupok?, hndlr? Alias, desc */
/* P:pfx, ln, opt_*, setwhere?, negateok?, valok?, dupok?, hndlr? Alias, desc*/

    /*
     * Most of the options are in alphabetical order; a few are forced
     * to the top of list so that doset() will list them first and
     * all_options_str() will gather them first to write to the top of
     * a new RC file by #saveoptions.
     *
     * windowtype comes first because its value can affect how wc_ and
     * wc2_ options are processed; playmode (for players who can't or
     * don't know how to specify a command line) and name (ditto, more
     * or less) come next; then role, race, gender, align.  Those will
     * be at the top of the file for #saveoptions constructed RC file.
     */
    NHOPTC(windowtype, Advanced, WINTYPELEN, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "windowing system to use (should be specified first)")
    NHOPTC(playmode, Advanced, 8, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "normal play, non-scoring explore mode, or debug mode")
    NHOPTC(name, Advanced, PL_NSIZ, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "your character's name (e.g., name:Merlin-W)")
    NHOPTC(role, Advanced, PL_CSIZ, opt_in, set_gameview,
                Yes, Yes, Yes, No, "character",
                "your starting role (e.g., Barbarian, Valkyrie)")
    NHOPTC(race, Advanced, PL_CSIZ, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias,
                "your starting race (e.g., Human, Elf)")
    NHOPTC(gender, Advanced, 8, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias,
                "your starting gender (male or female)")
    NHOPTC(alignment, Advanced, 8, opt_in, set_gameview,
                Yes, Yes, Yes, No, "align",
                "your starting alignment (lawful, neutral, or chaotic)")
    /* end of special ordering; remainder of entries are in alphabetical order
     */
    NHOPTB(acoustics, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.acoustics)
 /* NHOPTC(align) -- moved to top */
    NHOPTC(align_message, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, No, Yes, NoAlias, "message window alignment")
    NHOPTC(align_status, Advanced, 20, opt_in, set_gameview,
                No, Yes, No, Yes, NoAlias, "status window alignment")
#ifdef WIN32
    NHOPTC(altkeyhandling, Advanced, 20, opt_in, set_in_game,
                No, Yes, No, Yes, "altkeyhandler", "alternative key handling")
#else
    NHOPTC(altkeyhandling, Advanced, 20, opt_in, set_in_config,
                No, Yes, No, Yes, "altkeyhandler", "(not applicable)")
#endif
#ifdef ALTMETA
    NHOPTB(altmeta, Advanced, 0, opt_out, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.altmeta)
#else
    NHOPTB(altmeta, Advanced, 0, opt_out, set_in_config,
                Off, Yes, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(ascii_map, Advanced, 0, opt_in, set_in_game,
                ascii_map_Def, Yes, No, No, NoAlias, &iflags.wc_ascii_map)
    NHOPTB(autodescribe, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &iflags.autodescribe)
    NHOPTB(autodig, Behavior, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.autodig)
    NHOPTB(autoopen, Behavior, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.autoopen)
    NHOPTB(autopickup, Behavior, 0, opt_out, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.pickup)
    NHOPTO("autopickup exceptions", Behavior, o_autopickup_exceptions, BUFSZ,
                opt_in, set_in_game,
                No, Yes, No, NoAlias, "edit autopickup exceptions")
    NHOPTB(autoquiver, Behavior, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.autoquiver)
    NHOPTC(autounlock, Behavior, 80, opt_out, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "action to take when encountering locked door or chest")
    NHOPTO("bind keys", Advanced, o_bind_keys, BUFSZ, opt_in, set_in_game,
                No, Yes, No, NoAlias, "edit key binds")
#if defined(MICRO) && !defined(AMIGA)
    NHOPTB(BIOS, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.BIOS)
#else
    NHOPTB(BIOS, Advanced, 0, opt_in, set_in_config,
                Off, No, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(blind, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, "permablind", &u.uroleplay.blind)
    NHOPTB(bones, Advanced, 0, opt_out, set_in_config,
                On, Yes, No, No, NoAlias, &flags.bones)
#ifdef BACKWARD_COMPAT
    NHOPTC(boulder, Advanced, 1, opt_in, set_in_game,
                No, Yes, No, No, NoAlias,
                "deprecated (use S_boulder in sym file instead)")
#endif
    NHOPTC(catname, Advanced, PL_PSIZ, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "name of your starting pet if it is a kitten")
#ifdef INSURANCE
    NHOPTB(checkpoint, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.ins_chkpt)
#else
    NHOPTB(checkpoint, Advanced, 0, opt_out, set_in_config,
                Off, No, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(cmdassist, Behavior, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &iflags.cmdassist)
    NHOPTB(color, Map, 0, opt_in, set_in_game,
                On, Yes, No, No, "colour", &iflags.wc_color)
    NHOPTB(confirm, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.confirm)
#ifdef CURSES_GRAPHICS
    NHOPTC(cursesgraphics, Advanced, 70, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "load curses display symbols into symset")
#endif
    NHOPTB(dark_room, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.dark_room)
#ifdef BACKWARD_COMPAT
    NHOPTC(DECgraphics, Advanced, 70, opt_in, set_in_config,
                Yes, Yes, No, No, NoAlias,
                "load DECGraphics display symbols into symset")
#endif
    NHOPTB(debug_hunger, Advanced, 0, opt_in, set_wiznofuz,
                Off, Yes, No, No, NoAlias, &iflags.debug_hunger)
    NHOPTB(debug_mongen, Advanced, 0, opt_in, set_wiznofuz,
                Off, Yes, No, No, NoAlias, &iflags.debug_mongen)
    NHOPTB(debug_overwrite_stairs, Advanced, 0, opt_in, set_wiznofuz,
                Off, Yes, No, No, NoAlias, &iflags.debug_overwrite_stairs)
    NHOPTC(disclose, Advanced, sizeof flags.end_disclose * 2,
                opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "the kinds of information to disclose at end of game")
    NHOPTC(dogname, Advanced, PL_PSIZ, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "name of your starting pet if it is a little dog")
    NHOPTC(dungeon, Advanced, MAXDCHARS + 1,opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "list of symbols to use in drawing the dungeon map")
    NHOPTC(effects, Advanced, MAXECHARS + 1, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "list of symbols to use in drawing special effects")
    NHOPTB(eight_bit_tty, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.wc_eight_bit_input)
    NHOPTB(extmenu, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.extmenu)
    NHOPTB(female, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, "male", &flags.female)
    NHOPTB(fireassist, Behavior, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &iflags.fireassist)
    NHOPTB(fixinv, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.invlet_constant)
    NHOPTC(font_map, Advanced, 40, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "font to use in the map window")
    NHOPTC(font_menu, Advanced, 40, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "font to use in menus")
    NHOPTC(font_message, Advanced, 40, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias,
                "font to use in the message window")
    NHOPTC(font_size_map, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "size of the map font")
    NHOPTC(font_size_menu, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "size of the menu font")
    NHOPTC(font_size_message, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "size of the message font")
    NHOPTC(font_size_status, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "size of the status font")
    NHOPTC(font_size_text, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "size of the text font")
    NHOPTC(font_status, Advanced, 40, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "font to use in status window")
    NHOPTC(font_text, Advanced, 40, opt_in, set_gameview,
                Yes, Yes, Yes, No, NoAlias, "font to use in text windows")
    NHOPTB(force_invmenu, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.force_invmenu)
    NHOPTC(fruit, General, PL_FSIZ, opt_in, set_in_game,
                No, Yes, No, No, NoAlias, "name of a fruit you enjoy eating")
    NHOPTB(fullscreen, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.wc2_fullscreen)
 /* NHOPTC(gender) -- moved to top */
    NHOPTC(glyph, Advanced, 40, opt_in, set_in_game,
                No, Yes, Yes, No, NoAlias,
                "set representation of a glyph to a unicode value and color")
    NHOPTB(goldX, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.goldX)
    NHOPTB(guicolor, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &iflags.wc2_guicolor)
    NHOPTB(help, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.help)
    NHOPTB(herecmd_menu, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.herecmd_menu)
#if defined(MAC)
    NHOPTC(hicolor, Advanced, 15, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "same as palette, only order is reversed")
#endif
    NHOPTB(hilite_pet, Map, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.wc_hilite_pet)
    NHOPTB(hilite_pile, Map, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.hilite_pile)
#ifdef STATUS_HILITES
    NHOPTC(hilite_status, Advanced, 13, opt_out, set_in_game,
                Yes, Yes, Yes, No, NoAlias,
                "a status highlighting rule (can occur multiple times)")
#else
    NHOPTC(hilite_status, Advanced, 13, opt_out, set_in_config,
                Yes, Yes, Yes, No, NoAlias, "(not available)")
#endif
    NHOPTB(hitpointbar, Status, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.wc2_hitpointbar)
    NHOPTC(horsename, Advanced, PL_PSIZ, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "name of your starting pet if it is a pony")
#ifdef BACKWARD_COMPAT
    NHOPTC(IBMgraphics, Advanced, 70, opt_in, set_in_config,
                Yes, Yes, No, No, NoAlias,
                "load IBMGraphics display symbols into symset")
#endif
#ifndef MAC
    NHOPTB(ignintr, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.ignintr)
#else
    NHOPTB(ignintr, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(implicit_uncursed, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.implicit_uncursed)
#if 0   /* obsolete - pre-OSX Mac */
    NHOPTB(large_font, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.obsolete)
#endif
    NHOPTB(legacy, Advanced, 0, opt_out, set_in_config,
                On, Yes, No, No, NoAlias, &flags.legacy)
    NHOPTB(lit_corridor, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.lit_corridor)
    NHOPTB(lootabc, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.lootabc)
#if defined(BACKWARD_COMPAT) && defined(MAC_GRAPHICS_ENV)
    NHOPTC(Macgraphics, Advanced, 70, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "load MACGraphics display symbols into symset")
#endif
    NHOPTB(mail, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.biff)
    NHOPTC(map_mode, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, No, No, NoAlias, "map display mode under Windows")
    NHOPTB(mention_decor, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.mention_decor)
    NHOPTB(mention_walls, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.mention_walls)
    NHOPTC(menu_deselect_all, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "deselect all items in a menu")
    NHOPTC(menu_deselect_page, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "deselect all items on this page of a menu")
    NHOPTC(menu_first_page, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "jump to the first page in a menu")
    NHOPTC(menu_headings, Advanced, 4, opt_in, set_in_game,
                No, Yes, No, Yes, NoAlias, "display style for menu headings")
    NHOPTC(menu_invert_all, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "invert all items in a menu")
    NHOPTC(menu_invert_page, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "invert all items on this page of a menu")
    NHOPTC(menu_last_page, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "jump to the last page in a menu")
    NHOPTC(menu_next_page, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "go to the next menu page")
    NHOPTB(menu_objsyms, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.menu_head_objsym)
#ifdef TTY_GRAPHICS
    NHOPTB(menu_overlay, Advanced, 0, opt_in, set_in_game,
                On, Yes, No, No, NoAlias, &iflags.menu_overlay)
#else
    NHOPTB(menu_overlay, Advanced, 0, opt_in, set_in_config,
                Off, No, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTC(menu_previous_page, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "go to the previous menu page")
    NHOPTC(menu_search, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "search for a menu item")
    NHOPTC(menu_select_all, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "select all items in a menu")
    NHOPTC(menu_select_page, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "select all items on this page of a menu")
    NHOPTC(menu_shift_left, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "pan current menu page left")
    NHOPTC(menu_shift_right, Advanced, 4, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "pan current menu page right")
    NHOPTB(menu_tab_sep, Advanced, 0, opt_in, set_wizonly,
                Off, Yes, No, No, NoAlias, &iflags.menu_tab_sep)
    NHOPTB(menucolors, Advanced, 0, opt_in, set_in_game,
                Off, Yes, Yes, No, NoAlias, &iflags.use_menu_color)
    NHOPTO("menu colors", Status, o_menu_colors, BUFSZ, opt_in, set_in_game,
                No, Yes, No, NoAlias, "edit menu colors")
    NHOPTC(menuinvertmode, Advanced, 5, opt_in, set_in_game,
                No, Yes, No, No, NoAlias,
                "experimental behavior of menu inverts")
    NHOPTC(menustyle, Advanced, MENUTYPELEN, opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "user interface for object selection")
    NHOPTO("message types", Advanced, o_message_types, BUFSZ,
                opt_in, set_in_game,
                No, Yes, No, NoAlias, "edit message types")
    NHOPTB(monpolycontrol, Advanced, 0, opt_in, set_wizonly,
                Off, Yes, No, No, NoAlias, &iflags.mon_polycontrol)
    NHOPTC(monsters, Advanced, MAXMCLASSES, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "list of symbols to use for monsters")
    NHOPTC(mouse_support, Advanced, 0, opt_in, set_in_game,
                No, Yes, No, No, NoAlias,
                "game receives click info from mouse")
#if PREV_MSGS /* tty or curses */
    NHOPTC(msg_window, Advanced, 1, opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "control of \"view previous message(s)\" (^P) behavior")
#else
    NHOPTC(msg_window, Advanced, 1, opt_in, set_in_config,
                Yes, Yes, No, Yes, NoAlias, "(not applicable)")
#endif
    NHOPTC(msghistory, Advanced, 5, opt_in, set_gameview,
                Yes, Yes, No, No, NoAlias,
                "number of top line messages to save")
 /* NHOPTC(name) -- moved to top */
#ifdef NEWS
    NHOPTB(news, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.news)
#else
    NHOPTB(news, Advanced, 0, opt_in, set_in_config,
                Off, No, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(nudist, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &u.uroleplay.nudist)
    NHOPTB(null, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.null)
    NHOPTC(number_pad, General, 1, opt_in, set_in_game,
                No, Yes, No, Yes, NoAlias,
                "use the number pad for movement")
    NHOPTC(objects, Advanced, MAXOCLASSES, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "list of symbols to use for objects")
    NHOPTC(packorder, Advanced, MAXOCLASSES, opt_in, set_in_game,
                No, Yes, No, No, NoAlias,
                "the inventory order of the items in your pack")
#ifdef CHANGE_COLOR
#ifndef WIN32
    NHOPTC(palette, Advanced, 15, opt_in, set_in_game,
                No, Yes, No, No, "hicolor",
                "palette (00c/880/-fff is blue/yellow/reverse white)")
#else
    NHOPTC(palette, Advanced, 15, opt_in, set_in_config,
                No, Yes, No, No, "hicolor",
                "palette (adjust an RGB color in palette (color-R-G-B)")
#endif
#endif
    /* prior to paranoid_confirmation, 'prayconfirm' was a distinct option */
    NHOPTC(paranoid_confirmation, Advanced, 28, opt_in, set_in_game,
                Yes, Yes, Yes, Yes, "prayconfirm",
                "extra prompting in certain situations")
    NHOPTB(perm_invent, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.perm_invent)
    NHOPTC(petattr, Advanced, 88, opt_in, set_in_game, /* curses only */
                No, Yes, No, No, NoAlias, "attributes for highlighting pets")
    /* pettype is ignored for some roles */
    NHOPTC(pettype, Advanced, 4, opt_in, set_gameview,
                Yes, Yes, No, No, "pet", "your preferred initial pet type")
    NHOPTC(pickup_burden, Advanced, 20, opt_in, set_in_game,
                No, Yes, No, Yes, NoAlias,
                "maximum burden picked up before prompt")
    NHOPTB(pickup_thrown, Behavior, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.pickup_thrown)
    NHOPTC(pickup_types, Behavior, MAXOCLASSES, opt_in, set_in_game,
                No, Yes, No, Yes, NoAlias,
                "types of objects to pick up automatically")
    NHOPTC(pile_limit, Advanced, 24, opt_in, set_in_game,
                Yes, Yes, No, No, NoAlias,
                "threshold for \"there are many objects here\"")
    NHOPTC(player_selection, Advanced, 12, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "choose character via dialog or prompts")
 /* NHOPTC(playmode) -- moved to top */
    NHOPTB(popup_dialog, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.wc_popup_dialog)
    NHOPTB(preload_tiles, Advanced, 0, opt_out, set_in_config, /* MSDOS only */
                On, Yes, No, No, NoAlias, &iflags.wc_preload_tiles)
    NHOPTB(pushweapon, Behavior, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.pushweapon)
    NHOPTB(quick_farsight, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.quick_farsight)
 /* NHOPTC(race) -- moved to top */
#ifdef MICRO
    NHOPTB(rawio, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.rawio)
#else
    NHOPTB(rawio, Advanced, 0, opt_in, set_in_config,
                Off, No, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(rest_on_space, Advanced, 0, opt_in, set_in_game, Off,
                Yes, No, No, NoAlias, &flags.rest_on_space)
    NHOPTC(roguesymset, Advanced, 70, opt_in, set_in_game,
                No, Yes, No, Yes, NoAlias,
                "load a set of rogue display symbols from symbols file")
 /* NHOPTC(role) -- moved to top */
    NHOPTC(runmode, Advanced, sizeof "teleport", opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "display frequency when `running' or `travelling'")
    NHOPTB(safe_pet, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.safe_dog)
    NHOPTB(safe_wait, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.safe_wait)
    NHOPTB(sanity_check, Advanced, 0, opt_in, set_wizonly,
                Off, Yes, No, No, NoAlias, &iflags.sanity_check)
    NHOPTC(scores, Advanced, 32, opt_in, set_in_game,
                No, Yes, No, No, NoAlias,
                "the parts of the score list you wish to see")
    NHOPTC(scroll_amount, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, No, No, NoAlias,
                "amount to scroll map when scroll_margin is reached")
    NHOPTC(scroll_margin, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, No, No, NoAlias,
                "scroll map when this far from the edge")
    NHOPTB(selectsaved, Advanced, 0, opt_out, set_in_config,
                On, Yes, No, No, NoAlias, &iflags.wc2_selectsaved)
    NHOPTB(showexp, Status, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.showexp)
    NHOPTB(showrace, Map, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.showrace)
#ifdef SCORE_ON_BOTL
    NHOPTB(showscore, Status, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.showscore)
#else
    NHOPTB(showscore, Status, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(silent, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.silent)
    NHOPTB(softkeyboard, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.wc2_softkeyboard)
    NHOPTC(sortdiscoveries, Advanced, 0, opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "preferred order when displaying discovered objects")
    NHOPTC(sortloot, Advanced, 4, opt_in, set_in_game,
                No, Yes, No, Yes, NoAlias,
                "sort object selection lists by description")
    NHOPTB(sortpack, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.sortpack)
    NHOPTC(sortvanquished, Advanced, 0, opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "preferred order when displaying vanquished monsters")
    NHOPTB(sparkle, Map, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.sparkle)
    NHOPTB(splash_screen, Advanced, 0, opt_out, set_in_config,
                On, Yes, No, No, NoAlias, &iflags.wc_splash_screen)
    NHOPTB(standout, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.standout)
    NHOPTB(status_updates, Advanced, 0, opt_out, set_in_config,
                On, Yes, No, No, NoAlias, &iflags.status_updates)
    NHOPTO("status condition fields", Status, o_status_cond, BUFSZ,
                opt_in, set_in_game,
                No, Yes, No, NoAlias, "edit status condition fields")
#ifdef STATUS_HILITES
    NHOPTC(statushilites, Advanced, 20, opt_in, set_in_game,
                Yes, Yes, Yes, No, NoAlias,
                "0=no status highlighting, N=show highlights for N turns")
    NHOPTO("status highlight rules", Status, o_status_hilites, BUFSZ,
                opt_in, set_in_game,
                No, Yes, No, NoAlias, "edit status hilites")
#else
    NHOPTC(statushilites, Advanced, 20, opt_in, set_in_config,
                Yes, Yes, Yes, No, NoAlias, "highlight control")
#endif
    NHOPTC(statuslines, Status, 20, opt_in, set_in_game,
                No, Yes, No, No, NoAlias, "2 or 3 lines for status display")
#ifdef WIN32CON
    NHOPTC(subkeyvalue, Advanced, 7, opt_in, set_in_config,
                No, Yes, Yes, No, NoAlias, "override keystroke value")
#endif
    NHOPTC(suppress_alert, Advanced, 8, opt_in, set_in_game,
                No, Yes, Yes, No, NoAlias,
                "suppress alerts about version-specific features")
    NHOPTC(symset, Map, 70, opt_in, set_in_game,
                No, Yes, No, Yes, NoAlias,
                "load a set of display symbols from symbols file")
    NHOPTC(term_cols, Advanced, 6, opt_in, set_in_config,
                No, Yes, No, No, "termcolumns", "number of columns")
    NHOPTC(term_rows, Advanced, 6, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "number of rows")
    NHOPTC(tile_file, Advanced, 70, opt_in, set_gameview,
                No, Yes, No, No, NoAlias, "name of tile file")
    NHOPTC(tile_height, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, No, No, NoAlias, "height of tiles")
    NHOPTC(tile_width, Advanced, 20, opt_in, set_gameview,
                Yes, Yes, No, No, NoAlias, "width of tiles")
    NHOPTB(tiled_map, Advanced, 0, opt_in, set_in_game,
                tiled_map_Def, Yes, No, No, NoAlias, &iflags.wc_tiled_map)
    NHOPTB(time, Status, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.time)
#ifdef TIMED_DELAY
    NHOPTB(timed_delay, Map, 0, opt_out, set_in_game,
                Off, Yes, No, No, NoAlias, &flags.nap)
#else
    NHOPTB(timed_delay, Map, 0, opt_in, set_in_config,
                Off, No, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(tombstone, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.tombstone)
    NHOPTB(toptenwin, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.toptenwin)
    NHOPTC(traps, Advanced, MAXTCHARS + 1, opt_in, set_in_config,
                No, Yes, No, No, NoAlias,
                "list of symbols to use in drawing traps")
    NHOPTB(travel, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.travelcmd)
#ifdef DEBUG
    NHOPTB(travel_debug, Advanced, 0, opt_out, set_wizonly,
                Off, Yes, No, No, NoAlias, &iflags.trav_debug)
#else
    NHOPTB(travel_debug, Advanced, 0, opt_out, set_wizonly,
                Off, No, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTB(use_darkgray, Advanced, 0, opt_out, set_in_config,
                On, Yes, No, No, NoAlias, &iflags.wc2_darkgray)
    NHOPTB(use_inverse, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &iflags.wc_inverse)
    NHOPTB(use_truecolor, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, "use_truecolour", &iflags.use_truecolor)
    NHOPTC(vary_msgcount, Advanced, 20, opt_in, set_gameview,
                No, Yes, No, No, NoAlias, "show more old messages at a time")
#if defined(NO_VERBOSE_GRANULARITY)
    NHOPTB(verbose, Advanced, 0, opt_out, set_in_game,
                On, Yes, No, No, NoAlias, &flags.verbose)
#endif
#ifdef MSDOS
    NHOPTC(video, Advanced, 20, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "method of video updating")
#endif
#ifdef VIDEOSHADES
    NHOPTC(videocolors, Advanced, 40, opt_in, set_gameview,
                No, Yes, No, No, "videocolours",
                "color mappings for internal screen routines")
    NHOPTC(videoshades, Advanced, 32, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "gray shades to map to black/gray/white")
#endif
#ifdef MSDOS
    NHOPTC(video_width, Advanced, 10, opt_in, set_gameview,
                No, Yes, No, No, NoAlias, "video width")
    NHOPTC(video_height, Advanced, 10, opt_in, set_gameview,
                No, Yes, No, No, NoAlias, "video height")
#endif
#ifdef TTY_TILES_ESCCODES
    NHOPTB(vt_tiledata, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.vt_tiledata)
#else
    NHOPTB(vt_tiledata, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, (boolean *) 0)
#endif
#ifdef TTY_SOUND_ESCCODES
    NHOPTB(vt_sounddata, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, &iflags.vt_sounddata)
#else
    NHOPTB(vt_sounddata, Advanced, 0, opt_in, set_in_config,
                Off, Yes, No, No, NoAlias, (boolean *) 0)
#endif
    NHOPTC(warnings, Advanced, 10, opt_in, set_in_config,
                No, Yes, No, No, NoAlias, "display characters for warnings")
    NHOPTC(whatis_coord, Advanced, 1, opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "show coordinates when auto-describing cursor position")
    NHOPTC(whatis_filter, Advanced, 1, opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias,
                "filter coordinate locations when targeting next or previous")
    NHOPTB(whatis_menu, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.getloc_usemenu)
    NHOPTB(whatis_moveskip, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.getloc_moveskip)
    NHOPTC(windowborders, Advanced, 9, opt_in, set_in_game,
                Yes, Yes, No, Yes, NoAlias, "0 (off), 1 (on), 2 (auto)")
#ifdef WINCHAIN
    NHOPTC(windowchain, Advanced, WINTYPELEN, opt_in, set_in_sysconf,
                No, Yes, No, No, NoAlias, "window processor to use")
#endif
    NHOPTC(windowcolors, Advanced, 80, opt_in, set_gameview,
                No, Yes, No, No, NoAlias,
                "the foreground/background colors of windows")
 /* NHOPTC(windowtype) -- moved to top */
    NHOPTB(wizmgender, Advanced, 0, opt_in, set_wizonly,
                Off, Yes, No, No, NoAlias, &iflags.wizmgender)
    NHOPTB(wizweight, Advanced, 0, opt_in, set_wizonly,
                Off, Yes, No, No, NoAlias, &iflags.wizweight)
    NHOPTB(wraptext, Advanced, 0, opt_in, set_in_game,
                Off, Yes, No, No, NoAlias, &iflags.wc2_wraptext)

    /*
     * Prefix-based Options
     */

    NHOPTP(cond_, Advanced, 0, opt_in, set_hidden,
                Yes, No, Yes, Yes, NoAlias, "prefix for cond_ options")
    NHOPTP(font, Advanced, 0, opt_in, set_hidden,
                Yes, Yes, Yes, No, NoAlias, "prefix for font options")
#if defined(MICRO) && !defined(AMIGA)
    /* included for compatibility with old NetHack.cnf files */
    NHOPTP(IBM_, Advanced, 0, opt_in, set_hidden,
                No, No, Yes, No, NoAlias, "prefix for old micro IBM_ options")
#endif /* MICRO */
#if !defined(NO_VERBOSE_GRANULARITY)
    NHOPTP(verbose, Advanced, 0, opt_out, set_in_game,
                Yes, Yes, Yes, Yes, NoAlias, "suppress verbose messages")
#endif
#undef NoAlias
#undef NHOPTB
#undef NHOPTC
#undef NHOPTP
#undef NHOPTO

/* *INDENT-ON* */
/* clang-format on */
#endif /* NHOPT_PROTO || NHOPT_ENUM || NHOPT_PARSE */

/* end of optlist */
