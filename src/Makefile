#
# This file is generated automatically.  Do not edit.
# Your changes will be lost.  See sys/unix/NewInstall.unx.
# Identify this file:
MAKEFILE_SRC=1

###
### Start hints/macOS.370 PRE
###
# (new segment at source line 15 )
# macOS hints file
#

# note: '#-INCLUDE' is not just a comment; multiw-1 contains sections 1 to 2

#------------------------------------------------------------------------------
# NetHack 3.7  multiw-1.370 $NHDT-Date: 1597332785 2020/08/13 15:33:05 $  $NHDT-Branch: NetHack-3.7 $

# 1. Which windowing interface(s) should be included in this binary?
# One or more of these can be manually uncommented and/or can be specified
# on the 'make' command line.  If none are enabled, tty will be used.
#WANT_WIN_TTY=1
#WANT_WIN_CURSES=1
#WANT_WIN_X11=1
#WANT_WIN_QT=1

# 2. What is the default window system?
# Exactly one of these can be manually uncommented and/or can be specified
# on the 'make' command line.  If none is enabled, the first among
# WANT_WIN_{tty,curses,X11,Qt} that is enabled will become default.
#WANT_DEFAULT=tty
#WANT_DEFAULT=curses
#WANT_DEFAULT=Qt
#WANT_DEFAULT=X11

#end of multiw-1.370
#------------------------------------------------------------------------------

ifneq "$(USEMACPORTS)" "1"
HAVE_HOMEBREW := $(shell expr `which -s brew; echo $$?` = 0)
endif
ifneq "$(USEHOMEBREW)" "1"
HAVE_MACPORTS := $(shell expr `which -s port; echo $$?` = 0)
endif

ifndef LIBXPM
LIBXPM= -L/opt/X11/lib -lXpm
endif

# 4. Other

#-----------------------------------------------------------------------------
# You shouldn't need to change anything below here (in the hints file; if
# you're reading this in Makefile augmented by hints, that may not be true).
#

#------------------------------------------------------------------------------
# NetHack 3.7  multiw-2.370 $NHDT-Date: 1599337709 2020/09/05 20:28:29 $  $NHDT-Branch: NetHack-3.7 $
#
# Sorts out support for multiple window ports (interfaces) to included in the build.
#
# Included from:
#           hints/linux.370
#           hints/macOS.370
#
# The following will be set appropriately following this:
#     - WANT_WIN_XXX  (at least one will be set; default is TTY)
#     - WANT_DEFAULT (set to match one of the enabled WANT_WIN_XXX)
#     - WINCFLAGS
#     - WINSRC
#     - WINOBJ0
#---
# User selections could be specified as combinations of any of the following:
# WIN_WANT_TTY=1, WIN_WANT_CURSES=1, WIN_WANT_QT=1, WIN_WANT_X11=1
# The selections will all be linked into the same binary.
#
# Assuming you have the prerequisite packages mentioned above, you can
# specify, right on the make command line, which window ports (or interfaces)
# to include in your build. Doing it via the make command line means that won't
# have to edit the Makefile.
#
# make WANT_WIN_QT=1 WANT_WIN_X11=1 WANT_WIN_CURSES=1 WANT_WIN_TTY=1 install
#
# Add WANT_DEFAULT=Qt (or other interface) if you want nethack to use
# something other than tty as the default interface.
#

ifdef WANT_WIN_ALL
WANT_WIN_TTY=1
WANT_WIN_CURSES=1
WANT_WIN_X11=1
WANT_WIN_QT=1
else
# Make sure that at least one interface is enabled.
ifndef WANT_WIN_TTY
ifndef  WANT_WIN_CURSES
ifndef   WANT_WIN_X11
ifndef    WANT_WIN_QT
WANT_WIN_TTY=1
endif
endif
endif
endif
endif

ifdef WANT_LIBNH
WANT_DEFAULT=shim
endif

# Make sure that a default interface is specified; this doesn't guarantee
# sanity for something like 'make WANT_WIN_CURSES=1 WANT_DEFAULT=X11' but
# 'makedefs -v' would notice, complain, and quit causing 'make' to quit.
ifndef WANT_DEFAULT
# pick the first one enabled among { tty, curses, X11, Qt }
ifdef WANT_WIN_TTY
WANT_DEFAULT=tty
else
ifdef  WANT_WIN_CURSES
WANT_DEFAULT=curses
else
ifdef   WANT_WIN_X11
WANT_DEFAULT=X11
else
ifdef    WANT_WIN_QT
WANT_DEFAULT=Qt
else
# ? shouldn't be able to get here...
endif
endif
endif
endif
endif

WINCFLAGS=
WINSRC =
WINOBJ0 =
XTRASRC =
XTRAOBJ =

ifdef WANT_WIN_TTY
WINSRC += $(WINTTYSRC)
WINOBJ0 += $(WINTTYOBJ)
else
WINCFLAGS += -DNOTTYGRAPHICS
endif

ifdef WANT_WIN_CURSES
WINCFLAGS += -DCURSES_GRAPHICS
WINSRC += $(WINCURSESSRC)
WINOBJ0 += $(WINCURSESOBJ)
endif

ifdef WANT_WIN_X11
WINCFLAGS += -DX11_GRAPHICS
WINSRC += $(WIINX11SRC)
WINOBJ0 += $(WINX11OBJ)
XTRASRC += tile.c
XTRAOBJ += $(TARGETPFX)tile.o
endif

ifndef WANT_WIN_QT
ifdef WANT_WIN_ALL
WANT_WIN_QT=1
endif
ifdef WANT_WIN_QT4
ifndef WANT_WIN_QT
WANT_WIN_QT=1
endif   # not WANT_WIN_QT
endif   # WANT_WIN_QT4
ifdef WANT_WIN_QT5
ifndef WANT_WIN_QT
WANT_WIN_QT=1
endif   # not WANT_WIN_QT
endif   # WANT_WIN_QT5
ifdef WANT_WIN_QT6
ifndef WANT_WIN_QT
WANT_WIN_QT=1
endif   # not WANT_WIN_QT
endif   # WANT_WIN_QT6
endif   # not def WANT_WIN_QT

ifdef WANT_WIN_QT
# WANT_WIN_QT5 is the default
ifndef WANT_WIN_QT4
ifndef WANT_WIN_QT5
ifndef WANT_WIN_QT6
WANT_WIN_QT5=1
endif   # not WANT_WIN_QT6
endif   # not WANT_WIN_QT5
endif   # not WANT_WIN_QT4
ifdef WANT_WIN_QT4
#Slackware 14.2 puts Qt4 here
#if your Qt4 is elsewhere, change this to match
QT4DIR=/usr/lib64/qt
QTDIR=$(QT4DIR)
endif  # WANT_WIN_QT4
endif   # WANT_WIN_QT

ifdef WANT_WIN_QT
WINCFLAGS += -DQT_GRAPHICS
WINSRC += $(WINQTSRC)
WINOBJ0 += $(WINQTOBJ)
XTRASRC += tile.c
XTRAOBJ += $(TARGETPFX)tile.o
#
ifndef CPLUSPLUS_NEEDED
CPLUSPLUS_NEEDED = 1
endif   # CPLUSPLUS_NEEDED
ifdef WANT_WIN_QT6
CPLUSPLUS_NEED17 = 1
CPLUSPLUS_NEED_DEPSUPPRESS = 1
endif   # WANT_WIN_QT6
endif   # WANT_WIN_QT

ifeq "$(GIT)" "1"
ifndef GITSUBMODULES
GITSUBMODULES=1
endif
endif

ifeq "$(git)" "1"
ifndef GITSUBMODULES
GITSUBMODULES=1
endif
endif

ifeq "$(CPPREGEX)" "1"
REGEXOBJ=$(TARGETPFX)cppregex.o
ifndef CPLUSPLUS_NEEDED
CPLUSPLUS_NEEDED = 1
endif
endif

ifeq "$(cppregex)" "1"
REGEXOBJ=$(TARGETPFX)cppregex.o
ifndef CPLUSPLUS_NEEDED
CPLUSPLUS_NEEDED = 1
endif
endif

#end of hints/include/multiw-2.370
#------------------------------------------------------------------------------


# compiler.370 contains compiler detection and adjustments common
# to both linux and macOS

#------------------------------------------------------------------------------
# NetHack 3.7  compiler.370 $NHDT-Date: 1668359835 2022/11/13 17:17:15 $  $NHDT-Branch: NetHack-3.7 $

# compiler flags:  CCFLAGS is used to construct a value for CFLAGS with
#	various -I, -D, and -W settings appended below;
#	these are the settings of most interest for an end-user build
#	(clang doesn't support '-Og', gcc needs 4.x or later)
CCFLAGS = -g
#CCFLAGS = -g -Og
#CCFLAGS = -O2
#	Note: this is not the usual 'CFLAGS' which is used in default
#	rules for compiling C code; specifying a value for that on the
#	'make' command line should be avoided.

#If you want to force use of one particular set of compilers, do it
#here, ahead of the detection, so that the detection will match your
#choice and set variables CCISCLANG, GCCGTEQ, CLANGPPGTEQ9 etc.
#accordingly.
#
#CC= gcc
#CXX= g++ -std-gnu++11
#
#CC= clang
#CXX=clang++ -std=gnu++11
#
# If these are set on entry, preparation for C++ compiles is affected.
#    CPLUSPLUS_NEEDED = 1           C++ compile bits included
#    CPLUSPLUS_NEED17 = 1           C++ -std=c++17 (at least)
#    CPLUSPLUS_NEED_DEPSUPPRESS = 1 C++ -Wno-deprecated-copy,
#                                       -Wno-deprecated-declarations


# If you want to override the compiler detection just carried out
# uncomment one of the following pairs. Note, however, that
# doing this after the detection above will likely result in
# mismatched variable values for CCISCLANG, GCCGTEQ, CLANGPPGTEQ9 etc.
#
#CC= gcc
#CXX= g++ -std-gnu++11
#
#CC= clang
#CXX=clang++ -std=gnu++11

CFLAGS=$(CCFLAGS) -I../include -DNOTPARMDECL
CFLAGS+=-Wall -Wextra -Wno-missing-field-initializers \
	-Wreturn-type -Wunused -Wformat -Wswitch -Wshadow -Wwrite-strings
CFLAGS+=-pedantic
CFLAGS+=-Wmissing-declarations

# these are left out of the C++ flags
CFLAGS+=-Wformat-nonliteral
CFLAGS+=-Wunreachable-code

#
# the following are not allowed in C++
CFLAGS+=-Wimplicit
CFLAGS+=-Wimplicit-function-declaration
CFLAGS+=-Wimplicit-int
CFLAGS+=-Wmissing-prototypes
CFLAGS+=-Wold-style-definition
CFLAGS+=-Wstrict-prototypes

#detection of clang vs gcc
CCISCLANG := $(shell echo `$(CC) --version` | grep clang)
ifeq "$(CCISCLANG)" ""
# gcc-specific follows
CXX=g++ -std=gnu++11
# get the version of gcc
GCCGTEQ9 := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 9)
GCCGTEQ11 := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 11)
GCCGTEQ12 := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCGTEQ9)" "1"
# flags present in gcc version greater than or equal to 9 can go here
CFLAGS+=-Wformat-overflow
CFLAGS+=-Wmissing-parameter-type
endif   # GCC greater than or equal to 9
#ifeq "$(GCCGTEQ11)" "1"
#endif
#ifeq "$(GCCGTEQ12)" "1"
#endif
# end of gcc-specific
else   # gcc or clang?
CXX=clang++ -std=gnu++11
# clang-specific follows
# none
endif  # clang-specific ends here

ifdef MAKEFILE_SRC
ifdef CPLUSPLUS_NEEDED
CCXXFLAGS = -g -I../include -DNOTPARMDECL
CCXXFLAGS+=-Wall -Wextra -Wno-missing-field-initializers \
        -Wreturn-type -Wunused -Wformat -Wswitch -Wshadow -Wwrite-strings
CCXXFLAGS+=-pedantic
CCXXFLAGS+=-Wmissing-declarations
#detection of clang++ vs g++
CXXISCLANG := $(shell echo `$(CXX) --version` | grep clang)
ifeq "$(CXXISCLANG)" ""
# g++-specific
CCXX=g++ -std=gnu++11
# get the version of g++
GPPGTEQ9 := $(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \>= 9)
GPPGTEQ11 := $(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \>= 11)
GPPGTEQ12 := $(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GPPGTEQ9)" "1"
CCXXFLAGS+=-Wformat-overflow
ifdef CPLUSPLUS_NEED_DEPSUPPRESS
CCXXFLAGS+=-Wno-deprecated-copy
CCXXFLAGS+=-Wno-deprecated-declarations
endif  # CPLUSPLUS_NEED_DEPSUPPRESS
endif  # g++ version greater than or equal to 9
ifeq "$(GPPGTEQ11)" "1"
# the g++ linker will have trouble linking if the following isn't included
# when compiling the C files.
CFLAGS+=-fPIC
endif  # g++ version greater than or equal to 11
ifdef CPLUSPLUS_NEED17
ifeq "$(GPPGTEQ12)" "1"
CCXX=g++ -std=c++20
else   # g++ version greater than or equal to 12? (no follows)
CCXX=g++ -std=c++17
endif  # g++ version greater than or equal to 12
endif  # CPLUSPLUS_NEED17

else   # g++ or clang++ ?

# clang++-specific
CCXX=clang++ -std=c++11
# get the version of clang++
CLANGPPGTEQ9 := $(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \>= 9)
CLANGPPGTEQ11 := $(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \>= 11)
CLANGPPGTEQ14 := $(shell expr `$(CXX) -dumpversion | cut -f1 -d.` \>= 14)
ifeq "$(CLANGPPGTEQ9)" "1"
#CCXXFLAGS+=-Wformat-overflow
endif
ifdef CPLUSPLUS_NEED_DEPSUPPRESS
CCXXFLAGS+=-Wno-deprecated
CCXXFLAGS+=-Wno-deprecated-declarations
endif  # CPLUSPLUS_NEED_DEPSUPPRESS
# The clang++ linker seems to have trouble linking if the following isn't
# included when compiling the C files by clang..
CFLAGS+=-fPIC
ifdef CPLUSPLUS_NEED17
ifeq "$(CLANGPPGTEQ14)" "1"
CCXX=clang++ -std=c++20
else
CCXX=clang++ -std=c++17
endif  # clang++ greater than or equal to 14
endif  # CPLUSPLUS_NEED17
endif  # end of clang++-specific section
CXX=$(CCXX)
endif  # CPLUSPLUS_NEEDED

endif   # MAKEFILE_SRC

#end of compiler.370
#------------------------------------------------------------------------------

ifdef WANT_WIN_QT
ifeq "$(HAVE_HOMEBREW)" "1"
ifdef WANT_WIN_QT5
# Qt5 installed via homebrew
QTDIR :=$(shell brew --prefix)/opt/qt@5
endif   # WANT_WIN_QT5
ifdef WANT_WIN_QT6
QTDIR :=$(shell brew --prefix)/opt/qt@6
endif   # WANT_WIN_QT6
endif   # HAVE_HOMEBREW
ifndef QTDIR
ifeq "$(HAVE_MACPORTS)" "1"
# Qt installed via macports
ifdef WANT_WIN_QT5
QTDIR=/opt/local/libexec/qt5
endif   # WANT_WIN_QT5
ifdef WANT_WIN_QT6
QTDIR=/opt/local/libexec/qt6
endif   # WANT_WIN_QT6
endif   # HAVE_MACPORTS
endif   # QTDIR
endif   # WANT_WIN_QT

# multiw-3.370 must come after compiler.370
# and after QTDIR is defined

#------------------------------------------------------------------------------
# NetHack 3.7  multiw-3.370 $NHDT-Date: 1668359836 2022/11/13 17:17:16 $  $NHDT-Branch: NetHack-3.7 $
#
# Further set-up  for multiple window ports (interfaces) that comes after compiler.370.
#
# Included from:
#           hints/linux.370
#           hints/macOS.370
#

# This ensures that .moc files are compatible with the version of Qt chosen.
#
ifdef MAKEFILE_SRC
ifdef WANT_WIN_QT
# when switching from Qt5 to Qt6 or vice versa, any old .moc files will be
# incompatible; get rid of them in case user hasn't run 'make spotless';
# object files are incompatable with Qt library, so get rid of them too;
# Qt*.h-t are empty timestamp files and at most one should exist
QTany_H = Qt*.h-t
ifdef WANT_WIN_QT6
# Qt 6 builds and runs (with a couple of warnings) but needs more testing
QTn_H = Qt6.h-t
else
# Qt 5 is currently the default version for nethack 3.7.x's Qt interface
QTn_H = Qt5.h-t
endif
$(QTn_H) ::
	@if test ! -f $@; then ( rm -f $(QTany_H) *.moc qt_*.o; touch $@ ); fi;
endif #WANT_WIN_QT
endif #MAKFILE_SRC

ifdef WANT_WIN_TTY
USE_CURSESLIB=1
endif

ifdef WANT_WIN_CURSES
ifneq "$(USE_CURSESLIB)" "1"
USE_CURSESLIB=1
endif
endif

ifeq "$(GIT)" "1"
ifndef GITSUBMODULES
GITSUBMODULES=1
endif
endif

ifeq "$(git)" "1"
ifndef GITSUBMODULES
GITSUBMODULES=1
endif
endif

ifeq "$(CPPREGEX)" "1"
REGEXOBJ=$(TARGETPFX)cppregex.o
ifndef CPLUSPLUS_NEEDED
CPLUSPLUS_NEEDED = 1
endif
endif

ifeq "$(cppregex)" "1"
REGEXOBJ=$(TARGETPFX)cppregex.o
ifndef CPLUSPLUS_NEEDED
CPLUSPLUS_NEEDED = 1
endif
endif

#end of hints/include/multiw-3.370
#------------------------------------------------------------------------------


# NetHack sources control
NHCFLAGS+=-DDLB
NHCFLAGS+=-DHACKDIR=\"$(HACKDIR)\"
NHCFLAGS+=-DDEFAULT_WINDOW_SYS=\"$(WANT_DEFAULT)\"
NHCFLAGS+=-DSYSCF -DSYSCF_FILE=\"$(HACKDIR)/sysconf\" -DSECURE
#NHCFLAGS+=-DTIMED_DELAY
#NHCFLAGS+=-DDUMPLOG
#NHCFLAGS+=-DCONFIG_ERROR_SECURE=FALSE
NHCFLAGS+=-DGREPPATH=\"/usr/bin/grep\"
#NHCFLAGS+=-DCOMPRESS=\"/bin/gzip\" -DCOMPRESS_EXTENSION=\".gz\"
NHCFLAGS+=-DNOMAIL
#NHCFLAGS+=-DEXTRA_SANITY_CHECKS
#NHCFLAGS+=-DEDIT_GETLIN
#NHCFLAGS+=-DSCORE_ON_BOTL
#NHCFLAGS+=-DMSGHANDLER
#NHCFLAGS+=-DTTY_TILES_ESCCODES
#NHCFLAGS+=-DTTY_SOUND_ESCCODES
#NHCFLAGS+=-DNO_CHRONICLE
#NHCFLAGS+=-DLIVELOG

