TOPDIR = ../..

include $(TOPDIR)/defines.mak

OBJECTS = key_arch.$(OBJ) joy2.$(OBJ) mouse.$(OBJ) timer.$(OBJ) mono.$(OBJ) \
        joyc.$(OBJ) dpmi.$(OBJ) disk.$(OBJ) init.$(OBJ) \
        modex.$(OBJ) dosgr.$(OBJ) vesa.$(OBJ) \
        joydefs.$(OBJ) bcd.$(OBJ) \
        
	
ifdef NETWORK
OBJECTS += ipx.$(OBJ) serial.$(OBJ) arch_ip.$(OBJ)
endif

SUBDIRS = comm wsock

ifdef ALLEGRO
SUBDIRS += allg_snd
OBJECTS += digiallg.$(OBJ) midiallg.$(OBJ)
else
ifdef ALLG_MIDI
SUBDIRS += allg_snd
OBJECTS += midiallg.$(OBJ)
endif
endif

ifdef MIKMOD
SUBDIRS += mm_snd
OBJECTS += digimm.$(OBJ)
endif

OUTPUT = $(LIBDIR)io.$(ARC)

include $(TOPDIR)/default.mak

ifdef MIKMOD
CFLAGS += -Imm_snd/include
endif

CFLAGS += -I$(TOPDIR)/main
