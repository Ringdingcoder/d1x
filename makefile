TOPDIR = .

include $(TOPDIR)/pre.mak

SUBDIRS = arch maths 2d 3d texmap misc mem iff cfile main

ifdef MAKE_EDITOR
SUBDIRS += editor ui 
D1XPREFIX = m
else
D1XPREFIX = d
endif



ifdef ENV_DJGPP
EXT=.exe
endif
ifdef ENV_MINGW32
EXT=mw.exe
endif
ifdef D1XD3D
EXT=3d.exe
endif

ifdef SHAREWARE
SHRWR = sh
else
ifdef DEBUG
DBG = db
else

ifdef ALLEGRO
#SDN = a
else
ifdef MIKMOD
ifdef ALLG_MIDI
SND = c
else
SND = b
endif
endif
endif

endif
endif

ifdef OGL
ifndef SND
SND = _
endif
OPT = ogl
endif

OUTPUT = $(D1XPREFIX)1x$(D1XMAJOR)$(D1XMINOR)$(SHRWR)$(DBG)$(SND)$(OPT)$(EXT)

LIBS = \
	$(LIBDIR)main.$(ARC)	\
	$(LIBDIR)3d.$(ARC)	\
	$(LIBDIR)2d.$(ARC)	\
	$(LIBDIR)iff.$(ARC)	\
	$(LIBDIR)maths.$(ARC)	\
	$(LIBDIR)cfile.$(ARC) \
	$(LIBDIR)mem.$(ARC)	\
	$(LIBDIR)misc.$(ARC)	\
	$(LIBDIR)texmap.$(ARC)	\
        $(LIBDIR)io.$(ARC)

ifdef NOERROR
E_CFLAGS += -Werror
endif

ifdef ENV_DJGPP
LIBS+= $(LIBDIR)wsock.$(ARC)
ifdef ALLEGRO
USE_ALLEGRO = 1
endif
ifdef ALLG_MIDI
USE_ALLEGRO = 1
endif
ifdef USE_ALLEGRO
LIBS += $(LIBDIR)allg_snd.$(ARC)
endif
ifdef MIKMOD
LIBS += $(LIBDIR)mmsnd.$(ARC)
endif
LIBS += $(LIBDIR)comm.$(ARC)
endif

ifdef ENV_MINGW32
ifdef WGL_IO
ifndef OGL_RUNTIME
LINKLIBS += -lopengl32
endif
LINKLIBS += -lglu32 -lgdi32
endif
LINKLIBS += -ldinput -lddraw -ldsound -ldxguid -lwsock32 -lwinmm -luser32 -lkernel32
endif

ifdef D1XD3D
LIBS += $(LIBDIR)d3dframe.$(ARC)
endif
ifdef ENV_MSVC
LIBS += $(LIBDIR)d1x.res
endif
ifdef ENV_MINGW32
LIBS += $(LIBDIR)d1x_res.$(OBJ)
endif
ifdef ENV_MSVC
LINKLIBS += dinput.lib ddraw.lib dsound.lib dxguid.lib wsock32.lib \
	winmm.lib user32.lib kernel32.lib gdi32.lib
ifdef DEBUG
LINKLIBS += msvcrtd.lib
else
LINKLIBS += msvcrt.lib
endif
ifdef RELEASE
LFLAGS = -OPT:REF -PDB:NONE
else
LFLAGS = -DEBUG -DEBUGTYPE:CV -PDB:$(TOPDIR)/lib/
endif
endif

ifdef SCRIPT
LIBS += $(LIBDIR)script.$(ARC)
E_CFLAGS += -DSCRIPT
endif

ifdef OGL
LIBS += $(LIBDIR)ogl.$(ARC)
endif

ifdef ENV_LINUX

ifdef SDL
LIBS += $(LIBDIR)sdl.$(ARC)
endif

ifdef SVGALIB
LIBS += $(LIBDIR)svgalib.$(ARC)
endif

ifdef GGI
LIBS += $(LIBDIR)ggi.$(ARC)
endif
endif

