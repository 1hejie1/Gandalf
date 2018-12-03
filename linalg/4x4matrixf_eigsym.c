/**
 * File:          $RCSfile: 4x4matrixf_eigsym.c,v $
 * Module:        4x4 symmetric matrix eigenvalues/vectors (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.5 $
 * Last edited:   $Date: 2002/04/18 14:56:23 $
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

#include <gandalf/linalg/4x4matrixf_eigsym.h>
#include <gandalf/linalg/matf_square.h>
#include <gandalf/linalg/matf_gen.h>
#include <gandalf/linalg/matf_symmetric.h>
#include <gandalf/linalg/matf_diagonal.h>
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
 * \addtogroup FixedSizeMatrixEigen
 * \{
 */

#define gel(M,i,j)   gan_matf_get_el(M,i,j)
#define sel(M,i,j,v) gan_matf_set_el(M,i,j,v)
#define sgel(M,i,j)   gan_squmatf_get_el(M,i,j)
#define ssel(M,i,j,v) gan_squmatf_set_el(M,i,j,v)

#ifdef HAVE_LAPACK
#define WORKSPACE_SIZE 300
#else
#define WORKSPACE_SIZE 0
#endif

/**
 * \brief Eigenvalues and maybe eigenvectors of symmetric 4x4 matrix.
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Computes the eigenvalues and, optionally, the eigenvectors of a symmetric
 * 4x4 input matrix \a A, i.e. computing diagonal matrix \a W as the
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
 gan_symmat44f_eigsym ( Gan_SquMatrix44_f *A, Gan_Vector4_f *W,
                        Gan_Matrix44_f *Z )
{
   Gan_SquMatrix_f Am, Wm;
   Gan_Matrix_f    Zm;
   float           Adata[4*(4+1)/2], Wdata[4], Zdata[4*4],
   #ifdef HAVE_LAPACK
                   wkdata[WORKSPACE_SIZE];
   #else
                   wkdata[1]; /* Can't declare an array with 0 elements */
   #endif

   /* convert to general matrices */
   if ( gan_symmatf_form_data ( &Am, 4, Adata, 4*(4+1)/2 ) == NULL ||
        gan_diagmatf_form_data ( &Wm, 4, Wdata, 4 ) == NULL ||
        ( Z != NULL && gan_matf_form_data ( &Zm, 4, 4, Zdata, 4*4 ) == NULL) )
   {
      gan_err_register ( "gan_symmat44f_eigen", GAN_ERROR_FAILURE, "" );
      return GAN_FALSE;
   }

   /* copy data from matrix A into general matrix Am */
   if ( gan_symmatf_fill_va ( &Am, 4,
                    (double)A->xx,
                    (double)A->yx, (double)A->yy,
                    (double)A->zx, (double)A->zy, (double)A->zz,
                    (double)A->wx, (double)A->wy, (double)A->wz, (double)A->ww)
        == NULL )
   {
      gan_err_register ( "gan_symmat44f_eigen", GAN_ERROR_FAILURE, "" );
      return GAN_FALSE;
   }

   /* perform eigendecomposition */
   if ( !gan_symmatf_eigen ( &Am, &Wm, (Z == NULL) ? NULL : &Zm, GAN_TRUE,
                             wkdata, WORKSPACE_SIZE ) )
   {
      gan_err_register ( "gan_symmat44f_eigen", GAN_ERROR_FAILURE, "" );
      return GAN_FALSE;
   }

   /* copy eigenvalues and eigenvectors */
   gan_vec4f_fill_q ( W, sgel(&Wm,0,0), sgel(&Wm,1,1),
                         sgel(&Wm,2,2), sgel(&Wm,3,3) );
   if ( Z != NULL )
      gan_mat44f_fill_q ( Z,
                      gel(&Zm,0,0), gel(&Zm,0,1), gel(&Zm,0,2), gel(&Zm,0,3),
                      gel(&Zm,1,0), gel(&Zm,1,1), gel(&Zm,1,2), gel(&Zm,1,3),
                      gel(&Zm,2,0), gel(&Zm,2,1), gel(&Zm,2,2), gel(&Zm,2,3),
                      gel(&Zm,3,0), gel(&Zm,3,1), gel(&Zm,3,2), gel(&Zm,3,3) );

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
