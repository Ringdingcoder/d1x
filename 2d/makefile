TOPDIR = ..

include $(TOPDIR)/pre.mak

OBJECTS =  \
        palette.$(OBJ) canvas.$(OBJ) \
	pixel.$(OBJ) rect.$(OBJ) 2dsline.$(OBJ) line.$(OBJ) \
	box.$(OBJ) poly.$(OBJ) disc.$(OBJ) gpixel.$(OBJ) \
	font.$(OBJ) bitmap.$(OBJ) bitblt.$(OBJ) pcx.$(OBJ) \
	rle.$(OBJ) ibitblt.$(OBJ) \
        circle.$(OBJ) tmerge.$(OBJ)

ifdef ENV_DJGPP
OBJECTS += scale.$(OBJ) scalea.$(OBJ)
else
OBJECTS += scalec.$(OBJ)
endif

ifndef NO_ASM
OBJECTS += linear.$(OBJ) tmerge_a.$(OBJ)
endif

OUTPUT = $(LIBDIR)2d.$(ARC)

include $(TOPDIR)/default.mak
