/* real-to-complex fast Fourier tranform using FFTW
 * sudo apt-get install fftw3-dev
 * gcc 1dc1.c -lfftw3 */
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>


/* brute-force calculation */
void cost1(int n, double *in, double *out)
{
  int j, k;
  double *c;

  c = calloc(2*n, sizeof(*c));
  for (j = 0; j < 2*n; j++) c[j] = cos(M_PI*j/n);
  for (k = 0; k <= n; k++)
    /* out[k] = in[0] + (-)^k in[n]
     *        + 2 * sum_{j from 1 to n - 1} in[j] * cos(pi*j*k/n) */
    for (out[k] = in[0] + (k % 2 ? -in[n] : in[n]), j = 1; j < n; j++)
      out[k] += 2 * in[j] * c[j * k % (2*n)];
  free(c);
}


int main(void)
{
  double *in, *in2, *out, *out2;
  fftw_plan p, q;
  int i, n = 12;

  in = (double *) fftw_malloc(sizeof(*in) * (n + 1));
  in2 = (double *) fftw_malloc(sizeof(*in2) * (n + 1));
  out = (double *) fftw_malloc(sizeof(*out2) * (n + 1));
  out2 = (double *) fftw_malloc(sizeof(*out2) * (n + 1));
  p = fftw_plan_r2r_1d(n + 1, in, out, FFTW_REDFT00, FFTW_ESTIMATE);

  // for n = 3: in[0] = 1; in[1] = 2; in[2] = 3; in[3] = 5;
  for (i = 0; i <= n; i++) in[i] = cos(2*M_PI*3*i/n);

  fftw_execute(p);
  cost1(n, in, out2);

  for (i = 0; i <= n; i++)
    printf("%6d %20.10f |  %20.10f\n", i, out[i], out2[i]);

  printf("\nApplying the inverse transform:\n");
  q = fftw_plan_r2r_1d(n + 1, out, in2, FFTW_REDFT00, FFTW_ESTIMATE);
  fftw_execute(q);
  for (i = 0; i <= n; i++)
    printf("%6d %20.10f |  %20.10f\n", i, in[i], in2[i]/(2*n));

  fftw_destroy_plan(p); fftw_destroy_plan(q); fftw_cleanup();
  fftw_free(in); fftw_free(in2); fftw_free(out); fftw_free(out2);
  return 0;
}

