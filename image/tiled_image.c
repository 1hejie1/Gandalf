/**
 * File:          $RCSfile: tiled_image.c,v $
 * Module:        Definition of a structure for storing an image as a set of image tiles
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.7 $
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

#include "tiled_image.h"

#include <gandalf/image/image_extract.h>

Gan_ImageTile *gan_image_tile_alloc ( Gan_ImageFormat format, Gan_Type type,
                                                  unsigned long height, unsigned long width )
{
   Gan_ImageTile *tile = gan_malloc_object(Gan_ImageTile);

   // Allocate an image using the provided parameters
   tile->image = gan_image_alloc ( format, type, height, width );

   // set the parent tiled image to NULL
   tile->parent = NULL;

   // the position is undefined, because there is no parent, so no need to initialise it
   //tile->position;

   // the image was allocated by us
   tile->image_alloc = GAN_TRUE;

   return tile;
}

Gan_ImageTile *gan_image_tile_alloc_image ( Gan_Image *image )
{
   Gan_ImageTile *tile = gan_malloc_object(Gan_ImageTile);

   // Allocate an image using the provided parameters
   tile->image = image;

   // set the parent tiled image to NULL
   tile->parent = NULL;

   // the position is undefined, because there is no parent, so no need to initialise it
   //tile->position;

   // the image was allocated by us
   tile->image_alloc = GAN_FALSE;

   return tile;
}

Gan_ImageTile *gan_image_tile_alloc_data ( Gan_ImageFormat format, Gan_Type type,
                                                       unsigned long height, unsigned long width,
                                                       void *pix_data, size_t pix_data_size,
                                                       void *row_data, size_t row_data_size )
{
   Gan_ImageTile *tile = gan_malloc_object(Gan_ImageTile);

   // Allocate an image using the provided parameters
   tile->image = gan_image_alloc_data( format, type, height, width,
                                       pix_data, pix_data_size, row_data, row_data_size );

   // set the parent tiled image to NULL
   tile->parent = NULL;

   // the position is undefined, because there is no parent, so no need to initialise it
   //tile->position;

   // the image was allocated by us
   tile->image_alloc = GAN_TRUE;

   return tile;
}

void gan_image_tile_free ( Gan_ImageTile *tile )
{   
   if (tile->image_alloc)
      gan_image_free( tile->image );
   free( tile );
}

/************************************************************************/

void gan_tiled_image_data_size( Gan_ImageFormat format, Gan_Type type,
                                unsigned long height, unsigned long width,
                                unsigned int tile_height, unsigned int tile_width,
                                unsigned int *p_num_tiles_vertically,
                                unsigned int *p_num_tiles_horizontally,
                                unsigned int *p_num_blocks,
                                unsigned int *p_pix_data_block_bytes,
                                unsigned int *p_row_data_block_bytes )
{
   *p_num_tiles_vertically   = 1 + (height - 1) / tile_height;
   *p_num_tiles_horizontally = 1 + ( width - 1) / tile_width;
   *p_num_blocks = *p_num_tiles_vertically * *p_num_tiles_horizontally;
   *p_pix_data_block_bytes = tile_height * gan_image_min_stride ( format, type, tile_width, 0 );
   *p_row_data_block_bytes = tile_height;
}

unsigned int gan_tiled_image_bits_per_image( Gan_ImageFormat format, Gan_Type type,
                                             unsigned long height, unsigned long width,
                                             unsigned int tile_height, unsigned int tile_width)
{
   unsigned int num_tiles_vertically   = 1 + (height - 1) / tile_height;
   unsigned int num_tiles_horizontally = 1 + ( width - 1) / tile_width;
   return gan_image_bits_per_pixel(format, type) * 
           num_tiles_vertically * tile_height * num_tiles_horizontally * tile_width;
}

GANDALF_API Gan_TiledImage *gan_tiled_image_alloc ( Gan_ImageFormat format, Gan_Type type,
                                                    unsigned long height, unsigned long width,
                                                    unsigned int tile_height, unsigned int tile_width,
                                                    Gan_ImageTile **existing_tiles, unsigned int num_existing_tiles)
{
   Gan_Bool set_ok;
   Gan_TiledImage *tiled_image = gan_malloc_object(Gan_TiledImage);
   tiled_image->num_tiles = 0; // set the current number of tiles

   set_ok = gan_tiled_image_set_properties ( tiled_image, format, type, height, width,
                                             tile_height, tile_width, existing_tiles, num_existing_tiles );

   if (!set_ok)
   {
      gan_tiled_image_free( tiled_image );
      return 0;
   }

   return tiled_image;
}

/// set the parent of the tiles in a tiled image to NULL
void gan_tiled_image_release_tiles ( Gan_TiledImage *tiled_image )
{
   unsigned int i;
   if (tiled_image && tiled_image->tiles)
   {
      for (i=0; i<tiled_image->num_tiles; ++i)
         tiled_image->tiles[i]->parent = NULL;
   }
}

