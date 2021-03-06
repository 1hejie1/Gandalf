/**************************************************************************
*
* File:          $RCSfile: dtpsv.c,v $
* Module:        BLAS function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.6 $
* Last edited:   $Date: 2005/02/25 09:30:20 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#include <math.h>
#include <gandalf/linalg/cblas/dtpsv.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/common/compare.h>
#include <gandalf/common/misc_error.h>

/* only define this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)

Gan_Bool
 gan_dtpsv ( Gan_LapackUpLoFlag upper, Gan_TposeFlag trans,
             Gan_LapackUnitFlag unit, long n, double *ap, double *x, long incx )
{
   long i, j;
   double total;
   
   gan_err_test_bool ( upper, "gan_dtpsv", GAN_ERROR_NOT_IMPLEMENTED, "" );
   gan_err_test_bool ( !unit, "gan_dtpsv", GAN_ERROR_NOT_IMPLEMENTED, "" );

   if ( n == 0 ) return GAN_TRUE;
   if ( trans )
      for ( i = 0; i < n; i++ )
      {
         for ( j = 0, total = x[i*incx]; j < i; j++ )
            total -= ap[i*(i+1)/2+j]*x[j*incx];

         x[i*incx] = total/ap[i*(i+1)/2+i];
      }
   else /* !trans */
      for ( i = n-1; i >= 0; i-- )
      {
         for ( j = i+1, total = x[i*incx]; j < n; j++ )
            total -= ap[j*(j+1)/2+i]*x[j*incx];

         x[i*incx] = total/ap[i*(i+1)/2+i];
      }

   /* success */
   return GAN_TRUE;
}

#endif /* #if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK) */
