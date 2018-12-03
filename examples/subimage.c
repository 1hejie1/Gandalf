/**************************************************************************
*
* File:          $RCSfile: subimage.c,v $
* Module:        Image package example program using sub-images
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.5 $
* Last edited:   $Date: 2001/11/05 10:13:58 $
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
#include <gandalf/image/image_extract.h>

static void vPrintArguments ( char *acProgName )
{
   fprintf ( stderr, "Usage: %s <input file> <format> <col> <row> <width> <height> [<output file>]\n", acProgName );
   exit(-1);
}

int main ( int argc, char *argv[] )
{
   Gan_ImageFileFormat eImageFileFormat;
   int iRow, iCol, iWidth, iHeight;
   Gan_Image *pImage, *pSubImage;

   if ( argc != 7 && argc != 8 )
      vPrintArguments(argv[0]);

   /* determine image file format */
   eImageFileFormat = gan_image_interpret_format_string ( argv[2] );
   if ( eImageFileFormat == GAN_UNKNOWN_FORMAT )
   {
      fprintf ( stderr, "Error: could not interpret image file format \"%s\"\n", argv[2] );
      exit(-1);
   }

   /* read and check bottom-left corner coordinates */
   if ( sscanf ( argv[3], "%d", &iCol ) != 1 ||
        sscanf ( argv[4], "%d", &iRow ) != 1 )
   {
      fprintf ( stderr, "Error: could not interpret corner coordinates \"%s\" and \"%s\"\n", argv[3], argv[4] );
      exit(-1);
   }

   if ( iCol < 0 || iRow < 0 )
   {
      fprintf ( stderr, "Error: illegal negative coordinate(s) %d %d\n",
                iCol, iRow );
      exit(-1);
   }

   /* read image */
   pImage = gan_image_read ( argv[1], eImageFileFormat, NULL );
   if ( pImage == NULL )
   {
      fprintf ( stderr, "Error: could not read image file \"%s\"\n", argv[1] );
      exit(-1);
   }

   if ( iCol >= pImage->width || iRow >= pImage->height )
   {
      fprintf ( stderr, "Error: coordinate(s) %d %d outside image\n",
                iCol, iRow );
      exit(-1);
   }

   /* read and check sub-image dimensions */
   if ( sscanf ( argv[5], "%d", &iWidth ) != 1 ||
        sscanf ( argv[6], "%d", &iHeight ) != 1 )
   {
      fprintf ( stderr, "Error: could not interpret sub-image dimensions \"%s\" and \"%s\"\n", argv[5], argv[6] );
      exit(-1);
   }

   if ( iWidth < 0 || iHeight < 0 )
   {
      fprintf ( stderr, "Error: illegal negative dimension(s) %d %d\n",
                iWidth, iHeight );
      exit(-1);
   }

   if ( iCol+iWidth > pImage->width || iRow+iHeight > pImage->height < 0 )
   {
      fprintf ( stderr, "Error: sub-image outside image\n" );
      exit(-1);
   }

   /* compute sub-image */
   pSubImage = gan_image_extract_s ( pImage, iRow, iCol, iHeight, iWidth,
                                     pImage->format, pImage->type, GAN_TRUE );
   if ( pSubImage == NULL )
   {
      fprintf ( stderr, "Error: could not extract sub-image\n" );
      exit(-1);
   }
          
   /* write output file */
   if ( argc == 8 )
   {
      if ( !gan_image_write ( argv[7], eImageFileFormat, pSubImage ) )
      {
         fprintf ( stderr, "Error: could not output image file \"%s\"\n",
                   argv[7] );
         exit(-1);
      }
   }
   else
      if ( !gan_image_write_stream ( stdout, eImageFileFormat, pSubImage ) )
      {
         fprintf ( stderr, "Error: could not output image\n" );
         exit(-1);
      }

   /* success */
   return 0;
}
