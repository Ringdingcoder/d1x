TOPDIR = ..

include $(TOPDIR)/pre.mak

ifdef ENV_DJGPP
SUBDIRS = dos
endif
ifdef ENV_LINUX
SUBDIRS = linux
ifdef SDL
SUBDIRS += sdl
endif
endif
ifdef ENV_MINGW32
SUBDIRS = win32
endif
ifdef ENV_MSVC
SUBDIRS = win32
endif
ifdef OGL
SUBDIRS += ogl
endif

include $(TOPDIR)/default.mak
