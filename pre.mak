#this file must be included in all makefiles right after TOPDIR is defined
include $(TOPDIR)/defines.mak

ifdef ENV_DJGPP
SUPPORTS_NET_IP = 1
endif

ifdef ENV_LINUX
SUPPORTS_NET_IP = 1
endif

#cygwin is pretty much the same thing, just needs extra cmdline args
ifdef ENV_CYGWIN
SUPPORTS_NET_IP = 1
ENV_MINGW32 = 1
else
#cygwin can handle long command lines, but mingw can't.
ifdef ENV_MINGW32
SUPPORTS_NET_IP = 1
CRAPPY_SHELL = 1
endif
endif

ifdef ENV_MSVC
SUPPORTS_NET_IP = 1
CRAPPY_SHELL = 1
endif

ifdef ENV_DJGPP_REALDOS
ENV_DJGPP = 1
endif
ifdef ENV_DJGPP
CRAPPY_SHELL = 1
endif

#if we are doing a nonetwork build, we can't do internet either.
ifndef NETWORK
SUPPORTS_NET_IP=
endif

ifdef WGL_IO
OGL = 1
endif

ifdef GLX_IO
OGL = 1
GGI = 1
GII_XWIN = 1
GII_INPUT = 1
endif

ifdef SDLGL_IO
OGL = 1
SDL_INPUT = 1
SDL = 1
endif
ifdef SDL_IO
SDL_INPUT = 1
SDL_VIDEO = 1
SDL = 1
endif
ifdef SDL_AUDIO
SDL = 1
endif

ifdef SVGALIB_IO
SVGALIB_INPUT = 1
SVGALIB_VIDEO = 1
SVGALIB = 1
endif

ifdef GGI_IO
GII_INPUT = 1
GGI_VIDEO = 1
GGI = 1
endif

ifdef MAKE_EDITOR
NO_RL2 = 1
endif
ifdef SHAREWARE
NO_RL2 = 1
endif