Gan_Bool gan_tiled_image_set_properties ( Gan_TiledImage *tiled_image,
                                          Gan_ImageFormat format, Gan_Type type,
                                          unsigned long height, unsigned long width,
                                          unsigned int tile_height, unsigned int tile_width,
                                          Gan_ImageTile **existing_tiles, unsigned int num_existing_tiles)
{
   unsigned int i, c, r;

   // check the number of image tiles
   unsigned int num_tiles_vertically;
   unsigned int num_tiles_horizontally;
   unsigned int num_blocks;
   unsigned int pix_data_block_bytes;
   unsigned int row_data_block_bytes;
   unsigned int last_horizontal_tile_width;
   unsigned int last_vertical_tile_height;
   unsigned int current_tile_height;
   unsigned int current_tile_width;

   gan_tiled_image_data_size( format, type, height, width,
                              tile_height, tile_width, 
                              &num_tiles_vertically,
                              &num_tiles_horizontally,
                              &num_blocks,
                              &pix_data_block_bytes,
                              &row_data_block_bytes );

   if (existing_tiles && num_existing_tiles != num_blocks)
      return GAN_FALSE;

   // now set the data
   tiled_image->format    = format;
   tiled_image->type      = type;
   tiled_image->height    = height;
   tiled_image->width     = width;
   tiled_image->num_tiles_horizontally = num_tiles_horizontally;
   tiled_image->num_tiles_vertically   = num_tiles_vertically;
   tiled_image->tile_height = tile_height;
   tiled_image->tile_width  = tile_width;

   // reallocate the tile pointer array if necessary
   if (tiled_image->num_tiles != num_blocks)
   {
      if (tiled_image->num_tiles && tiled_image->tiles)
      {
         gan_tiled_image_release_tiles ( tiled_image );
         free( tiled_image->tiles );
      }
      tiled_image->num_tiles = num_blocks;
      tiled_image->tiles = (Gan_ImageTile **) malloc( sizeof(Gan_ImageTile*) * num_blocks );
   }

   // copy the image tile pointers from the provided list, or initialise them to NULL
   if (existing_tiles)
   {
      for (i=0; i<tiled_image->num_tiles; ++i)
         tiled_image->tiles[i] = existing_tiles[i];
   }
   else
   {
      for (i=0; i<tiled_image->num_tiles; ++i)
         tiled_image->tiles[i] = NULL;
   }

   // set the parent and the position of each tile
   last_horizontal_tile_width = tiled_image->width  % tiled_image->tile_width  ? 
                                  tiled_image->width  % tiled_image->tile_width  : tiled_image->tile_width;
   last_vertical_tile_height  = tiled_image->height % tiled_image->tile_height ? 
                                  tiled_image->height % tiled_image->tile_height : tiled_image->tile_height;
   for (r=0; r<tiled_image->num_tiles_vertically; ++r)
   {
      current_tile_height = r == (tiled_image->num_tiles_vertically-1) ? last_vertical_tile_height : tiled_image->tile_height;
      for (c=0; c<tiled_image->num_tiles_horizontally; ++c)
      {
         current_tile_width = c == (tiled_image->num_tiles_horizontally-1) ? last_horizontal_tile_width : tiled_image->tile_width;

         tiled_image->tiles[r*num_tiles_horizontally+c]->parent = tiled_image;
         tiled_image->tiles[r*num_tiles_horizontally+c]->position.c0     = c*tiled_image->tile_width;
         tiled_image->tiles[r*num_tiles_horizontally+c]->position.r0     = r*tiled_image->tile_height;
         tiled_image->tiles[r*num_tiles_horizontally+c]->position.width  = current_tile_width;
         tiled_image->tiles[r*num_tiles_horizontally+c]->position.height = current_tile_height;
      }
   }

   return GAN_TRUE;
}

void gan_tiled_image_free ( Gan_TiledImage *tiled_image )
{  
   if (tiled_image)
   {
      if (tiled_image->tiles)
      {
         gan_tiled_image_release_tiles ( tiled_image );
         free( tiled_image->tiles );
      }
      free( tiled_image );
   }
}

Gan_Bool gan_tiled_image_copy_from_gan_image ( Gan_Image *image, Gan_TiledImage *tiled_image )
{
   unsigned int r, c;
   Gan_ImageTile *tile;

   if ( (image->width != tiled_image->width) || (image->height != tiled_image->height) )
      return GAN_FALSE;

   if ( (image->format != tiled_image->format) || (image->type != tiled_image->type) )
      return GAN_FALSE;

   // copy the data across
   for (r=0; r<tiled_image->num_tiles_vertically; ++r)
   {
      for (c=0; c<tiled_image->num_tiles_horizontally; ++c)
      {
         tile = tiled_image->tiles[r*tiled_image->num_tiles_horizontally+c];

         gan_image_extract_q ( image,
                               tile->position.r0, tile->position.c0,
                               tiled_image->tile_height, tiled_image->tile_width,
                               tile->image->format, tile->image->type,
                               GAN_TRUE,
                               tile->image );
      }
   }

   return GAN_TRUE;
}
