#ifndef math_library_f_h
#define math_library_f_h

/* one letter prefixes in routine names have the following meanings
   (no prefix indicates single precision real)
     c -- complex data is being used
     d -- doubles are being used
     d_c -- double complex data is to be input
*/
/* this is a set of wrappers for the math library
*  the available routines are
*
*      c_fft
*      c_fft_inv
*          ( internal: c_set_calc_eigenvalues
*          ( internal: c_init_calc_eigenvalues
*      c_calc_eigenvalues
*      c_mult_matricies
*
*          { internal: c_set_invert_matrix
*          { internal: c_init_invert_matrix
*      c_invert_matrix
*          { internal: set_invert_matrix
*          { internal: init_invert_matrix
*      invert_matrix
*      invert_matrix_cond
*          { internal: d_set_invert_matrix
*          { internal: d_init_invert_matrix
*      d_invert_matrix
*
*          { internal: c_set_solve_linear
*          { internal: c_init_solve_linear
*      c_solve_linear
*          { internal: d_c_set_solve_linear
*          { internal: d_c_init_solve_linear
*      d_c_solve_linear
*
*      lu_factor
*      lu_factor_cond
*      dlu_factor
*
*      lu_solve_linear
*      dlu_solve_linear
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "magicad.h"
#include "math_library.h"

int n_invert_matrix = 0;
int n_init_invert_matrix = 0;
int *invert_matrix_ipvt = NULL;
double *invert_matrix_wrk = NULL;

/* ***********************************************************************
 * ROUTINE NAME set_invert_matrix
 *
 *
 * ABSTRACT  Will set the size of the workspace created for
 *           the routine invert_matrix. This is
 *           designed to allow multiple calls with the
 *           largest size being retained.
 *
 *
 *
 * ENVIRONMENT  set_invert_matrix
 *
 *
 *
 *
 * INPUTS
 *    n                    the size of the square matrix
 *                           that will be input into
 *                           c_invert_matrix
 *
 * OUTPUTS
 *
 * FUNCTIONS CALLED
 *
 *
 *
 *
 * AUTHOR          Andrew Staniszewski
 *
 * MODIFICATION HISTORY
 * 1.00     Original                          AJS       3-15-91
 *
 * ***********************************************************************
 */
void set_invert_matrix(int *n)

{
  extern int n_invert_matrix;

  if (n_invert_matrix < (*n))
    n_invert_matrix = (*n);

  return;
}

/* ***********************************************************************
 * ROUTINE NAME  init_invert_matrix
 *
 *
 * ABSTRACT  this routine sets up the workspace for the routine
 *             invert_matrix. It should only be called
 *             from within invert_matrix
 *
 *
 *
 * ENVIRONMENT  init_invert_matrix
 *
 *
 *
 *
 * INPUTS
 *
 * OUTPUTS
 *    status                       will be either SUCCESS or FAIL
 *
 * FUNCTIONS CALLED
 *
 *
 *
 *
 * AUTHOR          Andrew Staniszewski
 *
 * MODIFICATION HISTORY
 * 1.00     Original                          AJS       3-8-91
 *
 * ***********************************************************************
 */
void init_invert_matrix(int *status)
{

  extern int *invert_matrix_ipvt;
  extern double *invert_matrix_wrk;

  extern int n_invert_matrix;
  extern int n_init_invert_matrix;

  int n;
  n = n_init_invert_matrix = n_invert_matrix;
  /* malloc the workspace */
  if (invert_matrix_ipvt != NULL)
    {
      free(invert_matrix_ipvt);
      free(invert_matrix_wrk);
    }


/* malloc some workspace */
  invert_matrix_ipvt = (int *)calloc(n,sizeof(int));
  invert_matrix_wrk = (double *)calloc(n*n,sizeof(double));

  (*status) = SUCCESS;
  return;
}

/* ***********************************************************************
 * ROUTINE NAME invert_matrix
 *
 *
 * ABSTRACT  will supply the inverse of a matrix
 *
 *
 *
 * ENVIRONMENT  invert_matrix
 *
 *
 *
 * INPUTS
 *     n                   the size of the a and b is n*n
 *     a                   the input matrix
 *     lda                 leading dimension of a
 *     ldb                 leading dimension of b
 *
 * OUTPUTS
 *     b              the inverted matrix
 *     status         SUCCESS or FAIL
 *
 *
 * FUNCTIONS CALLED
 *
 *
 *
 *
 * AUTHOR          Andrew Staniszewski
 *
 * MODIFICATION HISTORY
 * 1.00     Original                          AJS       12-15-90
 * 2.00     Update for use from fortran       AJS        3-18-91
 *
 * ***********************************************************************
 */

