LIBDIR = $(TOPDIR)/lib/

include $(TOPDIR)/pre.mak

#Figured its better to put it here than in defines, since its not supposed
#to be set by the user, only the maintainer
D1XMAJOR = 1
D1XMINOR = 43
#for instance, to make ver 1.3, use major=1, minor=40
ifdef ENV_MSVC
# definitions for MS commandline tools
OBJ = obj
ARC = lib

CC=cl

CFLAGS = -nologo -c -W3 -Zi -I$(TOPDIR)/include \
	-I$(TOPDIR)/arch/win32/include -D__WINDOWS__
ifdef DEBUG
CFLAGS += -MDd -Od
else
ifdef DEBUGABLE
CFLAGS += -MDd -Od -DNDEBUG
else
CFLAGS += -MD -Ox -DNDEBUG
endif
endif
%.obj: %.c
	$(CC) $(CFLAGS) $(E_CFLAGS) /Fo$@ $^
%.obj: %.cpp
	$(CC) $(CFLAGS) $(E_CFLAGS) /Fo$@ $^
else #!ENV_MSVC
# definitions for gcc
OBJ = o
ARC = a
#CC = egcc
CC = gcc
ifdef ENV_DJGPP
CXX = gxx
else
CXX = g++
endif
ifdef CHECKER
CC = $(CHECKER)
LINKLIBS += -lm
endif
ifdef DEBUG
CFLAGS = -g -c -Wall -O -funsigned-char -I$(TOPDIR)/include
else #!DEBUG
CFLAGS = -g -c -Wall -O3  -funsigned-char -I$(TOPDIR)/include -DNDEBUG
ifndef DEBUGABLE
CFLAGS += -fomit-frame-pointer
endif #!DEBUGABLE
endif #!DEBUG
ifdef MINGW_EXTRA
CFLAGS += -I$(MINGW_EXTRA)/include
LFLAGS += -L$(MINGW_EXTRA)/lib
endif
ifdef ENV_CYGWIN
CFLAGS += -mno-cygwin
LFLAGS += -mno-cygwin
#CFLAGS += -mno-cygwin -mwindows
#LFLAGS += -mno-cygwin -mwindows
endif #ENV_CYGWIN
ifdef PROFILE
CFLAGS += -p
LFLAGS += -p
endif #PROFILE
endif #!ENV_MSVC
ifndef MONO
CFLAGS += -DNMONO
endif
ifdef NETWORK
CFLAGS += -DNETWORK
endif
ifdef RELEASE
CFLAGS += -DRELEASE 
endif
ifdef SHAREWARE
CFLAGS += -DSHAREWARE
endif
ifdef NO_ASM
CFLAGS += -DNO_ASM
endif
ifdef D1XD3D
CFLAGS += -DD1XD3D
endif
ifdef DXBASE
CFLAGS += -I$(DXBASE)/include
LINKLIBS += -L$(DXBASE)/lib
endif

ifdef NOERROR
CFLAGS += -Werror
endif

CFLAGS += -DD1XMAJOR=\"$(D1XMAJOR)\" -DD1XMINOR=\"$(D1XMINOR)\"

ifdef ENV_DJGPP
CFLAGS += -I$(TOPDIR)/arch/dos/include
ifdef ENV_DJGPP_REALDOS
NASM = nasm -f coff
else
NASM = nasmw -f coff
endif

ifdef ALLEGRO
CFLAGS += -DALLEGRO
endif
ifdef ALLG_MIDI
CFLAGS += -DALLG_MIDI
endif
ifdef MIKMOD
CFLAGS += -DMIKMOD
endif

endif

ifdef SUPPORTS_NET_IP
CFLAGS += -DSUPPORTS_NET_IP
endif
ifdef BIGENDIAN
CFLAGS += -DBIGENDIAN
endif


ifdef SDLGL_IO
LINKLIBS += -lGL -lGLU
CFLAGS += -DSDL_GL
endif

ifdef GLX_IO
LINKLIBS += -L/usr/X11R6/lib
ifndef OGL_RUNTIME
LINKLIBS += -lGL 
endif
#if -lGLU doesn't work, and you have a MesaGLU, it should be -lGLU, not MesaGLU...  symlink it..  or change this
LINKLIBS += -lGLU -lm -lX11 -lXext
CFLAGS += -DGLX_VIDEO
#LINKLIBS += -L/usr/X11R6/lib -lMesaGL  -lMesaGLU -lm -lX11 -lXext
endif
ifdef OGL
ifdef OGL_RUNTIME
CFLAGS += -DOGL_RUNTIME_LOAD
endif
CFLAGS += -I$(TOPDIR)/arch/ogl/include -DOGL
endif

