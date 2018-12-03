CC = gcc
INSTALL = /usr/bin/install -c
PNG_LIBS = -lpng -lz
TIFF_LIB = -ltiff
JPEG_LIB = -ljpeg
LAPACK_LIBS = -llapack -lblas -lf2c
OPENGL_LIBS = -lGLU -lGL -lXmu -lXi -lX11 -lpthread
GLUT_LIBS = -lglut
X_LIBS = 
prefix = /usr/local
includedir = ${prefix}/include
exec_prefix = ${prefix}
libdir = ${exec_prefix}/lib

include make.inc
include config

TOPLEVEL = .

# Gandalf source directories
SRCDIRS = common linalg image vision

# Rule for compiling Gandalf library
gandalf:
	for f in $(SRCDIRS); do (cd $$f; $(MAKE)); done
	$(LIBTOOL) --mode=link $(CC) $(CFLAGS) -o libgandalf.la \
		common/*$(OBJECT_SUFFIX).lo linalg/*$(OBJECT_SUFFIX).lo \
		linalg/cblas/*$(OBJECT_SUFFIX).lo \
		linalg/clapack/*$(OBJECT_SUFFIX).lo \
		linalg/matrix/*$(OBJECT_SUFFIX).lo \
		image/*$(OBJECT_SUFFIX).lo image/io/*$(OBJECT_SUFFIX).lo \
		vision/*$(OBJECT_SUFFIX).lo \
		-version-info 2:1:1 -rpath $(DESTDIR)$(libdir) $(LDFLAGS) $(LIBS)

# Rule for compiling Gandalf library and test programs
all:
	for f in $(SRCDIRS); do (cd $$f; $(MAKE) all;) done

distclean: clean

clean:
	for f in $(SRCDIRS); do (cd $$f; $(MAKE) clean;) done
	(cd TestFramework; $(MAKE) clean;)
	rm -f TestOutput/*.*
	$(RM) -r libgandalf.la .libs config.{status,log,cache}
	$(RM) *~

# Rule for installing Gandalf header files and library
install: install-header install-lib

install-header:
	@echo Installing the header files.
	if [ ! -d $(DESTDIR)$(includedir) ]; then mkdir -p $(DESTDIR)$(includedir); fi
	if [ ! -d $(DESTDIR)$(includedir)/gandalf ]; then mkdir $(DESTDIR)$(includedir)/gandalf; fi
	$(INSTALL) -m 644 config.h $(DESTDIR)$(includedir)/gandalf/
	for f in $(SRCDIRS); do (cd $$f; $(MAKE) install); done

install-lib:
	@echo Installing the library archive file.
	if [ ! -d $(DESTDIR)$(libdir) ]; then mkdir $(DESTDIR)$(libdir); fi
	$(LIBTOOL) --mode=install $(INSTALL) $(LIB) $(DESTDIR)$(libdir)/$(LIB)

# Rule for preprocessing Gandalf source prior to generating documentation
docsource:
	$(CC) -DNDEBUG preprocess.c -o preprocess
	for f in $(SRCDIRS); do (cd $$f; $(MAKE) docsource;) done
	for f in $(SRCDIRS); do (cd $$f; $(MAKE) docfinish;) done
