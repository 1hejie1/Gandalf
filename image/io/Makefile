CC = gcc
CFLAGS = -g -Wall -I/usr/X11R6/include -Wall
LIBS = -lX11 -lm -lX11 -lm 
LDFLAGS =  -L/usr/local/lib 
INSTALL = /usr/bin/install -c
prefix = /usr/local
includedir = ${prefix}/include

include ../../make.inc
include ../../config

PACKAGE = image
SUBPACKAGE = io
OBJS = $(patsubst %.c,%$(OBJECT_SUFFIX).lo,$(CFILES))
CFILES = image_io.c movie.c png_io.c pbm_io.c pgm_io.c ppm_io.c tiff_io.c \
	 jpeg_io.c dpx_io.c cineon_io.c sgi_io.c targa_io.c
HFILES = $(patsubst %.c,%.h,$(CFILES))
TOPLEVEL = ../..

all: $(OBJS)

install: installsubh

$(CFILES): ../$(SUBPACKAGE).h

include ../../make.targets