ifdef MAKE_EDITOR
NO_RL2 = 1
endif
ifdef SHAREWARE
NO_RL2 = 1
endif

ifdef MAKE_EDITOR
LIBS += $(LIBDIR)editor.$(ARC) $(LIBDIR)ui.$(ARC) ./2d/box.o
E_CFLAGS += -DEDITOR -I.
ifdef LINUX
LINKLIBS += -lm 
endif
endif

#these are in rules.mak now, to remove duplication -Matt Mueller
#ifdef OBJECTS
#CLEANOBJ=rm -f $(OBJECTS)
#endif
#ifdef OUTPUT
#CLEANOUT=rm -f $(OUTPUT)
#endif
#ifdef SUBDIRS
#ifdef ENV_LINUX
#CLEANSUBS=set -e; for I in $(SUBDIRS); do make -C $$I clean;done
#else
#ifdef ENV_MINGW32
#CLEANSUBS=$(SUBDIRS): dummy\
#	make -C $@
#else
#CLEANSUBS=for %I in ($(SUBDIRS)) do make -C %I clean
#endif
#endif
#CLEANSUBS=$(FOR) $(SUBDIRS) $(DO) make clean -C $(DONE)
#endif



include $(TOPDIR)/rules.mak

ifdef ENV_MSVC
$(OUTPUT):  $(SUBDIRS) $(LIBS)
	link $(LFLAGS) -out:$(OUTPUT)  -machine:i386 -subsystem:console $(LIBS) $(LINKLIBS)
else
$(OUTPUT):  $(SUBDIRS) $(LIBS)
ifdef CHECKER
	$(CC) $(LFLAGS) -o $(OUTPUT) $(TOPDIR)/main/inferno.o $(TOPDIR)/misc/checker.o $(LIBS) $(LINKLIBS) 
else
	$(CXX) $(LFLAGS) -o $(OUTPUT) $(LIBS) $(LINKLIBS) 
ifdef	RELEASE
ifndef DEBUGABLE
	$(STRIP) --strip-all $(OUTPUT)
endif
endif
endif
endif
#	 ld -X -o d1x.exe -L $(DJDIR)/lib $(OBJECTS) $(LIBS) $(DJDIR)/lib/crt0.o -lc -lgcc -T $(DJDIR)/lib/djgpp.djl

ifdef SUPPORTS_NET_IP
IP_DAEMON_OUTPUT=d1x_udpd_$(D1XMAJOR)$(D1XMINOR)$(SHRWR)$(DBG)$(EXT)
#IP_DAEMON_LIBS=$(TOPDIR)/main/ipserver.$(OBJ) $(TOPDIR)/main/ip_base.$(OBJ) $(TOPDIR)/main/ipclient.$(OBJ) $(TOPDIR)/arch/linux/arch_ip.$(OBJ)
IP_DAEMON_LIBS=$(TOPDIR)/main/ipserver.$(OBJ) $(TOPDIR)/arch/linux/arch_ip.$(OBJ) $(TOPDIR)/main/ip_base.$(OBJ) $(TOPDIR)/arch/linux/timer.$(OBJ) $(TOPDIR)/arch/linux/mono.$(OBJ) $(TOPDIR)/lib/maths.a $(TOPDIR)/main/args.$(OBJ) $(TOPDIR)/mem/mem.$(OBJ) $(TOPDIR)/misc/strio.$(OBJ) $(TOPDIR)/misc/strutil.$(OBJ) $(TOPDIR)/misc/error.$(OBJ)

d1x_udpd udpd ip_daemon udp_daemon: $(IP_DAEMON_OUTPUT)

$(IP_DAEMON_OUTPUT): $(SUBDIRS) $(IP_DAEMON_LIBS) 
	$(CC) $(LFLAGS) -o $(IP_DAEMON_OUTPUT) $(IP_DAEMON_LIBS)
endif

$(SUBDIRS): dummy
	make -C $@

dep depend:
	$(DEPSUBS)

clean:
	$(CLEANOBJ)
	$(CLEANOUT)
	$(CLEANSUBS)

dummy:
