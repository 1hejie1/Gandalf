/**************************************************************************
*
* File:          $RCSfile: invimage.c,v $
* Module:        Image package example program using sub-images
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.2 $
* Last edited:   $Date: 2007/03/13 14:00:27 $
* Author:        $Author: pm $
* Copyright:     (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       
*
**************************************************************************/

#include <stdio.h>
#include <gandalf/linalg/3x3matrix.h>
#include <gandalf/image/io/image_io.h>
#include <gandalf/image/image_invert.h>

static void vPrintArguments ( char *acProgName )
{
   fprintf ( stderr, "Usage: %s <input file> <format> [<output file>]\n", acProgName );
   exit(-1);
}

int main ( int argc, char *argv[] )
{
   Gan_ImageFileFormat eImageFileFormat;
   Gan_Image *pImage, *pInvImage;

   if ( argc != 3 && argc != 4 )
      vPrintArguments(argv[0]);

   /* determine image file format */
   eImageFileFormat = gan_image_interpret_format_string ( argv[2] );
   if ( eImageFileFormat == GAN_UNKNOWN_FORMAT )
   {
      fprintf ( stderr, "Error: could not interpret image file format \"%s\"\n", argv[2] );
      exit(-1);
   }

   /* read image */
   pImage = gan_image_read ( argv[1], eImageFileFormat, NULL, NULL, NULL );
   if ( pImage == NULL )
   {
      fprintf ( stderr, "Error: could not read image file \"%s\"\n", argv[1] );
      exit(-1);
   }

   /* compute inverse of image */
   pInvImage = gan_image_invert_s ( pImage );
   if ( pInvImage == NULL )
   {
      fprintf ( stderr, "Error: could not invert image\n" );
      exit(-1);
   }
          
   /* write output file */
   if ( argc == 4 )
   {
      if ( !gan_image_write ( argv[3], eImageFileFormat, pInvImage, NULL ) )
      {
         fprintf ( stderr, "Error: could not output image file \"%s\"\n",
                   argv[3] );
         exit(-1);
      }
   }
   else
      if ( !gan_image_write_stream ( stdout, eImageFileFormat, pInvImage, GAN_TRUE, NULL ) )
      {
         fprintf ( stderr, "Error: could not output image\n" );
         exit(-1);
      }

   /* success */
   return 0;
}