/* this routine will invert a single precision real matrix */

void invert_matrix(int *n,double *a,double *b,
       int *lda, int *ldb, int *status)

{
  extern int *invert_matrix_ipvt;
  extern double *invert_matrix_wrk;

  extern int n_init_invert_matrix;

  double t1[2];           /* workspace matricies */
  double rcond;            /* value indicating condition of input matrix */
  int ierr;             /*status flag for call */
  int i,j;                 /*loop variable */
  int calc_inv = 0;       /* indicates inverse of is to be calculated */
  int zero_dim = 0; /* indicates that no solutions is needed see
         NSWC page 211
      */

  if ((*n) > n_init_invert_matrix)
    {
      set_invert_matrix(n);
      init_invert_matrix(status);
    }



/* first copy a to b */

  for (i = 0; i < (*n); i++)
    {
      for (j = 0; j < (*n); j++)
  {
    b[i*(*ldb)+j] = a[i*(*lda)+j];
  }
    }

  MSLV(&calc_inv,n,&zero_dim,b,ldb,NULL,&zero_dim,&t1[0],
       &rcond,&ierr,invert_matrix_ipvt,invert_matrix_wrk);

  if (ierr != 0)
    {
      (*status) = FAIL;
      fprintf(stderr,"ELECTRO-F-INVRSINT #2 Error in matrix inversion, NSWC code %d\n", ierr);
      return;
    }

  (*status) = SUCCESS;
  return;
}

/* ***********************************************************************
 * ROUTINE NAME set_solve_nonlinear
 *
 *
 * ABSTRACT  Will set the size of the workspace created for
 *           the routine solve_nonlinear. This is
 *           designed to allow multiple calls with the
 *           largest size being retained.
 *
 *
 *
 * ENVIRONMENT  set_solve_nonlinear
 *
 *
 *
 *
 * INPUTS
 *    n                   the number of varibles in the nonlinear equation
 *
 * OUTPUTS
 *    status               will be SUCCESS or FAIL
 *
 * FUNCTIONS CALLED
 *
 *
 *
 *
 * AUTHOR          Andrew Staniszewski
 *
 * MODIFICATION HISTORY
 * 1.00     Original                          AJS       3-15-91
 *
 * ***********************************************************************
 */
// void set_solve_nonlinear(int *n)
//
// {
//   extern int n_solve_nonlinear;
//
//   if (n_solve_nonlinear < (*n))
//     n_solve_nonlinear = (*n);
//
//   return;
// }
// 
/* ***********************************************************************
 * ROUTINE NAME  init_solve_nonlinear
 *
 *
 * ABSTRACT  this routine sets up the workspace for the routine
 *             solve_nonlinear. It should only be called
 *             from within solve_nonlinear
 *
 *
 *
 * ENVIRONMENT  init_solve_nonlinear
 *
 *
 *
 *
 * INPUTS
 *
 * OUTPUTS
 *    status                       will be either SUCCESS or FAIL
 *
 * FUNCTIONS CALLED
 *
 *
 *
 *
 * AUTHOR          Andrew Staniszewski
 *
 * MODIFICATION HISTORY
 * 1.00     Original                          AJS       3-8-91
 *
 * ***********************************************************************
 */
