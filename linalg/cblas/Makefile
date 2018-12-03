CC = gcc
CFLAGS = -g -Wall -I/usr/X11R6/include -Wall
LIBS = -lX11 -lm -lX11 -lm 
LDFLAGS =  -L/usr/local/lib 
INSTALL = /usr/bin/install -c
prefix = /usr/local
includedir = ${prefix}/include

include ../../make.inc
include ../../config

PACKAGE = linalg
SUBPACKAGE = cblas
OBJS = $(patsubst %.c,%$(OBJECT_SUFFIX).lo,$(CFILES))
CFILES = daxpy.c dcopy.c ddot.c dgemm.c dgemv.c dger.c dnrm2.c dscal.c \
	 dspmv.c dspr.c dspr2.c dtpmv.c dtpsv.c dswap.c dtrmv.c dtrsm.c \
	 idamax.c \
	 saxpy.c scopy.c sdot.c sgemm.c sgemv.c sger.c snrm2.c sscal.c \
	 sspmv.c sspr.c sspr2.c stpmv.c stpsv.c sswap.c strmv.c strsm.c \
	 isamax.c
HFILES = $(patsubst %.c,%.h,$(CFILES)) extern.h
TOPLEVEL = ../..

all: $(OBJS)

install: installsubh

$(CFILES): ../$(SUBPACKAGE).h

include ../../make.targets
