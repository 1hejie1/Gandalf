/**************************************************************************
*
* File:          $RCSfile: dopgtr.c,v $
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
#include <gandalf/linalg/clapack/dopgtr.h>
#include <gandalf/linalg/clapack/dorg2l.h>
#include <gandalf/linalg/clapack/dorg2r.h>
#include <gandalf/common/compare.h>

/* only define this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)

/* modified from CLAPACK source */

Gan_Bool gan_dopgtr(Gan_LapackUpLoFlag upper, long n, double *ap, 
                    double *tau, double *q, long ldq, double *work, 
                    long *info)
{
   long i__, j;
   long iinfo;
   long ij;
#define q_ref(a_1,a_2) q[(a_2)*ldq + a_1]

   *info = 0;
   if (n < 0)
      *info = -2;
   else if (ldq < gan_max2(1,n))
      *info = -6;
   if (*info != 0)
      return GAN_FALSE;

   if (n == 0)
      return GAN_TRUE;

   if (upper)
   {
      /*        Q was determined by a call to DSPTRD with UPLO = 'U'   

      Unpack the vectors which define the elementary reflectors and   
      set the last row and column of Q equal to those of the unit   
      matrix */

      ij = 1;
      for (j = 0; j < n-1; ++j)
      {
         for (i__ = 0; i__ < j; ++i__)
         {
            q_ref(i__, j) = ap[ij];
            ++ij;
         }

         ij += 2;
         q_ref(n-1, j) = 0.0;
      }

      for (i__ = 0; i__ < n-1; ++i__)
         q_ref(i__, n-1) = 0.0;

      q_ref(n-1, n-1) = 1.0;

      /*        Generate Q(1:n-1,1:n-1) */
      gan_dorg2l(n-1, n-1, n-1, q, ldq, tau, work, &iinfo);
   }
   else
   {
      /*        Q was determined by a call to DSPTRD with UPLO = 'L'.   

      Unpack the vectors which define the elementary reflectors and   
      set the first row and column of Q equal to those of the unit   
      matrix */

      q_ref(0, 0) = 1.0;
      for (i__ = 1; i__ < n; ++i__)
         q_ref(i__, 0) = 0.0;

      ij = 2;
      for (j = 1; j < n; ++j)
      {
         q_ref(0, j) = 0.0;
         for (i__ = j + 1; i__ < n; ++i__)
         {
            q_ref(i__, j) = ap[ij];
            ++ij;
         }

         ij += 2;
      }

      if (n > 1)
         gan_dorg2r(n-1, n-1, n-1, &q_ref(1, 1), ldq, tau, work, &iinfo);
   }

   return GAN_TRUE;
}

#undef q_ref

#endif /* #if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK) */