ifdef ENV_LINUX
CFLAGS += -I$(TOPDIR)/arch/linux/include -D__LINUX__
ifdef GGI_VIDEO
LINKLIBS += -lggi
endif
ifdef GII_INPUT
LINKLIBS += -lgii
endif
ifdef GII_XWIN
CFLAGS += -DGII_XWIN
endif
ifdef SDL
ifdef STATICSDL
LINKLIBS += $(STATICSDL) -ldl -L/usr/X11R6/lib -lX11 -lXext -lXxf86dga -lXxf86vm
CFLAGS += -D_SDL_STATIC_LIB
else
LINKLIBS += `sdl-config --libs`
endif
endif
ifdef SVGALIB
LINKLIBS += -lvga -lvgagl
endif
ifdef GLIBC
CFLAGS += -D_REENTRANT
LINKLIBS += -lpthread
endif
NASM = nasm -f elf -d__LINUX__
ifdef HAVENETIPX
CFLAGS += -DHAVE_NETIPX_IPX_H
endif
endif

ifdef MAKE_EDITOR
CFLAGS += -DEDITOR -I.
ifdef ENV_LINUX
LINKLIBS += -lm
endif
endif

ifdef SVGALIB
CFLAGS += -D__SVGALIB__
ifdef SVGALIB_INPUT
CFLAGS += -I$(TOPDIR)/arch/linux/svgalib/include -DSVGALIB_INPUT
endif
ifdef SVGALIB_VIDEO
CFLAGS += -DSVGALIB_VIDEO
endif
endif

ifdef GGI
CFLAGS += -D__GGI__
ifdef GGI_VIDEO
CFLAGS += -DGGI_VIDEO
endif
ifdef GII_INPUT
CFLAGS += -I$(TOPDIR)/arch/linux/ggi/include -DGII_INPUT
endif
endif

ifdef SDL
CFLAGS += -D__SDL__
ifdef SDL_INPUT
CFLAGS += -I$(TOPDIR)/arch/sdl/include -DSDL_INPUT
endif
ifdef SDL_VIDEO
CFLAGS += -DSDL_VIDEO
endif
ifdef SDL_AUDIO
CFLAGS += -DSDL_AUDIO
endif
ifdef SDLROOTDIR
CFLAGS += -I$(SDLROOTDIR)/include
LINKLIBS += -L$(SDLROOTDIR)/lib
endif
endif

ifdef GR_LOCK
CFLAGS += -DGR_LOCK -DTEST_GR_LOCK
endif

ifdef ENV_MINGW32
CFLAGS += -I$(TOPDIR)/arch/win32/include -D__WINDOWS__
NASM = nasmw -f win32
endif

ifdef ENV_RSXDJGPP
CFLAGS += -Zwin32
endif

%.o: %.c
	$(CC) $(CFLAGS) $(E_CFLAGS) -o $@ $<
%.o: %.cpp
	$(CXX) $(CFLAGS) $(E_CFLAGS) -o $@ $<
%.o: %.asm
	$(NASM) $< -o $@
%.o: %.s
	$(CC) $(CFLAGS) $(patsubst %.s,%.S,$<) -o $@


ifdef SUBDIRS
ifdef ENV_LINUX
FOR=set -e; for I in
DO=; do 
DONE=$$I;done
else
ifeq ($(findstring /,$(SHELL)),/)
FOR=set -e; for I in
DO=; do 
DONE=$$I;done
else
FOR=for %%I in (
DO=) do 
DONE=%%I
endif
endif
endif
DOSUBS=$(FOR) $(SUBDIRS) $(DO) make -C $(DONE)
ifdef SUBDIRS
CLEANSUBS=$(FOR) $(SUBDIRS) $(DO) make clean -C $(DONE)
DEPSUBS=$(FOR) $(SUBDIRS) $(DO) make -k dep -C $(DONE)
endif

ifdef OBJECTS
ifdef CRAPPY_SHELL
CLEANOBJ=rm -f *.$(OBJ)
else
CLEANOBJ=rm -f $(OBJECTS) $(MISCOBJECTS)
endif
endif
ifdef OUTPUT
CLEANOUT=rm -f $(OUTPUT) $(MISCOUTPUT)
endif

AR=ar
STRIP=strip
WINDRES=windres

ifeq ($(TOPDIR)/overrides.mak,$(wildcard $(TOPDIR)/overrides.mak))
include $(TOPDIR)/overrides.mak
endif