ifdef MAKEFILE_SRC
# default
CURSESLIB = -lncurses
ifeq "$(CURSES_UNICODE)" "sys"
NHCFLAGS+=-DCURSES_UNICODE
WINLIB += $(CURSESLIB)
else
ifeq "$(CURSES_UNICODE)" "0"
WINLIB += $(CURSESLIB)
else
ifeq "$(USE_CURSESLIB)" "1"
NHCFLAGS+=-DCURSES_UNICODE
else
# If CURSES_UNICODE is defined, we need ncursesw.
# Without CURSES_UNICODE the following simpler setting works.
# CURSESLIB = -lncurses -ltinfo
comma:=,
NCURSES_LFLAGS = $(shell pkg-config ncursesw --libs)
ifneq (,$(findstring ncurses, $(NCURSES_LFLAGS)))
HAVE_NCURSESW=1
else
HAVE_NCURSESW=0
endif
ifeq "$(HAVE_NCURSESW)" "1"
CURSESLIB = $(NCURSES_LFLAGS)
NHCFLAGS+=-DCURSES_UNICODE
else
$(info Attention: CURSES_UNICODE is not being defined without ncursesw)
endif   #HAVE_NCURSESW
endif   #USE_CURSESLIB
ifdef CURSESLIB
PKGCFLAGS=
ifeq "$(HAVE_HOMEBREW)" "1"
HAVE_HOMEBREW_NCURSES := $(shell expr `brew ls --versions ncurses > /dev/null; echo $$?` = 0)
#$(info HAVE_HOMEBREW_NCURSES=$(HAVE_HOMEBREW_NCURSES))
ifeq "$(HAVE_HOMEBREW_NCURSES)" "1"
# Newer versions of ncurses are commonly installed via homebrew, but intentionally unlinked.
HOMEBREW_LFLAGS := -L$(shell brew --prefix)/opt/ncurses/lib
HOMEBREW_WINLIB := -I$(shell brew --prefix)/opt/ncurses/include
HOMEBREW_CFLAGS =
endif   #HAVE_HOMEBREW_NCURSES
endif   #HAVE_HOMEBREW
ifeq "$(HAVE_MACPORTS)" "1"
MACPORTS_CFLAGS = -I/opt/local/include
MACPORTS_LFLAGS = -L/opt/local/lib
CURSESLIB=
ifneq ($(wildcard /opt/local/lib/libncursesw*),)
MACPORTS_WINLIB = -lncursesw
else
MACPORTS_WINLIB = -lncurses
endif
endif   #HAVE_MACPORTS
LFLAGS += $(HOMEBREW_LFLAGS) $(MACPORTS_LFLAGS)
WINLIB += $(HOMEBREW_WINLIB) $(MACPORTS_WINLIB) $(CURSESLIB)
PKGCFLAGS += $(HOMEBREW_CFLAGS) $(MACPORTS_CFLAGS)
endif   #CURSESLIB
WINLIB += $(CURSESLIB)
#$(info WINLIB=$(WINLIB))
#$(info CURSESLIB=$(CURSESLIB))
endif   #CURSES_UNICODE=0
endif   #CURSES_UNIODE=sys
endif   #MAKEFILE_SRC

CFLAGS+= $(PKGCFLAGS) $(WINCFLAGS)  #WINCFLAGS set from multiw-2.370
CFLAGS+= $(NHCFLAGS)

CCXXFLAGS+= $(WINCFLAGS) #WINCFLAGS set from multiw-2.370
CCXXFLAGS+= $(NHCFLAGS)

VARDATND =
VARDATND0 =

ifdef WANT_WIN_CHAIN
HINTSRC=$(CHAINSRC)
HINTOBJ=$(CHAINOBJ)
endif # WANT_WIN_CHAIN

ifdef WANT_WIN_X11
USE_XPM=1
WINX11LIB = -lXaw -lXmu -lXext -lXt -lX11
VARDATND0 += x11tiles NetHack.ad pet_mark.xbm pilemark.xbm
# -x: if built without dodlb, some versions of mkfontdir think *.lev are fonts
POSTINSTALL += bdftopcf win/X11/nh10.bdf > $(HACKDIR)/nh10.pcf; ( cd $(HACKDIR); mkfontdir -x .lev );
# separate from CFLAGS so that we don't pass it to every file
X11CFLAGS = -I/opt/X11/include
# avoid repeated complaints about _X_NONNULL(args...) in <X11/Xfuncproto.h>
X11CFLAGS += -Wno-variadic-macros
ifdef USE_XPM
CFLAGS += -DUSE_XPM
WINX11LIB += -lXpm
VARDATND0 += rip.xpm
endif
WINLIB += $(WINX11LIB)
LFLAGS += -L/opt/X11/lib
endif	# WANT_WIN_X11

ifdef WANT_WIN_QT
LINK = $(CXX)
ifdef WANT_WIN_QT5
# Qt5 requires C++11
QTCXXFLAGS += $(sort $(shell PKG_CONFIG_PATH=$(QTDIR)/lib/pkgconfig \
		pkg-config Qt5Gui Qt5Widgets Qt5Multimedia --cflags))
WINLIB += $(shell PKG_CONFIG_PATH=$(QTDIR)/lib/pkgconfig \
		pkg-config Qt5Gui Qt5Widgets Qt5Multimedia --libs)
endif    # WANT_WIN_QT5
ifdef WANT_WIN_QT6
QTCXXFLAGS += -std=c++17 -I $(QTDIR)/include -I $(QTDIR)/include/QtCore \
		-I $(QTDIR)/include/QtMultimedia
MOC = moc
MOCPATH = $(QTDIR)/share/qt/libexec/moc
WINLIB += -F $(QTDIR)/Frameworks -framework QtCore -framework QtGui \
		-framework QtWidgets -framework QtMultimedia
endif    # WANT_WIN_QT6
VARDATND0 += nhtiles.bmp rip.xpm nhsplash.xpm
# XXX if /Developer/qt exists and QTDIR not set, use that
ifndef QTDIR
$(error QTDIR not defined in the environment or Makefile)
endif	# QTDIR
# XXX make sure QTDIR points to something reasonable
else	# !WANT_WIN_QT
LINK=$(CC)
endif	# !WANT_WIN_QT

# prevent duplicate tile.o in WINOBJ
WINOBJ = $(WINOBJ0) $(sort $(XTRAOBJ))
# prevent duplicates in VARDATND if both X11 and Qt are being supported
VARDATND += $(sort $(VARDATND0))

GIT_HASH := $(shell echo `git rev-parse --verify HEAD` 2>&1)
GIT_BRANCH := $(shell echo `git rev-parse --abbrev-ref HEAD` 2>&1)

ifdef GIT_HASH
GITHASH = -DNETHACK_GIT_SHA=\"$(GIT_HASH)\"
endif
ifdef GIT_BRANCH
GITBRANCH = -DNETHACK_GIT_BRANCH=\"$(GIT_BRANCH)\"
endif 

ifdef WANT_LIBNH
CFLAGS += -DSHIM_GRAPHICS -DNOTTYGRAPHICS -DNOSHELL -DLIBNH
LIBNHSYSSRC = ../sys/libnh/libnhmain.c \
		../sys/share/ioctl.c ../sys/share/unixtty.c \
		../sys/unix/unixunix.c ../sys/unix/unixres.c \
		../win/shim/winshim.c
LIBNHSYSOBJ = $(TARGETPFX)libnhmain.o $(TARGETPFX)ioctl.o \
		$(TARGETPFX)unixtty.o $(TARGETPFX)unixunix.o \
		$(TARGETPFX)unixres.o $(TARGETPFX)winshim.o
#don't bother building the game executable as it will fail
#without winshim
override GAME=
MOREALL += ( cd src ; $(MAKE) pregame ; $(MAKE) $(TARGETPFX)libnh.a )
endif  # WANT_LIBNH

# Lua
# when building liblua.a, avoid warning that use of tmpnam() should be
# replaced by mkstemp(); the lua code doesn't use nethack's config.h so
# this needs to be passed via make rather than defined in unixconf.h
ifdef GITSUBMODULES
LUAFLAGS=CC='$(CC)' MYCFLAGS=' -DLUA_USE_MACOSX'
ifneq "$(CCISCLANG)" ""
# clang
LUAFLAGS +=CWARNGCC=''
endif   # clang
override LUAHEADERS = submodules/lua
override LUA2NHTOP = ../..
override LUAMAKEFLAGS=$(LUAFLAGS)
endif   # GITSUBMODULES

WANT_BUNDLE=1
ifdef WANT_SHARE_INSTALL
# if $GAMEUID is root, we install into roughly proper Mac locations, otherwise
# we install into ~/nethackdir
ifeq ($(GAMEUID),root)
PREFIX:=/Library/NetHack
SHELLDIR=/usr/local/bin
HACKDIR=$(PREFIX)/nethackdir
CHOWN=chown
CHGRP=chgrp
# We run sgid so the game has access to both HACKDIR and user preferences.
GAMEPERM = 02755
else	# ! root
PREFIX:=/Users/$(GAMEUID)
SHELLDIR=$(PREFIX)/bin
HACKDIR=$(PREFIX)/Library/NetHack/nethackdir
CHOWN=/usr/bin/true
CHGRP=/usr/bin/true
GAMEPERM = 0500
endif	# ! root
VARFILEPERM = 0664
VARDIRPERM = 0775
ROOTCHECK= [[ `id -u` == 0 ]] || ( echo "Must run install with sudo."; exit 1)
# XXX it's nice we don't write over sysconf, but we've already erased it
# make sure we have group GAMEUID and group GAMEGRP
PREINSTALL= . sys/unix/hints/macosx.sh user2 $(GAMEUID); \
		. sys/unix/hints/macosx.sh group2 $(GAMEGRP); \
		mkdir $(SHELLDIR); chown $(GAMEUID) $(SHELLDIR)
POSTINSTALL+= sys/unix/hints/macosx.sh editsysconf sys/unix/sysconf $(HACKDIR)/sysconf; \
		$(CHOWN) $(GAMEUID) $(HACKDIR)/sysconf; \
		$(CHGRP) $(GAMEGRP) $(HACKDIR)/sysconf; \
		chmod $(VARFILEPERM) $(HACKDIR)/sysconf;

else ifdef WANT_SOURCE_INSTALL

PREFIX=$(abspath $(NHSROOT))
# suppress nethack.sh
#SHELLDIR=
HACKDIR=$(PREFIX)/playground
CHOWN=/usr/bin/true
CHGRP=/usr/bin/true
GAMEPERM = 0700
VARFILEPERM = 0600
VARDIRPERM = 0700
POSTINSTALL+= sys/unix/hints/macosx.sh editsysconf sys/unix/sysconf $(HACKDIR)/sysconf;
# We can use "make all" to build the whole thing - but it misses some things:
MOREALL=$(MAKE) install
CFLAGS+=-DSYSCF -DSYSCF_FILE=\"$(HACKDIR)/sysconf\" -DSECURE

else	# !WANT_SOURCE_INSTALL

PREFIX:=$(wildcard ~)
SHELLDIR=$(PREFIX)/bin
HACKDIR=$(PREFIX)/nethackdir
CHOWN=/usr/bin/true
CHGRP=/usr/bin/true
GAMEPERM = 0700
VARFILEPERM = 0600
VARDIRPERM = 0700
ifdef ($(WANT_DEFAULT),X11)
# install nethack.rc as ~/.nethackrc if no ~/.nethackrc exists
PREINSTALL= cp -n win/X11/nethack.rc ~/.nethackrc || true
endif	# WANT_DEFAULT X11

POSTINSTALL+= sys/unix/hints/macosx.sh editsysconf sys/unix/sysconf $(HACKDIR)/sysconf; \
		$(CHOWN) $(GAMEUID) $(HACKDIR)/sysconf; \
		$(CHGRP) $(GAMEGRP) $(HACKDIR)/sysconf; \
		chmod $(VARFILEPERM) $(HACKDIR)/sysconf;
ifdef WANT_BUNDLE
#
# Bundle
#
# $(HACKDIR)/$(GAME).app/
#              Contents/
#                 Frameworks/
#                 Info.plist
#                 MacOS/
#                    $(GAME)
#                 PkgInfo/
#                 PlugIns/
#                 Resources/
#                 SharedFrameWorks/
#
BUNDLE = mkdir -p $(HACKDIR)/nethack.app/Contents/MacOS; \
              sys/unix/hints/macosx.sh infoplist > $(HACKDIR)/nethack.app/Contents/Info.plist; \
              mv $(HACKDIR)/nethack $(HACKDIR)/nethack.app/Contents/MacOS/nethack;
ifdef WANT_SHARE_INSTALL
BUNDLE+= chmod $(GAMEPERM) $(HACKDIR)/nethack.app/Contents/MacOS/nethack;
endif

POSTINSTALL+= $(BUNDLE)
POSTINSTALL+= if test -f $(SHELLDIR)/$(GAME); then \
			  sed -i '' 's;HACKDIR/$(GAME);HACKDIR/$(GAME).app/Contents/MacOS/$(GAME);' $(SHELLDIR)/$(GAME) ; fi;
endif   # WANT_BUNDLE
endif   # !WANT_SHARE_INSTALL

INSTDIR=$(HACKDIR)
VARDIR=$(HACKDIR)

# ~/Library/Preferences/NetHack Defaults
# OPTIONS=name:player,number_pad,menustyle:partial,!time,showexp
# OPTIONS=hilite_pet,toptenwin,msghistory:200,windowtype:Qt
#
# Install.Qt mentions a patch for macos - it's not there (it seems to be in the Qt binary
# package under the docs directory).
#
#===============-=================================================
# NetHack 3.7  include/cross-pre $NHDT-Date: 1597332785 2020/08/13 15:33:05 $  $NHDT-Branch: NetHack-3.7 $
#
# Cross-compiling -PRE section
#

ifdef CROSS_TO_MSDOS
CROSS=1
BUILD_TARGET_LUA=1
BUILD_PDCURSES=1
CROSS_SHARED=1
override TARGET = msdos
override TARGETDIR=../targets/$(TARGET)
override TARGETPFX = $(TARGETDIR)/
override TARGET_LIBS=
endif

ifdef CROSS_TO_WASM
CROSS=1
BUILD_TARGET_LUA=1
HACKDIR=/
PREFIX=
override TARGET = wasm
override TARGETDIR=../targets/$(TARGET)
override TARGETPFX = $(TARGETDIR)/
override TARGET_LIBS=
endif

ifdef CROSS
override PREGAME=
override BUILDMORE=
override CLEANMORE=
override PACKAGE=
endif

ifdef BUILD_TARGET_LUA
#===============-=================================================
# LUA library
# Source from http://www.lua.org/ftp/lua-5.4.4.tar.gz
#=================================================================
LUA_VERSION ?=5.4.4
LUATOP ?= ../lib/lua-$(LUA_VERSION)
LUASRCDIR ?= $(LUATOP)/src
LUAOBJFILES1 =  $(TARGETPFX)lapi.o $(TARGETPFX)lauxlib.o \
		$(TARGETPFX)lbaselib.o $(TARGETPFX)lcode.o \
		$(TARGETPFX)lcorolib.o $(TARGETPFX)lctype.o \
		$(TARGETPFX)ldblib.o
ifeq "$(LUA_VERSION)" "5.3.5"
LUAOBJFILES1 += $(TARGETPFX)lbitlib.o
endif
LUAOBJFILES2 =  $(TARGETPFX)ldebug.o $(TARGETPFX)ldo.o $(TARGETPFX)ldump.o \
		$(TARGETPFX)lfunc.o $(TARGETPFX)lgc.o $(TARGETPFX)linit.o \
		$(TARGETPFX)liolib.o $(TARGETPFX)llex.o
LUAOBJFILES3 =  $(TARGETPFX)lmathlib.o $(TARGETPFX)lmem.o \
		$(TARGETPFX)loadlib.o $(TARGETPFX)lobject.o \
		$(TARGETPFX)lopcodes.o $(TARGETPFX)loslib.o \
		$(TARGETPFX)lparser.o $(TARGETPFX)lstate.o
LUAOBJFILES4 =  $(TARGETPFX)lstring.o $(TARGETPFX)lstrlib.o \
		$(TARGETPFX)ltable.o $(TARGETPFX)ltablib.o \
		$(TARGETPFX)ltm.o $(TARGETPFX)lundump.o \
		$(TARGETPFX)lutf8lib.o $(TARGETPFX)lvm.o $(TARGETPFX)lzio.o
LUALIBOBJS = $(LUAOBJFILES1) $(LUAOBJFILES2) $(LUAOBJFILES3) $(LUAOBJFILES4)
LUACROSSLIB = $(TARGETPFX)lua$(subst .,,$(LUA_VERSION)).a
LUAINCL  = -I$(LUASRCDIR)
override BUILDMORE += $(LUACROSSLIB)
override CLEANMORE += rm -f $(LUACROSSLIB) ;
override TARGET_LIBS += $(LUACROSSLIB) -lm
else
LUAINCL=
endif  # BUILD_TARGET_LUA

ifdef BUILD_PDCURSES
#===============-=================================================
# PD Curses library
#===============-=================================================
ifdef WANT_WIN_CURSES
ifdef WANT_DOSVGA
PDCTOP = ../lib/pdcursesmod
PDCPORT = $(PDCTOP)/dosvga
PDCURSESDEF= -I$(PDCTOP) -I$(PDCPORT) \
		-D"CURSES_GRAPHICS" -D"CURSES_BRIEF_INCLUDE" \
		-D"PDC_WIDE" -D"CURSES_UNICODE"
else
PDCTOP = ../lib/pdcurses
PDCPORT = $(PDCTOP)/dos
PDCURSESDEF= -I$(PDCTOP) -I$(PDCPORT) \
		-D"CURSES_GRAPHICS" -D"CURSES_BRIEF_INCLUDE"
endif # WANT_DOSVGA
PDCLIBOBJ1= $(TARGETPFX)addch.o $(TARGETPFX)addchstr.o \
		$(TARGETPFX)addstr.o $(TARGETPFX)attr.o \
		$(TARGETPFX)beep.o $(TARGETPFX)bkgd.o \
		$(TARGETPFX)border.o $(TARGETPFX)clear.o \
		$(TARGETPFX)color.o $(TARGETPFX)delch.o \
		$(TARGETPFX)deleteln.o $(TARGETPFX)getch.o \
		$(TARGETPFX)getstr.o $(TARGETPFX)getyx.o \
		$(TARGETPFX)inch.o
PDCLIBOBJ2= $(TARGETPFX)inchstr.o $(TARGETPFX)initscr.o \
		$(TARGETPFX)inopts.o $(TARGETPFX)insch.o \
		$(TARGETPFX)insstr.o $(TARGETPFX)instr.o \
		$(TARGETPFX)kernel.o $(TARGETPFX)keyname.o \
		$(TARGETPFX)mouse.o $(TARGETPFX)move.o \
		$(TARGETPFX)outopts.o $(TARGETPFX)overlay.o
