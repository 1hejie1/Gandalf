/**************************************************************************
*
* File:          $RCSfile: isamax.c,v $
* Module:        BLAS function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.5 $
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
#include <gandalf/config.h>
#include <gandalf/linalg/cblas/isamax.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/common/compare.h>
#include <gandalf/common/misc_error.h>

/* only define this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)
/* our version of isamax_() returns a value between 0 and *n-1 inclusive,
 * instead of the Fortran style 1,...,*n.
 */
long
 gan_isamax ( long n, float *dx, long incx )
{
   long i, best_i=0;
   float val, high = -1.0F;

   assert ( n >= 0 );
   if ( n == 0 ) return 0;
      
   if ( incx == 1 )
   {
      for ( i = n-1; i >= 0; i-- )
         if ( (val = (float)fabs(dx[i])) > high )
         {
            high = val;
            best_i = i;
         }
   }
   else
   {
      for ( i = n-1; i >= 0; i--, dx += incx )
         if ( (val = (float)fabs(*dx)) > high )
         {
            high = val;
            best_i = i;
         }
   }

   return best_i;
}

#endif /* #if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK) */
