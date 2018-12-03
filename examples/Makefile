CC = gcc
PNG_LIBS = -lpng -lz
JPEG_LIB = -ljpeg
TIFF_LIB = -ltiff
LAPACK_LIBS = -llapack -lblas -lf2c
OPENGL_LIBS = -lGLU -lGL -lXmu -lXi -lX11 -lpthread
X_LIBS = 

include ../make.inc
include ../config

PACKAGE = examples
TOPLEVEL = ..

EXECUTABLES = linalg image subimage invimage copy_file
targets: $(EXECUTABLES)

linalg: linalg.c
	$(LIBTOOL) --mode=link $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -static linalg.c -o linalg $(LDFLAGS) $(LIB) $(LIBS)

image: image.c
	$(LIBTOOL) --mode=link $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -static image.c -o image $(LDFLAGS) $(LIB) $(LIBS)

subimage: subimage.c
	$(LIBTOOL) --mode=link $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -static subimage.c -o subimage $(LDFLAGS) $(LIB) $(LIBS)

invimage: invimage.c
	$(LIBTOOL) --mode=link $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -static invimage.c -o invimage $(LDFLAGS) $(LIB) $(LIBS)

copy-file: copy_file.c
	$(LIBTOOL) --mode=link $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -static copy_file.c -o copy_file $(LDFLAGS) $(LIB) $(LIBS)

GARBAGE += $(EXECUTABLES)

include ../make.targets