// void init_solve_nonlinear(int *status)
// {
//   extern int *solve_nonlinear_iwk;
//   extern double *solve_nonlinear_wrk;
//   extern double *solve_nonlinear_x;
//
//
//   extern int n_init_solve_nonlinear;
//   extern int n_solve_nonlinear;
//   extern int m_solve_nonlinear;
//
//   int n;
//   int m;
//
//   n = n_init_solve_nonlinear = n_solve_nonlinear;
//
//   /* malloc the workspace */
//
//   if (solve_nonlinear_wrk != NULL)
//     {
//       free(solve_nonlinear_wrk);
//     }
//
//   /* malloc some workspace */
//
//   m_solve_nonlinear = m = (int ) (ceil(n*(n+1)/2.0) + n*n +7*n) ;
//
//   solve_nonlinear_wrk = (double *)calloc(m,sizeof(double));
//   solve_nonlinear_iwk = (int *)calloc(n,sizeof(int));
//   solve_nonlinear_x = (double *)calloc(n,sizeof(double));
//
//   (*status) = SUCCESS;
//   return;
// }
//
//
/* ***********************************************************************
 * ROUTINE NAME solve_nonlinear
 *
 *
 * ABSTRACT  will solve a non-linear system of equations
 *
 *
 *
 * ENVIRONMENT  sovle_nonlinear
 *
 *
 *
 * INPUTS
 *     void (*f)()              a pointer to a function that
 *                                will evaluate the system of equations
 *                                see page 137 of NSWC
 *     int n;                   the size of the system of equation
 *     double *x                 the initial guess for the solution
 *     double EPS                a statement of the relitive accuracy of (*f)()
 *     double TOL                the desired accuracy of the soln
 *                                s/b less than 1.0e-5
 * OUTPUTS
 *    double *x                 the final solution
 *    double *fvec              a pointer to a vector that represents
 *                                what (*f)() evaluates to at the final
 *                                solution
 *
 * FUNCTIONS CALLED
 *
 *
 *
 *
 * AUTHOR          Andrew Staniszewski
 *
 * MODIFICATION HISTORY
 * 1.00     Original                          AJS       12-15-90
 *
 * ***********************************************************************
 */
//
// void solve_nonlinear(void (*f)(),void (*f2)(), int *n,double *eps,double *tol,
//         double *x, double *fvec, int *status)
//
// {
//   extern double *solve_nonlinear_wrk;
//   extern int *solve_nonlinear_iwk;
//   extern double *solve_nonlinear_x;
//   extern int n_init_solve_nonlinear;
//   int info = 0;
//   int i;
//   int m;
//   int mode = 1;
//   int maxfev = 200;
//   int ml_mu;
//   double factor = 100.0;
//   double gtol = 0.0;
//   int nprint = 0;
//   int nfev = 0;
//   int lr;
//   double sum;
//   double *m1,*m2,*m3,*m4,*m5,*m6,*m7,*mm;
//
//   ml_mu = (*n) -1;
//
//   if ((*n) > n_init_solve_nonlinear)
//     {
//       set_solve_nonlinear(n);
//       init_solve_nonlinear(status);
//     }
//
//   m = n_init_solve_nonlinear;
//   lr = (int )ceil((m*(m+1))/2.0);
//   m1 = solve_nonlinear_wrk + lr;
//   m2 = m1 + m;
//   m3 = m2 + m;
//   m4 = m3 + m;
//   m5 = m4 + m;
//   m6 = m5 + m;
//   m7 = m6 + m;
//   mm = m7 + m;
//
//   for (i = 0; i < (*n); i++)
//     {
//       solve_nonlinear_x[i] = x[i];
//     }
// /*
//   HYBRD(f,n,solve_nonlinear_x,fvec,tol,&maxfev,&ml_mu,&ml_mu,eps,
//  m1,&mode,&factor,&nprint,&info,&nfev,mm,&m,solve_nonlinear_wrk,
//  &lr,m2,m3,m4,m5,m6);
// */
//   if (info != 1)
//     {
//       for (i = 0; i < (*n); i++)
//  {
//    solve_nonlinear_x[i] = x[i];
//  }
// /*
//       LMDIF(f2,n,n,solve_nonlinear_x,fvec,tol,tol,&gtol,&maxfev,eps,
//      m1,&mode,&factor,&nprint,&info,&nfev,mm,&m,m2,m3,m4,m5,
//      m6,m7);
// */
//       printf("dummy, you didn't reactivate the non linear problem solver\n");
//       if (info == 4)
//  {
//    for (i = 0,sum=0; i < (*n); i++)
//      {
//        sum += fvec[i] * fvec[i];
//      }
//    if (sum == 0)
//      info = 3;
//  }
//
//      if (info != 1 && info != 2 && info != 3)
//
//  {
//    (*status) = FAIL;
//    fprintf(stderr,"ELECTRO-F-NONLININT Error in solution of nonlinear system, NSWC code %ld\n",info);
//    return;
//  }
//     }
//   for (i = 0; i < (*n); i++)
//     {
//       x[i] = solve_nonlinear_x[i];
//     }
//   (*status) = SUCCESS;
//   return;
// }
// 
/* ***********************************************************************
 * ROUTINE NAME lu_factor
 *
 *
 * ABSTRACT  Factors a real matrix A by gaussian elimination (A = L*U).
 *
 * ENVIRONMENT  lu_factor(n, a, lu, lda, ipvt, status)
 *
 * INPUTS
 *    int *n;               the order of matrix a
 *    double *a;             the matrix to be factored
 *    int *lda;             leading dimension of a
 *
 * OUTPUTS
 *    int *ipvt;      integer vector of pivot indices
 *    double *lu;      factorization of A (= L*U)
 *                          if a is not needed, pass a or NULL for lu
 *    int     *status;      SUCCESS or FAIL
 *
 * FUNCTIONS CALLED
 *    sgefa (NSWC originally from LINPACK)
 *
 * AUTHOR          Jeff Prentice
 *
 * ***********************************************************************
 */