PDCLIBOBJ3= $(TARGETPFX)pad.o $(TARGETPFX)panel.o $(TARGETPFX)printw.o \
		$(TARGETPFX)refresh.o $(TARGETPFX)scanw.o \
		$(TARGETPFX)scr_dump.o $(TARGETPFX)scroll.o \
		$(TARGETPFX)slk.o $(TARGETPFX)termattr.o
PDCLIBOBJ4= $(TARGETPFX)touch.o $(TARGETPFX)util.o $(TARGETPFX)window.o \
		$(TARGETPFX)debug.o
PDCLIBOBJS = $(PDCLIBOBJ1) $(PDCLIBOBJ2) $(PDCLIBOBJ3) $(PDCLIBOBJ4)
PDCLIB = $(TARGETPFX)pdclib.a
PDCINCL = -I$(PDCTOP) -I$(PDCTOP)/pdcurses
PDCOBJS = $(TARGETPFX)pdcclip.o $(TARGETPFX)pdcdisp.o \
		$(TARGETPFX)pdcgetsc.o $(TARGETPFX)pdckbd.o \
		$(TARGETPFX)pdcscrn.o $(TARGETPFX)pdcsetsc.o \
		$(TARGETPFX)pdcutil.o
override TARGET_LIBS += $(PDCLIB)
ifdef CROSS_TO_MSDOS
endif
override BUILDMORE += $(PDCLIB)
override CLEANMORE += rm -f $(PDCLIB) ;
else   #WANT_WIN_CURSES
PDCURSESDEF=
PDCLIBOBJS=
PDCOBJS=
PDCLIB=
PDCINCL=
endif  # WANT_WIN_CURSES
endif  # BUILD_PDCURSES

ifdef CROSS_TO_MSDOS
#===============-=================================================
# MSDOS cross-compile recipe
#===============-=================================================
# Uses an MSDOS djgpp cross-compiler on linux or macos.
#
# 1. You can obtain the cross-compiler for your system via:
#     sys/msdos/fetch-cross.sh
# 2. Then
#     make CROSS_TO_MSDOS=1 WANT_WIN_TTY=1 WANT_WIN_CURSES=1 all
#
# Source from http://www.lua.org/ftp/lua-5.4.4.tar.gz
#=================================================================

CFLAGS += -DCROSSCOMPILE

#
# Override the build tools and some obj files to
# reflect the msdos djgpp cross-compiler.
#
TOOLTOP1 = ../lib/djgpp/bin
TOOLTOP2 = ../lib/djgpp/i586-pc-msdosdjgpp/bin
override TARGET_CC = $(TOOLTOP1)/i586-pc-msdosdjgpp-gcc
override TARGET_CXX = $(TOOLTOP1)/i586-pc-msdosdjgpp-g++
override TARGET_AR = $(TOOLTOP1)/i586-pc-msdosdjgpp-gcc-ar
override TARGET_STUBEDIT = ../lib/djgpp/i586-pc-msdosdjgpp/bin/stubedit
MSDOS_TARGET_CFLAGS = -c -O -I../include -I../sys/msdos -I../win/share \
	$(LUAINCL) -DDLB $(PDCURSESDEF) \
	-DUSE_TILES -DCROSSCOMPILE -DCROSSCOMPILE_TARGET -DCROSS_TO_MSDOS \
        -Wall -Wextra -Wno-missing-field-initializers -Wreturn-type -Wunused \
        -Wformat -Wswitch -Wshadow -Wwrite-strings \
	-Wimplicit -Wimplicit-function-declaration -Wimplicit-int \
	-Wmissing-parameter-type -Wold-style-definition -Wstrict-prototypes
MSDOS_TARGET_CXXFLAGS = -c -O -I../include -I../sys/msdos -I../win/share \
        $(LUAINCL) -DDLB $(PDCURSESDEF) \
        -DUSE_TILES -DCROSSCOMPILE -DCROSSCOMPILE_TARGET -DCROSS_TO_MSDOS \
        -Wall -Wextra -Wno-missing-field-initializers -Wreturn-type -Wunused \
        -Wformat -Wswitch -Wshadow -Wwrite-strings -Wno-maybe-uninitialized
PDCINCL += -I$(PDCPORT)
PDC_TARGET_CFLAGS = $(MSDOS_TARGET_CFLAGS) -Wno-unused-parameter \
			-Wno-missing-prototypes
FONTVER = terminus-font-4.49.1
FONTTOP = ../lib/$(FONTVER)
DOSFONT = ../sys/msdos/fonts
FONTTARGETS = $(DOSFONT)/ter-u16b.psf $(DOSFONT)/ter-u16v.psf \
		$(DOSFONT)/ter-u18b.psf $(DOSFONT)/ter-u20b.psf \
		$(DOSFONT)/ter-u22b.psf $(DOSFONT)/ter-u24b.psf \
		$(DOSFONT)/ter-u28b.psf $(DOSFONT)/ter-u32b.psf
LUABIN = ../lib/lua-$(LUA_VERSION)/src/lua
LUA_TARGET_CFLAGS = $(MSDOS_TARGET_CFLAGS)
override TARGET_CFLAGS = $(MSDOS_TARGET_CFLAGS) -Wmissing-declarations \
			-Wmissing-prototypes -pedantic -Wmissing-declarations \
			-Wformat-nonliteral
override TARGET_CXXFLAGS = $(MSDOS_TARGET_CXXFLAGS)
ifdef CPLUSPLUS_NEEDED
override TARGET_LINK = $(TOOLTOP1)/i586-pc-msdosdjgpp-g++
else
override TARGET_LINK = $(TOOLTOP1)/i586-pc-msdosdjgpp-gcc
endif
override TARGET_LFLAGS=
override TARGET_LIBS += -lpc
override SYSSRC = ../sys/share/pcmain.c ../sys/msdos/msdos.c \
		../sys/share/pcsys.c ../sys/share/pctty.c \
		../sys/share/pcunix.c ../sys/msdos/video.c \
		../sys/msdos/vidtxt.c ../sys/msdos/pckeys.c \
		../sys/msdos/vidvga.c ../sys/msdos/vidvesa.c \
		../sys/msdos/font.c \
		../win/share/bmptiles.c ../win/share/giftiles.c \
		../win/share/tileset.c
override SYSOBJ= $(TARGETPFX)pcmain.o $(TARGETPFX)msdos.o \
		$(TARGETPFX)pcsys.o $(TARGETPFX)pctty.o \
		$(TARGETPFX)pcunix.o $(TARGETPFX)video.o \
		$(TARGETPFX)vidtxt.o $(TARGETPFX)pckeys.o \
		$(TARGETPFX)vidvga.o $(TARGETPFX)vidvesa.o \
		$(TARGETPFX)font.o \
		$(TARGETPFX)bmptiles.o $(TARGETPFX)giftiles.o \
		$(TARGETPFX)tileset.o $(TARGETPFX)tile.o
override WINLIB=
override LUALIB=
override LUALIBS=
override TOPLUALIB=
override GAMEBIN = $(TARGETPFX)nethack.exe
override PACKAGE = dospkg
override PREGAME += mkdir -p $(TARGETDIR) ; make $(TARGETPFX)exceptn.o ;
override CLEANMORE += rm -f -r $(TARGETDIR) ; rm -f -r $(FONTTARGETS) ;
VARDATND += nhtiles.bmp
#
ifdef WANT_WIN_CURSES
# rules for pdcurses dos-specific files
$(TARGETPFX)%.o : $(PDCPORT)/%.c
	$(TARGET_CC) $(PDCINCL) $(PDC_TARGET_CFLAGS) -o$@  $<
endif  # WANT_WIN_CURSES
#
# Rule for files in sys/msdos
$(TARGETPFX)%.o : ../sys/msdos/%.c
	$(TARGET_CC) $(TARGET_CFLAGS) -o$@ $<
endif  # CROSS_TO_MSDOS
#=================================================================


ifdef CROSS_TO_WASM
#===============-=================================================
# WASM
# originally from https://github.com/NetHack/NetHack/pull/385
#===============-=================================================
#
WASM_DEBUG = 1
WASM_DATA_DIR = $(TARGETPFX)wasm-data
WASM_TARGET = $(TARGETPFX)nethack.js
EMCC_LFLAGS =
#EMCC_LFLAGS += -s SINGLE_FILE=1
EMCC_LFLAGS += -DHACKDIR=\"$(HACKDIR)\"
EMCC_LFLAGS += -s WASM=1
EMCC_LFLAGS += -s ALLOW_TABLE_GROWTH
EMCC_LFLAGS += -s ASYNCIFY -s ASYNCIFY_IMPORTS='["local_callback"]'
EMCC_LFLAGS += -O3
EMCC_LFLAGS += -s MODULARIZE
EMCC_LFLAGS += -s EXPORTED_FUNCTIONS='["_main", "_shim_graphics_set_callback", "_display_inventory"]'
EMCC_LFLAGS += -s EXPORTED_RUNTIME_METHODS='["cwrap", "ccall", "addFunction", \
			"removeFunction", "UTF8ToString", "getValue", "setValue"]'
EMCC_LFLAGS += -s ERROR_ON_UNDEFINED_SYMBOLS=0
# XXX: the "@/" at the end of "--embed-file" tells emscripten to embed the files
# in the root directory, otherwise they will end up in the $(WASM_DATA_DIR) path
EMCC_LFLAGS += --embed-file $(WASM_DATA_DIR)@/
# For a list of EMCC settings:
# https://github.com/emscripten-core/emscripten/blob/master/src/settings.js
#
# WASM C flags
EMCC_CFLAGS =
EMCC_CFLAGS += -Wall
EMCC_CFLAGS += -Werror
EMCC_CFLAGS += -DNO_SIGNAL
#EMCC_CFLAGS += -s DISABLE_EXCEPTION_CATCHING=0
EMCC_DEBUG_LFLAGS += -s ASSERTIONS=1
EMCC_DEBUG_LFLAGS += -s ASSERTIONS=2
EMCC_DEBUG_LFLAGS += -s STACK_OVERFLOW_CHECK=2
EMCC_DEBUG_LFLAGS += -s SAFE_HEAP=1
EMCC_DEBUG_LFLAGS += -s LLD_REPORT_UNDEFINED=1
EMCC_DEBUG_LFLAGS += -s EXCEPTION_DEBUG=1
#EMCC_DEBUG_CFLAGS += -fsanitize=undefined -fsanitize=address -fsanitize=leak
EMCC_DEBUG_LFLAGS += -s NO_EXIT_RUNTIME
# XXX: if --profiling isn't included then any error dumps 10MB of WASM to the screen rather than a useful message
EMCC_DEBUG_LFLAGS += --profiling
EMCC_PROD_CFLAGS += -O3
ifdef WASM_DEBUG
EMCC_CFLAGS += $(EMCC_DEBUG_CFLAGS)
EMCC_LFLAGS += $(EMCC_DEBUG_LFLAGS)
else
EMCC_CFLAGS += $(EMCC_PROD_CFLAGS)
EMCC_LFLAGS += $(EMCC_PROD_LFLAGS)
endif
#
# Override the build tools and some obj files to
# reflect emscripten
override TARGET_CC = emcc
override TARGET_CXX = emcc
override TARGET_AR = emar
WASM_CFLAGS = -Wall -Wextra -Wno-missing-field-initializers
WASM_CFLAGS += -Wimplicit -Wreturn-type -Wunused -Wformat -Wswitch
WASM_CFLAGS += -Wshadow
# WASM_CFLAGS += -Wwrite-strings
# WASM_CFLAGS += -Werror
# Nethack C flags
WASM_CFLAGS += $(WINCFLAGS)   #WINCFLAGS set from multiw-2.370
WASM_CFLAGS += -DSYSCF -DSYSCF_FILE=\"/sysconf\" -DSECURE
WASM_CFLAGS += -g -I../include -DNOTPARMDECL
# NetHack sources control
WASM_CFLAGS += -DDLB
WASM_CFLAGS += -DHACKDIR=\"$(HACKDIR)\"
WASM_CFLAGS += -DDEFAULT_WINDOW_SYS=\"shim\" \
#override TARGET_CFLAGS += -DGREPPATH=\"/usr/bin/grep\"
WASM_CFLAGS += -DNOMAIL
WASM_CFLAGS += $(LUAINCL)
WASM_CFLAGS += -DNOTTYGRAPHICS -DSHIM_GRAPHICS -DLIBNH
WASM_CFLAGS += -DCROSSCOMPILE
WASM_TARGET_CFLAGS = -DCROSSCOMPILE_TARGET -DCROSS_TO_WASM
# For src Makefile
override CFLAGS = $(WASM_CFLAGS)
override TARGET_CFLAGS = $(EMCC_CFLAGS) $(WASM_CFLAGS) $(WASM_TARGET_CFLAGS)
#
LUA_TARGET_CFLAGS = $(TARGET_CFLAGS)
override TARGET_CXXFLAGS = $(TARGET_CFLAGS)
override TARGET_LINK = $(TARGET_CC)
override TARGET_LFLAGS= $(EMCC_LFLAGS)
override SYSSRC = ../sys/libnh/libnhmain.c \
		../sys/share/ioctl.c ../sys/share/unixtty.c \
		../sys/unix/unixunix.c ../sys/unix/unixres.c \
		../win/shim/winshim.c
override SYSOBJ= $(TARGETPFX)libnhmain.o \
		$(TARGETPFX)ioctl.o $(TARGETPFX)unixtty.o \
		$(TARGETPFX)unixunix.o $(TARGETPFX)unixres.o \
		$(TARGETPFX)winshim.o
override WINLIB = emranlib
override LUALIB=
override TOPLUALIB=
override REGEXOBJ = $(TARGETPFX)posixregex.o
override WINOBJ=
# don't bother Making regular NetHack executable
override GAME=
# the real VARDAT hasn't been defined yet for use in ALLDEP override
WASM_DAT = bogusmon data engrave epitaph oracles options quest.lua rumors
WASMDEP = include/nhlua.h $(WASM_DAT) spec_levs check-dlb
override ALLDEP = $(WASMDEP) wasm
override PREGAME += mkdir -p $(TARGETDIR)/wasm-data ;
override CLEANMORE += rm -rf $(TARGETDIR) ;
RANLIB=$(EMRANLIB)
#VARDATND += nhtiles.bmp
# Rule for file in sys/unix
$(TARGETPFX)%.o : ../sys/unix/%.c
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o$@ $<
# Rule for file in sys/libnh
$(TARGETPFX)%.o : ../sys/libnh/%.c
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o$@ $<
# Rule for files in win/shim
$(TARGETPFX)%.o : ../win/shim/%.c
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o$@ $<
endif  # CROSS_TO_WASM
#=================================================================

ifdef WANT_WIN_CURSES
ifdef BUILD_PDCURSES
# Rules for PDCurses files
$(TARGETPFX)%.o : $(PDCTOP)/pdcurses/%.c
	$(TARGET_CC) $(PDCINCL) $(PDC_TARGET_CFLAGS) -c -o$@  $<
endif  # BUILD_PDCURSES
endif  # WANT_WIN_CURSES

ifdef CROSS_SHARED
# Rules for win/share files
$(TARGETPFX)%.o : ../win/share/%.c
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o$@ $<
# Rules for util files heading for target
$(TARGETPFX)%.o : ../util/%.c
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o$@ $<
endif  # CROSS_SHARED

ifdef BUILD_TARGET_LUA
# Rule for LUA files
$(TARGETPFX)%.o : $(LUATOP)/src/%.c
	$(TARGET_CC) $(LUA_TARGET_CFLAGS) -c $(LUA_FLAGS) -o$@ $<
endif  # BUILD_TARGET_LUA
#
# End of cross-compiling -PRE section
#===============-=================================================

#
#
# NetHack 3.7  gbdates-pre.370 $NHDT-Date: 1599687610 2020/09/09 21:40:10 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.11 $

ifdef MAKEFILE_DOC
ifneq "$(GIT)" "0"
#Get the hash of the last update to Guidebook.mn
GB_LAST_COMMIT := $(shell git log -n 1 --pretty=format:%H -- Guidebook.mn)
ifneq "$(GB_LAST_COMMIT)" ""
GB_DATESTAMP := $(shell git show -s --format=%cd --date=format:'%B %d, %Y' $(GB_LAST_COMMIT))
endif   # GB_LAST_COMMIT
ifneq "$(GB_DATESTAMP)" ""
DOC_EXTRAS += Guidebook.dated.mn Guidebook.dated.tex
override GUIDEBOOK_MN = Guidebook.dated.mn
override GUIDEBOOK_TEX = Guidebook.dated.tex
DOC_SPOTLESS_EXTRAS += Guidebook.pdf
endif   # GB_DATESTAMP
endif   # GIT=0 explicitly
endif   # MAKEFILE_DOC
#
#
### End hints/macOS.370 PRE

###
### Start Makefile.src
###
#	NetHack Makefile.
# NetHack 3.7  Makefile.src    $NHDT-Date: 1654287121 2022/06/03 20:12:01 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.145 $
# Copyright (c) 2018 by Pasi Kallinen
# NetHack may be freely redistributed.  See license for details.

# Root of source tree:
NHSROOT=..

# newer makes predefine $(MAKE) to 'make' and do smarter processing of
# recursive make calls if $(MAKE) is used
# these makes allow $(MAKE) to be overridden by the environment if someone
# wants to (or has to) use something other than the standard make, so we do
# not want to unconditionally set $(MAKE) here
#
# unfortunately, some older makes do not predefine $(MAKE); if you have one of
# these, uncomment the following line
# (you will know that you have one if you get complaints about being unable
# to find 'makedefs')
# MAKE = make

# This makefile replaces the previous Makefile.unix, Makefile.xenix,
# Makefile.3B2, Makefile.att, and Makefile.tos.
# Set SYSTEM to one of:
#	'Sysunix'	-- generic UNIX
#	'Sys3B2'	-- AT&T 3B2, 3B5, etc.
#	'Sysatt'	-- AT&T UNIXPC, 7300, 3B1
#	'SysV-AT'	-- Microport 286 UNIX (put -DDUMB in CFLAGS)
#	'Systos'	-- Atari
#	'SysBe'		-- BeOS
SYSTEM = Sysunix

#
# Make sure that your bourne shell is specified here, as you have to spawn
# some of the commands (eg. depend) in bourne shell for them to work.
#
# For Systos users compiling on the ST, you'll either need a bourne shell
# clone or you'll need to do make depend, etc. by hand. In either case,
# the line below probably needs changing
SHELL=/bin/sh
# for Atari
# SHELL=E:/GEMINI2/MUPFEL.TTP

# Usually, the C compiler driver is used for linking:
#LINK=$(CC)

# If we're cross-compiling, a hints file will override this
# to a uniq target directory, but otherwise it just goes in
# ../src
TARGETPFX=

# Pick the SYSSRC and SYSOBJ lines corresponding to your desired operating
# system.
#
# for UNIX systems
SYSSRC = ../sys/share/ioctl.c ../sys/share/unixtty.c ../sys/unix/unixmain.c \
	../sys/unix/unixunix.c ../sys/unix/unixres.c
