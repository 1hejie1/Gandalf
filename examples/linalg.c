/**************************************************************************
*
* File:          $RCSfile: linalg.c,v $
* Module:        Linear algebra package example program
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.5 $
* Last edited:   $Date: 2001/10/04 17:27:43 $
* Author:        $Author: pm $
* Copyright:     (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       
*
**************************************************************************/

/* error handling */
#include <gandalf/common/misc_error.h>

/* general rectangular matrix functions */
#include <gandalf/linalg/mat_gen.h>

/* symmetric matrix functions */
#include <gandalf/linalg/mat_symmetric.h>
#include <gandalf/linalg/mat_diagonal.h>

/* example code for using the linear algebra package */

int main ( int argc, char *argv[] )
{
   Gan_Vector z, *x, *a, *b;
   Gan_Matrix A;
   Gan_SquMatrix N;

   /* turn on error tracing */
   gan_err_set_trace ( GAN_ERR_TRACE_ON );
   
   /* allocate a vector of size 10 */
   x = gan_vec_alloc(10);
   if ( x == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* this does the same, but avoids a call to malloc() to allocate the
      structure */
   if ( gan_vec_form ( &z, 1 ) == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* allocate a diagonal matrix */
   if ( gan_diagmat_form ( &N, 10 ) == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* allocate a general rectangular matrix */
   if ( gan_mat_form ( &A, 8, 10 ) == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* fill matrices and vectors with zero */
   if ( gan_vec_fill_zero_q ( x, 10 ) == NULL ||
        gan_vec_fill_zero_q ( &z, 1 ) == NULL ||
        gan_diagmat_fill_zero_q ( &N, 10 ) == NULL ||
        gan_mat_fill_zero_q ( &A, 10, 10 ) == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* fill vectors with values, changing their size at the same time. Gandalf
      supports dynamic upsizing/downsizing of any vector/matrix type */
   if ( gan_vec_fill_va ( x, 3, 1.0, 2.0, 3.0 ) == NULL ||
        gan_vec_fill_va ( &z, 3, 4.0, 5.0, 6.0 ) == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* create and fill new vector. Note that we can create it with zero size
      and let the filling routine reallocate the vector to the new size*/
   a = gan_vec_alloc ( 3 );
   if ( a == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   a = gan_vec_fill_va ( a, 3, 7.0, 8.0, 9.0 );
   if ( a == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* add two vectors together, writing the result into a third. Similar
      functions work for matrices: use gan_mat_add_q() or gan_squmat_add_q().
      For subtraction use gan_vec_sub_q() etc. */
   printf ( "adding two vectors:\n" );
   gan_vec_print ( x, "x", 0, "%f" );
   gan_vec_print ( &z, "z", 0, "%f" );
   printf ( "\n" );
   gan_vec_add_q ( x, &z, a );
   gan_vec_print ( a, "result a", 0, "%f" );

   /* add two vectors, returning the result as a new vector */
   b = gan_vec_add_s ( x, &z );
   gan_vec_print ( b, "result b", 0, "%f" );

   /* add two vectors, writing the result into the first */
   gan_vec_increment ( x, &z );
   gan_vec_print ( x, "result x", 0, "%f" );

   /* multiply a matrix and a vector */
   if ( gan_mat_fill_va ( &A, 4, 3,
                          1.0, 2.0, 3.0,
                          4.0, 5.0, 6.0,
                          7.0, 8.0, 9.0,
                          10.0, 11.0, 12.0 ) == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   if ( gan_mat_multv_q ( &A, x, a ) == NULL )
      /* print error(s) and exit */
      gan_err_default_reporter();

   /* increment an element of a vector by a value*/
   gan_vec_inc_el ( &z, 1, 4.0 );
   gan_vec_print ( &z, "incremented z", 0, "%f" );

   /* decrement an element of a vector by a value */
   gan_vec_inc_el ( &z, 0, 2.0 );
   gan_vec_print ( &z, "decremented z", 0, "%f" );

   /* free allocated vectors & matrices */
   gan_vec_free ( b );
   gan_vec_free_va ( a, x, &z, NULL ); /* free freeing more than one vector */
   gan_mat_free ( &A );
   gan_squmat_free ( &N );
   
   gan_heap_report(NULL);
   return 0;
}
