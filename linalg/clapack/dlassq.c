/**************************************************************************
*
* File:          $RCSfile: dlassq.c,v $
* Module:        CLAPACK function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.2 $
* Last edited:   $Date: 2005/02/25 09:30:24 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#include <math.h>
#include <gandalf/linalg/clapack/dlassq.h>
#include <gandalf/common/compare.h>

/* only define this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)

/* modified from CLAPACK source */

int gan_dlassq(long n, double *x, long incx, double *scale, double *sumsq)
{
   long i__1;
   double d__1;
   double absxi;
   long ix;

   if (n > 0)
   {
      i__1 = (n-1)*incx;
      for (ix = 0; (incx < 0) ? (ix >= i__1) : (ix <= i__1); ix += incx)
      {
         if (x[ix] != 0.0)
         {
            absxi = fabs(x[ix]);
            if (*scale < absxi)
            {
               /* Computing 2nd power */
               d__1 = *scale / absxi;
               *sumsq = *sumsq * (d__1 * d__1) + 1;
               *scale = absxi;
            }
            else
            {
               /* Computing 2nd power */
               d__1 = absxi / *scale;
               *sumsq += d__1 * d__1;
            }
         }
      }
   }

   return GAN_TRUE;
}

#endif /* #if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK) */