SYSOBJ = $(TARGETPFX)ioctl.o $(TARGETPFX)unixmain.o $(TARGETPFX)unixtty.o \
	$(TARGETPFX)unixunix.o $(TARGETPFX)unixres.o
#
# for Systos
# SYSSRC = ../sys/atari/tos.c ../sys/share/pcmain.c ../sys/share/pcsys.c \
#	../sys/share/pctty.c ../sys/share/pcunix.c
# SYSOBJ = $(TARGETPFX)tos.o $(TARGETPFX)pcmain.o $(TARGETPFX)pcsys.o \
#	$(TARGETPFX)pctty.o $(TARGETPFX)pcunix.o
#
# for BeOS
#SYSSRC = ../sys/be/bemain.c ../sys/share/unixtty.c ../sys/share/ioctl.c
#SYSOBJ = $(TARGETPFX)bemain.o $(TARGETPFX)unixtty.o $(TARGETPFX)ioctl.o


# if you are using gcc as your compiler:
#	uncomment the CC definition below if it's not in your environment
#	if you get setcgtty() warnings during execution, you are feeding gcc
#		a non-ANSI <sys/ioctl.h> -- either run fixincludes on it or use
#		-traditional in CFLAGS
# CC = gcc
#
#	For Bull DPX/2 systems at B.O.S. 2.0 or higher use the following:
#
# CC = gcc -ansi -D_BULL_SOURCE -D_XOPEN_SOURCE -D_POSIX_SOURCE
#
#	If you are using GCC 2.2.2 or higher on a DPX/2, just use:
#
# CC = gcc -ansi
#
#	For HP/UX 10.20 with GCC:
# CC = gcc -D_POSIX_SOURCE
#
#	For cross-compiling, eg. with gcc on Linux (see also CXX further down):
# CC = arm-linux-gcc
#
#
# if you're debugging and want gcc to check as much as possible, use:
# CC = gcc -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wswitch -Wshadow -Wcast-qual -Wwrite-strings

# flags may have to be changed as required
# flags for 286 Xenix:
# CFLAGS = -Ml2t16 -O -LARGE -I../include
# LFLAGS = -Ml -F 4000 -SEG 512

# flags for 286 Microport SysV-AT
# CFLAGS = -DDUMB -Ml -I../include
# LFLAGS = -Ml

# flags for Atari gcc (3.2.1)
# CFLAGS = -O -I../include
# LFLAGS = -s
# flags for Atari gcc (3.3)
# CFLAGS = -mshort -O2 -fomit-frame-pointer -I../include
# LFLAGS = -mshort -s

# flags for AIX 3.1 cc on IBM RS/6000 to define
# a suitable subset of standard libraries
# (note that there is more info regarding the "-qchars=signed"
# switch in file Install.unx note 8)
# CFLAGS = -D_NO_PROTO -D_XOPEN_SOURCE -O -I../include -qchars=signed
#
# Some of our subroutines are complex enough that this is required for full
# optimization under AIX 3.2 (I don't know about 3.1).
#
# CFLAGS = -D_NO_PROTO -D_XOPEN_SOURCE -D_ALL_SOURCE -O -I../include -qchars=signed -qmaxmem=5000

# flags for A/UX 2.01 using native cc or c89
# gcc predefines AUX so that's not needed there
# Remember to use -lcurses for WINLIB below !
# CFLAGS = -ZS -D_POSIX_SOURCE -O -I../include -DAUX

# flags for IRIX 4.0.x using native cc
# The include files are __STDC__, but have bugs involving const
# CFLAGS = -O -I../include -D__STDC__ -Dconst= -woff 100,293
# LFLAGS = -s

# flags for BSD/OS 2.0
# CFLAGS = -O -I../include -I/usr/X11/include
# LFLAGS = -L/usr/X11/lib

# flags for Linux
#   compile normally
# CFLAGS = -O2 -fomit-frame-pointer -I../include
# LFLAGS = -L/usr/X11R6/lib
#   OR compile backwards compatible a.out format
# CFLAGS = -O2 -b i486-linuxaout -fomit-frame-pointer -I../include
# LFLAGS = -b i486-linuxaout -L/usr/X11R6/lib

# flags for BeOS
#   on a Mac/BeBox:
#CC = mwcc
#CFLAGS = -r -I../include
#LINK = mwld
#LFLAGS = -map nethack.xMAP
#   on Intel:
#CFLAGS = -O -I../include
#LINK = gcc
#LFLAGS = -Xlinker -soname=_APP_

# Compile with PDCurses installed in a separate directory that doesn't
# conflict with the system curses/ncurses library
#CFLAGS = -O -I../include -I/usr/local/include/pdcurses
# Same as above, but for XCurses
#CFLAGS = -O -DXCURSES -I../include -I/usr/local/include/pdcurses
# Compile against system curses library, such as ncurses
#CFLAGS = -O -I../include
#
# files in ../win/X11 (relative to src) are passed $(CFLAGS) $(X11CFLAGS)
# and by default will find <X11/foo.h> in /usr/include/X11/foo.h;
# can be overridden via hints; post-10.7 OSX with XQuartz uses
# X11CFLAGS=-I/opt/X11/include to find <X11/foo.h> in /opt/X11/include/X11/foo.h
#X11CFLAGS=

# flags for debugging:
# CFLAGS = -g -I../include

#CFLAGS = -O -I../include
#LFLAGS =

# The Qt and Be window systems are written in C++, while the rest of
# NetHack is standard C.  If using Qt, uncomment the LINK line here to get
# the C++ libraries linked in.
CXXFLAGS = $(CCXXFLAGS) -I. -I$(QTDIR)/include $(QTCXXFLAGS)
CXX ?= g++
MOC ?= moc
MOCPATH ?= $(QTDIR)/bin/$(MOC)
#LINK=g++
# included for documentation purposes if not using the relevant hints files;
# when not using those to manage the value, it should remain empty
#QTn_H =

# The default is for the TARGET_* variables to match the defaults.
# If we're cross-compiling these will get overridden elsewhere, likely via
# a hints file. TARGETPFX was set above earlier.
TARGET_CC = $(CC)
TARGET_CFLAGS = $(CFLAGS)
TARGET_LINK = $(LINK)
TARGET_LFLAGS = $(LFLAGS)
TARGET_CXX = $(CXX)
TARGET_CXXFLAGS = $(CXXFLAGS)
TARGET_LIBS = $(LIBS)

# we specify C preprocessor flags via CFLAGS; files built with default rules
# might include $(CPPFLAGS) which could get a value from user's environment;
# we avoid that by forcing it empty rather than by overriding default rules
CPPFLAGS =

# file for regular expression matching
REGEXOBJ ?= $(TARGETPFX)posixregex.o
#REGEXOBJ = $(TARGETPFX)pmatchregex.o
#REGEXOBJ = $(TARGETPFX)cppregex.o

# Set the WINSRC, WINOBJ, and WINLIB lines to correspond to your desired
# combination of windowing systems.  Also set matching USE_x_GRAPHICS in
# config.h.  Note that if you are building for any window system which
# uses tiles, uncomment '#$(TARGETPFX)tile.o' (by removing the '#') in that
# system's WINxOBJ (WINX11OBJ or WINQTOBJ or WINQT3OBJ).  If you are building
# nethack with support for multiple window systems, only uncomment that for
# one of them to avoid duplicate tile.o.
#
# files for a straight tty port using no native windowing system
WINTTYSRC = ../win/tty/getline.c ../win/tty/termcap.c ../win/tty/topl.c \
	../win/tty/wintty.c
WINTTYOBJ = $(TARGETPFX)getline.o $(TARGETPFX)termcap.o $(TARGETPFX)topl.o \
	$(TARGETPFX)wintty.o
#
# Files for curses interface
WINCURSESSRC = ../win/curses/cursmain.c ../win/curses/curswins.c \
	../win/curses/cursmisc.c ../win/curses/cursdial.c \
	../win/curses/cursstat.c ../win/curses/cursinit.c \
	../win/curses/cursmesg.c ../win/curses/cursinvt.c
WINCURSESOBJ = $(TARGETPFX)cursmain.o $(TARGETPFX)curswins.o \
	$(TARGETPFX)cursmisc.o $(TARGETPFX)cursdial.o \
	$(TARGETPFX)cursstat.o $(TARGETPFX)cursinit.o \
	$(TARGETPFX)cursmesg.o $(TARGETPFX)cursinvt.o
#
# files for an X11 port
# (tile.c is a generated source file)
WINX11SRC = ../win/X11/Window.c ../win/X11/dialogs.c ../win/X11/winX.c \
	../win/X11/winmap.c  ../win/X11/winmenu.c ../win/X11/winmesg.c \
	../win/X11/winmisc.c ../win/X11/winstat.c ../win/X11/wintext.c \
	../win/X11/winval.c tile.c
WINX11OBJ = $(TARGETPFX)Window.o $(TARGETPFX)dialogs.o $(TARGETPFX)winX.o \
	$(TARGETPFX)winmap.o $(TARGETPFX)winmenu.o $(TARGETPFX)winmesg.o \
	$(TARGETPFX)winmisc.o $(TARGETPFX)winstat.o $(TARGETPFX)wintext.o \
	$(TARGETPFX)winval.o #$(TARGETPFX)tile.o
#
# Files for a Qt 3 interface (renamed since nethack 3.6.x)
#
#WINQT3SRC = ../win/Qt3/qt3_win.cpp ../win/Qt3/qt3_clust.cpp \
#	../win/Qt3/qt3tableview.cpp
#WINQT3OBJ = $(TARGETPFX)qt3_win.o $(TARGETPFX)qt3_clust.o \
#	$(TARGETPFX)qt3tableview.o #$(TARGETPFX)tile.o
# empty values for 'make depend'
WINQT3SRC =
WINQT3OBJ =

#
# Files for a Qt 4, Qt 5, or Qt 6 interface
#
# generated source files made by Qt's 'moc' program from ../win/Qt/qt_*.h;
# appended to WINQTSRC for use by 'make depend'
WINQTMOC = qt_kde0.moc qt_main.moc qt_map.moc qt_menu.moc qt_msg.moc \
	qt_plsel.moc qt_set.moc qt_stat.moc qt_xcmd.moc qt_yndlg.moc
WINQTSRC = ../win/Qt/qt_bind.cpp ../win/Qt/qt_click.cpp \
	../win/Qt/qt_clust.cpp ../win/Qt/qt_delay.cpp \
	../win/Qt/qt_glyph.cpp ../win/Qt/qt_icon.cpp ../win/Qt/qt_inv.cpp \
	../win/Qt/qt_key.cpp ../win/Qt/qt_line.cpp ../win/Qt/qt_main.cpp \
	../win/Qt/qt_map.cpp ../win/Qt/qt_menu.cpp ../win/Qt/qt_msg.cpp \
	../win/Qt/qt_plsel.cpp ../win/Qt/qt_rip.cpp ../win/Qt/qt_set.cpp \
	../win/Qt/qt_stat.cpp ../win/Qt/qt_str.cpp ../win/Qt/qt_streq.cpp \
	../win/Qt/qt_svsel.cpp ../win/Qt/qt_win.cpp ../win/Qt/qt_xcmd.cpp \
	../win/Qt/qt_yndlg.cpp $(WINQTMOC) tile.c
WINQTOBJ = $(TARGETPFX)qt_bind.o $(TARGETPFX)qt_click.o \
	$(TARGETPFX)qt_clust.o $(TARGETPFX)qt_delay.o \
	$(TARGETPFX)qt_glyph.o $(TARGETPFX)qt_icon.o \
	$(TARGETPFX)qt_inv.o $(TARGETPFX)qt_key.o $(TARGETPFX)qt_line.o \
	$(TARGETPFX)qt_main.o $(TARGETPFX)qt_map.o $(TARGETPFX)qt_menu.o \
	$(TARGETPFX)qt_msg.o $(TARGETPFX)qt_plsel.o $(TARGETPFX)qt_rip.o \
	$(TARGETPFX)qt_set.o $(TARGETPFX)qt_stat.o $(TARGETPFX)qt_str.o \
	$(TARGETPFX)qt_streq.o $(TARGETPFX)qt_svsel.o $(TARGETPFX)qt_win.o \
	$(TARGETPFX)qt_xcmd.o $(TARGETPFX)qt_yndlg.o #$(TARGETPFX)tile.o

# Files for Shim windowing interface for libnh -- doesn't do anything,
# just passes along the API calls to the library
#
WINSHIMSRC = ../win/shim/winshim.c
WINSHIMOBJ = winshim.o

#
# Files for a BeOS InterfaceKit port -- not ready for prime time
WINBESRC =
WINBEOBJ =
#WINBESRC = ../win/BeOS/winbe.cpp ../win/BeOS/NHWindow.cpp \
#	../win/BeOS/NHMenuWindow.cpp ../win/BeOS/NHMapWindow.cpp tile.c
#WINBEOBJ = $(TARGETPFX)winbe.o $(TARGETPFX)NHWindow.o \
#	$(TARGETPFX)NHMenuWindow.o $(TARGETPFX)NHMapWindow.o \
#	$(TARGETPFX)tile.o
#
#
#WINSRC = $(WINTTYSRC)
#WINOBJ = $(WINTTYOBJ)
#
# Curses - Karl Garrison, Tangles
#WINSRC = $(WINCURSESSRC)
#WINOBJ = $(WINCURSESOBJ)
#
# on some systems the termcap library is in -ltermcap or -lcurses
# on 386 Xenix, the -ltermlib tputs() seems not to work; use -lcurses instead
# Sysatt uses shared library in lieu of this option
# Systos needs -lcurses16 if you use -mshort
# AIX 3.1 on RS/6000 likes -lcurses if TERMINFO defined in unixconf.h
# and -ltermcap otherwise
# Linux uses -lncurses (newer) or -ltermcap (older)
# Be uses -ltermcap
#
# libraries for tty ports
# WINTTYLIB = -ltermcap
# WINTTYLIB = -lcurses
# WINTTYLIB = -lcurses16
# WINTTYLIB = -lncurses
#WINTTYLIB = -ltermlib
#
# libraries for X11
# If USE_XPM is defined in config.h, you will also need -lXpm here.
#WINX11LIB = -lXaw -lXmu -lXext -lXt -lX11
# WINX11LIB = -lXaw -lXmu -lXt -lX11
# WINX11LIB = -lXaw -lXmu -lXext -lXt -lXpm -lX11 -lm
# WINX11LIB = -lXaw -lXmu -lXpm -lXext -lXt -lX11 -lSM -lICE -lm # BSD/OS 2.0
#
#
# libraries for Qt 3
WINQT3LIB = -L$(QTDIR)/lib -lqt
#
# libraries for Qt 4
WINQT4LIB = `pkg-config QtGui --libs`
#
# libraries for Qt 5 (use with WINQTSRC and WINQTOBJ)
WINQT5LIB = `pkg-config Qt5Gui Qt5Widgets Qt5Multimedia --libs`
#
# libraries for KDE (with Qt)
WINKDELIB = -lkdecore -lkdeui -lXext
#
# libraries for BeOS
WINBELIB = -lbe
#
# libraries for curses port
# link with ncurses
WINCURSESLIB = -lncurses
# link with pdcurses for SDL, installed in a separate directory
#WINCURSESLIB = -L/usr/local/lib/pdcurses -lpdcurses -lSDL
# same as above, for XCurses
#WINCURSESLIB = -L/usr/local/lib/pdcurses -lXCurses -lXawM -lXmu -lXext -lXt -lX11
#
#WINLIB = $(WINTTYLIB)
#
# For Curses
#WINLIB = $(WINCURSESLIB)
#
# some platforms need to build the support libraries
# BUILDMORE = $(TARGETPFX)pdcurses.a

# any other strange libraries your system needs (for Sysunix only -- the more
# specialized targets should already be right)
#
# on HP-UX 8.x, the malloc(3x) routines in libmalloc.a seem to align things
# better than the malloc(3) ones in libc.a
# LIBS = -lmalloc
#
# DPX/2's also use the malloc(3x) routines.  In addition, if you are building
# for X11, you must include libinet.a.
# LIBS = -lmalloc -linet
#
# Linux NetHack uses some bsd style ioctl functions, thus it is necessary to
# use the bsd libs.  (Only if still compiling as BSD in unixconf.h; recent
# versions compile fine using SYSV without this.)
# LIBS = -lbsd
#
# for CYGWIN32 aka cygwin 1.1.1
# LIBS = -lcygwin
#
# Solaris 2.x seems to work with the following
# LIBS = -lsocket -lnsl
#
# IRIX 4.0.x needs -lsun if NIS (YP) is being used for passwd file lookup
# LIBS = -lsun
#
# If ZLIB_COMP is defined in config.h this is necessary to link with zlib.
# LIBS = -lz
#
# LIBS =

# make NetHack
GAME     = nethack
# GAME     = nethack.prg
GAMEBIN = $(GAME)

# if you defined RANDOM in unixconf.h since your system did not come
# with a reasonable random number generator
# RANDOBJ = $(TARGETPFX)random.o
RANDOBJ =

# used by `make depend' to reconstruct this Makefile; you shouldn't need this
# at all but can override with 'make AWK=nawk' or 'make AWK=gawk' if necessary
AWK	= awk

# when using 'makedefs -v', also force dat/gitinfo.txt to be up to date;
# changing this to 0 will change the behavior to only make that file if
# it doesn't already exist; to skip it completely, create an empty file
# of that name and also set this to 0; there shouldn't be any need to
# skip it--if nethack's sources don't reside in a git repository than
# the script which creates that file will fail benignly and 'makedefs -v'
# will proceed without it
GITINFO=1

# if you change this to 1, feedback while building will omit -Dthis -Wthat
# -Isomewhere so that each file being compiled is listed on one short line;
# it requires support for '$<' in rules with more than one prerequisite
# (rather than just in suffix default rule), such as is implemented by
# gnu make and others which have picked up its extensions;
# allowed values are 0, 1, and empty (which behaves like 0)
QUIETCC=0

# ----------------------------------------
#
# Nothing below this line should have to be changed.
#
# Other things that have to be reconfigured are in config.h,
# {unixconf.h, pcconf.h}, and possibly system.h

# Add rule for possible cross-compiler
$(TARGETPFX)%.o : %.c
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<

# Verbosity definitions, begin
#   Set QUIETCC=1 above to output less feedback while building.
#   CC and CXX obey verbosity, LD and LINK don't.
#   AT is @ when not verbose, empty otherwise
ACTUAL_CC := $(CC)
ACTUAL_CXX := $(CXX)
ACTUAL_LD := $(LD)
ACTUAL_LINK := $(LINK)

CC_V0 = $(ACTUAL_CC)
CC_V = $(CC_V0)
CC_V1 = @echo "[CC] $<"; $(ACTUAL_CC)
CC = $(CC_V$(QUIETCC))

CXX_V0 = $(ACTUAL_CXX)
CXX_V = $(CXX_V0)
CXX_V1 = @echo "[CXX] $<"; $(ACTUAL_CXX)
CXX = $(CXX_V$(QUIETCC))

# LD and LINK might be based on invoking CC and may not be able to substitute
# for QUIETCC, so feedback from them is handled differently (via $AT)
LD = $(ACTUAL_LD)
LINK = $(ACTUAL_LINK)

