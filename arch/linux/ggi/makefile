TOPDIR = ../../..

include $(TOPDIR)/pre.mak

OBJECTS += init.$(OBJ)

ifdef GGI_VIDEO
OBJECTS += gr.$(OBJ)
endif

ifdef GII_INPUT
OBJECTS += key_arch.$(OBJ) mouse.$(OBJ) event.$(OBJ)
endif

OUTPUT = $(LIBDIR)ggi.$(ARC)

include $(TOPDIR)/default.mak
CFLAGS += -I$(TOPDIR)/main
