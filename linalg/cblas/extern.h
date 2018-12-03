/**************************************************************************
*
* File:          $RCSfile: extern.h,v $
* Module:        BLAS function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.6 $
* Last edited:   $Date: 2001/10/04 16:27:00 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:         
* Private func:  
* History:       Modified from original CLAPACK source code 
*
**************************************************************************/

#ifndef _GAN_CBLAS_EXTERN_H
#define _GAN_CBLAS_EXTERN_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_LAPACK

#define integer long
#define real float
#define doublereal double

// function name translations
#if defined(_WIN32)
#define BLAS_DDOT   ddot_
#define BLAS_DAXPY  daxpy_
#define BLAS_DCOPY  dcopy_
#define BLAS_DSCAL  dscal_
#define BLAS_DGEMM  dgemm_
#define BLAS_DGEMV  dgemv_
#define BLAS_DTPSV  dtpsv_
#define BLAS_DPPTRI dpptri_
#define BLAS_DSPR   dspr_
#define BLAS_DGER   dger_
#define BLAS_DSPMV  dspmv_
#define BLAS_DPPTRF dpptrf_
#define BLAS_DPPTRI dpptri_
#define BLAS_DSPEV  dspev_
#define BLAS_SDOT   sdot_
#define BLAS_SAXPY  saxpy_
#define BLAS_SCOPY  scopy_
#define BLAS_SSCAL  sscal_
#define BLAS_SGEMM  sgemm_
#define BLAS_SGEMV  sgemv_
#define BLAS_STPSV  stpsv_
#define BLAS_SPPTRI spptri_
#define BLAS_SSPR   sspr_
#define BLAS_SGER   sger_
#define BLAS_SSPMV  sspmv_
#define BLAS_SPPTRF spptrf_
#define BLAS_SPPTRI spptri_
#define BLAS_SSPEV  sspev_
#else
#define BLAS_DDOT   f2c_ddot
#define BLAS_DAXPY  f2c_daxpy
#define BLAS_DCOPY  f2c_dcopy
#define BLAS_DSCAL  f2c_dscal
#define BLAS_DGEMM  f2c_dgemm
#define BLAS_DGEMV  f2c_dgemv
#define BLAS_DTPSV  f2c_dtpsv
#define BLAS_DPPTRI f2c_dpptri
#define BLAS_DSPR   f2c_dspr
#define BLAS_DGER   f2c_dger
#define BLAS_DSPMV  f2c_dspmv
#define BLAS_DPPTRF f2c_dpptrf
#define BLAS_DPPTRI f2c_dpptri
#define BLAS_DSPEV  f2c_dspev
#define BLAS_SDOT   f2c_sdot
#define BLAS_SAXPY  f2c_saxpy
#define BLAS_SCOPY  f2c_scopy
#define BLAS_SSCAL  f2c_sscal
#define BLAS_SGEMM  f2c_sgemm
#define BLAS_SGEMV  f2c_sgemv
#define BLAS_STPSV  f2c_stpsv
#define BLAS_SPPTRI f2c_spptri
#define BLAS_SSPR   f2c_sspr
#define BLAS_SGER   f2c_sger
#define BLAS_SSPMV  f2c_sspmv
#define BLAS_SPPTRF f2c_spptrf
#define BLAS_SPPTRI f2c_spptri
#define BLAS_SSPEV  f2c_sspev
#endif

/* these are prototypes for all the BLAS functions used in Gandalf */

/* double precision functions */
int BLAS_DSCAL ( integer *n, doublereal *da, doublereal *dx, integer *incx );
int BLAS_DSPR ( char *uplo, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *ap );
int BLAS_DSPR2 ( char *uplo, integer *n, doublereal *alpha,
                 doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *ap );
doublereal BLAS_DDOT ( integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy );
int BLAS_DGEMM ( char *transa, char *transb, integer *m, integer *n, integer *k,
                 doublereal *alpha, doublereal *a, integer *lda, 
                 doublereal *b, integer *ldb, doublereal *beta, doublereal *c,
                 integer *ldc );
int BLAS_DGEMV ( char *trans, integer *m, integer *n, doublereal *alpha,
                 doublereal *a, integer *lda, doublereal *x, integer *incx, 
                 doublereal *beta, doublereal *y, integer *incy);
int BLAS_DTPSV ( char *uplo, char *trans, char *diag, integer *n, doublereal *ap, doublereal *x, integer *incx );
int BLAS_DAXPY ( integer *n, doublereal *da, doublereal *dx, integer *incx, doublereal *dy, integer *incy );
int BLAS_DCOPY ( integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy );
int BLAS_DSPMV ( char *uplo, integer *n, doublereal *alpha, 
                 doublereal *ap, doublereal *x, integer *incx, doublereal *beta, 
                 doublereal *y, integer *incy );
int BLAS_DGER ( integer *m, integer *n, doublereal *alpha, 
                doublereal *x, integer *incx, doublereal *y, integer *incy, 
                doublereal *a, integer *lda );

/* single precision functions */
int BLAS_SSCAL ( integer *n, real *da, real *dx, integer *incx );
int BLAS_SSPR ( char *uplo, integer *n, real *alpha, real *x, integer *incx, real *ap );
int BLAS_SSPR2 ( char *uplo, integer *n, real *alpha, real *x, integer *incx, real *y, integer *incy, real *ap );
doublereal BLAS_SDOT ( integer *n, real *dx, integer *incx, real *dy, integer *incy );
int BLAS_SGEMM ( char *transa, char *transb, integer *m, integer *n, integer *k,
                 real *alpha, real *a, integer *lda, 
                 real *b, integer *ldb, real *beta, real *c,
                 integer *ldc );
int BLAS_SGEMV ( char *trans, integer *m, integer *n, real *alpha,
                 real *a, integer *lda, real *x, integer *incx, 
                 real *beta, real *y, integer *incy);
int BLAS_STPSV ( char *uplo, char *trans, char *diag, integer *n, real *ap, real *x, integer *incx );
int BLAS_SAXPY ( integer *n, real *da, real *dx, integer *incx, real *dy, integer *incy );
int BLAS_SCOPY ( integer *n, real *dx, integer *incx, real *dy, integer *incy );
int BLAS_SSPMV ( char *uplo, integer *n, real *alpha, 
                 real *ap, real *x, integer *incx, real *beta, 
                 real *y, integer *incy );
int BLAS_SGER ( integer *m, integer *n, real *alpha, 
                real *x, integer *incx, real *y, integer *incy, 
                real *a, integer *lda );

#undef real
#undef doublereal
#undef integer

#endif /* #ifdef HAVE_LAPACK */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_CBLAS_EXTERN_H */