AT_V0 :=
AT_V := $(AT_V0)
AT_V1 := @
AT = $(AT_V$(QUIETCC))
# Verbosity, end

# verbosity-adjacent; these will already have 'real' values if hints have
# set up cross-compiling, in which case these assignments will be no-ops
PREGAME=@true
CLEANMORE=@true
PACKAGE=@true


MAKEDEFS = ../util/makedefs

# -lm required by lua
LUA_VERSION ?=5.4.4
LUABASE = liblua-$(LUA_VERSION).a
LUALIB = ../lib/lua/$(LUABASE)
LUALIBS = $(LUALIB) -lm $(DLLIB)

# timestamp files to reduce `make' overhead and shorten .o dependency lists
CONFIG_H = ../src/config.h-t
HACK_H	= ../src/hack.h-t

# all .c that are part of the main NetHack program and are not operating- or
# windowing-system specific. Do not include date.c in this list.
HACKCSRC = allmain.c alloc.c apply.c artifact.c attrib.c ball.c bones.c \
	   botl.c cmd.c dbridge.c decl.c detect.c dig.c display.c dlb.c do.c \
	   do_name.c do_wear.c dog.c dogmove.c dokick.c dothrow.c drawing.c \
	   dungeon.c eat.c end.c engrave.c exper.c explode.c extralev.c \
	   files.c fountain.c hack.c hacklib.c \
	   insight.c invent.c isaac64.c light.c \
	   lock.c mail.c makemon.c mcastu.c mdlib.c mhitm.c \
	   mhitu.c minion.c mklev.c mkmap.c mkmaze.c mkobj.c mkroom.c mon.c \
	   mondata.c monmove.c monst.c mplayer.c mthrowu.c muse.c music.c \
	   nhlua.c nhlsel.c nhlobj.c o_init.c objects.c objnam.c \
	   options.c pager.c pickup.c pline.c polyself.c potion.c pray.c \
	   priest.c quest.c questpgr.c read.c rect.c region.c restore.c \
	   rip.c rnd.c role.c rumors.c save.c sfstruct.c \
	   shk.c shknam.c sit.c sounds.c \
	   sp_lev.c spell.c steal.c steed.c symbols.c sys.c teleport.c \
	   timeout.c topten.c track.c trap.c u_init.c utf8map.c \
	   uhitm.c vault.c version.c vision.c weapon.c were.c wield.c \
	   windows.c wizard.c worm.c worn.c write.c zap.c

# all operating-system-dependent .c (for dependencies and such)
SYSCSRC = ../sys/share/pcmain.c ../sys/share/pcsys.c \
	../sys/share/pctty.c ../sys/share/pcunix.c \
	../sys/share/pmatchregex.c ../sys/share/posixregex.c \
	../sys/share/random.c \
	../sys/share/ioctl.c ../sys/share/unixtty.c ../sys/unix/unixmain.c \
	../sys/unix/unixunix.c ../sys/unix/unixres.c
SYSCXXSRC = ../sys/share/cppregex.cpp

# generated source files (tile.c is handled separately via WINxxxSRC)
GENCSRC = #tile.c

# all windowing-system-dependent .c (for dependencies and such)
WINCSRC = $(WINTTYSRC) $(WINCURSESSRC) $(WINX11SRC) $(WINSHIMSRC)
# all windowing-system-dependent .cpp (for dependencies and such)
WINCXXSRC = $(WINQTSRC) $(WINQT3SRC) $(WINBESRC)

# Files for window system chaining. Requires SYSCF; include via HINTSRC/HINTOBJ
CHAINSRC = ../win/chain/wc_chainin.c ../win/chain/wc_chainout.c \
	   ../win/chain/wc_trace.c
CHAINOBJ = $(TARGETPFX)wc_chainin.o $(TARGETPFX)wc_chainout.o \
	$(TARGETPFX)wc_trace.o

# .c files for this version (for date.h)
VERSOURCES = $(HACKCSRC) $(SYSSRC) $(WINSRC) $(CHAINSRC) $(GENCSRC)

# .c files for all versions using this Makefile (for lint and tags)
CSOURCES = $(HACKCSRC) $(SYSCSRC) $(WINCSRC) $(CHAINSRC) $(GENCSRC)


# all .h files except date.h, which would
# cause dependency loops if run through "make depend"
# and dgn_file.h, special level & dungeon files.
#
HACKINCL = align.h artifact.h artilist.h attrib.h botl.h \
	color.h config.h config1.h context.h coord.h decl.h \
	display.h dlb.h dungeon.h engrave.h extern.h flag.h fnamesiz.h \
	func_tab.h global.h warnings.h hack.h lint.h mextra.h mfndpos.h \
	micro.h mkroom.h monattk.h mondata.h monflag.h monst.h monsters.h \
	obj.h objects.h objclass.h optlist.h patchlevel.h pcconf.h \
	permonst.h prop.h rect.h region.h sym.h defsym.h rm.h sp_lev.h \
	spell.h sys.h system.h tcap.h timeout.h tradstdc.h trap.h unixconf.h \
	vision.h vmsconf.h wintty.h wincurs.h winX.h winprocs.h wintype.h \
	you.h youprop.h

HSOURCES = $(HACKINCL) dgn_file.h

# the following .o's _must_ be made before any others (for makedefs)
FIRSTOBJ = monst.o objects.o
HOSTOBJ = $(FIRSTOBJ) alloc.o drawing.o

#
# $(TARGETPFX)date.o is not included in this list
#
HOBJ = $(TARGETPFX)allmain.o $(TARGETPFX)alloc.o \
	$(TARGETPFX)apply.o $(TARGETPFX)artifact.o $(TARGETPFX)attrib.o \
	$(TARGETPFX)ball.o $(TARGETPFX)bones.o $(TARGETPFX)botl.o \
	$(TARGETPFX)cmd.o $(TARGETPFX)dbridge.o $(TARGETPFX)decl.o \
	$(TARGETPFX)detect.o $(TARGETPFX)dig.o $(TARGETPFX)display.o \
	$(TARGETPFX)dlb.o $(TARGETPFX)do.o $(TARGETPFX)do_name.o \
	$(TARGETPFX)do_wear.o $(TARGETPFX)dog.o $(TARGETPFX)dogmove.o \
	$(TARGETPFX)dokick.o $(TARGETPFX)dothrow.o $(TARGETPFX)drawing.o \
	$(TARGETPFX)dungeon.o $(TARGETPFX)eat.o $(TARGETPFX)end.o \
	$(TARGETPFX)engrave.o $(TARGETPFX)exper.o $(TARGETPFX)explode.o \
	$(TARGETPFX)extralev.o $(TARGETPFX)files.o $(TARGETPFX)fountain.o \
	$(TARGETPFX)hack.o $(TARGETPFX)hacklib.o $(TARGETPFX)insight.o \
	$(TARGETPFX)invent.o $(TARGETPFX)isaac64.o $(TARGETPFX)light.o \
	$(TARGETPFX)lock.o $(TARGETPFX)mail.o $(TARGETPFX)makemon.o \
	$(TARGETPFX)mcastu.o $(TARGETPFX)mdlib.o \
	$(TARGETPFX)mhitm.o $(TARGETPFX)mhitu.o $(TARGETPFX)minion.o \
	$(TARGETPFX)mklev.o $(TARGETPFX)mkmap.o $(TARGETPFX)mkmaze.o \
	$(TARGETPFX)mkobj.o $(TARGETPFX)mkroom.o $(TARGETPFX)mon.o \
	$(TARGETPFX)mondata.o $(TARGETPFX)monmove.o $(TARGETPFX)monst.o \
	$(TARGETPFX)mplayer.o $(TARGETPFX)mthrowu.o $(TARGETPFX)muse.o \
	$(TARGETPFX)music.o $(TARGETPFX)nhlua.o $(TARGETPFX)nhlsel.o \
	$(TARGETPFX)nhlobj.o $(TARGETPFX)objects.o $(TARGETPFX)o_init.o \
	$(TARGETPFX)objnam.o $(TARGETPFX)options.o $(TARGETPFX)pager.o \
	$(TARGETPFX)pickup.o $(TARGETPFX)pline.o $(TARGETPFX)polyself.o \
	$(TARGETPFX)potion.o $(TARGETPFX)pray.o $(TARGETPFX)priest.o \
	$(TARGETPFX)quest.o $(TARGETPFX)questpgr.o $(TARGETPFX)read.o \
	$(TARGETPFX)rect.o $(TARGETPFX)region.o $(TARGETPFX)restore.o \
	$(TARGETPFX)rip.o $(TARGETPFX)rnd.o $(TARGETPFX)role.o \
	$(TARGETPFX)rumors.o $(TARGETPFX)save.o $(TARGETPFX)sfstruct.o \
	$(TARGETPFX)shk.o $(TARGETPFX)shknam.o $(TARGETPFX)sit.o \
	$(TARGETPFX)sounds.o $(TARGETPFX)sp_lev.o $(TARGETPFX)spell.o \
	$(TARGETPFX)symbols.o $(TARGETPFX)sys.o $(TARGETPFX)steal.o \
	$(TARGETPFX)steed.o $(TARGETPFX)teleport.o $(TARGETPFX)timeout.o \
	$(TARGETPFX)topten.o $(TARGETPFX)track.o $(TARGETPFX)trap.o \
	$(TARGETPFX)u_init.o $(TARGETPFX)uhitm.o $(TARGETPFX)utf8map.o \
	$(TARGETPFX)vault.o $(TARGETPFX)vision.o $(TARGETPFX)weapon.o \
	$(TARGETPFX)were.o $(TARGETPFX)wield.o $(TARGETPFX)windows.o \
	$(TARGETPFX)wizard.o $(TARGETPFX)worm.o $(TARGETPFX)worn.o \
	$(TARGETPFX)write.o $(TARGETPFX)zap.o \
	$(REGEXOBJ) $(RANDOBJ) $(SYSOBJ) $(WINOBJ) $(HINTOBJ) \
	$(TARGETPFX)version.o
#
DATE_O = $(TARGETPFX)date.o

# the .o files from the HACKCSRC, SYSSRC, and WINSRC lists

# first target is also the default target for 'make' without any arguments
all:	$(GAME)
	@echo ""

pregame:
	$(PREGAME)

$(GAME):	pregame $(MAKEDEFS) $(LUALIB) $(SYSTEM)
	@echo "$(GAME) is up to date."

Sysunix:	$(HOSTOBJ) $(HOBJ) $(DATE_O) $(BUILDMORE) Makefile
	@echo "Linking $(GAME)."
	$(AT)$(TARGET_LINK) $(TARGET_LFLAGS) -o $(GAMEBIN) \
		$(HOBJ) $(DATE_O) $(WINLIB) $(TARGET_LIBS) $(LUALIBS)
	@touch Sysunix

Sys3B2:	$(HOSTOBJ) $(HOBJ) $(DATE_O) $(BUILDMORE) Makefile
	@echo "Linking $(GAME)."
	$(AT)$(TARGET_LINK) $(TARGET_LFLAGS) -o $(GAMEBIN) \
		$(HOBJ) $(DATE_O) $(WINLIB) $(LUALIBS) -lmalloc
	@touch Sys3B2

Sysatt:	$(HOSTOBJ) $(HOBJ) $(DATE_O) $(BUILDMORE) Makefile
	@echo "Loading $(GAME)."
	$(AT)$(LD) $(TARGET_LFLAGS) /lib/crt0s.o /lib/shlib.ifile \
		-o $(GAMEBIN) $(HOSTOBJ) $(HOBJ) $(DATE_O) $(LUALIBS)
	@touch Sysatt

Systos:	$(HOSTOBJ) $(HOBJ) $(DATE_O) $(BUILDMORE) Makefile
	@echo "Linking $(GAME)."
	$(AT)$(TARGET_LINK) $(TARGET_LFLAGS) -o $(GAMEBIN) \
		$(HOBJ) $(DATE_O) $(WINLIB) $(LUALIBS)
	@touch Systos

SysV-AT:	DUMB.Setup $(HOSTOBJ) $(HOBJ) $(DATE_O) $(BUILDMORE) Makefile
	@echo "Linking $(GAME)."
	$(AT)$(TARGET_LINK) $(TARGET_LFLAGS) -o $(GAMEBIN) \
		$(HOBJ) $(DATE_O) $(WINLIB) $(LUALIBS)
	@touch SysV-AT

SysBe: $(HOSTOBJ) $(HOBJ) $(DATE_O) $(BUILDMORE) Makefile
	@echo "Linking $(GAME)."
	$(AT)$(TARGET_LINK) $(TARGET_LFLAGS) -o $(GAME) \
		$(HOBJ) $(DATE_O) $(WINLIB) $(TARGET_LIBS) $(LUALIBS)
	@xres -o $(GAME) ../win/BeOS/nethack.rsrc
	@mimeset -f $(GAME)
	@touch SysBe

DUMB.Setup:	../include/extern.h
	cp ../include/extern.h ../include/extern.h.BAK
	cat ../include/extern.h | \
		sed -e '/^E\ int\ /!b' \
			-e '/[^;/ 	]$$/N' \
			-e '/[(][*]occupation[)]/b' \
			-e '/[(][*]afternmv[)]/b' \
			-e '/float_down/b' \
			-e '/done1/b' \
			-e '/identify/b' \
			-e '/Hear_again/b' \
			-e '/hangup/b' \
			-e 's/^\(.*\)$$/\/\* \1 \/\*\*\//' | \
		sed -e '/^E\ void\ /!b' \
			-e '/[^;/ 	]$$/N' \
			-e 's/^\(.*\)$$/\/\* \1 \/\*\*\//' \
				>../include/extern.DUMB
	cp ../include/extern.DUMB ../include/extern.h
	@touch DUMB.Setup

$(LUALIB) ../include/nhlua.h:
	@( cd .. ; $(MAKE) lua_support )

#	dependencies for makedefs and its outputs, which the util
#	Makefile is responsible for keeping up to date
#

# special rules, to force update of makedefs, real dependencies should be
# below in the 'make depend' output.
monst.o:
	$(CC) $(CFLAGS) -c -o $@ monst.c
	@rm -f $(MAKEDEFS)

objects.o:
	$(CC) $(CFLAGS) -c -o $@ objects.c
	@rm -f $(MAKEDEFS)

# outdated Qt 3 windowport meta-object-compiler output
qt3_kde0.moc: ../win/Qt3/qt3_kde0.h
	$(QTDIR)/bin/moc -o qt3kde0.moc ../win/Qt3/qt3_kde0.h
qt3_win.moc: ../win/Qt3/qt3_win.h
	$(QTDIR)/bin/moc -o qt3win.moc ../win/Qt3/qt3_win.h
qt3tableview.moc: ../win/Qt3/qt3tableview.h
	$(QTDIR)/bin/moc -o qt3tableview.moc ../win/Qt3/qt3tableview.h

#	build monst.o and objects.o before executing '$(MAKE) makedefs'
$(MAKEDEFS): $(FIRSTOBJ) \
		../util/makedefs.c ../src/mdlib.c $(CONFIG_H) \
		../include/permonst.h ../include/monsters.h \
		../include/objclass.h ../include/objects.h ../include/sym.h \
		../include/defsym.h ../include/artilist.h \
		../include/dungeon.h ../include/obj.h ../include/monst.h \
		../include/you.h ../include/flag.h ../include/dlb.h \
		../include/patchlevel.h
	@( cd ../util ; $(MAKE) makedefs )

#	Source files formerly created by 'makedefs' at build time
#	but no longer used.
../include/onames.h: $(MAKEDEFS)
	@( cd ../util ; $(MAKE) ../include/onames.h )
../include/pm.h: $(MAKEDEFS)
	@( cd ../util ; $(MAKE) ../include/pm.h )
#	Created at build time for configurations which support tiles,
#	but not by makedefs so not connected to the others.
tile.c: ../win/share/tilemap.c $(HACK_H)
	@( cd ../util ; $(MAKE) ../src/tile.c )


../win/gnome/gn_rip.h: ../win/X11/rip.xpm
	cp ../win/X11/rip.xpm ../win/gnome/gn_rip.h

$(TARGETPFX)sfstruct.o: sfstruct.c $(HACK_H)

#	date.c should be recompiled any time any of the source or include code
#	is modified.
$(TARGETPFX)date.o: date.c $(HACK_H) $(HACKCSRC) $(HOBJ)
	$(TARGET_CC) $(TARGET_CFLAGS) $(GITHASH) $(GITBRANCH) -c -o $@ date.c

#	date.h should be remade any time any of the source or include code
#	is modified.  Unfortunately, this would make the contents of this
#	file far more complex.  Since "hack.h" depends on most of the include
#	files, we kludge around this by making date.h dependent on hack.h,
#	even though it doesn't include this file.
#	Do NOT include ../dat/gitinfo.txt as either a prerequisite or target.
#	'makedefs -v' processes it when present and ignores it if not.
#
../include/date.h: ../util/makedefs $(VERSOURCES) $(HACK_H)
	-$(SHELL) ../sys/unix/gitinfo.sh $(GITINFO) #before 'makedefs -v'
	../util/makedefs -v

lint:
# lint cannot have -p here because (i) capitals are meaningful:
# [Ww]izard, (ii) identifiers may coincide in the first six places:
# doweararm() versus dowearring().
# _flsbuf comes from <stdio.h>, a bug in the system libraries.
	@echo lint -axbh -DLINT ...
	@lint -axbh -I../include -DLINT $(CSOURCES) | sed '/_flsbuf/d'


tags: $(CSOURCES)
	@echo ctags -tw ...
	@ctags -tw $(CSOURCES)
	@( cd ../include ; ctags -tw $(HSOURCES) )
	@( cd ../util ; $(MAKE) tags )

clean:
	-rm -f *.o $(HACK_H) $(CONFIG_H)
	-rm -f monstr.c vis_tab.c ../include/vis_tab.h #obsolete generated files
	$(CLEANMORE)

spotless: clean
	-rm -f a.out core $(GAMEBIN) Sys*
	-rm -f ../include/nhlua.h
	-rm -f ../include/date.h #created but no longer used, at least by core
	-rm -f ../include/onames.h ../include/pm.h #obsolete generated files
	-rm -f tile.c *.moc Qt*.h-t
	-rm -f ../win/gnome/gn_rip.h

package:
	$(PACKAGE)
	@echo packaging complete.

depend: ../sys/unix/depend.awk \
		$(SYSCSRC) $(WINCSRC) $(SYSCXXSRC) $(WINCXXSRC) \
		$(CHAINSRC) $(GENCSRC) $(HACKCSRC)
	$(AWK) -f ../sys/unix/depend.awk ../include/*.h ../win/*/*.h \
		$(SYSCSRC) $(WINCSRC) $(SYSCXXSRC) $(WINCXXSRC) \
		$(CHAINSRC) $(GENCSRC) $(HACKCSRC) >makedep
	@echo '/^# DO NOT DELETE THIS LINE OR CHANGE ANYTHING BEYOND IT/+2,$$d' >eddep
	@echo '$$r makedep' >>eddep
	@echo 'w' >>eddep
	@cp Makefile Makefile.bak
	ed - Makefile < eddep
	@rm -f eddep makedep
	@echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	@echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	@echo '# see make depend above' >> Makefile
	- diff Makefile.bak Makefile
	@rm -f Makefile.bak

