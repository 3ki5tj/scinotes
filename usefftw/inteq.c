/* Numerically solve the 3D PY or HNC equation
 *    gcc -O3 inteq.c -lfftw3 -lm
 * For the PY version
 *    ./a.out > a.dat
 * For the HNC version
 *    ./a.out HNC > b.dat
 * In Gnuplot:
 *    plot "a.dat" u 1:3 w l t "g(r), PY", \
 *         "b.dat" u 1:3 w l t "g(r), HNC"
 * */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>
#define PI 3.14159265358979323846

int n = 512;
double rho = 0.5;
double tol = 1e-3;
double rmax = 5.12;
double beta = 1.0;

fftw_plan plan;
double *arr;



#define newarr(x, n) x = (double *) fftw_malloc(sizeof(double) * n)
#define delarr(x) fftw_free(x)

static double lj(double r) /* Lennard-Jones potential */
{ double ir6 = 1./(r*r*r); ir6 *= ir6; return 4*ir6*(ir6 - 1); }


int main(int argc, char **argv)
{
  int i, iter, hnc = 0;
  double *c, *cp, *t, *f, *arr;
  double dr, dk, dc, dcmax = 1e9;

  if ( argc > 1 ) hnc = (argv[1][0] == 'H');
  if ( argc > 2 ) n = atoi(argv[2]);
  dr = rmax/n; dk = PI/n/dr;
  newarr(c, n); newarr(cp, n); newarr(t, n); newarr(f, n);

  for ( i = 0; i < n; i++ ) /* initialize c as f */
    c[i] = f[i] = exp( -beta*lj((i + .5)*dr) ) - 1;

  newarr(arr, n);
  plan = fftw_plan_r2r_1d(n, arr, arr, FFTW_RODFT00, FFTW_ESTIMATE);

  /* main loop */
  for ( iter = 0; iter < 1000 && dcmax >= tol; iter++ ) {
    for ( i = 0; i < n; i++ ) {
      cp[i] = c[i]; /* make a copy */
      arr[i] = c[i] * (i+.5)*dr; /* c(r) r */
    }
    fftw_execute(plan); /* c(k) = 2 Pi/k Int 2r c(r) sin(kr) dr */
    for ( i = 0; i < n; i++ ) {
      c[i] = arr[i] * 2*PI*dr/((i+.5)*dk); /* c(k) */
      t[i] = rho*c[i]*c[i] / (1 - rho*c[i]);
      arr[i] = t[i] * (i*dk); /* t(k) k */
    }
    fftw_execute(plan); /* t(r) = 1/(4 Pi^2 r) Int 2k t(k) sin(kr) dk */
    for ( dcmax = 0, i = 0; i < n; i++ ) {
      t[i] = arr[i] * dk/(4*PI*PI*(i+.5)*dr); /* t(r) */
      if ( hnc )
        c[i] = (1 + f[i])*exp(t[i]) - (1 + t[i]); /* HNC closure */
      else
        c[i] = f[i] * (1 + t[i]); /* PY closure */
      if ( (dc = fabs(c[i] - cp[i])) > dcmax ) dcmax = dc;
    }
  }
  for ( i = 0; i < n; i++ )
    printf("%.4f %+14.6f %14.6f\n", (i+.5)*dr, c[i], 1 + c[i] + t[i]);
  fprintf(stderr, "%d iteration\n", iter);

  delarr(arr); fftw_destroy_plan(plan); fftw_cleanup();
  delarr(c); delarr(cp); delarr(t); delarr(f);
  return 0;
}
