TOPDIR = ../..

include $(TOPDIR)/pre.mak

OBJECTS += init.$(OBJ)

ifdef SDL_AUDIO
OBJECTS += digi.$(OBJ)
endif

ifdef SDL_INPUT
OBJECTS += event.$(OBJ) key_arch.$(OBJ) mouse.$(OBJ)
endif

ifdef SDL_VIDEO
OBJECTS += gr.$(OBJ) 
endif

OUTPUT = $(LIBDIR)sdl.$(ARC)

include $(TOPDIR)/default.mak
CFLAGS += -I$(TOPDIR)/main