# DO NOT DELETE THIS LINE OR CHANGE ANYTHING BEYOND IT

# config.h timestamp
$(CONFIG_H): ../include/config.h ../include/config1.h ../include/patchlevel.h \
		../include/tradstdc.h ../include/integer.h \
		../include/global.h ../include/coord.h ../include/vmsconf.h \
		../include/system.h ../include/nhlua.h ../include/unixconf.h \
		../include/pcconf.h ../include/micro.h ../include/windconf.h \
		../include/warnings.h ../include/fnamesiz.h
	touch $(CONFIG_H)
# hack.h timestamp
$(HACK_H): ../include/hack.h $(CONFIG_H) ../include/lint.h ../include/align.h \
		../include/dungeon.h ../include/wintype.h ../include/sym.h \
		../include/defsym.h ../include/mkroom.h ../include/artilist.h \
		../include/objclass.h ../include/objects.h \
		../include/youprop.h ../include/prop.h ../include/permonst.h \
		../include/monattk.h ../include/monflag.h \
		../include/monsters.h ../include/mondata.h \
		../include/context.h ../include/rm.h ../include/botl.h \
		../include/rect.h ../include/region.h ../include/trap.h \
		../include/display.h ../include/vision.h ../include/color.h \
		../include/decl.h ../include/quest.h ../include/spell.h \
		../include/obj.h ../include/engrave.h ../include/you.h \
		../include/attrib.h ../include/monst.h ../include/mextra.h \
		../include/skills.h ../include/timeout.h ../include/flag.h \
		../include/winprocs.h ../include/sys.h
	touch $(HACK_H)