void lu_factor(int *n, double *a, double *lu, int *lda,
     int *ipvt, int *status) {
  int i,j;  /* loop indices */
  int info;   /* status flag for call */

  /********************************************************************
  *                 *
  * If the matrix lu is passed (not NULL and different than a), the *
  * matrix a is copied to lu which is used in the factorization and *
  * will contain the results, preserving the contents of a.   *
  * Otherwise a will contain the results destroying its original  *
  * contents.               *
  *                 *
  ********************************************************************/
  if ((lu != NULL) && (lu != a)) {
    for (i = 0; i < (*n); i++)
      for (j = 0; j < (*n); j++)
        lu[i*(*n)+j] = a[i*(*lda)+j];
    SGEFA(lu, lda, n, ipvt, &info);
  } else {
    SGEFA(a, lda, n, ipvt, &info);
  }

  /********************************************************************
  *                 *
  * A nonzero value for info indicates that u(info,info) = 0.0.  This *
  * is not necessarily an error condition, however it does indicate *
  * that using the l*u factorization to solve (sgesl) or to invert  *
  * (sgedi) will divide by zero.          *
  *                 *
  ********************************************************************/
  if (info != 0) {
    (*status) = FAIL;
    fprintf(stderr, "ELECTRO-F-LUFACT Error in LU factorization of matrix, NSWC code %d\n", info);
    return;
  }

  (*status) = SUCCESS;
  return;
}

/* ***********************************************************************
 * ROUTINE NAME lu_solve_linear
 *
 *
 * ABSTRACT  Solves the real system A*X=B using the factors computed
 *       from lu_factor.
 *
 * ENVIRONMENT  lu_solve_linear(n, a, x, b, lda, ipvt, status)
 *
 * INPUTS
 *    int *n;               the order of matrix a
 *    double *a;             lu factored matrix output from lu_factor
 *    double *b;             right hand side vector (a*x=b)
 *    int *lda;             leading dimension of matrix
 *    int *ipvt;      integer vector of pivot indices from lu_factor
 *
 * OUTPUTS
 *    double *x;       the solution vector
 *                          if b is not needed, pass b or NULL in for x
 *    int     *status;      SUCCESS
 *
 * FUNCTIONS CALLED
 *    sgesl (NSWC originally from LINPACK)
 *
 * AUTHOR          Jeff Prentice
 *
 * ***********************************************************************
 */

void lu_solve_linear(int *n, double *a, double *x, double *b, int *lda,
         int *ipvt, int *status) {
  int i;  /* loop indices */
  int job=0;  /* indicates to solve a*x=b */

  /********************************************************************
  *                 *
  * If the matrix x is passed (not NULL and different than b), the  *
  * matrix b is copied to x which will contain the results,   *
  * preserving the contents of b.  Otherwise b will contain the *
  * results destroying its original contents.       *
  *                 *
  ********************************************************************/
  if ((x != NULL) && (x != b)) {
    for (i = 0; i < (*n); i++)
      x[i] = b[i];
    SGESL(a, lda, n, ipvt, x, &job);
  } else {
    SGESL(a, lda, n, ipvt, b, &job);
  }

  (*status) = SUCCESS;
  return;
}

#endif
