/**
 * File:          $RCSfile: 2x2matrix_eigsym.c,v $
 * Module:        2x2 symmetric matrix eigenvalues/vectors (double precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.2 $
 * Last edited:   $Date: 2003/03/21 13:21:23 $
 * Author:        $Author: pm $
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

#include <gandalf/linalg/2x2matrix_eigsym.h>
#include <gandalf/common/numerics.h>
#include <gandalf/common/misc_error.h>

/**
 * \addtogroup LinearAlgebra
 * \{
 */

/**
 * \addtogroup FixedSizeMatVec
 * \{
 */

/**
 * \addtogroup FixedSizeMatrix
 * \{
 */

/**
 * \defgroup FixedSizeMatrixEigen Eigendecomposition of a Fixed Size Matrix
 * \{
 */

/**
 * \brief Eigenvalues and maybe eigenvectors of symmetric 2x2 matrix.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Computes the eigenvalues and, optionally, the eigenvectors of a symmetric
 * 2x2 input matrix \a A, i.e. computing diagonal matrix \a W as the
 * eigenvalues \a W, and orthogonal matrix of eigenvectors \a Z such that
 * \f[
 *   A\:Z = Z\:W, \;\; Z^{\top}\:A = W\:`Z^{\top}
 * \f]
 * If \a Z is passed as \c NULL then the eigenvectors are not computed.
 *
 * NOTE: the contents of \a A are NOT destroyed.
 *
 * The eigenvalues \a W are provided in ascending order.
 */
Gan_Bool
 gan_symmat22_eigen ( Gan_SquMatrix22 *A,
                      Gan_Vector2 *W, Gan_Matrix22 *Z )
{
   double fDisc;

   /* compute eigenvalues */
   fDisc = sqrt(4.0F*A->yx*A->yx + gan_sqr_d(A->xx-A->yy));
   W->x = 0.5F*(A->xx + A->yy - fDisc);
   W->y = 0.5F*(A->xx + A->yy + fDisc);

   if ( Z != NULL )
   {
      double dTheta, dCosT, dSinT;

      /* compute eigenvectors */
      if ( A->yx == 0.0 && A->xx == A->yy )
         dTheta = 0.0;
      else
         dTheta = 0.5*atan2(-2.0*A->yx, A->yy-A->xx);
      
      dCosT = cos(dTheta);
      dSinT = sin(dTheta);
      (void)gan_mat22_fill_q ( Z, dCosT, -dSinT,
                                  dSinT,  dCosT );
#if 1
      {
         /* check result */
         Gan_Matrix22 m22Tmp1, m22Tmp2;

         (void)gan_mat22_fill_q ( &m22Tmp1, A->xx, A->yx,
                                            A->yx, A->yy );
         m22Tmp1 = gan_mat22_rmultm22_s ( &m22Tmp1, Z );
         (void)gan_mat22_fill_q ( &m22Tmp2, W->x*Z->xx, W->y*Z->xy,
                                            W->x*Z->yx, W->y*Z->yy );
         (void)gan_mat22_decrement ( &m22Tmp1, &m22Tmp2 );
      }
#endif
   }

   /* success */
   return GAN_TRUE;
}
 
/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */
