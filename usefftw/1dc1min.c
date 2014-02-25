/* gcc 1dc1min.c -lfftw3 */
#include <stdio.h>
#include <math.h>
#include <fftw3.h>
#define n (128+1) /* notice the "+1" */
int main(void) {
  double in[n], in2[n], out[n];
  fftw_plan p, q;
  int i;
  p = fftw_plan_r2r_1d(n, in, out, FFTW_REDFT00, FFTW_ESTIMATE);
  for (i = 0; i < n; i++) in[i] = cos(2*M_PI*10*i/(n - 1)); /* n - 1 instead of n */
  fftw_execute(p);
  q = fftw_plan_r2r_1d(n, out, in2, FFTW_REDFT00, FFTW_ESTIMATE);
  fftw_execute(q);
  for (i = 0; i < n; i++)
    printf("%3d %9.5f %9.5f\n", i, in[i], in2[i]/(2*(n - 1))); /* n - 1 instead of n */
  fftw_destroy_plan(p); fftw_destroy_plan(q); fftw_cleanup();
  return 0;
}

