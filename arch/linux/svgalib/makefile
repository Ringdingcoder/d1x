TOPDIR = ../../..

include $(TOPDIR)/pre.mak

OBJECTS += init.$(OBJ)

ifdef SVGALIB_VIDEO
OBJECTS += gr.$(OBJ)
endif

ifdef SVGALIB_INPUT
OBJECTS += mouse.$(OBJ) key_arch.$(OBJ) event.$(OBJ)
endif

OUTPUT = $(LIBDIR)svgalib.$(ARC)

include $(TOPDIR)/default.mak
CFLAGS += -I$(TOPDIR)/main
