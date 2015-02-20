#ifndef math_library_h
#define math_library_h

/* header file for routines using the math library */
/* one letter prefixes in routine names have the following meanings

      --  no prefix indicates single precision real
    c --  complex data being used

*/

#include <math.h>
#include "complex_numbers.h"

/* Create aliases for NSWC FORTRAN routines so C programs can call them */
/* on Alpha/OSF and Sun Sparc hosts */

//--------------------------------------
#ifdef FORTRAN_UNDERBARS

#define MSLV mslv_
#define SGEFA sgefa_
#define SGESL sgesl_

/* And create aliases so C routines in math_library.c can be called from
   FORTRAN on Alpha and Sparc */

#define set_invert_matrix set_invert_matrix_
#define init_invert_matrix init_invert_matrix_
#define invert_matrix invert_matrix_
#define lu_factor lu_factor_
#define lu_solve_linear lu_solve_linear_

//  For Gnu gcc and g77, we need double-underbars, before and after
// the name.
#else
#ifdef __GCC__

#define MSLV _mslv_
#define SGEFA _sgefa_
#define SGESL _sgesl_

// Other hosts (hp7, you need just case conversion to call FORTRAN from C
// Since FORTRAN uppercase is all converted to lowercase.
//--------------------------------------

#else

#define MSLV mslv
#define SGEFA sgefa
#define SGESL sgesl

// end of else for fortran underbars

#endif
#endif

// C function definitions
extern "C" void set_invert_matrix(int *n);

extern "C" void init_invert_matrix(int *status);

extern "C" void invert_matrix(int *n,double *a,double *b,
         int *lda, int *ldb, int *status);

extern "C" void lu_factor(int *n, double *a, double *lu, int *lda,
     int *ipvt, int *status);

extern "C" void lu_solve_linear(int *n, double *a, double *x, double *b, int *lda,
     int *ipvt, int *status);

/* Declarations of NSWC routines */
extern "C"  void MSLV(int *calc_inv,int *n,int *zero_dim1,
        double *b,int *ldb,int *dum,int *zero_dim2,
        double *t1, double *rcond,int *ierr,
        int *invert_matrix_ipvt,double *invert_matrix_wrk);

extern "C" void SGEFA(double *lu, int *lda, int *n, int *ipvt, int *info);

extern "C" void SGESL(double *a, int *lda, int *n, int *ipvt, double *x, int *job);

#endif
