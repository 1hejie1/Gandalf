/**
 * File:          $RCSfile: 3x4matrixf.c,v $
 * Module:        3x4 matrices (single precision)
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.13 $
 * Last edited:   $Date: 2004/03/18 18:26:20 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

#include <math.h>
#include <gandalf/linalg/3x4matrixf.h>

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
 * \addtogroup FixedSizeMatrixIO
 * \{
 */

/**
 * \brief Print 3x4 matrix to file
 *
 * Print 3x4 matrix \a A to file pointer \a fp, with prefix string \a prefix,
 * indentation \a indent and floating-point format \a fmt.
 *
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
Gan_Bool
 gan_mat34f_fprint ( FILE *fp, const Gan_Matrix34_f *A,
                     const char *prefix, int indent, const char *fmt )
{
   int i;

   /* print indentation on first line */
   for ( i = indent-1; i >= 0; i-- ) fprintf ( fp, " " );
   fprintf ( fp, "%s\n", prefix );
   for ( i = indent-1; i >= 0; i-- ) fprintf ( fp, " " );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->xx );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->xy );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->xz );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->xw );
   fprintf ( fp, "\n" );
   for ( i = indent-1; i >= 0; i-- ) fprintf ( fp, " " );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->yx );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->yy );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->yz );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->yw );
   fprintf ( fp, "\n" );
   for ( i = indent-1; i >= 0; i-- ) fprintf ( fp, " " );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->zx );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->zy );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->zz );
   fprintf ( fp, " " ); fprintf ( fp, fmt, A->zw );
   fprintf ( fp, "\n" );

   /* success */
   return GAN_TRUE;
}

