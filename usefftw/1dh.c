/* real-to-complex fast Fourier tranform using FFTW
 * sudo apt-get install fftw3-dev
 * gcc 1dh.c -lfftw3 */
#include <stdlib.h>
#include <math.h>
#include <fftw3.h>


/* brute-force calculation */
void ht(int n, double *in, double *out)
{
  int j, k;
  double *c, *s;

  c = calloc(n, sizeof(*c));
  s = calloc(n, sizeof(*s));
  for (j = 0; j < n; j++) {
    c[j] = cos(2*M_PI*j/n);
    s[j] = sin(2*M_PI*j/n);
  }
  for (k = 0; k < n; k++)
    /* out[k] = sum_{j from 0 to n - 1} in[j] * [sin(2*pi*j*k/n) + cos(2*pi*j*k/n)] */
    for (out[k] = 0, j = 0; j < n; j++)
      out[k] += in[j] * (c[j * k % n] + s[j * k % n]);
  free(c); free(s);
}


int main(void)
{
  double *in, *in2, *out, *out2;
  fftw_plan p, q;
  int i, n = 12;

  in = (double *) fftw_malloc(sizeof(*in) * n);
  in2 = (double *) fftw_malloc(sizeof(*in2) * n);
  out = (double *) fftw_malloc(sizeof(*out) * n);
  out2 = (double *) fftw_malloc(sizeof(*out2) * n);
  p = fftw_plan_r2r_1d(n, in, out, FFTW_DHT, FFTW_ESTIMATE);

  // for n = 3: in[0] = 0; in[1] = 1; in[2] = 2;
  for (i = 0; i < n; i++) in[i] = sin(2*M_PI*3*(i + 0.3)/n);

  fftw_execute(p);
  ht(n, in, out2);

  for (i = 0; i < n; i++)
    printf("%6d %20.10f |  %20.10f\n", i, out[i], out2[i]);

  printf("\nApplying the inverse transform:\n");
  q = fftw_plan_r2r_1d(n, out, in2, FFTW_DHT, FFTW_ESTIMATE);
  fftw_execute(q);
  for (i = 0; i < n; i++)
    printf("%6d %20.10f |  %20.10f\n", i, in[i], in2[i]/n);

  fftw_destroy_plan(p); fftw_destroy_plan(q); fftw_cleanup();
  fftw_free(in); fftw_free(in2); fftw_free(out); fftw_free(out2);
  return 0;
}

