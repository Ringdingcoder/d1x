TOPDIR = ..

include $(TOPDIR)/pre.mak

OBJECTS= error.$(OBJ) d_io.$(OBJ) d_glob.$(OBJ) strutil.$(OBJ) strio.$(OBJ) \
        d_delay.$(OBJ) compare.$(OBJ) d_slash.$(OBJ)

OUTPUT = $(LIBDIR)misc.$(ARC)
ifdef CHECKER
MISCOUTPUT = checker.$(OBJ)
endif

include $(TOPDIR)/default.mak

ifdef CHECKER
checker.$(OBJ): checker.c
	$(NORMALCC) $(CFLAGS) $(CHECKERINCLUDE) -c $^
endif
	