/**
 * \brief Read 3x4 matrix from file.
 *
 * Read 3x4 matrix \a A from file pointer \a fp. The prefix
 * string for the matrix is read from the file into the \a prefix string, up
 * to the maximum length \a prefix_len of the \a prefix string. Any remaining
 * characters after \a prefix has been filled are ignored. Pass \c NULL for
 * \a prefix and zero for \a prefix_len to ignore the prefix string.
 *
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
Gan_Bool
 gan_mat34f_fscanf ( FILE *fp, Gan_Matrix34_f *A,
                     char *prefix, int prefix_len )
{
   int ch, result;

   /* read indentation */
   for(;;)
      if ( (ch = getc(fp)) != ' ' || ch == EOF )
         break;

   /* end of file means corrupted file */
   if ( ch == EOF )
   {
      gan_err_flush_trace();
      gan_err_register ( "gan_mat34f_fscanf", GAN_ERROR_CORRUPTED_FILE, "" );
      return GAN_FALSE;
   }
   
   /* rewind one character to reread the prefix string */
   fseek ( fp, -1, SEEK_CUR );

   /* read prefix string, terminated by end-of-line */
   for ( prefix_len--; prefix_len > 0; prefix_len-- )
   {
      ch = getc(fp);
      if ( ch == EOF || ch == '\n' ) break;
      if ( prefix != NULL ) *prefix++ = (char)ch;
   }

   gan_err_test_bool ( ch == '\n', "gan_mat34f_fscanf",
                       GAN_ERROR_CORRUPTED_FILE, "" );

   /* terminate string */
   if ( prefix != NULL ) *prefix = '\0';

   /* read rest of string if necessary */
   if ( prefix_len == 0 )
   {
      for(;;)
      {
         ch = getc(fp);
         if ( ch == EOF || ch == '\n' ) break;
      }

      gan_err_test_bool ( ch == '\n', "gan_mat34f_fscanf",
                          GAN_ERROR_CORRUPTED_FILE, "" );
   }

   /* read rows of matrix */
   result = 0;
   result += fscanf ( fp, "\n%f%f%f%f\n", &A->xx, &A->xy, &A->xz, &A->xw );
   result += fscanf ( fp, "%f%f%f%f\n",   &A->yx, &A->yy, &A->yz, &A->yw );
   result += fscanf ( fp, "%f%f%f%f",     &A->zx, &A->zy, &A->zz, &A->zw );
   gan_err_test_bool ( result == 12, "gan_mat34f_fscanf",
                       GAN_ERROR_CORRUPTED_FILE, "" );

   /* read end-of-line character */
   result = getc(fp);
   gan_err_test_bool ( result == '\n', "gan_mat34f_fscanf",
                       GAN_ERROR_CORRUPTED_FILE, "" );

   /* success */
   return GAN_TRUE;
}

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixFill
 * \{
 */

/**
 * \brief Fill 3x4 matrix with values.
 *
 * Fill 3x4 matrix with values:
 * \f[
 *     \left(\begin{array}{cccc} XX & XY & XZ & XW \\ YX & YY & YZ & YW \\
 *                               ZX & ZY & ZZ & ZW
 *     \end{array}\right)
 * \f]
 *
 * \return Filled matrix.
 */
Gan_Matrix34_f
 gan_mat34f_fill_s ( float XX, float XY, float XZ, float XW,
                     float YX, float YY, float YZ, float YW,
                     float ZX, float ZY, float ZZ, float ZW )
{
   Gan_Matrix34_f A;

   (void)gan_mat34f_fill_q ( &A, XX, XY, XZ, XW,
                                 YX, YY, YZ, YW,
                                 ZX, ZY, ZZ, ZW );
   return A;
}

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixVectorProduct
 * \{
 */

/**
 * \brief Multiply 3x4 matrix by homogeneous 3-vector.
 *
 * Multiply 3x4 matrix \a A by 3-vector \a p expanded to a homogeneous
 * 4-vector by adding fourth element \a h, in other words compute and
 * return
 * \f[
 *    A \left(\begin{array}{c} p \\ h \end{array}\right)
 * \f]
 */
Gan_Vector3_f
 gan_mat34f_multv3h_s ( const Gan_Matrix34_f *A, const Gan_Vector3_f *p, float h )
{
   Gan_Vector3_f q;

   (void)gan_mat34f_multv3h_q ( A, p, h, &q );
   return q;
}

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixInvert
 * \{
 */

/**
 * \brief Compute inverse of completed 4x4 matrix.
 *
 * Given 3x4 matrix \a A and scalar value \a a, compute 3x4 matrix B and
 * scalar \a b such that
 * \f[
 *   \left(\begin{array}{cc} \multicolumn{2}{c}{B} \\ 0^{\top} & b
 *   \end{array}\right)
 * = \left(\begin{array}{cc} \multicolumn{2}{c}{A} \\ 0^{\top} & a
 *   \end{array}\right)^{-1}
 * \f]
 *
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 */
Gan_Bool
 gan_mat34hf_invert_q ( const Gan_Matrix34_f *A, float a,
                        Gan_Matrix34_f *B, float *b )
{
   Gan_Matrix33_f H;
   Gan_Vector3_f h;

   (void)gan_mat34f_get_m33l_q ( A, &H );
   gan_assert ( a != 0.0F && gan_mat33f_det_q(&H) != 0.0F,
                "illegal arguments to gan_mat34hf_invert_q" );
   (void)gan_mat34f_get_v3r_q ( A, &h );
   H = gan_mat33f_invert_s ( &H );
   h = gan_mat33f_multv3_s ( &H, &h );
   (void)gan_vec3f_divide_i ( &h, -a );
   (void)gan_mat34f_set_parts_q ( B, &H, &h );
   if ( b != NULL ) *b = 1.0F/a;
   return GAN_TRUE;
}

/**
 * \brief Compute inverse of completed 4x4 matrix.
 *
 * Given 3x4 matrix \a A and scalar value \a a, compute 3x4 matrix B and
 * scalar \a b such that
 * \f[
 *   \left(\begin{array}{cc} \multicolumn{2}{c}{B} \\ 0^{\top} & b
 *   \end{array}\right)
 * = \left(\begin{array}{cc} \multicolumn{2}{c}{A} \\ 0^{\top} & a
 *   \end{array}\right)^{-1}
 * \f]
 *
 * \return Result matrix \a B as a new 3x4 matrix.
 */
Gan_Matrix34_f
 gan_mat34hf_invert_s ( const Gan_Matrix34_f *A, float a, float *b )
{
   Gan_Matrix34_f B;

   (void)gan_mat34hf_invert_q ( A, a, &B, b );
   return B;
}

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixExtract
 * \{
 */

/**
 * \brief Extract rows of 3x4 matrix.
 *
 * Extract rows of 3x4 matrix \a A into 4-vectors \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{c} p^{\top} \\ q^{\top} \\ r^{\top}
 *         \end{array}\right)
 * \f]
 *
 * \return No value.
 */
void gan_mat34f_get_rows_s ( const Gan_Matrix34_f *A,
                             Gan_Vector4_f *p, Gan_Vector4_f *q,
                             Gan_Vector4_f *r )
{
   gan_mat34f_get_rows_q ( A, p, q, r );
}

/**
 * \brief Extract columns of 3x4 matrix
 *
 * Extract columns of 3x4 matrix \a A into 3-vectors \a p, \a q, \a r and \a s.
 * The arrangement can be written
 * \f[
 *     A = \left(\begin{array}{cccc} p & q & r & s \end{array}\right)
 * \f]
 *
 * \return No value.
 */
void gan_mat34f_get_cols_s ( const Gan_Matrix34_f *A,
                             Gan_Vector3_f *p, Gan_Vector3_f *q,
                             Gan_Vector3_f *r, Gan_Vector3_f *s )
{
   gan_mat34f_get_cols_q ( A, p, q, r, s );
}

/**
 * \brief Extract left-hand 3x3 part of 3x4 matrix.
 *
 * Extract left-hand 3x3 part of 3x4 matrix \a A into 3x3 matrix \a B.
 *
 * \return Result \a B as a new 3x3 matrix.
 */
Gan_Matrix33_f gan_mat34f_get_m33l_s ( const Gan_Matrix34_f *A )
{
   Gan_Matrix33_f B;

   (void)gan_mat34f_get_m33l_q ( A, &B );
   return B;
}

/**
 * \brief Extract right-hand column of 3x4 matrix.
 *
 * Extract right-hand column of 3x4 matrix \a A into 3-vector \a p.
 *
 * \return Result \a p as a new 3-vector.
 */
Gan_Vector3_f gan_mat34f_get_v3r_s ( const Gan_Matrix34_f *A )
{
   Gan_Vector3_f p;

   (void)gan_mat34f_get_v3r_q ( A, &p );
   return p;
}

/**
 * \}
 */

/**
 * \addtogroup FixedSizeMatrixBuild
 * \{
 */

/**
 * \brief Build 3x4 matrix from 3x3 matrix and column 3-vector.
 *
 * Build 3x4 matrix from 3x3 matrix \a B and column 3-vector \a p,
 * which are respectively inserted in the left-hand and right-hand parts
 * of the 3x4 matrix. The arrangement is thus
 * \f[
 *    \left(\begin{array}{cc} B & p \end{array}\right)
 * \f]
 *
 * \return Result as a new 3x4 matrix.
 */
Gan_Matrix34_f gan_mat34f_set_parts_s ( const Gan_Matrix33_f *B, const Gan_Vector3_f *p )
{
   Gan_Matrix34_f A;

   (void)gan_mat34f_set_parts_q ( &A, B, p );
   return A;
}

/**
 * \brief Build 3x4 matrix from 3-vector columns.
 *
 * Build 3x4 matrix from 3-vector columns \a p, \a q, \a r and \a s.
 * The arrangement can be written
 * \f[
 *     \left(\begin{array}{cccc} p & q & r & s \end{array}\right)
 * \f]
 *
 * \return Filled matrix.
 */
Gan_Matrix34_f
 gan_mat34f_set_cols_s ( const Gan_Vector3_f *p, const Gan_Vector3_f *q,
                         const Gan_Vector3_f *r, const Gan_Vector3_f *s )
{
   Gan_Matrix34_f A;

   (void)gan_mat34f_set_cols_q ( &A, p, q, r, s );
   return A;
}

/**
 * \brief Build 3x4 matrix from 4-vector rows.
 *
 * Build 3x4 matrix from 4-vector rows \a p, \a q and \a r.
 * The arrangement can be written
 * \f[
 *     \left(\begin{array}{c} p^{\top} \\ q^{\top} \\ r^{\top}
 *     \end{array}\right)
 * \f]
 *
 * \return Filled matrix.
 */
Gan_Matrix34_f
 gan_mat34f_set_rows_s ( const Gan_Vector4_f *p, const Gan_Vector4_f *q, const Gan_Vector4_f *r )
{
   Gan_Matrix34_f A;

   (void)gan_mat34f_set_rows_q ( &A, p, q, r );
   return A;
}

/**
 * \}
 */

#include <gandalf/common/misc_error.h>

/**
 * \addtogroup FixedSizeMatrixConvert
 * \{
 */

/**
 * \brief Convert generic rectangular matrix to 3x4 matrix structure.
 *
 * Convert generic rectangular matrix \a A to 3x4 matrix structure \a B.
 *
 * \return Pointer to result matrix \a B.
 */
Gan_Matrix34_f *
 gan_mat34f_from_matf_q ( const Gan_Matrix_f *A, Gan_Matrix34_f *B )
{
   if ( !gan_matf_read_va ( A, 3, 4, &B->xx, &B->xy, &B->xz, &B->xw,
                                     &B->yx, &B->yy, &B->yz, &B->yw,
                                     &B->zx, &B->zy, &B->zz, &B->zw ) )
   {
      gan_err_register ( "gan_mat34f_from_matf_q", GAN_ERROR_FAILURE, "" );
      return NULL;
   }

   return B;
}

/**
 * \}
 */

/* define all the standard small matrix functions for 3x4 matrices */
#include <gandalf/linalg/3x4matf_noc.h>
#include <gandalf/linalg/matrixf_noc.c>

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */
