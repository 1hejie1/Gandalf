CC = gcc
CFLAGS = -g -Wall -I/usr/X11R6/include -Wall
LIBS = -lX11 -lm -lX11 -lm 
LDFLAGS =  -L/usr/local/lib 
RANLIB = @RANLIB@
LAPACK_LIBS = -llapack -lblas -lf2c
OPENGL_LIBS = -lGLU -lGL -lXmu -lXi -lX11 -lpthread
GLUT_LIBS = -lglut
PNG_LIBS = -lpng -lz
JPEG_LIB = -ljpeg
TIFF_LIB = -ltiff
X_LIBS = 

include ../make.inc
include ../config

PACKAGE = testframework
TOPLEVEL = ..
OBJS = list_test.o common_test.o linalg_test.o matrixf_eigen_test.o \
       image_test.o bitmap_test.o vision_test.o camera_test.o \
       hough_transform_test.o convolve2D_test.o
LIST_TEST_C            = $(TOPLEVEL)/common/list_test.c
COMMON_TEST_C          = $(TOPLEVEL)/common/common_test.c
LINALG_TEST_C          = $(TOPLEVEL)/linalg/linalg_test.c
MATRIXF_EIGEN_TEST_C   = $(TOPLEVEL)/linalg/matrixf_eigen_test.c
IMAGE_TEST_C           = $(TOPLEVEL)/image/image_test.c
BITMAP_TEST_C          = $(TOPLEVEL)/image/bitmap_test.c
VISION_TEST_C          = $(TOPLEVEL)/vision/vision_test.c
CAMERA_TEST_C          = $(TOPLEVEL)/vision/camera_test.c
HOUGH_TRANSFORM_TEST_C = $(TOPLEVEL)/vision/hough_transform_test.c
CONVOLVE2D_TEST_C      = $(TOPLEVEL)/vision/convolve2D_test.c

test: cUnit.c cUnit.h $(OBJS)
	$(LIBTOOL) --mode=link $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) cUnit.c path_builder.c $(OBJS) -o cUnit $(LDFLAGS) $(LIB) $(LIBS)

include ../make.targets

GARBAGE += cUnit

list_test.o: $(LIST_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(LIST_TEST_C)

common_test.o: $(COMMON_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(COMMON_TEST_C)

linalg_test.o: $(LINALG_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(LINALG_TEST_C)

matrixf_eigen_test.o: $(MATRIXF_EIGEN_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(MATRIXF_EIGEN_TEST_C)

image_test.o: $(IMAGE_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(IMAGE_TEST_C)

bitmap_test.o: $(BITMAP_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(BITMAP_TEST_C)

vision_test.o: $(VISION_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(VISION_TEST_C)

camera_test.o: $(CAMERA_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(CAMERA_TEST_C)

hough_transform_test.o: $(HOUGH_TRANSFORM_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(HOUGH_TRANSFORM_TEST_C)

convolve2D_test.o: $(CONVOLVE2D_TEST_C)
	$(LIBTOOL) --mode=compile $(CC) -I$(TOPLEVEL)/.. $(CFLAGS) -c $(CONVOLVE2D_TEST_C)
