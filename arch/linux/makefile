TOPDIR = ../..

include $(TOPDIR)/pre.mak

OBJECTS = joystick.$(OBJ) init.$(OBJ) \
          joydefs.$(OBJ) mono.$(OBJ) \
          timer.$(OBJ)

ifdef NETWORK
OBJECTS += linuxnet.$(OBJ) ipx_bsd.$(OBJ) \
          ipx_kali.$(OBJ) ukali.$(OBJ) \
          serial.$(OBJ) arch_ip.$(OBJ)
endif

#ipx_udp.$(OBJ) 
	  
ifdef ALSA_AUDIO
OBJECTS += alsadigi.$(OBJ)
endif

ifdef HMIPLAY
OBJECTS += hmiplay.$(OBJ)
else
OBJECTS += hmistub.$(OBJ)
endif

ifdef SVGALIB
SUBDIRS += svgalib
endif

ifdef GGI
SUBDIRS += ggi
endif

OUTPUT = $(LIBDIR)io.$(ARC)

include $(TOPDIR)/default.mak

ifdef WANT_AWE32
CFLAGS += -DWANT_AWE32
endif
ifdef WANT_MPU401
CFLAGS += -DWANT_MPU401
endif

CFLAGS += -I$(TOPDIR)/main
