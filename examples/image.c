/**************************************************************************
*
* File:          $RCSfile: image.c,v $
* Module:        Image package example program
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.8 $
* Last edited:   $Date: 2002/03/25 10:11:59 $
* Author:        $Author: pm $
* Copyright:     (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       
*
**************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <gandalf/image/image_defs.h>
#include <gandalf/image/image_gl_uchar.h>
#include <gandalf/image/image_gl_uint.h>
#include <gandalf/image/image_gl_int.h>
#include <gandalf/image/image_rgb_uchar.h>
#include <gandalf/common/misc_error.h>

/* Prints the image */
static Gan_Bool print_image ( Gan_Image *img )
{
   unsigned int r, c;

   printf ( "Image (%ld,%ld):\n", img->width, img->height );
        
   switch ( img->format )
   {
      case GAN_GREY_LEVEL_IMAGE:
      {
         switch ( img->type )
         {
            case GAN_UCHAR:
            {
               for ( r = 0; r < img->height; r++ )
               {
                  for ( c = 0; c < img->width; c++ )
                     printf ( " %2x", gan_image_get_pix_gl_uc(img,r,c) );
                  
                  printf ( "\n" );
               }
            } /* End of case */
            break;
            
            case GAN_INT:
            {
               for ( r = 0; r < img->height; r++ )
               {
                  for ( c = 0; c < img->width; c++ )
                     printf ( " %3x", gan_image_get_pix_gl_i(img,r,c) );
                  
                  printf ( "\n" );
               }
            } /* End of case */
            break;
                                
            case GAN_UINT:
            {
               for ( r = 0; r < img->height; r++ )
               {
                  for ( c = 0; c < img->width; c++ )
                     printf ( " %3x", gan_image_get_pix_gl_ui(img,r,c) );
                  
                  printf ( "\n" );
               }
            } /* End of case */
            break;
                                
            default:
              assert(0);
              break;
         }
      }
      break;
                
      case GAN_RGB_COLOUR_IMAGE:
      {
         switch ( img->type )
         {
            case GAN_UCHAR:
            {
               Gan_RGBPixel_uc rgb;
               
               for ( r = 0; r < img->height; r++ )
               {
                  for ( c = 0; c < img->width; c++ )
                  {
                     rgb = gan_image_get_pix_rgb_uc(img,r,c);
                     printf ( " (%x,%x,%x)", rgb.R, rgb.G, rgb.B );
                  }
                  
                  printf ( "\n" );
               }
            }
            break;
            
            default:
              assert(0);
              break;
         }
      }
      break;
      
      default:
        assert(0);
        break;
   }
   
   printf ( "\n" );
   return GAN_TRUE;
}

static Gan_Bool ramp_image ( Gan_Image *img )
{
   unsigned int r, c;
   
   switch ( img->format )
   {
      case GAN_GREY_LEVEL_IMAGE:
      {
         switch ( img->type )
         {
            case GAN_UCHAR:
            {
               for ( r = 0; r < img->height; r++ )
               {
                  for ( c = 0; c < img->width; c++ )
                     gan_image_set_pix_gl_uc ( img, r, c, r+c );
               }
            }
            break;
                                
            case GAN_UINT:
            {
               for ( r = 0; r < img->height; r++ )
               {
                  for ( c = 0; c < img->width; c++ )
                     gan_image_set_pix_gl_ui ( img, r, c, r+c );
               }
            }
            break;
                                
            default:
              assert(0);
              break;
         } /* End of nested switch */
      } /* End of case */
      break;
                
      case GAN_RGB_COLOUR_IMAGE:
      {
         switch ( img->type )
         {
            case GAN_UCHAR:
            {        
               Gan_RGBPixel_uc rgb;
               
               for ( r = 0; r < img->height; r++ )
               {
                  for ( c = 0; c < img->width; c++ )
                  {
                     rgb.R = rgb.G = rgb.B = r+c;
                     gan_image_set_pix_rgb_uc ( img, r, c, &rgb );
                  }
               }
            } /* End of case */
            break;
            
            default:
              assert(0);
              break;
         } /* End of switch */
         break;
      } /* End of case */        
      default:
        assert(0);
        break;
   } /* End of main switch */
   return GAN_TRUE;
}

int main ( int argc, char *argv[] )
{
   Gan_Image *img, *img2;
   int pix[12], i;

   /* build image */
   for ( i = 11; i >= 0; i-- )
      pix[i] = i;

   img = gan_image_form_data_gl_i ( NULL, 3, 4, 4*sizeof(int),
                                    pix, 12*sizeof(int), NULL, 0 );
   if ( img == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* print pixel values and free image */
   print_image(img);
   gan_image_free ( img );

   /* build new image */
   img = gan_image_alloc_gl_uc ( 5, 3 );
   if ( img == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();
        
   /* fill image with constant pixel value */
   gan_image_fill_const_gl_uc ( img, 100);

   /* set specific pixel */
   gan_image_set_pix_gl_uc ( img, 2, 1, 150 );
   printf ( "img[2][1]=%d\n", gan_image_get_pix_gl_uc ( img, 2, 1 ) );
        
   /* reset image dimensions. The new dimensions are larger so there will
    * be reallocation of the pixel and row pointer arrays inside the
    * function. Here we set stride = width.
    */
   img = gan_image_set_gl_uc ( img, 7, 9 );
   if ( img == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();
        
   /* fill image with linear ramp */
   ramp_image ( img );
        
   /* print pixel values */
   print_image(img);

   /* copy image. In Gandalf, the functions with a "_s" suffix are `slow'
    * functions which create a new object for the result
    */
   img2 = gan_image_copy_s(img);
   if ( img2 == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();
        
   /* modify image and copy it back. Functions with a "_q" suffix are `quick'
    * functions which copy the result into a pre-existing object.
    */
   gan_image_fill_const_gl_uc ( img2, 254 );
   print_image(img2);

   img = gan_image_copy_q ( img2, img );
   if ( img == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();
        
   /* convert img2 to unsigned integer type */
   img2 = gan_image_set_type ( img2, GAN_UINT );
   if ( img2 == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();
        
   /* fill with ramp for new image type */
   ramp_image ( img2 );
   print_image(img2);
        
   /* convert img to RGB colour */
   img = gan_image_set_format_type ( img, GAN_RGB_COLOUR_IMAGE, GAN_UCHAR );
   if ( img == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();
        
   /* fill with ramp for new image format and type */
   ramp_image ( img );
   print_image(img);
        
   /* free both images and exit */
   gan_image_free_va ( img2, img, NULL );
        
   gan_heap_report(NULL);
   return GAN_TRUE;
}
