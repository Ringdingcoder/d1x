TOPDIR = ../..

include $(TOPDIR)/pre.mak

#OBJECTS += init.$(OBJ)

OBJECTS += gr.$(OBJ) ogl.$(OBJ)

ifdef SDLGL_IO
OBJECTS += sdlgl.$(OBJ)
endif
ifdef GLX_IO
OBJECTS += glx.$(OBJ)
endif
ifdef WGL_IO
OBJECTS += wgl.$(OBJ)
endif

OUTPUT = $(LIBDIR)ogl.$(ARC)

include $(TOPDIR)/default.mak
CFLAGS += -I$(TOPDIR)/main
