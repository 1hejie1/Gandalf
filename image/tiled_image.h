/**
 * File:          $RCSfile: tiled_image.h,v $
 * Module:        Definition of a structure for storing an image as a set of image tiles
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.6 $
 * Last edited:   $Date: 2007/04/19 11:04:59 $
 * Author:        $Author: ndm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _GAN_TILED_IMAGE_H
#define _GAN_TILED_IMAGE_H

#include <gandalf/image/pixel.h>
#include <gandalf/image/image_defs.h>

struct Gan_Image;
struct Gan_ImageWindow;
struct Gan_TiledImage;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup TiledImage
 * \{
 */

/*******************/
/*  Gan_ImageTile  */

typedef struct Gan_ImageTile
{
   /// the tile as an image 
   struct Gan_Image *image;

   /// the position of the tile in the parent image tile set
   struct Gan_ImageWindow position;

   /// pointer to the parent image tile set
   struct Gan_TiledImage *parent;

   /// whether or not the image should be freed (true) or not (false) when the tile is freed
   Gan_Bool image_alloc;

} Gan_ImageTile;

/**
 * \brief Macro: Allocate and return a new image tile.
 *
 * Allocates and returns a new image tile with given \a format
 * (e.g. #GAN_GREY_LEVEL_IMAGE, #GAN_RGB_COLOUR_IMAGE), type (e.g. #GAN_UCHAR
 * for unsigned character images, #GAN_DOUBLE for floating point images),
 * \a height and \a width.
 *
 * The image pointer is set through a call to gan_image_alloc()
 *
 * \sa gan_image_tile_alloc_image(), gan_image_tile_alloc_data() and gan_image_tile_free.
 */
GANDALF_API Gan_ImageTile *gan_image_tile_alloc ( Gan_ImageFormat format, Gan_Type type,
                                                  unsigned long height, unsigned long width );

/**
 * \brief Macro: Allocate and return a new image tile.
 *
 * Allocates and returns a new image tile from an existing Gam_Image pointer.
 *
 * The existing image is wrapped by a tile image structure, which does not take ownership of it
 *
 * \sa gan_image_tile_alloc(), gan_image_tile_alloc_data(), and gan_image_tile_free.
 */
GANDALF_API Gan_ImageTile *gan_image_tile_alloc_image ( Gan_Image *image );

/**
 * \brief Macro: Allocate image tile.
 *
 * Allocates and returns an image tile with given \a format, \a type, dimensions
 * \a height and \a width. If the provided \a pix_data and/or \a row_data
 * pointers are \c NULL (in any combination), the pixel data array and/or the
 * row start pointer array are dynamically allocated. If either are not \c NULL
 * they must be big enough to hold the pixel/row pointer array data.
 * If necessary use gan_image_data_size() to compute the necessary size
 * of the \a pix_data array (the necessary size of \a row_data is
 * \a height pointers).
 *
 * If you want to dynamically allocate the pixel data array and/or the
 * row pointer array with sizes greater than that necessary for the
 * given \a height and \a width, pass \a pix_data and/or \a row_data
 * as \c NULL and set \a pix_data_size and/or \a row_data_size appropriately.
 *
 * The image pointer is set through a call to gan_image_alloc_data()
 *
* \sa gan_image_tile_alloc(), gan_image_tile_alloc_image(), and gan_image_tile_free.
 */
GANDALF_API Gan_ImageTile *gan_image_tile_alloc_data ( Gan_ImageFormat format, Gan_Type type,
                                                       unsigned long height, unsigned long width,
                                                       void *pix_data, size_t pix_data_size,
                                                       void *row_data, size_t row_data_size );
/**
 * \brief Macro: Free an image.
 *
 * Free the memory associated with the image tile \a img.
 *
 * The image pointer is freed through a call to gan_image_free()
 */
GANDALF_API void gan_image_tile_free ( Gan_ImageTile *tile );

/********************/
/*  Gan_TiledImage  */

/**
 * \brief Calculate the memory block size and the number of memory blocks needed to form a Gan_TiledImage of a particular size and format
 *
 */
GANDALF_API void gan_tiled_image_data_size( Gan_ImageFormat format, Gan_Type type,
                                            unsigned long height, unsigned long width,
                                            unsigned int tile_height, unsigned int tile_width, 
                                            unsigned int *p_num_tiles_vertically,
                                            unsigned int *p_num_tiles_horizontally,
                                            unsigned int *p_num_blocks,
                                            unsigned int *p_pix_data_block_bytes,
                                            unsigned int *p_row_data_block_bytes );

/**
 * \brief Calculate the memory requirement for a tiled image
 *
 */
GANDALF_API unsigned int gan_tiled_image_bits_per_image( Gan_ImageFormat format, Gan_Type type,
                                                         unsigned long height, unsigned long width,
                                                         unsigned int tile_height, unsigned int tile_width);

/**
 * \brief An image class which is composed of image tiles
 *
 */
typedef struct Gan_TiledImage
{
   /// the number of image tiles
   unsigned int num_tiles;

   /// array of image tiles
   Gan_ImageTile **tiles;

   /// format of image: grey-level, RGB colour etc.
   Gan_ImageFormat format;

   /// type of pixel values: unsigned char, float etc.
   Gan_Type type;

   /// image dimensions
   unsigned long height, width;

   unsigned int num_tiles_horizontally;
   unsigned int num_tiles_vertically;

   unsigned int tile_height;
   unsigned int tile_width;

} Gan_TiledImage;


/**
 * \brief Form a new tiled image, optionally using a set of existing image tiles
 * \return A newly allocated tiled image
 *
 */
GANDALF_API Gan_TiledImage *gan_tiled_image_alloc ( Gan_ImageFormat format, Gan_Type type,
                                                    unsigned long height, unsigned long width,
                                                    unsigned int tile_height, unsigned int tile_width,
                                                    Gan_ImageTile **existing_tiles, unsigned int num_existing_tiles);

/**
 * \brief Form a new tiled image, optionally using a set of existing image tiles
 * \return A newly allocated tiled image
 *
 */
GANDALF_API Gan_Bool gan_tiled_image_set_properties( Gan_TiledImage *tiled_image, Gan_ImageFormat format, Gan_Type type,
                                                     unsigned long height, unsigned long width,
                                                     unsigned int tile_height, unsigned int tile_width,
                                                     Gan_ImageTile **existing_tiles, unsigned int num_existing_tiles);

/**
 * \brief Free a tiled image.
 *
 * Free the memory associated with the tiled image \a tiled_image.
 */
GANDALF_API void gan_tiled_image_free ( struct Gan_TiledImage *tiled_image );

/**
 * \brief Copy a gan image to a gan tiled image
 *
 */
GANDALF_API Gan_Bool gan_tiled_image_copy_from_gan_image ( struct Gan_Image *image, struct Gan_TiledImage *tiled_image );


/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_TILED_IMAGE_H */