#
$(TARGETPFX)pcmain.o: ../sys/share/pcmain.c $(HACK_H) ../include/dlb.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/pcmain.c
$(TARGETPFX)pcsys.o: ../sys/share/pcsys.c $(HACK_H) ../include/wintty.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/pcsys.c
$(TARGETPFX)pctty.o: ../sys/share/pctty.c $(HACK_H) ../include/wintty.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/pctty.c
$(TARGETPFX)pcunix.o: ../sys/share/pcunix.c $(HACK_H) ../include/wintty.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/pcunix.c
$(TARGETPFX)pmatchregex.o: ../sys/share/pmatchregex.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/pmatchregex.c
$(TARGETPFX)posixregex.o: ../sys/share/posixregex.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/posixregex.c
$(TARGETPFX)random.o: ../sys/share/random.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/random.c
$(TARGETPFX)ioctl.o: ../sys/share/ioctl.c $(HACK_H) ../include/tcap.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/ioctl.c
$(TARGETPFX)unixtty.o: ../sys/share/unixtty.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/share/unixtty.c
$(TARGETPFX)unixmain.o: ../sys/unix/unixmain.c $(HACK_H) ../include/dlb.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/unix/unixmain.c
$(TARGETPFX)unixunix.o: ../sys/unix/unixunix.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/unix/unixunix.c
$(TARGETPFX)unixres.o: ../sys/unix/unixres.c $(CONFIG_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../sys/unix/unixres.c
$(TARGETPFX)getline.o: ../win/tty/getline.c $(HACK_H) ../include/wintty.h \
		../include/func_tab.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/tty/getline.c
$(TARGETPFX)termcap.o: ../win/tty/termcap.c $(HACK_H) ../include/wintty.h \
		../include/tcap.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/tty/termcap.c
$(TARGETPFX)topl.o: ../win/tty/topl.c $(HACK_H) ../include/tcap.h \
		../include/wintty.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/tty/topl.c
$(TARGETPFX)wintty.o: ../win/tty/wintty.c $(HACK_H) ../include/dlb.h \
		../include/tcap.h ../include/wintty.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/tty/wintty.c
$(TARGETPFX)cursmain.o: ../win/curses/cursmain.c $(HACK_H) ../include/wincurs.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/cursmain.c
$(TARGETPFX)curswins.o: ../win/curses/curswins.c $(HACK_H) \
		../include/wincurs.h ../win/curses/curswins.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/curswins.c
$(TARGETPFX)cursmisc.o: ../win/curses/cursmisc.c $(HACK_H) \
		../include/wincurs.h ../win/curses/cursmisc.h \
		../include/func_tab.h ../include/dlb.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/cursmisc.c
$(TARGETPFX)cursdial.o: ../win/curses/cursdial.c $(HACK_H) \
		../include/wincurs.h ../win/curses/cursdial.h \
		../include/func_tab.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/cursdial.c
$(TARGETPFX)cursstat.o: ../win/curses/cursstat.c $(HACK_H) \
		../include/wincurs.h ../win/curses/cursstat.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/cursstat.c
$(TARGETPFX)cursinit.o: ../win/curses/cursinit.c $(HACK_H) \
		../include/wincurs.h ../win/curses/cursinit.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/cursinit.c
$(TARGETPFX)cursmesg.o: ../win/curses/cursmesg.c $(HACK_H) \
		../include/wincurs.h ../win/curses/cursmesg.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/cursmesg.c
$(TARGETPFX)cursinvt.o: ../win/curses/cursinvt.c $(HACK_H) \
		../include/wincurs.h ../win/curses/cursinvt.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/curses/cursinvt.c
$(TARGETPFX)Window.o: ../win/X11/Window.c ../include/xwindowp.h \
		../include/xwindow.h $(CONFIG_H) ../include/lint.h \
		../include/winX.h ../include/color.h ../include/wintype.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/Window.c
$(TARGETPFX)dialogs.o: ../win/X11/dialogs.c $(CONFIG_H) ../include/lint.h \
		../include/winX.h ../include/color.h ../include/wintype.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/dialogs.c
$(TARGETPFX)winX.o: ../win/X11/winX.c $(HACK_H) ../include/winX.h \
		../include/dlb.h ../include/xwindow.h ../win/X11/nh72icon \
		../win/X11/nh56icon ../win/X11/nh32icon
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/winX.c
$(TARGETPFX)winmap.o: ../win/X11/winmap.c ../include/xwindow.h $(HACK_H) \
		../include/dlb.h ../include/winX.h ../include/tile2x11.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/winmap.c
$(TARGETPFX)winmenu.o: ../win/X11/winmenu.c $(HACK_H) ../include/winX.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/winmenu.c
$(TARGETPFX)winmesg.o: ../win/X11/winmesg.c ../include/xwindow.h $(HACK_H) \
		../include/winX.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/winmesg.c
$(TARGETPFX)winmisc.o: ../win/X11/winmisc.c $(HACK_H) ../include/func_tab.h \
		../include/winX.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/winmisc.c
$(TARGETPFX)winstat.o: ../win/X11/winstat.c $(HACK_H) ../include/winX.h \
		../include/xwindow.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/winstat.c
$(TARGETPFX)wintext.o: ../win/X11/wintext.c $(HACK_H) ../include/winX.h \
		../include/xwindow.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/wintext.c
$(TARGETPFX)winval.o: ../win/X11/winval.c $(HACK_H) ../include/winX.h
	$(TARGET_CC) $(TARGET_CFLAGS) $(X11CFLAGS) -c -o $@ ../win/X11/winval.c
$(TARGETPFX)tile.o: tile.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ tile.c
$(TARGETPFX)winshim.o: ../win/shim/winshim.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/shim/winshim.c
$(TARGETPFX)cppregex.o: ../sys/share/cppregex.cpp $(CONFIG_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../sys/share/cppregex.cpp
$(TARGETPFX)qt_bind.o: ../win/Qt/qt_bind.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_bind.h ../win/Qt/qt_main.h \
		../win/Qt/qt_kde0.h ../win/Qt/qt_click.h ../win/Qt/qt_delay.h \
		../win/Qt/qt_xcmd.h ../win/Qt/qt_key.h ../win/Qt/qt_map.h \
		../win/Qt/qt_win.h ../win/Qt/qt_clust.h ../win/Qt/qt_menu.h \
		../win/Qt/qt_rip.h ../win/Qt/qt_msg.h ../win/Qt/qt_plsel.h \
		../win/Qt/qt_svsel.h ../win/Qt/qt_set.h ../win/Qt/qt_stat.h \
		../win/Qt/qt_icon.h ../win/Qt/qt_streq.h ../win/Qt/qt_line.h \
		../win/Qt/qt_yndlg.h ../win/Qt/qt_str.h ../include/dlb.h \
		$(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_bind.cpp
$(TARGETPFX)qt_click.o: ../win/Qt/qt_click.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_click.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_click.cpp
$(TARGETPFX)qt_clust.o: ../win/Qt/qt_clust.cpp ../win/Qt/qt_clust.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_clust.cpp
$(TARGETPFX)qt_delay.o: ../win/Qt/qt_delay.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_delay.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_delay.cpp
$(TARGETPFX)qt_glyph.o: ../win/Qt/qt_glyph.cpp $(HACK_H) \
		../include/tile2x11.h ../win/Qt/qt_pre.h ../win/Qt/qt_post.h \
		../win/Qt/qt_glyph.h ../win/Qt/qt_bind.h ../win/Qt/qt_main.h \
		../win/Qt/qt_kde0.h ../win/Qt/qt_set.h ../win/Qt/qt_inv.h \
		../win/Qt/qt_map.h ../win/Qt/qt_win.h ../win/Qt/qt_clust.h \
		../win/Qt/qt_str.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_glyph.cpp
$(TARGETPFX)qt_icon.o: ../win/Qt/qt_icon.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_icon.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_icon.cpp
$(TARGETPFX)qt_inv.o: ../win/Qt/qt_inv.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_inv.h ../win/Qt/qt_glyph.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h ../win/Qt/qt_set.h \
		../win/Qt/qt_bind.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_inv.cpp
$(TARGETPFX)qt_key.o: ../win/Qt/qt_key.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_key.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_key.cpp
$(TARGETPFX)qt_line.o: ../win/Qt/qt_line.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_line.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_line.cpp
$(TARGETPFX)qt_main.o: ../win/Qt/qt_main.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_main.h ../win/Qt/qt_kde0.h \
		qt_main.moc ../win/Qt/qt_bind.h ../win/Qt/qt_glyph.h \
		../win/Qt/qt_inv.h ../win/Qt/qt_key.h ../win/Qt/qt_map.h \
		../win/Qt/qt_win.h ../win/Qt/qt_clust.h ../win/Qt/qt_msg.h \
		../win/Qt/qt_set.h ../win/Qt/qt_stat.h ../win/Qt/qt_icon.h \
		../win/Qt/qt_str.h qt_kde0.moc $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_main.cpp
$(TARGETPFX)qt_map.o: ../win/Qt/qt_map.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_map.h ../win/Qt/qt_win.h \
		../win/Qt/qt_clust.h qt_map.moc ../win/Qt/qt_click.h \
		../win/Qt/qt_glyph.h ../win/Qt/qt_set.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h ../win/Qt/qt_str.h \
		$(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_map.cpp
$(TARGETPFX)qt_menu.o: ../win/Qt/qt_menu.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_menu.h ../win/Qt/qt_win.h \
		../win/Qt/qt_rip.h qt_menu.moc ../win/Qt/qt_key.h \
		../win/Qt/qt_glyph.h ../win/Qt/qt_set.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h ../win/Qt/qt_streq.h \
		../win/Qt/qt_line.h ../win/Qt/qt_str.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_menu.cpp
$(TARGETPFX)qt_msg.o: ../win/Qt/qt_msg.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_msg.h ../win/Qt/qt_win.h \
		qt_msg.moc ../win/Qt/qt_map.h ../win/Qt/qt_clust.h \
		../win/Qt/qt_set.h ../win/Qt/qt_bind.h ../win/Qt/qt_main.h \
		../win/Qt/qt_kde0.h ../win/Qt/qt_str.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_msg.cpp
$(TARGETPFX)qt_plsel.o: ../win/Qt/qt_plsel.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_plsel.h qt_plsel.moc \
		../win/Qt/qt_bind.h ../win/Qt/qt_main.h ../win/Qt/qt_kde0.h \
		../win/Qt/qt_glyph.h ../win/Qt/qt_set.h ../win/Qt/qt_str.h \
		$(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_plsel.cpp
$(TARGETPFX)qt_rip.o: ../win/Qt/qt_rip.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_rip.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h ../win/Qt/qt_str.h \
		$(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_rip.cpp
$(TARGETPFX)qt_set.o: ../win/Qt/qt_set.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_set.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h qt_set.moc \
		../win/Qt/qt_glyph.h ../win/Qt/qt_xcmd.h ../win/Qt/qt_str.h \
		$(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_set.cpp
$(TARGETPFX)qt_stat.o: ../win/Qt/qt_stat.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_stat.h ../win/Qt/qt_win.h \
		../win/Qt/qt_icon.h qt_stat.moc ../win/Qt/qt_set.h \
		../win/Qt/qt_bind.h ../win/Qt/qt_main.h ../win/Qt/qt_kde0.h \
		../win/Qt/qt_str.h ../win/Qt/qt_xpms.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_stat.cpp
$(TARGETPFX)qt_str.o: ../win/Qt/qt_str.cpp ../win/Qt/qt_str.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_str.cpp
$(TARGETPFX)qt_streq.o: ../win/Qt/qt_streq.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_streq.h ../win/Qt/qt_line.h \
		../win/Qt/qt_str.h ../win/Qt/qt_set.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_streq.cpp
$(TARGETPFX)qt_svsel.o: ../win/Qt/qt_svsel.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_svsel.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h ../win/Qt/qt_str.h \
		$(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_svsel.cpp
$(TARGETPFX)qt_win.o: ../win/Qt/qt_win.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_win.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h ../win/Qt/qt_click.h \
		../win/Qt/qt_glyph.h ../win/Qt/qt_inv.h ../win/Qt/qt_key.h \
		../win/Qt/qt_icon.h ../win/Qt/qt_map.h ../win/Qt/qt_clust.h \
		../win/Qt/qt_menu.h ../win/Qt/qt_rip.h ../win/Qt/qt_msg.h \
		../win/Qt/qt_set.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_win.cpp
$(TARGETPFX)qt_xcmd.o: ../win/Qt/qt_xcmd.cpp $(HACK_H) ../include/func_tab.h \
		../win/Qt/qt_pre.h ../win/Qt/qt_post.h ../win/Qt/qt_xcmd.h \
		qt_xcmd.moc ../win/Qt/qt_key.h ../win/Qt/qt_bind.h \
		../win/Qt/qt_main.h ../win/Qt/qt_kde0.h ../win/Qt/qt_set.h \
		../win/Qt/qt_str.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_xcmd.cpp
$(TARGETPFX)qt_yndlg.o: ../win/Qt/qt_yndlg.cpp $(HACK_H) ../win/Qt/qt_pre.h \
		../win/Qt/qt_post.h ../win/Qt/qt_yndlg.h qt_yndlg.moc \
		../win/Qt/qt_key.h ../win/Qt/qt_str.h $(QTn_H)
	$(TARGET_CXX) $(TARGET_CXXFLAGS) -c -o $@ ../win/Qt/qt_yndlg.cpp
qt_kde0.moc: ../win/Qt/qt_kde0.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_kde0.h
qt_main.moc: ../win/Qt/qt_main.h ../win/Qt/qt_kde0.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_main.h
qt_map.moc: ../win/Qt/qt_map.h ../win/Qt/qt_win.h ../win/Qt/qt_clust.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_map.h
qt_menu.moc: ../win/Qt/qt_menu.h ../win/Qt/qt_win.h ../win/Qt/qt_rip.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_menu.h
qt_msg.moc: ../win/Qt/qt_msg.h ../win/Qt/qt_win.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_msg.h
qt_plsel.moc: ../win/Qt/qt_plsel.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_plsel.h
qt_set.moc: ../win/Qt/qt_set.h ../win/Qt/qt_bind.h ../win/Qt/qt_main.h \
		../win/Qt/qt_kde0.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_set.h
qt_stat.moc: ../win/Qt/qt_stat.h ../win/Qt/qt_win.h ../win/Qt/qt_icon.h \
		$(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_stat.h
qt_xcmd.moc: ../win/Qt/qt_xcmd.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_xcmd.h
qt_yndlg.moc: ../win/Qt/qt_yndlg.h $(QTn_H)
	$(MOCPATH) -o $@ ../win/Qt/qt_yndlg.h
$(TARGETPFX)wc_chainin.o: ../win/chain/wc_chainin.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/chain/wc_chainin.c
$(TARGETPFX)wc_chainout.o: ../win/chain/wc_chainout.c $(HACK_H)
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/chain/wc_chainout.c
$(TARGETPFX)wc_trace.o: ../win/chain/wc_trace.c $(HACK_H) ../include/wintty.h \
		../include/func_tab.h
	$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ ../win/chain/wc_trace.c
$(TARGETPFX)allmain.o: allmain.c $(HACK_H)
$(TARGETPFX)alloc.o: alloc.c $(CONFIG_H)
$(TARGETPFX)apply.o: apply.c $(HACK_H)
$(TARGETPFX)artifact.o: artifact.c $(HACK_H) ../include/artifact.h
$(TARGETPFX)attrib.o: attrib.c $(HACK_H)
$(TARGETPFX)ball.o: ball.c $(HACK_H)
$(TARGETPFX)bones.o: bones.c $(HACK_H)
$(TARGETPFX)botl.o: botl.c $(HACK_H)
$(TARGETPFX)cmd.o: cmd.c $(HACK_H) ../include/func_tab.h
$(TARGETPFX)dbridge.o: dbridge.c $(HACK_H)
$(TARGETPFX)decl.o: decl.c $(HACK_H)
$(TARGETPFX)detect.o: detect.c $(HACK_H) ../include/artifact.h
$(TARGETPFX)dig.o: dig.c $(HACK_H)
$(TARGETPFX)display.o: display.c $(HACK_H)
$(TARGETPFX)dlb.o: dlb.c $(CONFIG_H) ../include/dlb.h
$(TARGETPFX)do.o: do.c $(HACK_H)
$(TARGETPFX)do_name.o: do_name.c $(HACK_H)
$(TARGETPFX)do_wear.o: do_wear.c $(HACK_H)
$(TARGETPFX)dog.o: dog.c $(HACK_H)
$(TARGETPFX)dogmove.o: dogmove.c $(HACK_H) ../include/mfndpos.h
$(TARGETPFX)dokick.o: dokick.c $(HACK_H)
$(TARGETPFX)dothrow.o: dothrow.c $(HACK_H)
$(TARGETPFX)drawing.o: drawing.c $(CONFIG_H) ../include/color.h \
		../include/rm.h ../include/objclass.h ../include/defsym.h \
		../include/objects.h ../include/wintype.h ../include/sym.h
$(TARGETPFX)dungeon.o: dungeon.c $(HACK_H) ../include/dgn_file.h \
		../include/dlb.h
$(TARGETPFX)eat.o: eat.c $(HACK_H)
$(TARGETPFX)end.o: end.c $(HACK_H) ../include/dlb.h
$(TARGETPFX)engrave.o: engrave.c $(HACK_H)
$(TARGETPFX)exper.o: exper.c $(HACK_H)
$(TARGETPFX)explode.o: explode.c $(HACK_H)
$(TARGETPFX)extralev.o: extralev.c $(HACK_H)
$(TARGETPFX)files.o: files.c $(HACK_H) ../include/dlb.h ../include/wintty.h \
		#zlib.h
$(TARGETPFX)fountain.o: fountain.c $(HACK_H)
$(TARGETPFX)hack.o: hack.c $(HACK_H)
$(TARGETPFX)hacklib.o: hacklib.c $(HACK_H)
$(TARGETPFX)insight.o: insight.c $(HACK_H)
$(TARGETPFX)invent.o: invent.c $(HACK_H)
$(TARGETPFX)isaac64.o: isaac64.c $(CONFIG_H) ../include/isaac64.h
$(TARGETPFX)light.o: light.c $(HACK_H)
$(TARGETPFX)lock.o: lock.c $(HACK_H)
$(TARGETPFX)mail.o: mail.c $(HACK_H) ../include/mail.h
$(TARGETPFX)makemon.o: makemon.c $(HACK_H)
$(TARGETPFX)mcastu.o: mcastu.c $(HACK_H)
$(TARGETPFX)mdlib.o: mdlib.c $(CONFIG_H) ../include/permonst.h \
		../include/align.h ../include/monattk.h ../include/monflag.h \
		../include/monsters.h ../include/objclass.h \
		../include/defsym.h ../include/objects.h ../include/wintype.h \
		../include/sym.h ../include/artilist.h ../include/dungeon.h \
		../include/obj.h ../include/monst.h ../include/mextra.h \
		../include/you.h ../include/attrib.h ../include/prop.h \
		../include/skills.h ../include/context.h ../include/flag.h \
		../include/dlb.h
$(TARGETPFX)mhitm.o: mhitm.c $(HACK_H) ../include/artifact.h
$(TARGETPFX)mhitu.o: mhitu.c $(HACK_H) ../include/artifact.h
$(TARGETPFX)minion.o: minion.c $(HACK_H)
$(TARGETPFX)mklev.o: mklev.c $(HACK_H)
$(TARGETPFX)mkmap.o: mkmap.c $(HACK_H) ../include/sp_lev.h
$(TARGETPFX)mkmaze.o: mkmaze.c $(HACK_H) ../include/sp_lev.h
$(TARGETPFX)mkobj.o: mkobj.c $(HACK_H)
$(TARGETPFX)mkroom.o: mkroom.c $(HACK_H)
$(TARGETPFX)mon.o: mon.c $(HACK_H) ../include/mfndpos.h
$(TARGETPFX)mondata.o: mondata.c $(HACK_H)
$(TARGETPFX)monmove.o: monmove.c $(HACK_H) ../include/mfndpos.h \
		../include/artifact.h
$(TARGETPFX)monst.o: monst.c $(CONFIG_H) ../include/permonst.h \
		../include/align.h ../include/monattk.h ../include/monflag.h \
		../include/monsters.h ../include/wintype.h ../include/sym.h \
		../include/defsym.h ../include/color.h
$(TARGETPFX)mplayer.o: mplayer.c $(HACK_H)
$(TARGETPFX)mthrowu.o: mthrowu.c $(HACK_H)
$(TARGETPFX)muse.o: muse.c $(HACK_H)
$(TARGETPFX)music.o: music.c $(HACK_H)
$(TARGETPFX)nhlua.o: nhlua.c $(HACK_H) ../include/dlb.h
$(TARGETPFX)nhlsel.o: nhlsel.c $(HACK_H) ../include/sp_lev.h
$(TARGETPFX)nhlobj.o: nhlobj.c $(HACK_H) ../include/sp_lev.h
$(TARGETPFX)o_init.o: o_init.c $(HACK_H)
$(TARGETPFX)objects.o: objects.c $(CONFIG_H) ../include/obj.h \
		../include/prop.h ../include/skills.h ../include/color.h \
		../include/objclass.h ../include/defsym.h ../include/objects.h
$(TARGETPFX)objnam.o: objnam.c $(HACK_H)
$(TARGETPFX)options.o: options.c $(CONFIG_H) ../include/objclass.h \
		../include/defsym.h ../include/objects.h ../include/flag.h \
		$(HACK_H) ../include/tcap.h ../include/optlist.h
$(TARGETPFX)pager.o: pager.c $(HACK_H) ../include/dlb.h
$(TARGETPFX)pickup.o: pickup.c $(HACK_H)
$(TARGETPFX)pline.o: pline.c $(HACK_H)
$(TARGETPFX)polyself.o: polyself.c $(HACK_H)
$(TARGETPFX)potion.o: potion.c $(HACK_H)
$(TARGETPFX)pray.o: pray.c $(HACK_H)
$(TARGETPFX)priest.o: priest.c $(HACK_H) ../include/mfndpos.h
$(TARGETPFX)quest.o: quest.c $(HACK_H)
$(TARGETPFX)questpgr.o: questpgr.c $(HACK_H) ../include/dlb.h \
		../include/wintty.h
$(TARGETPFX)read.o: read.c $(HACK_H)
$(TARGETPFX)rect.o: rect.c $(HACK_H)
$(TARGETPFX)region.o: region.c $(HACK_H)
$(TARGETPFX)restore.o: restore.c $(HACK_H) ../include/tcap.h
$(TARGETPFX)rip.o: rip.c $(HACK_H)
$(TARGETPFX)rnd.o: rnd.c $(HACK_H) ../include/isaac64.h
$(TARGETPFX)role.o: role.c $(HACK_H)
$(TARGETPFX)rumors.o: rumors.c $(HACK_H) ../include/dlb.h
$(TARGETPFX)save.o: save.c $(HACK_H)
$(TARGETPFX)sfstruct.o: sfstruct.c $(HACK_H)
$(TARGETPFX)shk.o: shk.c $(HACK_H)
$(TARGETPFX)shknam.o: shknam.c $(HACK_H)
$(TARGETPFX)sit.o: sit.c $(HACK_H) ../include/artifact.h
$(TARGETPFX)sounds.o: sounds.c $(HACK_H)
$(TARGETPFX)sp_lev.o: sp_lev.c $(HACK_H) ../include/sp_lev.h
$(TARGETPFX)spell.o: spell.c $(HACK_H)
$(TARGETPFX)steal.o: steal.c $(HACK_H)
$(TARGETPFX)steed.o: steed.c $(HACK_H)
$(TARGETPFX)symbols.o: symbols.c $(HACK_H) ../include/tcap.h
$(TARGETPFX)sys.o: sys.c $(HACK_H)
$(TARGETPFX)teleport.o: teleport.c $(HACK_H)
$(TARGETPFX)timeout.o: timeout.c $(HACK_H)
$(TARGETPFX)topten.o: topten.c $(HACK_H) ../include/dlb.h
$(TARGETPFX)track.o: track.c $(HACK_H)
$(TARGETPFX)trap.o: trap.c $(HACK_H)
$(TARGETPFX)u_init.o: u_init.c $(HACK_H)
$(TARGETPFX)utf8map.o: utf8map.c $(HACK_H)
$(TARGETPFX)uhitm.o: uhitm.c $(HACK_H)
$(TARGETPFX)vault.o: vault.c $(HACK_H)
$(TARGETPFX)version.o: version.c $(HACK_H) ../include/dlb.h
$(TARGETPFX)vision.o: vision.c $(HACK_H)
$(TARGETPFX)weapon.o: weapon.c $(HACK_H)
$(TARGETPFX)were.o: were.c $(HACK_H)
$(TARGETPFX)wield.o: wield.c $(HACK_H)
$(TARGETPFX)windows.o: windows.c $(HACK_H) ../include/dlb.h ../include/wintty.h
$(TARGETPFX)wizard.o: wizard.c $(HACK_H)
$(TARGETPFX)worm.o: worm.c $(HACK_H)
$(TARGETPFX)worn.o: worn.c $(HACK_H)
$(TARGETPFX)write.o: write.c $(HACK_H)
$(TARGETPFX)zap.o: zap.c $(HACK_H)
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
### End Makefile.src

###
### Start hints/macOS.370 POST
###
# (new segment at source line 374 )

#
# NetHack 3.7  gbdates-post.370 $NHDT-Date: 1599687610 2020/09/09 21:40:10 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.11 $
ifdef MAKEFILE_DOC
ifdef GB_DATESTAMP
Guidebook.dated.mn: $(GUIDEBOOK_MN_SRC)
	@awk 'f{$$0=".ds f2 \"$(GB_DATESTAMP)";f=0}/NH_DATESUB/{f=1} 1' < $(GUIDEBOOK_MN_SRC) > $@
Guidebook.dated.tex: $(GUIDEBOOK_TEX_SRC)
	@awk 'f{$$0="\\date{$(GB_DATESTAMP)}";f=0}/NH_DATESUB/{f=1} 1' < $(GUIDEBOOK_TEX_SRC) > $@
endif   # GB_DATESTAMP

Guidebook.pdf: Guidebook.dated.tex
	pdflatex -interaction=nonstopmode -jobname=Guidebook Guidebook.dated.tex
	pdflatex -interaction=nonstopmode -jobname=Guidebook Guidebook.dated.tex
endif   # MAKEFILE_DOC
#
#

ifdef WANT_LIBNH
$(TARGETPFX)libnh.a: $(HOBJ) $(LIBNHSYSOBJ) ../lib/lua/liblua.a
	$(AR) rcs $@ $(HOBJ) $(LIBNHSYSOBJ) ../lib/lua/liblua.a
	@echo "$@ built."
$(TARGETPFX)libnhmain.o : ../sys/libnh/libnhmain.c $(HACK_H)
	$(CC) $(CFLAGS) -c -o$@ $<
$(TARGETPFX)winshim.o : ../win/shim/winshim.c $(HACK_H)
	$(CC) $(CFLAGS) -c -o$@ $<
endif  # WANT_LIBNH

ifdef MAKEFILE_TOP
###
### Packaging
###
# Notes:
# 1) The Apple developer utilities must be installed in the default location.
# 2) Do a normal build before trying to package the game.
# 3) This matches the 3.4.3 Term package, but there are some things that
#    should be changed.
#
# Packages that are being distributed must be signed by a Developer ID
# Installer certificate.  Set DEVELOPER_CERT to the name of the certificate
# if you wish for your package to be signed for distribution.
#
# If building a package for signing, you must use sudo approriately.
# the binaries and package using sudo but you DO NOT use sudo to sign the
# package.  If you use sudo to sign the package, it will fail.
#
#   sudo make all
#   sudo make build_tty_pkg
#   make sign_tty_pkg
#

ifdef WANT_WIN_TTY
DEVUTIL=/Developer/Applications/Utilities
SVS=$(shell $(NHSROOT)/util/makedefs --svs)
SVSDOT=$(shell $(NHSROOT)/util/makedefs --svs .)

PKGROOT_UG	= PKGROOT/$(PREFIX)
PKGROOT_UGLN	= PKGROOT/$(HACKDIR)
PKGROOT_BIN	= PKGROOT/$(SHELLDIR)

#DEVELOPER_CERT = Developer ID Installer: Bart House
DEVELOPER_CERT = NONE

spotless::
	rm -rf RESOURCES
	rm -rf PKG
	rm -rf PKGSCRIPTS
	rm -rf PKGROOT
	rm -f Info.plist
	rm -f Distribution.xml
	rm -f NetHack-*-mac-Term*

build_tty_pkg:
ifneq (,$(WANT_WIN_X11)$(WANT_WIN_QT))
	-echo build_tty_pkg only works for a tty-only build
	exit 1
else
	rm -rf NetHack-$(SVS)-mac-Term.pkg NetHack-$(SVS)-mac-Term.dmg
	$(MAKE) build_package_root
	rm -rf RESOURCES
	mkdir RESOURCES
	#enscript --language=rtf -o - < dat/license >RESOURCES/License.rtf
	sys/unix/hints/macosx.sh descplist > RESOURCES/Description.plist
	sys/unix/hints/macosx.sh infoplist > Info.plist

	mkdir PKGROOT/Applications
	#osacompile -o NetHackQt/NetHackQt.app/nethackdir/NetHackRecover.app \
	#	 win/macosx/NetHackRecover.applescript
	#cp win/macosx/recover.pl NetHackQt/NetHackQt.app/nethackdir
	osacompile -o PKGROOT/Applications/NetHackRecover.app \
		 win/macosx/NetHackRecover.applescript
	cp win/macosx/recover.pl $(PKGROOT_UGLN)

	osacompile -o PKGROOT/Applications/NetHackTerm.app \
		 win/macosx/NetHackTerm.applescript

	# XXX integrate into Makefile.doc
	(cd doc; cat Guidebook.mn | ../util/makedefs --grep --input - --output - \
	| tbl tmac.n - | groff | pstopdf -i -o Guidebook.pdf)
	cp doc/Guidebook.pdf $(PKGROOT_UG)/doc/NetHackGuidebook.pdf

	osacompile -o PKGROOT/Applications/NetHackGuidebook.app \
		 win/macosx/NetHackGuidebook.applescript

	mkdir -p PKG
	pkgbuild --root PKGROOT --identifier org.nethack.term --scripts PKGSCRIPTS PKG/NH-Term.pkg
	productbuild --synthesize --product Info.plist --package PKG/NH-Term.pkg Distribution.xml
	productbuild --distribution Distribution.xml --resources RESOURCES --package-path PKG NetHack-$(SVS)-mac-Term-unsigned.pkg
ifeq ($(DEVELOPER_CERT),NONE)
	cp NetHack-$(SVS)-mac-Term-unsigned.pkg NetHack-$(SVS)-mac-Term.pkg
	hdiutil create -verbose -srcfolder NetHack-$(SVS)-mac-Term-unsigned.pkg NetHack-$(SVS)-mac-Term-unsigned.dmg
	@echo -------------------------------------------
	@echo PACKAGE IS NOT SIGNED FOR DISTRIBUTION!!!!!
	@echo ===========================================
else
	@echo "run 'make sign_tty_pkg' to complete package"
endif

sign_tty_pkg:
	productsign --timestamp=none --sign "$(DEVELOPER_CERT)" NetHack-$(SVS)-mac-Term-unsigned.pkg NetHack-$(SVS)-mac-Term.pkg || (echo "Package signing failed"; exit 1)
	spctl -a -v --type install NetHack-$(SVS)-mac-Term.pkg || (echo "Package not signed properly"; exit 1)
	hdiutil create -verbose -srcfolder NetHack-$(SVS)-mac-Term.pkg NetHack-$(SVS)-mac-Term.dmg

build_package_root:
	cd src/..       # make sure we are at TOP
	rm -rf PKGROOT
	mkdir -p $(PKGROOT_UG)/lib $(PKGROOT_BIN) $(PKGROOT_UG)/man/man6 $(PKGROOT_UG)/doc $(PKGROOT_UGLN)
	install -p src/nethack $(PKGROOT_BIN)
	# XXX should this be called nethackrecover?
	install -p util/recover $(PKGROOT_BIN)
	install -p doc/nethack.6 $(PKGROOT_UG)/man/man6
	install -p doc/recover.6 $(PKGROOT_UG)/man/man6
	install -p doc/Guidebook $(PKGROOT_UG)/doc
	install -p dat/nhdat $(PKGROOT_UGLN)
	sys/unix/hints/macosx.sh editsysconf sys/unix/sysconf $(PKGROOT_UGLN)/sysconf
	cd dat; install -p $(DATNODLB) ../$(PKGROOT_UGLN)
# XXX these files should be somewhere else for good Mac form
	touch $(PKGROOT_UGLN)/perm $(PKGROOT_UGLN)/record $(PKGROOT_UGLN)/logfile $(PKGROOT_UGLN)/xlogfile $(PKGROOT_UGLN)/livelog
	mkdir $(PKGROOT_UGLN)/save
# XXX what about a news file?

	mkdir -p PKGSCRIPTS
	echo '#!/bin/sh'                              >  PKGSCRIPTS/postinstall
	echo dseditgroup -o create -r '"Games Group"' -s 3600 $(GAMEGRP) >> PKGSCRIPTS/postinstall
	echo $(CHOWN) $(GAMEUID) $(HACKDIR)        >> PKGSCRIPTS/postinstall
	echo $(CHOWN) $(GAMEUID) $(HACKDIR)/*        >> PKGSCRIPTS/postinstall
	echo $(CHGRP) $(GAMEGRP) $(HACKDIR)        >> PKGSCRIPTS/postinstall
	echo $(CHGRP) $(GAMEGRP) $(HACKDIR)/*        >> PKGSCRIPTS/postinstall
	echo $(CHOWN) $(GAMEUID) $(SHELLDIR)/nethack  >> PKGSCRIPTS/postinstall
	echo $(CHGRP) $(GAMEGRP) $(SHELLDIR)/nethack  >> PKGSCRIPTS/postinstall
	echo $(CHOWN) $(GAMEUID) $(SHELLDIR)/recover  >> PKGSCRIPTS/postinstall
	echo $(CHGRP) $(GAMEGRP) $(SHELLDIR)/recover  >> PKGSCRIPTS/postinstall
	echo chmod $(VARDIRPERM)  $(HACKDIR)          >> PKGSCRIPTS/postinstall
	echo chmod $(VARDIRPERM)  $(HACKDIR)/save     >> PKGSCRIPTS/postinstall
	echo chmod $(FILEPERM)    $(HACKDIR)/license  >> PKGSCRIPTS/postinstall
	echo chmod $(FILEPERM)    $(HACKDIR)/nhdat    >> PKGSCRIPTS/postinstall
	echo chmod $(FILEPERM)    $(HACKDIR)/symbols  >> PKGSCRIPTS/postinstall
	echo chmod $(VARFILEPERM) $(HACKDIR)/perm     >> PKGSCRIPTS/postinstall
	echo chmod $(VARFILEPERM) $(HACKDIR)/record   >> PKGSCRIPTS/postinstall
	echo chmod $(VARFILEPERM) $(HACKDIR)/logfile  >> PKGSCRIPTS/postinstall
	echo chmod $(VARFILEPERM) $(HACKDIR)/xlogfile >> PKGSCRIPTS/postinstall
	echo chmod $(VARFILEPERM) $(HACKDIR)/livelog  >> PKGSCRIPTS/postinstall
	echo chmod $(VARFILEPERM) $(HACKDIR)/sysconf  >> PKGSCRIPTS/postinstall
	echo chmod $(GAMEPERM)   $(SHELLDIR)/nethack  >> PKGSCRIPTS/postinstall
	echo chmod $(EXEPERM)    $(SHELLDIR)/recover  >> PKGSCRIPTS/postinstall
	chmod 0775 PKGSCRIPTS/postinstall

endif	# end of build_tty_pkg
endif	# WANT_WIN_TTY for packaging

ifdef WANT_WIN_QT
# XXX untested and incomplete (see below)
build_qt_pkg:
ifneq (,$(WANT_WIN_X11)$(WANT_WIN_TTY))
	-echo build_qt_pkg only works for a qt-only build
	exit 1
else
	$(MAKE) build_package_root
	rm -rf NetHackQt
	mkdir -p NetHackQt/NetHackQt.app/nethackdir/save
	mkdir NetHackQt/Documentation
	cp doc/Guidebook.txt doc/nethack.txt doc/recover.txt NetHackQt/Documentation

	osacompile -o NetHackQt/NetHackQt.app/nethackdir/NetHackRecover.app \
		 win/macosx/NetHackRecover.applescript
	cp win/macosx/recover.pl NetHackQt/NetHackQt.app/nethackdir

	mkdir -p NetHackQt/NetHackQt.app/Contents/Frameworks
	cp $(QTDIR)/libqt-mt.3.dylib NetHackQt/NetHackQt.app/Contents/Frameworks

	mkdir NetHackQt/NetHackQt.app/Contents/MacOS
	mv PKGROOT/nethack NetHackQt/NetHackQt.app/Contents/MacOS

	mv PKGROOT/lib/nethackdir NetHackQt/NetHackQt.app/nethackdir

# XXX still missing:
#NetHackQt/NetHackQt.app
# /Contents
#	Info.plist
#	Resources/nethack.icns
#NetHackQt/Documentation
#NetHackQtRecover.txt
#NetHack Defaults.txt
#changes.patch XXX is this still needed?  why isn't it part of the tree?
#  doesn't go here
	hdiutil create -verbose -srcfolder NetHackQt NetHack-$(SVS)-macosx-qt.dmg
endif	# end of build_qt_pkg
endif	# WANT_WIN_QT for packaging
endif	# MAKEFILE_TOP
#
#===============-=================================================
# NetHack 3.7  include/cross-post $NHDT-Date: 1597332785 2020/08/13 15:33:05 $  $NHDT-Branch: NetHack-3.7 $
#
# Cross-compiling -POST section

ifdef CROSS_TO_MSDOS
#
$(TARGETPFX)msdos.o : ../sys/msdos/msdos.c $(HACK_H)
$(TARGETPFX)font.o : ../sys/msdos/font.c ../sys/msdos/font.h $(HACK_H)
$(TARGETPFX)pckeys.o : ../sys/msdos/pckeys.c $(HACK_H)
$(TARGETPFX)pctiles.o : ../sys/msdos/pctiles.c ../sys/msdos/portio.h $(HACK_H)
$(TARGETPFX)video.o : ../sys/msdos/video.c ../sys/msdos/portio.h $(HACK_H)
$(TARGETPFX)vidtxt.o : ../sys/msdos/vidtxt.c ../sys/msdos/portio.h \
		../win/share/tile.h ../include/tileset.h $(HACK_H)
$(TARGETPFX)vidvga.o : ../sys/msdos/vidvga.c ../sys/msdos/portio.h \
		../win/share/tile.h ../include/tileset.h $(HACK_H)
$(TARGETPFX)vidvesa.o : ../sys/msdos/vidvesa.c ../sys/msdos/portio.h \
		../win/share/tile.h ../include/tileset.h ../sys/msdos/font.h $(HACK_H)
$(TARGETPFX)vidstub.o : ../sys/msdos/vidvesa.c ../sys/msdos/portio.h \
		$(HACK_H)
$(TARGETPFX)tile.o : tile.c
$(TARGETPFX)exceptn.o : ../lib/djgpp/djgpp-patch/src/libc/go32/exceptn.S
	$(TARGET_CC) -c -o $@ ../lib/djgpp/djgpp-patch/src/libc/go32/exceptn.S
	$(TARGET_AR) ru ../lib/djgpp/i586-pc-msdosdjgpp/lib/libc.a $(TARGETPFX)exceptn.o
$(GAMEBIN) : $(HOBJ) $(LUACROSSLIB)
	$(TARGET_LINK) $(TARGET_LFLAGS) -o $(GAMEBIN) \
	$(HOBJ) $(WINLIB) $(TARGET_LIBS)
$(DOSFONT)/ter-u16b.psf: $(FONTTOP)/ter-u16b.bdf $(DOSFONT)/nh-u16b.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u16b.bdf $(DOSFONT)/nh-u16b.bdf $@
$(DOSFONT)/ter-u16v.psf: $(FONTTOP)/ter-u16v.bdf $(DOSFONT)/nh-u16v.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u16v.bdf $(DOSFONT)/nh-u16v.bdf $@
$(DOSFONT)/ter-u18b.psf: $(FONTTOP)/ter-u18b.bdf $(DOSFONT)/nh-u18b.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u18b.bdf $(DOSFONT)/nh-u18b.bdf $@
$(DOSFONT)/ter-u20b.psf: $(FONTTOP)/ter-u20b.bdf $(DOSFONT)/nh-u20b.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u20b.bdf $(DOSFONT)/nh-u20b.bdf $@
$(DOSFONT)/ter-u22b.psf: $(FONTTOP)/ter-u22b.bdf $(DOSFONT)/nh-u22b.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u22b.bdf $(DOSFONT)/nh-u22b.bdf $@
$(DOSFONT)/ter-u24b.psf: $(FONTTOP)/ter-u24b.bdf $(DOSFONT)/nh-u24b.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u24b.bdf $(DOSFONT)/nh-u24b.bdf $@
$(DOSFONT)/ter-u28b.psf: $(FONTTOP)/ter-u28b.bdf $(DOSFONT)/nh-u28b.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u28b.bdf $(DOSFONT)/nh-u28b.bdf $@
$(DOSFONT)/ter-u32b.psf: $(FONTTOP)/ter-u32b.bdf $(DOSFONT)/nh-u32b.bdf $(DOSFONT)/makefont.lua $(LUABIN)
	$(LUABIN) $(DOSFONT)/makefont.lua $(FONTTOP)/ter-u32b.bdf $(DOSFONT)/nh-u32b.bdf $@
#
.PHONY: dodata dospkg dosfonts
dosfonts: $(FONTTARGETS)
dospkg: dodata dosfonts $(GAMEBIN) $(TARGETPFX)recover.exe ../dat/nhtiles.bmp
	$(TARGET_STUBEDIT) $(GAMEBIN) minstack=2048K
	mkdir -p $(TARGETPFX)pkg
	cp $(GAMEBIN) $(TARGETPFX)pkg/NETHACK.EXE
	cp $(TARGETPFX)recover.exe $(TARGETPFX)pkg/RECOVER.EXE
	cp ../dat/nhdat $(TARGETPFX)pkg/NHDAT
	cp ../dat/license $(TARGETPFX)pkg/LICENSE
	cp ../dat/nhtiles.bmp $(TARGETPFX)pkg/NHTILES.BMP
	cp ../dat/symbols $(TARGETPFX)pkg/SYMBOLS
	cp ../sys/share/NetHack.cnf $(TARGETPFX)pkg/NETHACK.CNF
	cp ../sys/msdos/sysconf $(TARGETPFX)pkg/SYSCONF
	cp ../doc/nethack.txt $(TARGETPFX)pkg/NETHACK.TXT
	cp $(DOSFONT)/ter-u16b.psf $(TARGETPFX)pkg/TER-U16B.PSF
	cp $(DOSFONT)/ter-u16v.psf $(TARGETPFX)pkg/TER-U16V.PSF
	cp $(DOSFONT)/ter-u18b.psf $(TARGETPFX)pkg/TER-U18B.PSF
	cp $(DOSFONT)/ter-u20b.psf $(TARGETPFX)pkg/TER-U20B.PSF
	cp $(DOSFONT)/ter-u22b.psf $(TARGETPFX)pkg/TER-U22B.PSF
	cp $(DOSFONT)/ter-u24b.psf $(TARGETPFX)pkg/TER-U24B.PSF
	cp $(DOSFONT)/ter-u28b.psf $(TARGETPFX)pkg/TER-U28B.PSF
	cp $(DOSFONT)/ter-u32b.psf $(TARGETPFX)pkg/TER-U32B.PSF
	cp  ../lib/djgpp/cwsdpmi/bin/CWSDPMI.EXE $(TARGETPFX)pkg/CWSDPMI.EXE
	-touch $(TARGETPFX)pkg/RECORD
	cd $(TARGETPFX)pkg ; zip -9 ../NH370DOS.ZIP * ; cd ../../..
	@echo msdos package zip file $(TARGETPFX)NH370DOS.ZIP

$(LUABIN):
	( cd .. && make luabin && cd src)
dodata:
	( cd .. && make dlb && cd src)

endif  # CROSS_TO_MSDOS

ifdef CROSS_TO_WASM
$(WASM_TARGET): pregame $(TARGETPFX)date.o $(HOSTOBJ) $(HOBJ) $(LUACROSSLIB) $(WASM_DATA_DIR)
	-rm $@
	$(TARGET_CC) $(TARGET_LFLAGS) $(TARGET_CFLAGS) -o $@ \
		$(HOBJ) $(TARGETPFX)date.o $(TARGET_LIBS)

$(WASM_DATA_DIR): $(WASM_DATA_DIR)/nhdat
	touch $(WASM_DATA_DIR)/perm
	touch $(WASM_DATA_DIR)/record
	touch $(WASM_DATA_DIR)/logfile
	touch $(WASM_DATA_DIR)/xlogfile
	touch $(WASM_DATA_DIR)/livelog
	cp ../sys/libnh/sysconf $(WASM_DATA_DIR)/sysconf

$(WASM_DATA_DIR)/nhdat:
	( cd ..; $(MAKE) INSTDIR='$(WASM_DATA_DIR)' $(WASMDEP) dofiles-dlb )

#
$(TARGETPFX)unixmain.o : ../sys/unix/unixmain.c $(HACK_H)
$(TARGETPFX)unixres.o : ../sys/unix/unixres.c $(HACK_H)
$(TARGETPFX)unixunix.o : ../sys/unix/unixunix.c $(HACK_H)
$(TARGETPFX)ioctl.o : ../sys/share/ioctl.c $(HACK_H)
$(TARGETPFX)unixtty.o : ../sys/share/unixtty.c $(HACK_H)
$(TARGETPFX)winshim.o : ../win/shim/winshim.c $(HACK_H)
$(TARGETPFX)libnhmain.o : ../sys/libnh/libnhmain.c $(HACK_H)
endif  # CROSS_TO_WASM
#

ifdef CROSS_SHARED
# shared file dependencies
$(TARGETPFX)pcmain.o : ../sys/share/pcmain.c $(HACK_H)
$(TARGETPFX)pcsys.o : ../sys/share/pcsys.c $(HACK_H)
$(TARGETPFX)pctty.o : ../sys/share/pctty.c $(HACK_H)
$(TARGETPFX)pcunix.o : ../sys/share/pcunix.c $(HACK_H)
$(TARGETPFX)tileset.o : ../win/share/tileset.c
$(TARGETPFX)bmptiles.o : ../win/share/bmptiles.c
$(TARGETPFX)giftiles.o : ../win/share/giftiles.c
$(TARGETPFX)recover.o : ../util/recover.c
$(TARGETPFX)recover.exe : $(TARGETPFX)recover.o
	$(TARGET_LINK) $(TARGET_LFLAGS) $(TARGETPFX)recover.o -o $@
endif  # CROSS_SHARED
#
ifdef BUILD_TARGET_LUA
# Lua lib
$(LUACROSSLIB): $(LUALIBOBJS)
	if [ -f $@ ]; then rm $@; fi;
	$(TARGET_AR) rcS $@ $(LUAOBJFILES1)
	$(TARGET_AR) rcS $@ $(LUAOBJFILES2)
	$(TARGET_AR) rcS $@ $(LUAOBJFILES3)
	$(TARGET_AR) rcs $@ $(LUAOBJFILES4)

#	$(TARGET_AR) rcs $@ $(LUALIBOBJS)

# Lua src
$(TARGETPFX)lapi.o : $(LUATOP)/src/lapi.c
$(TARGETPFX)lauxlib.o : $(LUATOP)/src/lauxlib.c
$(TARGETPFX)lbaselib.o : $(LUATOP)/src/lbaselib.c
$(TARGETPFX)lbitlib.o : $(LUATOP)/src/lbitlib.c
$(TARGETPFX)lcode.o : $(LUATOP)/src/lcode.c
$(TARGETPFX)lcorolib.o : $(LUATOP)/src/lcorolib.c
$(TARGETPFX)lctype.o : $(LUATOP)/src/lctype.c
$(TARGETPFX)ldblib.o : $(LUATOP)/src/ldblib.c
$(TARGETPFX)ldebug.o : $(LUATOP)/src/ldebug.c
$(TARGETPFX)ldo.o : $(LUATOP)/src/ldo.c
$(TARGETPFX)ldump.o : $(LUATOP)/src/ldump.c
$(TARGETPFX)lfunc.o : $(LUATOP)/src/lfunc.c
$(TARGETPFX)lgc.o : $(LUATOP)/src/lgc.c
$(TARGETPFX)linit.o : $(LUATOP)/src/linit.c
$(TARGETPFX)liolib.o : $(LUATOP)/src/liolib.c
$(TARGETPFX)llex.o : $(LUATOP)/src/llex.c
$(TARGETPFX)lmathlib.o : $(LUATOP)/src/lmathlib.c
$(TARGETPFX)lmem.o : $(LUATOP)/src/lmem.c
$(TARGETPFX)loadlib.o : $(LUATOP)/src/loadlib.c
$(TARGETPFX)lobject.o : $(LUATOP)/src/lobject.c
$(TARGETPFX)lopcodes.o : $(LUATOP)/src/lopcodes.c
$(TARGETPFX)loslib.o : $(LUATOP)/src/loslib.c
$(TARGETPFX)lparser.o : $(LUATOP)/src/lparser.c
$(TARGETPFX)lstate.o : $(LUATOP)/src/lstate.c
$(TARGETPFX)lstring.o : $(LUATOP)/src/lstring.c
$(TARGETPFX)lstrlib.o : $(LUATOP)/src/lstrlib.c
$(TARGETPFX)ltable.o : $(LUATOP)/src/ltable.c
$(TARGETPFX)ltablib.o : $(LUATOP)/src/ltablib.c
$(TARGETPFX)ltm.o : $(LUATOP)/src/ltm.c
$(TARGETPFX)lundump.o : $(LUATOP)/src/lundump.c
$(TARGETPFX)lutf8lib.o : $(LUATOP)/src/lutf8lib.c
$(TARGETPFX)lvm.o : $(LUATOP)/src/lvm.c
$(TARGETPFX)lzio.o : $(LUATOP)/src/lzio.c
endif  # BUILD_TARGET_LUA

ifdef BUILD_PDCURSES
ifdef WANT_WIN_CURSES
$(TARGETPFX)pdclib.a : $(PDCLIBOBJS) $(PDCOBJS)
	if [ -f $@ ]; then rm $@; fi;
	$(TARGET_AR) rcs $@ $(PDCLIBOBJS) $(PDCOBJS)
endif
# PDCurses src
$(TARGETPFX)addch.o : $(PDCTOP)/pdcurses/addch.c
$(TARGETPFX)addchstr.o : $(PDCTOP)/pdcurses/addchstr.c
$(TARGETPFX)addstr.o : $(PDCTOP)/pdcurses/addstr.c
$(TARGETPFX)attr.o : $(PDCTOP)/pdcurses/attr.c
$(TARGETPFX)beep.o : $(PDCTOP)/pdcurses/beep.c
$(TARGETPFX)bkgd.o : $(PDCTOP)/pdcurses/bkgd.c
$(TARGETPFX)border.o : $(PDCTOP)/pdcurses/border.c
$(TARGETPFX)clear.o : $(PDCTOP)/pdcurses/clear.c
$(TARGETPFX)color.o : $(PDCTOP)/pdcurses/color.c
$(TARGETPFX)delch.o : $(PDCTOP)/pdcurses/delch.c
$(TARGETPFX)deleteln.o : $(PDCTOP)/pdcurses/deleteln.c
$(TARGETPFX)getch.o : $(PDCTOP)/pdcurses/getch.c
$(TARGETPFX)getstr.o : $(PDCTOP)/pdcurses/getstr.c
$(TARGETPFX)getyx.o : $(PDCTOP)/pdcurses/getyx.c
$(TARGETPFX)inch.o : $(PDCTOP)/pdcurses/inch.c
$(TARGETPFX)inchstr.o : $(PDCTOP)/pdcurses/inchstr.c
$(TARGETPFX)initscr.o : $(PDCTOP)/pdcurses/initscr.c
$(TARGETPFX)inopts.o : $(PDCTOP)/pdcurses/inopts.c
$(TARGETPFX)insch.o : $(PDCTOP)/pdcurses/insch.c
$(TARGETPFX)insstr.o : $(PDCTOP)/pdcurses/insstr.c
$(TARGETPFX)instr.o : $(PDCTOP)/pdcurses/instr.c
$(TARGETPFX)kernel.o : $(PDCTOP)/pdcurses/kernel.c
$(TARGETPFX)keyname.o : $(PDCTOP)/pdcurses/keyname.c
$(TARGETPFX)mouse.o : $(PDCTOP)/pdcurses/mouse.c
$(TARGETPFX)move.o : $(PDCTOP)/pdcurses/move.c
$(TARGETPFX)outopts.o : $(PDCTOP)/pdcurses/outopts.c
$(TARGETPFX)overlay.o : $(PDCTOP)/pdcurses/overlay.c
$(TARGETPFX)pad.o : $(PDCTOP)/pdcurses/pad.c
$(TARGETPFX)panel.o : $(PDCTOP)/pdcurses/panel.c
$(TARGETPFX)printw.o : $(PDCTOP)/pdcurses/printw.c
$(TARGETPFX)refresh.o : $(PDCTOP)/pdcurses/refresh.c
$(TARGETPFX)scanw.o : $(PDCTOP)/pdcurses/scanw.c
$(TARGETPFX)scr_dump.o : $(PDCTOP)/pdcurses/scr_dump.c
$(TARGETPFX)scroll.o : $(PDCTOP)/pdcurses/scroll.c
$(TARGETPFX)slk.o : $(PDCTOP)/pdcurses/slk.c
$(TARGETPFX)termattr.o : $(PDCTOP)/pdcurses/termattr.c
$(TARGETPFX)touch.o : $(PDCTOP)/pdcurses/touch.c
$(TARGETPFX)util.o : $(PDCTOP)/pdcurses/util.c
$(TARGETPFX)window.o : $(PDCTOP)/pdcurses/window.c
$(TARGETPFX)debug.o : $(PDCTOP)/pdcurses/debug.c
$(TARGETPFX)pdcclip.o : $(PDCPORT)/pdcclip.c
$(TARGETPFX)pdcdisp.o : $(PDCPORT)/pdcdisp.c
$(TARGETPFX)pdcgetsc.o : $(PDCPORT)/pdcgetsc.c
$(TARGETPFX)pdckbd.o : $(PDCPORT)/pdckbd.c
$(TARGETPFX)pdcscrn.o : $(PDCPORT)/pdcscrn.c
$(TARGETPFX)pdcsetsc.o : $(PDCPORT)/pdcsetsc.c
$(TARGETPFX)pdcutil.o : $(PDCPORT)/pdcutil.c
endif  # BUILD_PDCURSES
#
# End of cross-compiling -POST section
#===============-=================================================


#
### End hints/macOS.370 POST
