include $(TOPDIR)/defines.mak

include $(TOPDIR)/rules.mak


CPPFLAGS= $(CFLAGS)

all: $(SUBDIRS) $(OUTPUT) $(MISCOUTPUT) $(MISCOBJECTS)

$(SUBDIRS): dummy
	make -C $@

$(filter %.a,$(OUTPUT)): $(OBJECTS)
	$(AR) rcs $@ $^

$(filter %.lib,$(OUTPUT)): $(OBJECTS)
	@lib -nologo -out:$@ $^

clean:
	$(CLEANOBJ)
	$(CLEANOUT)
	$(CLEANSUBS)

dummy:

#dependancy generation v2.  Works correctly for all file types.  No more errors. Yay.
# -Matt Mueller
#DEPFILE=.depend
#use dep.dep instead of .depend for dos compatibility.
DEPFILE=dep.dep
ifdef OUTPUT
DEPOBJ2=$(OBJECTS:.$(OBJ)=.dep2) $(MISCOBJECTS:.$(OBJ)=.dep2)
endif

#we don't actually create .dep2 files, but we need some way to let make do its
#magic of finding the correct source file (since a .o can be made by many types
#of source files.)
%.dep2: %.c
	$(CC) $(CFLAGS) $(E_CFLAGS) -MM $< >> $(DEPFILE)
%.dep2: %.cpp
	$(CXX) $(CFLAGS) $(E_CFLAGS) -MM $< >> $(DEPFILE) 
#dunno if this is the "right" way to make null rules, but it seems to work.
%.dep2: %.asm
	-
%.dep2: %.S
	-
%.dep2: %.s
	-
	
dep depend:
	-rm $(DEPFILE)
	make dep2_internal
	$(DEPSUBS)

#use two step dep process so it can delete .depend first. (since the rules dependancies are done before the rules actions)
dep2_internal: $(DEPOBJ2)


ifeq ($(DEPFILE),$(wildcard $(DEPFILE)))
include $(DEPFILE)
endif

